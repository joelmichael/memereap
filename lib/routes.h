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

#endif
