#ifndef template_h
#define template_h

#define use_template(template, filename) if(template == NULL) template = parse_template(filename)

struct template {
  char filename[32];
  struct tnode* head;
  struct tnode* tail;
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

struct template* parse_template(const char* filename);

void set_tvar(const char* name, char* value);

void print_template(struct template* template);

#endif
