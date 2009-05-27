#include "lib/template.h"

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

// could feasibly pre-calculate file sizes and store on stack

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
  char* ptr;
  char* lastptr;
  char* parsedptr;
  int dist = 0;
  
  length = tc->length;
  
  for(i = 0; i < tvar_count, i++) {
    length -= tvars[i].name_length + 4;
    length += tvars[i].value_length;
  }
  
  parsed = (char*)malloc(length + 1);
  
  parsedptr = parsed;
  lastptr = tc->content;
  ptr = tc->content;

  while(ptr = strstr(ptr, "{{")) {
    // copy everything between ptr and lastptr into parsed
    dist += ptr - lastptr;
    strncpy(parsedptr, lastptr, dist);
    parsedptr += dist;
    
    for(i = 0; i < tvar_count; i++) {
      if(strncmp(ptr+2, tvar[i].name, tvar[i].name_length) && strncmp(ptr+2+tvar[i].name_length, "}}", 2)) {
        // if there's a match, copy the replacement and update pointers
        strcpy(parsedptr, tvar[i].value);
        parsedptr += tvar[i].value_length;
        ptr += 2 + tvar[i].name_length + 2;
        break;
      }
    }
    
    lastptr = ptr;
  }
  
  // one last copy
  strcpy(parsedptr, lastptr);
  
  return parsed;
}
