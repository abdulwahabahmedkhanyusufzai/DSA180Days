"""
Nexus C++ Bridge — Compile & Execute Real C++ Algorithms via subprocess
========================================================================
STRATEGY:
  Every folder's existing .cpp file is a LeetCode-style `class Solution{}`.
  We:
    1. Write a thin _runner.cpp that #includes the original + adds main()
    2. Compile it once with g++ (cached per file)
    3. Call the binary via subprocess with JSON stdin → get JSON stdout

This module is the glue between FastAPI (Python) and the 18 C++ modules.
"""

from __future__ import annotations

import json
import logging
import os
import subprocess
import tempfile
import time
from pathlib import Path
from typing import Any, Dict, Optional

logger = logging.getLogger("nexus.cpp_bridge")

# Root of the repo — all paths are relative to this
REPO_ROOT = Path(__file__).resolve().parents[2]   # DSA180Days/
CACHE_DIR  = REPO_ROOT / "nexus" / "_compiled_cache"
CACHE_DIR.mkdir(parents=True, exist_ok=True)

# g++ flags
GPP_FLAGS = ["-O2", "-std=c++17", "-o"]


def _compile(runner_src: Path, output_bin: Path) -> bool:
    """Compile a runner .cpp into a binary. Returns True on success."""
    try:
        result = subprocess.run(
            ["g++", *GPP_FLAGS, str(output_bin), str(runner_src)],
            capture_output=True, text=True, timeout=30
        )
        if result.returncode != 0:
            logger.error(f"[CppBridge] Compile error:\n{result.stderr}")
            return False
        logger.info(f"[CppBridge] Compiled: {runner_src.name} → {output_bin.name}")
        return True
    except FileNotFoundError:
        logger.error("[CppBridge] g++ not found. Install MinGW or GCC.")
        return False
    except subprocess.TimeoutExpired:
        logger.error("[CppBridge] Compilation timed out.")
        return False


def call_cpp(
    binary_path: Path,
    stdin_data: str,
    timeout: float = 5.0,
) -> Dict[str, Any]:
    """
    Run a compiled C++ binary, pass stdin_data, return parsed stdout as dict.
    Binary must output a single JSON line to stdout.
    """
    try:
        result = subprocess.run(
            [str(binary_path)],
            input=stdin_data,
            capture_output=True,
            text=True,
            timeout=timeout,
        )
        if result.returncode != 0:
            return {"ok": False, "error": result.stderr.strip(), "output": None}
        raw = result.stdout.strip()
        try:
            return {"ok": True, "output": json.loads(raw), "raw": raw}
        except json.JSONDecodeError:
            return {"ok": True, "output": raw, "raw": raw}   # plain text output
    except subprocess.TimeoutExpired:
        return {"ok": False, "error": f"Timeout after {timeout}s", "output": None}
    except Exception as e:
        return {"ok": False, "error": str(e), "output": None}


# ---------------------------------------------------------------------------
# Module registry: maps logical name → (runner_src, bin_name)
# Each runner_src is written by us (see nexus/cpp_runners/*.cpp)
# ---------------------------------------------------------------------------
RUNNERS_DIR = REPO_ROOT / "nexus" / "cpp_runners"
RUNNERS_DIR.mkdir(parents=True, exist_ok=True)

_COMPILED: Dict[str, Path] = {}   # cache: name → compiled binary path


def get_binary(name: str) -> Optional[Path]:
    """Return path to compiled binary for `name`, compiling if needed."""
    if name in _COMPILED:
        return _COMPILED[name]

    runner_src = RUNNERS_DIR / f"{name}.cpp"
    if not runner_src.exists():
        logger.error(f"[CppBridge] Runner source not found: {runner_src}")
        return None

    bin_path = CACHE_DIR / (name + (".exe" if os.name == "nt" else ""))
    # Recompile if binary missing or source newer
    if not bin_path.exists() or runner_src.stat().st_mtime > bin_path.stat().st_mtime:
        if not _compile(runner_src, bin_path):
            return None

    _COMPILED[name] = bin_path
    return bin_path


def compile_all() -> Dict[str, bool]:
    """Pre-compile every runner in the runners directory."""
    results = {}
    for src in sorted(RUNNERS_DIR.glob("*.cpp")):
        name = src.stem
        ok = get_binary(name) is not None
        results[name] = ok
    return results
