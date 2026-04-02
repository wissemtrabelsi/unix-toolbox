# unix-toolbox

A collection of Unix system programming tools written in C and Bash.
Covers the two fundamental pillars of Unix systems: **file I/O** and **process management**.

## Structure

| Folder | Description | Language |
|--------|-------------|----------|
| [`file-io/`](file-io/) | Low-level file I/O tools using raw POSIX syscalls | C |
| [`file-attrs/`](file-attrs/) | File attribute utilities and link management | C |
| [`bash-scripts/`](bash-scripts/) | System monitoring daemon and shell utilities | Bash |
| [`process-utils/`](process-utils/) | Process management tools using fork/exec/signals | C |

## Tools Overview

### file-io — `filetool`
```bash
./filetool copy src.txt dst.txt       # copy a file using raw syscalls
./filetool append src.txt dst.txt     # append file contents
./filetool reverse input.txt          # reverse lines of a file
```

### file-attrs — `lx`
```bash
./lx attrib filename                  # show file attributes via stat()
./lx ln -sv target link_name         # create symbolic link with verbose output
```

### bash-scripts — `syswatch`
```bash
./syswatch.sh --interval 30           # monitor CPU, RAM, disk every 30s
./syswatch.sh --log /var/log/sys.log  # custom log file
```

### process-utils — `putil`
```bash
./putil pwatch 2 ls -l               # run ls -l every 2 seconds
./putil ptree 1234                    # show process info (Linux only)
./putil sig SIGTERM firefox           # send signal by process name (Linux only)
```

## Build & Test

Each folder has its own `Makefile`:
```bash
cd file-io && make test        # 6 tests
cd file-attrs && make test     # 8 tests
cd bash-scripts && make test   # 6 tests
cd process-utils && make test  # 8 tests
```

## Key Concepts Demonstrated

| Concept | Where |
|---------|-------|
| Raw POSIX file I/O (`open`, `read`, `write`) | `file-io/` |
| No `stdio.h` — pure syscalls | `file-io/` |
| Partial write handling | `file-io/append.c` |
| Same-file detection via `fstat` + inodes | `file-io/copy.c` |
| File attributes via `stat()` | `file-attrs/` |
| Hard links and symbolic links | `file-attrs/ln.c` |
| Human readable file sizes (B/KiB/MiB/GiB/TiB) | `file-attrs/utils.c` |
| Flag parsing with `getopt` | `file-attrs/ln.c` |
| System monitoring daemon | `bash-scripts/syswatch.sh` |
| Signal handling (`trap`, `SIGINT`, `SIGTERM`) | `bash-scripts/`, `process-utils/` |
| Cross-platform (Linux + macOS) | all folders |
| Fork-exec pattern | `process-utils/pwatch.c` |
| `/proc` filesystem | `process-utils/ptree.c`, `sig.c` |
| Automated test suites | all folders |

## Author

Wissem Trabelsi 