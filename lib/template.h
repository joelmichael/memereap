#ifndef template_h
#define template_h

#define LINE_MAX 512
#define VARNAME_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

struct tcache {
  char filename[24];
  struct tnode* first = NULL;
  struct tnode* last = NULL;
};

struct tnode {
  struct tnode* next = NULL;
  char* text = NULL;
  char* varname;
};

struct tvar {
  char name[24];
  char* value;
  struct tvar* next;
};

void cache_template(struct tcache* tc, const char* filename);

void set_tvar(struct tvar* tv, const char* name, const char* value);

void print_tcache(struct tcache* tc, struct tvar* tvars, const int tvar_count);

#endif
