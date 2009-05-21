#ifndef cgi_c
#define cgi_c

#include <stdlib.h>
#include <stdio.h>

#include "lib/routes.c"
#include "lib/db.c"

int main(int argc, char** argv) { 
  const char* host = getenv("HTTP_HOST");
  const char* referer = getenv("HTTP_REFERER");
  const char* uri = getenv("REQUEST_URI");
  const char* method = getenv("REQUEST_METHOD");
    
  connect_db("memereap");
  
  route(host, uri, method, referer);
  
  mysql_close(&mysql);
    
  return EXIT_SUCCESS;
}

#endif