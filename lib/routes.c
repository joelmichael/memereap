#include "routes.h"

#include "lib/request.h"

static struct route* head_route;

void add_route(char* route_str, void (*action)()) {
  struct route* route = parse_route_str(route_str);
  route->action = action;
  route->next = head_route;
  head_route = route;
}

struct route* parse_route_str(char* route_str) {
  // /users/edit/:id
  // /users/:action/:id
  // include request library so we can add params
  
}
