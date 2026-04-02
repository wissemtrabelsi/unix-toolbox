# process-utils

A collection of Unix process management tools written in C using POSIX syscalls.
All tools are bundled into a single CLI called `putil`.

## Tools

| Tool | Description | Key Syscalls |
|------|-------------|--------------|
| `pwatch` | Run a command repeatedly every N seconds | `fork`, `execvp`, `wait` |
| `ptree` | Show process info from /proc filesystem | `/proc/PID/status` |
| `sig` | Send signals to processes by name | `kill`, `opendir`, `readdir` |

## Build & Test (Automated)
```bash
make          # build putil
make test     # build and run all 8 tests
make clean    # remove binary
```

## Manual Usage
```bash
# run ls -l every 2 seconds
./putil pwatch 2 ls -l

# show process info for PID 1234 (Linux only)
./putil ptree 1234

# send SIGTERM to process named firefox (Linux only)
./putil sig SIGTERM firefox

# show help
./putil --help
```

## Platform Support

| Tool | Linux | macOS |
|------|-------|-------|
| `pwatch` | ✅ | ✅ |
| `ptree` | ✅ | ❌ requires /proc |
| `sig` | ✅ | ❌ requires /proc |

## Implementation Notes

- Automated test suite written in Bash (`tests/test.sh`) validates all tools and edge cases
- `pwatch` uses the Unix fork-exec pattern — parent forks child, child exec's the command, parent wait()'s then sleeps
- Signal handling in `pwatch` uses `sigaction()` for clean shutdown on `SIGINT`/`SIGTERM`
- `ptree` and `sig` use `#ifdef __linux__` for platform detection at compile time
- `sig` scans `/proc/*/status` using `opendir/readdir` to find processes by name
- `get_signal()` maps signal name strings to integer values using `strcmp`