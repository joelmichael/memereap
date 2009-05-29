#include "lib/template.h"

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

// this loads the template up into a data structure for fast substitution
// mallocs a bunch of stuff but we don't have to free it because it's permanent until program exit
// basically a linked list of nodes containing either text or a variable for substitution

static struct tvar* first_tvar;
static struct tvar* last_tvar;

void use_template(struct tcache* tc, const char* filename) {
  if(tc->first == NULL) {
    cache_template(tc, filename);
  }
}

void add_tvar(const char* name, const char* value) {
  struct tvar* tv;
  
  tv = (struct tvar*)malloc(sizeof(struct tvar));
  
  strcpy(tv->name, name);
  tv->value = value;
  
  if(first_tvar == NULL) {
    first_tvar = tv;
  }
  else {
    last_tvar->next = tv;
  }
  last_tvar = tv;
}

// this does all the var tnode substitutions and prints the tcache
// would like to avoid the tvar_count
// assume user is competent enough to add all used variables...?
// or make tvars a linked list?

void print_template(struct tcache tc) {
  struct tnode* tn = tc.first;
  struct tvar* tv = first_tvar;
  
  while(tn != NULL) {
    if(tn->text == NULL) {
      while(tv != NULL) {
        if(strcmp(tn->varname, tv->name) == 0) {
          printf("%s", tv->value);
        }
        
        tv = tv->next;
      }
    }
    else {
      printf("%s", tn->text);
    }
    
    tn = tn->next;
  }
  
  free_tvars();
}

// static functions

// create tnodes out of the line
// could use more protection against {{ at the end of a line

static void cache_template(struct tcache* tc, const char* filename) {
  FILE* file;
  struct stat st;
  char path[42];
  char line[LINE_MAX];
  int length;
  struct tnode* last = tc->first;
  
  strcpy(path, "../templates/");
  strcat(path, filename);
  strcpy(tc->filename, filename);
  
  stat(path, &st);
  tc->length = st.st_size;
    
  file = fopen(path, "r");

  while(!feof(file)) {
    fgets(line, LINE_MAX, file);
    parse_line(tc, line);
  }

  fclose(file);
}

static void parse_line(struct tcache* tc, const char* line) {
  char* ptr = line;
  char* lastptr = line;
  char* startptr, endptr;
  struct tnode* tn = tc->last;
  int textlen, varlen;
  int linelen = strlen(line);
  
  while(ptr = strstr(ptr, "{{")) {
    startptr = ptr + 2;
    endptr = strstr(startptr, "}}");
    
    // continue if this does not close
    if(endptr == NULL) {
      ptr++;
      continue;
    }
    
    varlen = endptr - startptr;
    
    // check for a valid variable name
    if(strspn(startptr, VARNAME_CHARS) == varlen) {
      textlen = ptr - lastptr;
      
      // create a text tnode of everything up to this point if there is anything
      if(textlen > 0) {
        add_text_tnode(tc, lastptr, textlen);
      }
            
      // create a var tnode
      add_var_tnode(tc, startptr, varlen);
      
      ptr = endptr+2;
      lastptr = ptr;
    }
    else {
      // continue if not
      ptr++;
    }
  }
  
  // create a text tnode of whatever remains
  add_text_tnode(tc, lastptr, linelen - (lastptr - line));
}

static void add_text_tnode(struct tcache* tc, const char* text, const int textlen) {
  struct tnode* tn;
  char* oldtext;
  int oldtextlen;
  
  // coalesce the previous text node if possible
  if(tc->last != NULL && tc->last.text != NULL) {
    tn = tc.last;
    oldtext = tn->text;
    oldtextlen = strlen(oldtext);
    tn->text = (char*)malloc(oldtextlen + textlen + 1);
    strncpy(tn->text, text, oldtextlen + textlen);
    tn->text[oldtextlen + textlen] = '\0'];
  }
  else {
    tn = (struct tnode*)malloc(sizeof(struct tnode));
    tn->text = (char*)malloc(textlen+1);
    strncpy(tn->text, text, textlen);
    tn->text[textlen] = '\0';
  }
  
  add_tnode(tn);
}

static void add_var_tnode(struct tcache* tc, const char* varname, const int varlen) {
  struct tnode* tn;
  
  tn = (struct tnode*)malloc(sizeof(struct tnode));
  tn->varname = (char*)malloc(varlen+1);
  strncpy(tn->varname, varname, varlen);
  tn->varname[varlen] = '\0';
  
  add_tnode(tn);
}

static void add_tnode(struct tcache* tc, struct tnode* tn) {
  if(tc->first == NULL) {
    tc->first = tn;
  }
  else {
    tc->last->next = tn;
  }
  tc->last = tn;
}

static void free_tvars() {
  struct tvar* tv = first_tvar;
  struct tvar* next;
  
  while(tv != NULL) {
    next = tv->next;
    free(tv->value);
    free(tv);
    tv = next;
  }
  
  first_tvar = NULL;
  last_tvar = NULL; 
}
