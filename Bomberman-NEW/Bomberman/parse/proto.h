#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct opt
{
  char name;
  char* valeur;
  struct opt* nxt;
} opt_s;

opt_s* addStartOpt(opt_s* option, char name, char* val, int flag);
opt_s* error_usage(char** argv, int i, opt_s* option, char* format);
opt_s* my_getopt(int argc, char** argv, char* format);
int check_doubles(char* format, int i, char* val_to_cmp, int cpt);
int doubles(char* val_to_cmp, char* format_origin);
int exist_opt(char* format, char** argv, int i);
int verif_arg(char* format, int argc, char** argv);
