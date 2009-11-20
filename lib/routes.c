#include "routes.h"

#include <string.h>
#include "lib/request.h"

static struct route* head_route;

static void add_text_rnode(struct route* route, char* text, int textlen);
static void add_var_rnode(struct route* route, char* varname, int varlen);
static void add_rnode(struct route* route, struct rnode* rn);

void add_route(char* route_str, void (*action)()) {
  struct route* route = parse_route_str(route_str);
  route->action = action;
  route->next = head_route;
  head_route = route;
}

// similar to basic rails routes
// /users/edit/:id
// /users/:action/:id
// include request library so we can add params and get VARNAME_CHARS
// something like that
  
struct route* parse_route_str(char* route_str) {
  struct route* route;
  char* ptr = route_str;
  char* lastptr = route_str;
  int varlen;
  int textlen;
  int routelen = strlen(route_str);
  
  route = (struct route*)malloc(sizeof(struct route));
  
  while(ptr = strstr(ptr, ":")) {
    ptr++;
    
    varlen = strspn(ptr, VARNAME_CHARS);
    
    // create a text node of everything up to this point
    textlen = ptr - lastptr - 1;
    add_text_rnode(route, lastptr, textlen);
    
    add_var_rnode(route, ptr, varlen);
    ptr += varlen;
    lastptr = ptr;
  }
  
  textlen = routelen - (lastptr - route_str);
  add_text_rnode(route, ptr, textlen);
}

static void add_text_rnode(struct route* route, char* text, int textlen) {
  struct rnode* rn;
  int oldtextlen;
  
  rn = (struct rnode*)malloc(sizeof(struct rnode));
  rn->next = NULL;
  rn->text = (char*)malloc(textlen+1);
  strncpy(rn->text, text, textlen);
  rn->text[textlen] = '\0';
  add_rnode(route, rn);
}

static void add_var_rnode(struct route* route, char* varname, int varlen) {
  struct rnode* rn;
  
  rn = (struct rnode*)malloc(sizeof(struct rnode));
  rn->varname = (char*)malloc(varlen+1);
  rn->next = NULL;
  strncpy(rn->varname, varname, varlen);
  rn->varname[varlen] = '\0';
  rn->text = NULL;
  
  add_rnode(route, rn);
}

static void add_rnode(struct route* route, struct rnode* rn) {  
  if(route->first == NULL) {
    route->first = rn;
  }
  else {
    route->last->next = rn;
  }
  route->last = rn;
}
