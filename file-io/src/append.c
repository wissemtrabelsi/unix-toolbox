//
// Created by Wissem Trabelsi
//
#include <fcntl.h>      // For open() and flags like O_RDONLY, O_APPEND
#include <unistd.h>     // For read(), write(), close()
#include <sys/stat.h>   // For fstat() and struct stat
#include "utils.h"

int do_append(int argc, char *argv[])
{
    int fd_src, fd_dst;
    char buf[4096];
    ssize_t bytes_read;
    struct stat stat_src, stat_dst;

    // Check that exactly two filenames were provided
    if (argc != 3) {
        const char *usage = "Usage: append <src-file> <dst-file>\n";
        write(2, usage, my_strlen(usage));
        return 1;
    }

    // Open source file for reading
    fd_src = open(argv[1], O_RDONLY);
    if (fd_src < 0) {
        print_error("Error: Cannot open source file: ", argv[1]);
        close(fd_src);
        return 1;
    }

    // Open destination file for appending
    // O_WRONLY: write only, O_CREAT: create if needed, O_APPEND: append to end
    // 0644: permissions (rw-r--r--) for newly created files
    fd_dst = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd_dst < 0) {
        print_error("Error: Cannot open destination file: ", argv[2]);
        close(fd_src);
        return 1;
    }

    // Get file information for source file
    if (fstat(fd_src, &stat_src) < 0) {
        print_error("Error: Cannot stat source file\n", NULL);
        close(fd_src);
        close(fd_dst);
        return 1;
    }

    // Get file information for destination file
    if (fstat(fd_dst, &stat_dst) < 0) {
        print_error("Error: Cannot stat destination file\n", NULL);
        close(fd_src);
        close(fd_dst);
        return 1;
    }

    // Check if source and destination are the same file
    // (prevents infinite loop when appending a file to itself)
    if (stat_src.st_dev == stat_dst.st_dev &&
        stat_src.st_ino == stat_dst.st_ino) {
        print_error("Error: Source and destination are the same file\n", NULL);
        close(fd_src);
        close(fd_dst);
        return 1;
    }

    // Read from source and write to destination
    while ((bytes_read = read(fd_src, buf, sizeof(buf))) > 0) {
        ssize_t total_written = 0;
        // Handle partial writes
        // (ensures all bytes are written even if write() returns less)
        while (total_written < bytes_read) {
            ssize_t bytes_written = write(fd_dst,buf + total_written,bytes_read - total_written);
            if (bytes_written < 0) {
                print_error("Error: Write failed\n", NULL);
                close(fd_src);
                close(fd_dst);
                return 1;
            }
            total_written += bytes_written;
        }
    }

    // Check for read errors
    if (bytes_read < 0) {
        print_error("Error: Read failed\n", NULL);
        close(fd_src);
        close(fd_dst);
        return 1;
    }

    // Clean up and exit successfully
    close(fd_src);
    close(fd_dst);
    return 0;
}