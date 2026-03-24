# file-io

A collection of low-level file I/O tools written in C using only POSIX syscalls.
No `stdio.h` functions are used — only `open`, `read`, `write`, `close`, `fstat`.
All tools are bundled into a single CLI called `filetool`.

## Tools

| Tool      | Description                            | Key Syscalls                     |
|-----------|----------------------------------------|----------------------------------|
| `copy`    | Copy a file, overwriting destination   | `open`, `read`, `write`, `fstat` |
| `append`  | Append source file to destination      | `open`, `read`, `write`, `fstat` |
| `reverse` | Print each line of a file reversed | `open`, `fdopen`, `getline`, `write` |

## Build & Test (Automated)
```bash
make          # build filetool
make test     # build and run all 6 tests
make clean    # remove binary
```

## Manual Usage
```bash
# copy a file
./filetool copy src.txt dst.txt

# append src to dst
./filetool append src.txt dst.txt

# reverse lines of a file
./filetool reverse input.txt

# show help
./filetool --help
```

## Implementation Notes

- All tools use raw POSIX syscalls — no `stdio.h`
- Same-file detection using `fstat()` with `st_ino` and `st_dev` prevents infinite loops
- Partial write handling ensures all bytes are written even if `write()` returns less
- Shared utilities (`utils.c`) provide `my_strlen()` and `print_error()` without stdlib
