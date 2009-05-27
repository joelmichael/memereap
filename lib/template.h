#ifndef template_h
#define template_h

struct tcache {
  char filename[24];
  unsigned int length;
  char* content;
};

struct tvar {
  char name[16];
  int name_length;
  char* value;
  unsigned int value_length;
};

void cache_template(struct tcache* tc, const char* filename);

void define_tvar(struct tvar* tv, const char* name, const char* value);

char* parse_template(const struct tcache tc, const struct tvar* tvars, const int tvar_count);

#endif
