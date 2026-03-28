# file-attrs

A collection of Unix file attribute tools written in C using POSIX syscalls.
All tools are bundled into a single CLI called `lx`.

## Tools

| Tool     | Description | Key Syscalls |
|----------|-------------|--------------|
| `attrib` | Display file attributes (type, size, permissions, links,modified time) | `stat` |
| `ln`     | Create hard or symbolic links with optional verbose output | `link`, `symlink` |

## Build & Test (Automated)
```bash
make          # build lx
make test     # build and run all 8 tests
make clean    # remove binary
```

## Manual Usage
```bash
# show file attributes
./lx attrib filename

# create a hard link
./lx ln target link_name

# create a symbolic link
./lx ln -s target link_name

# create a link with verbose output
./lx ln -v target link_name

# create a symbolic link with verbose output
./lx ln -sv target link_name

# show help
./lx --help
```

## Implementation Notes

- Automated test suite written in Bash (`tests/test.sh`) validates all tools and edge cases
- File size displayed in human readable format (B/KiB/MiB/GiB/TiB) using threshold-based conversion
- `format_size()` in `utils.c` uses `2048` thresholds and `(double)` casting for accurate decimal output
- `LL` suffix used for GiB/TiB arithmetic to prevent 32-bit integer overflow
- `getopt` used in `ln.c` for clean flag parsing (`-s`, `-v`)
- Hard links use `link()`, symbolic links use `symlink()` — both POSIX syscalls