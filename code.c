#include <stdio.h>
#include <stdlib.h>

void usage();

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        usage();
        exit(EXIT_FAILURE);
    }
    
    if(argv[1] != "txt" || argv[1] != "file")
    {
        usage();
        fprintf(stderr, "               ^must be 'txt' or 'file'\n");
    }

    switch (argv)
    {
    case "file":
        fprintf(stderr, "TODO: file encoding not implemented yet");
        break;
    
    default:
        break;
    }
    return 0;
}

void usage()
{
    fprintf(stderr, "USAGE: code txt/file <file/text> <encode_key> <key_identification>\n");
}