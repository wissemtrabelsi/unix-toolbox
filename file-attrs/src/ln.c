#include <stdio.h>//printf for verbose
#include <unistd.h> //link(),symlink()
#include "utils.h"

int do_ln(int argc,char *argv[])
{
    int flag_s = 0;
    int flag_v = 0;

    int opt = 0;
    while ((opt = getopt(argc,argv,"sv")) != -1)
    {
        switch (opt)
        {
            case 's':
                flag_s = 1;
                break;
            case 'v':
                flag_v = 1;
                break;
            default:
                print_error("Usage:ln [-s][-v] <target> <link_name>\n",NULL);
                return 1;
        }
    }
    if (optind + 1 >= argc)
    {
        print_error("Usage:ln [-s][-v] <target> <link_name>\n",NULL);
        return 1;
    }

    char *target = argv[optind];
    char *link_name = argv[optind + 1];
    if (flag_s == 1)//symbolic link
    {
        if (symlink(target, link_name) < 0)//or == -1
        {
            print_error("Can't create Symblic link  \n",link_name);
            return 1;
        }
        if (flag_v == 1)
        {
            printf("Symlink %s --> %s\n",target,link_name);
            return 0;
        }
    }
    else
	{
        if (link(target, link_name) < 0)
		{
            print_error("Can't create hard link  \n",link_name);
            return 1;
        }
        if (flag_v == 1)
        {
            printf("Link %s ==> %s\n",target,link_name);
            return 0;
        }
    }

return 0;
}