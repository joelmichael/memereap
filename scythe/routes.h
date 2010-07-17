#ifndef routes_h
#define routes_h

struct rnode {
  struct rnode* next;
  char* text;
  char* varname;
};

struct route {
  struct rnode* first;
  struct rnode* last;
  void (*action)();
  struct route* next;
};

void add_route(char* route_str, void (*action)());

struct route* parse_route_str(char* route_str);

struct route* determine_route(char* route_str);

void set_params_for_route(struct route*, char* route_str);

// defined in config/routes.c
void init_routes();

#endif
