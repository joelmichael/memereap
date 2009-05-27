#ifndef template_h
#define template_h

struct tcache {
  char[32] filename;
  unsigned int length;
  char* content;
};

struct tvar {
  char[24] name;
  int name_length;
  char* value;
  unsigned int value_length;
};

struct tcache[] tcaches;

struct tcache* cache_template(const char* filename);

void free_tcache(struct tcache* tc);

void define_tvar(struct tvar* tv, const char* name, const char* value);

char* parse_template(const char* template, struct tvar* tvars);

#endif
