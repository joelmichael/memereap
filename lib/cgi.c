#ifndef cgi_c
#define cgi_c

#include <stdlib.h>
#include <stdio.h>

#include "lib/routes.c"
#include "lib/db.c"

int main(int argc, char** argv) {
  char* request_uri = getenv("REQUEST_URI");
  
  printf("Content-type: text/plain\n\n");
  printf("REQUEST_URI: %s\n", request_uri);
  
  connect_db("memereap");
  
  route(request_uri);
  
  mysql_close(&mysql);
  
  return EXIT_SUCCESS;
}

#endif