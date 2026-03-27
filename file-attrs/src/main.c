#include <string.h>
#include <unistd.h>
#include "utils.h"
#include "attrib.h"
#include "ln.h"


static void print_usage(void)
{
	const char *msg =
	"Usage: lx <command> [args]\n"
    "\nCommands:\n"
    "  attrib <file>                    - show file attributes\n"
    "  ln     [-s] [-v] <target> <link> - create hard or symbolic link\n"
    "  --help                           - show this message\n";
	write(2, msg, my_strlen(msg));
}

int main(int argc, char *argv[]){

if (argc < 2) {
    print_usage();
    return 1;
}

if (strcmp(argv[1], "attrib") == 0){
    return do_attrib(argc - 1,argv + 1);
}else if (strcmp(argv[1], "ln") == 0){
    return do_ln(argc - 1,argv + 1);
}else if (strcmp(argv[1], "--help") == 0){
    print_usage();
    return 0;
}else {
    print_error("Unknown command\n", NULL);
    print_usage();
    return 1;
}

return 0;
}
