"""
Nexus DAG Engine — Entry Point
Usage:
    python main.py           (starts on http://localhost:8000)
    python main.py --port 9000
"""
import sys
import uvicorn

def main():
    port = 8000
    if "--port" in sys.argv:
        idx = sys.argv.index("--port")
        port = int(sys.argv[idx + 1])

    print(f"""
╔══════════════════════════════════════════════════════╗
║         NEXUS DAG ENGINE  v1.0.0                    ║
║   Autonomous AI-Agent Orchestration Platform         ║
║                                                      ║
║   Built from 18 DSA folders of REAL C++ algorithms  ║
║                                                      ║
║   API Docs   → http://localhost:{port}/docs           ║
║   Health     → http://localhost:{port}/health         ║
║   Compile    → http://localhost:{port}/compile        ║
╚══════════════════════════════════════════════════════╝
    """)

    uvicorn.run(
        "nexus.server:app",
        host="0.0.0.0",
        port=port,
        reload=False,
        log_level="info",
    )

if __name__ == "__main__":
    main()
