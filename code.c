#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage();

int main(int argc, char **argv)
{
    if (argc != 7)
    {
        usage();
        exit(EXIT_FAILURE);
    }    

    if (strcmp(argv[1], "encode") == 0)
    {
        fprintf(stderr, "TODO: encoding is not implemented yet\n");
    } else if(strcmp(argv[1], "decode") == 0)
    {
        fprintf(stderr, "TODO: decoding implemented yet\n");
    } else {
        usage();
        fprintf(stderr, "                  ^must be 'encode' or 'decode'\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[2], "txt") == 0)
    {
        fprintf(stderr, "TODO: en/decoding text from console is not implemented yet\n");
    } else if(strcmp(argv[2], "file") == 0)
    {
        fprintf(stderr, "TODO: en/decoding from file is not implemented yet\n");
    } else {
        usage();
        fprintf(stderr, "                            ^must be 'txt' or 'file'\n");
        exit(EXIT_FAILURE);
    }
}

void usage()
{
    fprintf(stderr, "USAGE: code encode/decode txt/file <file_in/text_in> <file_out> <encode_key> <key_identification>\n");
}