#include <fcgi_stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lib/routes.h"
#include "lib/request.h"
#include "lib/response.h"

void example_action() {
}

void test_add_route() {
  add_route("/example", example_action);
  add_route("/example/:id", example_action);
  add_route("/foo/:name/:dog/hey", example_action);
}

int main(int argc, char** argv) {
  test_add_route();
  //test_determine_route();
  
  return EXIT_SUCCESS;
}