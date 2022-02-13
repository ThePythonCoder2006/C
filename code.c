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

    printf("%i\n", argv[1] == "txt");
    if (argv[1] == "txt")
    {
        fprintf(stderr, "TODO: encoding text from console is not implemented yet");
    } else if(argv[1] == "file")
    {
        fprintf(stderr, "TODO: encoding from file is not implemented yet");
    } else {
        usage();
        fprintf(stderr, "               ^must be 'txt' or 'file'\n");
    }
}

void usage()
{
    fprintf(stderr, "USAGE: code txt/file <file/text> <encode_key> <key_identification>\n");
}