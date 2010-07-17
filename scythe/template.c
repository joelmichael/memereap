#include "template.h"

#include <fcgi_stdio.h>
#include <string.h>
#include <stdlib.h>
#include "request.h"

#define LINE_MAX 512

// this loads the template up into a simple data structure for fast substitution
// mallocs a bunch of stuff but we don't have to free it because it's permanent until program exit
// basically a linked list of nodes containing either text or a variable for substitution

static struct tvar* head_tvar;
static struct tvar* tail_tvar;

static void parse_line(struct template* template, char* line);
static void add_text_tnode(struct template* template, char* text, int textlen);
static void add_var_tnode(struct template* template, char* varname, int varlen);
static void add_tnode(struct template* template, struct tnode* tn);
static void free_tvars();

// create tnodes out of the line
// could use more protection against {{ at the end of a line

struct template* parse_template(const char* filename) {
  FILE* file;
  char path[42];
  char line[LINE_MAX];
  int length;
  struct template* template;
  
  template = (struct template*)malloc(sizeof(struct template));
  template->head = NULL;
  template->tail = NULL;
  
  strcpy(path, "../templates/");
  strcat(path, filename);
  strcpy(template->filename, filename);
      
  file = fopen(path, "r");

  while(fgets(line, LINE_MAX, file) != NULL) {
    parse_line(template, line);
  }

  fclose(file);
  
  return template;
}

void set_tvar(const char* name, char* value) {
  struct tvar* tv;
  
  tv = (struct tvar*)malloc(sizeof(struct tvar));
  tv->next = NULL;
  
  strcpy(tv->name, name);
  tv->value = value;
  
  if(head_tvar == NULL) {
    head_tvar = tv;
  }
  else {
    tail_tvar->next = tv;
  }
  
  tail_tvar = tv;
}

// this does all the var tnode substitutions and prints the template
// it then frees the tvars

void print_template(struct template* template) {
  struct tnode* tn = template->head;
  struct tvar* tv;
  
  while(tn != NULL) {
    if(tn->text == NULL) {
      tv = head_tvar;
      
      while(tv != NULL) {
        if(strcmp(tn->varname, tv->name) == 0) {
          printf("%s", tv->value);
          break;
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

static void parse_line(struct template* template, char* line) {
  char* ptr = line;
  char* lastptr = line;
  char* startptr;
  char* endptr;
  struct tnode* tn = template->tail;
  int textlen;
  int varlen;
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
        add_text_tnode(template, lastptr, textlen);
      }
            
      // create a var tnode
      add_var_tnode(template, startptr, varlen);
      
      ptr = endptr+2;
      lastptr = ptr;
    }
    else {
      // continue if not
      ptr++;
    }
  }
  
  // create a text tnode of whatever remains
  textlen = linelen - (lastptr - line);
  add_text_tnode(template, lastptr, textlen);
}

static void add_text_tnode(struct template* template, char* text, int textlen) {
  struct tnode* tn;
  int oldtextlen;
  
  // coalesce the previous text node if possible
  if(template->tail != NULL && template->tail->text != NULL) {
    tn = template->tail;
    oldtextlen = strlen(tn->text);
    tn->text = (char*)realloc(tn->text, oldtextlen + textlen + 1);
    strncpy(tn->text+oldtextlen, text, textlen);
    tn->text[oldtextlen + textlen] = '\0';
  }
  else {
    tn = (struct tnode*)malloc(sizeof(struct tnode));
    tn->next = NULL;
    tn->text = (char*)malloc(textlen+1);
    strncpy(tn->text, text, textlen);
    tn->text[textlen] = '\0';
    add_tnode(template, tn);
  }
}

static void add_var_tnode(struct template* template, char* varname, int varlen) {
  struct tnode* tn;
  
  tn = (struct tnode*)malloc(sizeof(struct tnode));
  tn->varname = (char*)malloc(varlen+1);
  tn->next = NULL;
  strncpy(tn->varname, varname, varlen);
  tn->varname[varlen] = '\0';
  tn->text = NULL;
  
  add_tnode(template, tn);
}

static void add_tnode(struct template* template, struct tnode* tn) {  
  if(template->head == NULL) {
    template->head = tn;
  }
  else {
    template->tail->next = tn;
  }
  template->tail = tn;
}

static void free_tvars() {
  struct tvar* tv = head_tvar;
  struct tvar* next;
  
  while(tv != NULL) {
    next = tv->next;
    free(tv);
    tv = next;
  }
  
  head_tvar = NULL;
  tail_tvar = NULL; 
}
