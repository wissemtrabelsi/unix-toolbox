# bash-scripts

A lightweight system monitoring daemon written in Bash, with cross-platform support for Linux and macOS.

## Main Tool: syswatch

A continuous monitoring daemon that tracks CPU, RAM, and disk usage, logs structured output with timestamps, and automatically backs up logs when disk usage exceeds a configurable threshold.
```bash
./syswatch.sh                         # start with defaults
./syswatch.sh --interval 30           # check every 30 seconds
./syswatch.sh --log /var/log/sys.log  # custom log file
./syswatch.sh --help                  # show help
```

### Example Output
```
[2026-03-29 23:39:06] INFO  syswatch started | interval: 60s | log: logs/syswatch.log
[2026-03-29 23:39:07] INFO  CPU 11% | RAM: 1.2 GiB/16.0 GiB | Disk: 14%
[2026-03-29 23:39:08] WARN  CPU spike detected: 87%
[2026-03-29 23:40:07] WARN  Disk usage critical: 82% — triggering auto backup
[2026-03-29 23:40:07] INFO  Logs backed up to backup/
[2026-03-29 23:40:08] INFO  syswatch stopped
```

### Features

| Feature | Description |
|---------|-------------|
| CPU monitoring | Detects spikes above threshold (default: 80%) |
| RAM monitoring | Shows used/total memory in GiB |
| Disk monitoring | Alerts and auto-backup when above threshold (default: 80%) |
| Structured logging | Timestamps + INFO/WARN levels saved to log file |
| Signal handling | Graceful shutdown on `Ctrl+C` or `kill` via `trap` |
| Cross-platform | Works on Linux and macOS |
| Input validation | `--interval` validated with regex, `--log` checked for empty value |

## Test
```bash
make test   # run automated test suite
```

## Implementation Notes

- Argument parsing uses `while/case` loop with `shift` — same pattern as `getopt` in C
- Signal handling with `trap` catches `SIGINT` and `SIGTERM` for graceful shutdown
- Cross-platform CPU/RAM detection using `$OSTYPE` — supports macOS and Linux
- RAM on macOS reported in pages (`vm_stat`) — converted to GiB (1 page = 4096 bytes)
- `=~` regex operator validates `--interval` is a positive integer before assignment
- `command -v` used in tests to detect `timeout` availability across platforms
- Auto-backup triggered automatically when disk threshold exceeded — daemon reacts to system state