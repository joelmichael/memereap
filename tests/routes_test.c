#include <fcgi_stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "scythe/routes.h"
#include "scythe/request.h"
#include "scythe/response.h"

void example_action1() {}
void example_action2() {}
void example_action3() {}

void test_routes() {
  struct route* route;
  char route_str[32];
  
  add_route("/example", example_action1);  
  add_route("/example/:id", example_action2);
  add_route("/foo/:name/:baz/:dog/hey", example_action3);
  
  strcpy(route_str, "/example");
  route = determine_route(route_str);
  set_params_for_route(route, route_str);
  
  assert(route->action == example_action1);
  assert(param("id") == NULL);
  
  free_params_and_cookies();
  
  strcpy(route_str, "/example/2");
  route = determine_route(route_str);
  set_params_for_route(route, route_str);
  
  assert(route->action == example_action2);
  assert(strcmp(param("id"), "2") == 0);
  
  free_params_and_cookies();
  
  strcpy(route_str, "/foo/what/snap/urjfjf/f/f/f/hey");
  route = determine_route(route_str);
  set_params_for_route(route, route_str);
  
  assert(route->action == example_action3);
  assert(strcmp(param("name"), "what") == 0);
  assert(strcmp(param("baz"), "snap") == 0);
  assert(strcmp(param("dog"), "urjfjf/f/f/f") == 0);
  
  free_params_and_cookies();
  
  route = determine_route("/nope");
  assert(route == NULL);
}

int main(int argc, char** argv) {
  test_routes();
  
  return EXIT_SUCCESS;
}