//
// Created by Wissem Trabelsi
//
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
int do_copy(int argc, char *argv[])
{
    //Usage check
    if (argc != 3)
    {
        const char *usage = "Usage: ./copy <src-file> <dst-file>\n";
        write(2, usage, my_strlen(usage));
        return 1;
    }
    int fd_src, fd_dst;
    fd_src=open(argv[1], O_RDONLY);
    if (fd_src < 0)
    {
        print_error("Error opening src-file",argv[1]);
        return 1;
    }
    //0644 permissions for newly created files
    fd_dst=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
    if (fd_dst < 0)
    {
        print_error("Error opening dst-file",argv[2]);
        close(fd_src);
        return 1;
    }
    struct stat stat_src, stat_dst;
    //Statting src file
    if (fstat(fd_src, &stat_src) < 0)
    {
        print_error("Error statting src-file",NULL);
        close(fd_src);
        close(fd_dst);
        return 1;
    }
    //Statting dst file
    if (fstat(fd_dst, &stat_dst) < 0)
    {
        print_error("Error statting dst-file",NULL);
        close(fd_src);
        close(fd_dst);
        return 1;
    }

    //Check if src, dst are the same file
    //prevent infinite loop
    if ((stat_src.st_ino == stat_dst.st_ino) &&
        (stat_dst.st_dev == stat_src.st_dev)){
        print_error("src,dst are the same file\n",NULL);
        close(fd_src);
        close(fd_dst);
        return 1;
        }

    ssize_t bytes_read;
    char buf[4096];
    //read from src overwrite dst
    while ((bytes_read = read(fd_src, buf, sizeof(buf))) > 0)
    {
        ssize_t tot_bytes_written = 0;
        while (tot_bytes_written < bytes_read)
        {
            ssize_t bytes_written = write(fd_dst, buf + tot_bytes_written, bytes_read - tot_bytes_written);
            if (bytes_written < 0)
            {
                print_error("write error\n",NULL);
                close(fd_src);
                close(fd_dst);
                return 1;
            }
            tot_bytes_written += bytes_written;
        }
    }

    //read error handling
    if (bytes_read < 0)
    {

        print_error("Error reading src-file",NULL);
        close(fd_src);
        close(fd_dst);
        return 1;
    }

    close(fd_src);
    close(fd_dst);
    return 0;
}