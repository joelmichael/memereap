#include <fcgi_stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lib/routes.h"
#include "lib/request.h"
#include "lib/response.h"

static void example_action1() {}
static void example_action2() {}
static void example_action3() {}

void test_add_route() {
  add_route("/example", example_action1);  
  add_route("/example/:id", example_action2);
  add_route("/foo/:name/:dog/hey", example_action3);
}

void test_determine_route() {
  struct route* route;
  
  route = determine_route("/example");
  assert(route->action == example_action1);
  
  route = determine_route("/example/2");
  assert(route->action == example_action2);
  
  route = determine_route("/foo/what/urjfjf/f/f/f/hey");
  assert(route->action == example_action3);
  
  route = determine_route("/nope");
  assert(route == NULL);
}

int main(int argc, char** argv) {
  test_add_route();
  test_determine_route();
  
  return EXIT_SUCCESS;
}