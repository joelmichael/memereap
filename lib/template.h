#ifndef template_h
#define template_h

#define LINE_MAX 512
#define VARNAME_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

struct tcache {
  char filename[32];
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

void use_template(struct tcache* tc, const char* filename);

void add_tvar(const char* name, const char* value);

void print_template(struct tcache tc);

#endif
