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
  char* varname = NULL;
};

struct tvar {
  char[16] name;
  char* value;
  unsigned int value_length;
};

void cache_template(struct tcache* tc, const char* filename);

void define_tvar(struct tvar* tv, const char* name, const char* value);

char* perform_subs(struct tcache* tc, struct tvar* tvars);

#endif
