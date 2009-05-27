#include "lib/template.h"

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

char* cache_template(const char* filename) {
  struct tcache* tc;
  FILE* file;
  struct stat stat;
  char pathname[42] = "templates/"
  
  tc = (struct tcache*)malloc(sizeof(tc));
  strcpy(tc->filename, filename);
  
  strcat(path, filename);
  file = fopen(path, "r");
  fstat(file, &stat);
  tc->length = stat.st_size;
  
  tc->content = (char*)malloc(tc.length + 1);
  
  fread(tc->content, tc->length, 1, fp);
  fclose(file);
  
  tc->content[tc->length] = '\0';
  
  return tc;
}

void define_tvar(struct tvar* tv, const char* name, const char* value) {
  strcpy(tv.name, name);
  tv.name_length = strlen(tv.name);
  tv.value = value;
  tv.value_length = strlen(value);
}

char* parse_template(struct tcache* tc, struct tvar* tvars, int tvar_count) {
  unsigned int length;
  char* parsed;
  int i;
  char* tcptr;
  char* parsedptr;
  int dist;
  
  length = tc->length;
  
  for(i = 0; i < tvar_count, i++) {
    length -= tvars[i].name_length + 4;
    length += tvars[i].value_length;
  }
  
  parsed = (char*)malloc(length + 1);
  
  tcptr = tc->content;
  
  while(tcptr = strstr(tcptr, "{{")) {
    dist = tcptr - tc->content;
    
  }
}
