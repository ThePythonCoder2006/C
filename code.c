#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//------------------------------------------------------------------------------------

void usage();

int encode(char txt[], int file, char output_file[], int key, int key_identifier);

int decode(char txt[], int file, char output_file[]);

FILE *open_file_or_panic(char path[], char mode[]);

char *hex(int val);

char *fhex(int val, int key, int identifier);

//------------------------------------------------------------------------------------

#define l_len 85
const signed char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890.+-*/=,;:!?%()[]{}&<>_";
int l_count[l_len] = {0};

//------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
  if (argc != 6)
  {
    usage();
    exit(EXIT_FAILURE);
  }

  int bool_encode = 0;

  if (strcmp(argv[1], "encode") == 0)
  {
    bool_encode = 1;
  } else if(strcmp(argv[1], "decode") == 0) {
    bool_encode = 0;
  } else {
    usage();
    fprintf(stderr, "                  ^must be 'encode' or 'decode'\n");
    exit(EXIT_FAILURE);
  }

  int file = 0;

  if (strcmp(argv[2], "txt") == 0)
  {
    file = 0;
  } else if(strcmp(argv[2], "file") == 0) {
    file = 1;
  } else {
    usage();
    fprintf(stderr, "                              ^must be 'txt' or 'file'\n");
    exit(EXIT_FAILURE);
  }

  //------------------------------------------------------------------------------------

  if (bool_encode){
    int ret = encode(argv[3], file, argv[4], (int) argv[5], (int) argv[6]);
    if(ret)
    {
      fprintf(stderr, "ERRROR: error appended while encoding. return with code '1'");
    }

  } else if(!bool_encode) {
    int ret = decode(argv[3], file, argv[4]);
    if(ret)
    {
      fprintf(stderr, "ERRROR: error appended while encoding. return with code '1'");
    }
  } else {
    fprintf(stderr, "unreachable !");
    exit(EXIT_FAILURE);
  }

  //------------------------------------------------------------------------------------

  printf("%s\n", hex(234867835));

  return 0;
}//main

void usage()
{
  fprintf(stderr, "USAGE: code encode/decode txt/file <file_in/text_in> <file_out> <encode_key> <key_identification>\n");
}

FILE *open_file_or_panic(char path[], char mode[])
{
  FILE *f = fopen(path, mode);

  if (f == NULL)
  {
    fprintf(stderr, "failed to open file %s", path);
    exit(EXIT_FAILURE);
  }

  return f;
}

char *hex(int val)
{
  static signed char hex_val[50];

  sprintf(hex_val, "%x", val);

  return hex_val;
}

int encode(char txt[], int file, char output_file[], int key, int key_identifier)
{
  if (file)
  {
    FILE *f_in = open_file_or_panic(txt, "r");
    FILE *f_out = open_file_or_panic(output_file, "w");

    while (!(feof(f_in)))
    {
      int character = fgetc(f_in);
      if (character >= 0) 
      {
        char *out;
        for (int i = 0; i < l_len; i++)
        {
          if (character == letters[i])
          {
            l_count[i]++;
            out = fhex(letters[i], key, key_identifier);
            break;
          }
        }
        fputs(out, f_out);
      }
    }
    

    fclose(f_out);
    fclose(f_in);
  }
  return 0;
}

int decode(char txt[], int file, char output_file[])
{
  fprintf(stderr, "TODO: decoding implemented yet\n");
  return 0;
}