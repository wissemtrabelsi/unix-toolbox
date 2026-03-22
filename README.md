# unix-toolbox

A collection of Unix system programming tools written in C and Bash,
focused on low-level file I/O, process management, and system utilities.

## Tools

| Folder           | Description                       | Key Concepts                      |
|------------------|-----------------------------------|-----------------------------------|
| `file-io/`       | File I/O tools using raw syscalls | `open`, `read`, `write`, `close`  |
| `file-attrs/`    | File attribute utilities          | `stat`, `chmod`, `link`, `symlink` |
| `bash-scripts/`  | Shell utilities and automation    | Bash scripting, MD5, process handling |
| `process-utils/` | Process monitoring tools          | `fork`, `exec`, `signals`, `/proc` |

## Build
```bash
make all
```

## Author

Wissem Trabelsi — Student @ BHT Berlin
