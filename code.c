#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*------------------------------------------------------------------------------------
run code in vsc terminal :
cd "c:\Users\paul\Desktop\documents\Programation\C\" ; if ($?) { gcc code.c -o code } ; if ($?) { .\code encode file input.txt output.txt 0 0 }
------------------------------------------------------------------------------------*/

typedef struct Short_string {
  char data[64];
} sstr;

void usage();

int encode(char txt[], int file, char output_file[], int key, int key_identifier);

int decode(char txt[], int file, char output_file[], char key[]);

FILE *open_file_or_panic(char path[], char mode[]);

sstr hex(int val);

sstr fhex(int val, int key, short identifier);

int hexti(char val[]);

sstr mult_char(int len, char *c);

sstr tidle(int len);

sstr space(int len);

//------------------------------------------------------------------------------------

const signed char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890.+-*=,;:!?%()[]{}&<>_/\n ";
#define l_len (sizeof(letters) - 1)
int l_count[l_len] = {0};

//------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
  srand(time(NULL));

  int bool_encode = 0;

  if (strcmp(argv[1], "encode") == 0)
  {
    bool_encode = 1;
    if (argc != 7)
    {
      usage();
      exit(EXIT_FAILURE);
    }
  } else if(strcmp(argv[1], "decode") == 0) {
    bool_encode = 0;
    if (argc != 6)
    {
      usage();
      exit(EXIT_FAILURE);
    }
  } else {
    fprintf(stderr, "code %s %s %s %s %s %s\n     ^%s <- must be 'encode' or 'decode'\n\n", argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], tidle(strlen(argv[1]) - 1).data);
    usage();
    exit(EXIT_FAILURE);
  }

  int file = 0;

  if (strcmp(argv[2], "txt") == 0)
  {
    file = 0;
  } else if(strcmp(argv[2], "file") == 0) {
    file = 1;
  } else {
    fprintf(stderr, "code %s %s %s %s %s %s\n%s^%s <- must be 'txt' or 'file'\n\n", argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], space(strlen(argv[1]) + 4 + 2).data, tidle(strlen(argv[2]) - 1).data);
    printf("ok\n");
    usage();
    exit(EXIT_FAILURE);
  }

  //------------------------------------------------------------------------------------

  if (bool_encode){
    int ret = encode(argv[3], file, argv[4], atoi(argv[5]), atoi(argv[6]));
    if(ret)
    {
      fprintf(stderr, "ERRROR: error appended while encoding. return with code '1'");
    }

  } else if(!bool_encode) {
    int ret = decode(argv[3], file, argv[4], argv[5]);
    if(ret)
    {
      fprintf(stderr, "ERRROR: error appended while encoding. return with code '1'");
    }
  } else {
    fprintf(stderr, "unreachable !");
    exit(EXIT_FAILURE);
  }

  //------------------------------------------------------------------------------------

  sstr test = tidle(5);

  return 0;
}//main

void usage()
{
  fprintf(stderr, "USAGE: code encode/decode txt/file <file_in/text_in> <file_out> <encode_key> <key_key_identifier>\n");
  fprintf(stderr, "USAGE:   encode/decode: encode for text encoding and decode for its decoding.\n");
  fprintf(stderr, "USAGE:   txt/file: txt for encoding/decoding text directly from the text written in <file_in/text_in> to <file_out> or file to use the file in <file_in/text_in>.\n");
  fprintf(stderr, "USAGE:   <file_in/text_in>: the text that will be encoded/decoded or the path to the file that will be encoded. MUST BE A VALID FILE PATH IF txt/file is file !\n");
  fprintf(stderr, "USAGE:   <file_out>: the path to the file in wich the encoded text will be pasted.\n");
  fprintf(stderr, "USAGE:   <encode_key>: the secret key that will be used to offset the char value. FOR ENCODING ONLY\n");
  fprintf(stderr, "USAGE:   <key_identifier>: the identifier of the secret key. FOR ENCODING ONLY\n");
}

sstr mult_char(int len, char *c)
{
  sstr chars;

  strcpy(chars.data, c);

  for (int i = 1; i < len; i++)
  {
    strcat(chars.data, c);
  }
  return chars;
}

sstr tidle(int len)
{
  return mult_char(len, "~");
}

sstr space(int len)
{
  return mult_char(len, " ");
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

sstr hex(int val)
{
  sstr hex_val;

  sprintf(hex_val.data, "%x", val);

  return hex_val;
}

sstr fhex(int val, int key, short identifier)
{
  sstr fhex_val;

  char tmp[7];
  sprintf(tmp, "%i", identifier);

  int iden_len = pow(10, strlen(tmp));
  int iden = rand() % iden_len;

  while (iden == identifier)
  {
    iden = rand() % iden_len;
  }

  return fhex_val;
}

int hexti(char val[])
{
  sstr tmp;
  sprintf(tmp.data, "%i", val);
  printf("%s\n", tmp.data);

}

int encode(char txt[], int file, char output_file[], int key, int key_identifier)
{
  if (file)
  {
    FILE *f_in = open_file_or_panic(txt, "r");
    FILE *f_out = open_file_or_panic(output_file, "w");

    while (!(feof(f_in)))
    {
      char character = fgetc(f_in);
      if (character >= 0) 
      {
        char out[50];
        for (int i = 0; i < l_len; i++)
        {
          if (character == letters[i])
          {
            
            l_count[i]++;
            sprintf(out, "%s ", fhex(i, key, key_identifier));
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

int decode(char txt[], int file, char output_file[], char key[])
{
  FILE *in = open_file_or_panic(txt, "r");
  FILE *out = open_file_or_panic(output_file, "w");

  sstr word;
  strcpy(word.data, fgetc(in));
  while (!(feof(in)))
  {
    char letter = fgetc(in);
  }
  

  fclose(in);
  fclose(out);
  return 0;
}