#include "cgi.h"

#include <stdlib.h>
#include <stdio.h>

#include "lib/routes.h"
#include "lib/db.h"

int main(int argc, char** argv) {
  const char* host = getenv("HTTP_HOST");
  const char* referer = getenv("HTTP_REFERER");
  const char* uri = getenv("REQUEST_URI");
  const char* method = getenv("REQUEST_METHOD");
    
  connect_db("memereap");
  
  route(host, uri, method, referer);
  
  disconnect_db();
    
  return EXIT_SUCCESS;
}
