#include "fastcgi.h"

#include <fcgi_stdio.h>
#include <stdlib.h>
#include "lib/routes.h"
#include "lib/db.h"

int main(int argc, char** argv) {
  char* host;
  char* referer;
  char* uri;
  char* method;
  
  connect_db("memereap");
  
  while(FCGI_Accept() >= 0) {
    host = getenv("HTTP_HOST");
    referer = getenv("HTTP_REFERER");
    uri = getenv("REQUEST_URI");
    method = getenv("REQUEST_METHOD");
    
    route(host, uri, method, referer);
  }
  
  disconnect_db();
  
  return EXIT_SUCCESS;
}
