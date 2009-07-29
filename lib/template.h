#ifndef template_h
#define template_h

#define use_template(template, filename) if(template == NULL) template = cache_template(filename)

struct template {
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

struct template* cache_template(const char* filename);

void add_tvar(const char* name, char* value);

void print_template(struct template* tc);

#endif
