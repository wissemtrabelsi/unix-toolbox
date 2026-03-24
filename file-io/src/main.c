//
// Created by Wissem Trabelsi
//
#include "append.h"
#include "copy.h"
#include "reverse.h"
#include "utils.h"
#include <string.h>
#include <unistd.h>//write()...
static void print_usage(void)
{
    const char *usage_msg =
        "Usage: filetool <command> [args]\n"
        "\nCommands:\n"
        "copy    <src_file> <dst_file>  - copy a file\n"
        "append  <src_file> <dst_file>  - append src to dst\n"
        "reverse <file>       - reverse lines of a file\n"
        "--help               - show this message\n";
    write(2,usage_msg,my_strlen(usage_msg));
}
int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage();
        return 1;
    }
    if (strcmp(argv [1], "copy") == 0)
        return do_copy(argc - 1, argv + 1);
    else if (strcmp(argv [1], "append") == 0)
        return do_append(argc -1 , argv + 1);
    else if (strcmp(argv [1], "reverse") == 0)
        return do_reverse(argc - 1, argv + 1);
    else if (strcmp(argv[1], "--help") == 0)
    {
        print_usage();
        return 0;
    }
    else
    {
        print_error("Unknown command\n",NULL);
        print_usage();
        return 1;
    }

    return 0;
}