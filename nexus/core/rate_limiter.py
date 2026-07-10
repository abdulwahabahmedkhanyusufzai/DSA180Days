"""
Nexus Rate Limiter — Sliding Window Token Tracker
==================================================
SOURCE MODULE: 05_Two_Pointers (sliding window pattern)

LLM providers (OpenAI, Gemini) enforce token-per-minute (TPM) limits.
If you exceed them, every agent in the system gets throttled.

Algorithm: Sliding Window (05_Two_Pointers / SubarraySomeEqualtoK pattern)
  - Maintain a deque of (timestamp, tokens_used) events.
  - Left pointer advances to drop events older than the window (60s).
  - Right pointer is always the current event.
  - Sum between left and right is O(1) with a running counter.

This prevents 429-rate-limit errors before they happen.
"""

from __future__ import annotations

import asyncio
import logging
import time
from collections import deque
from typing import Dict, Optional, Tuple

logger = logging.getLogger("nexus.ratelimiter")


# ---------------------------------------------------------------------------
# TokenBucket per provider / model
# ---------------------------------------------------------------------------
class SlidingWindowRateLimiter:
    """
    05_Two_Pointers / sliding-window rate limiter.

    Window = window_seconds (default 60).
    If adding `tokens` would exceed `max_tokens`, the call blocks
    (or returns False in non-blocking mode) until the window slides enough.
    """

    def __init__(
        self,
        max_tokens:     int   = 90_000,   # e.g. GPT-4 tier-1 TPM
        window_seconds: float = 60.0,
        provider:       str   = "openai",
    ):
        self._max_tokens     = max_tokens
        self._window         = window_seconds
        self._provider       = provider
        self._events: deque  = deque()     # (timestamp, tokens)
        self._running_total: int = 0
        self._lock           = asyncio.Lock()

    # -----------------------------------------------------------------------
    # Sliding Window core  (05_Two_Pointers)
    # -----------------------------------------------------------------------
    def _slide(self) -> None:
        """Drop events outside the left boundary of the window."""
        cutoff = time.time() - self._window
        while self._events and self._events[0][0] < cutoff:
            _, evicted_tokens = self._events.popleft()
            self._running_total -= evicted_tokens

    async def acquire(self, tokens: int, block: bool = True) -> bool:
        """
        Attempt to consume `tokens`.
        If block=True, sleep until the window slides enough.
        Returns True on success, False if non-blocking and over limit.
        """
        async with self._lock:
            self._slide()

            if self._running_total + tokens <= self._max_tokens:
                self._events.append((time.time(), tokens))
                self._running_total += tokens
                logger.debug(
                    f"[RateLimit:{self._provider}] Acquired {tokens} tokens "
                    f"(total={self._running_total}/{self._max_tokens})"
                )
                return True

            if not block:
                logger.warning(
                    f"[RateLimit:{self._provider}] BLOCKED {tokens} tokens "
                    f"(would exceed {self._max_tokens})"
                )
                return False

        # Release lock while waiting so other coroutines can proceed
        wait_time = self._estimate_wait(tokens)
        logger.warning(
            f"[RateLimit:{self._provider}] Over limit. Waiting {wait_time:.1f}s..."
        )
        await asyncio.sleep(wait_time)
        return await self.acquire(tokens, block)   # retry

    def _estimate_wait(self, tokens_needed: int) -> float:
        """Estimate how long until enough tokens free up."""
        now = time.time()
        freed = 0
        for ts, tok in self._events:
            freed += tok
            if self._running_total - freed + tokens_needed <= self._max_tokens:
                return max(0.1, (ts + self._window) - now)
        return self._window

    def current_usage(self) -> Tuple[int, int]:
        """Returns (tokens_used, tokens_available)."""
        self._slide()
        return self._running_total, self._max_tokens - self._running_total

    def stats(self) -> Dict:
        used, avail = self.current_usage()
        return {
            "provider":        self._provider,
            "tokens_used":     used,
            "tokens_available": avail,
            "max_tokens":      self._max_tokens,
            "window_seconds":  self._window,
            "utilisation_pct": round(used / self._max_tokens * 100, 2),
        }


# ---------------------------------------------------------------------------
# Multi-provider rate limiter registry
# ---------------------------------------------------------------------------
class RateLimiterRegistry:
    """Holds one SlidingWindowRateLimiter per LLM provider."""

    _DEFAULT_LIMITS: Dict[str, int] = {
        "openai":     90_000,
        "gemini":     60_000,
        "anthropic":  100_000,
        "local":      999_999_999,
    }

    def __init__(self):
        self._limiters: Dict[str, SlidingWindowRateLimiter] = {}

    def get(self, provider: str) -> SlidingWindowRateLimiter:
        if provider not in self._limiters:
            max_tpm = self._DEFAULT_LIMITS.get(provider, 60_000)
            self._limiters[provider] = SlidingWindowRateLimiter(
                max_tokens=max_tpm, provider=provider
            )
        return self._limiters[provider]

    def all_stats(self) -> Dict:
        return {p: l.stats() for p, l in self._limiters.items()}
