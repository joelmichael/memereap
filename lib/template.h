#ifndef template_h
#define template_h

#define LINE_MAX 512
#define VARNAME_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

struct tcache {
  char filename[32];
  struct tnode* first;
  struct tnode* last;
};

struct tnode {
  struct tnode* next;
  char* text;
  char* varname;
};

struct tvar {
  char name[24];
  char* value;
  struct tvar* next;
};

struct tcache* cache_template(const char* filename);

void add_tvar(const char* name, char* value);

void print_tcache(struct tcache* tc);

#endif
