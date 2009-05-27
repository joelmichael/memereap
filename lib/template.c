#include "lib/template.h"

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

// could feasibly pre-calculate file sizes and store on stack

void cache_template(struct tcache* tc, const char* filename) {
  FILE* file;
  struct stat st;
  char path[42];
  
  strcpy(path, "templates/");
  strcat(path, filename);
  strcpy(tc->filename, filename);
  
  stat(path, &st);
  tc->length = st.st_size;
  tc->content = (char*)malloc(tc->length + 1);
    
  file = fopen(path, "r");
  fread(tc->content, tc->length, 1, file);
  tc->content[tc->length] = '\0';
  fclose(file);
}

void define_tvar(struct tvar* tv, const char* name, const char* value) {
  strcpy(tv->name, name);
  tv->name_length = strlen(tv->name);
  tv->value = (char*)value;
  tv->value_length = strlen(value);
}

char* parse_template(const struct tcache tc, const struct tvar* tvars, const int tvar_count) {
  unsigned int length;
  char* parsed;
  int i;
  char* ptr;
  char* lastptr;
  char* parsedptr;
  int dist;
  
  length = tc.length;
  
  for(i = 0; i < tvar_count; i++) {
    length -= tvars[i].name_length + 4;
    length += tvars[i].value_length;
  }
  
  parsed = (char*)malloc(length + 1);
  
  parsedptr = parsed;
  lastptr = tc.content;
  ptr = tc.content;

  while(ptr = strstr(ptr, "{{")) {    
    // copy everything between ptr and lastptr into parsed
    dist = ptr - lastptr;
    strncpy(parsedptr, lastptr, dist);
    parsedptr += dist;
    
    for(i = 0; i < tvar_count; i++) {
      if(strncmp(ptr+2, tvars[i].name, tvars[i].name_length) && strncmp(ptr+2+tvars[i].name_length, "}}", 2)) {
        // if there's a match, copy the replacement and update pointers
        strncpy(parsedptr, tvars[i].value, tvars[i].value_length);
        parsedptr += tvars[i].value_length;
        ptr += 2 + tvars[i].name_length + 2;
        break;
      }
    }
    
    lastptr = ptr;
    ptr++;
  }
  
  // one last copy
  strcpy(parsedptr, lastptr);
  
  return parsed;
}
