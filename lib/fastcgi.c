#include <fcgi_stdio.h>
#include <stdlib.h>
#include "lib/request.h"
#include "lib/db.h"

int main(int argc, char** argv) {
  connect_db("memereap");
  
  while(FCGI_Accept() >= 0) {
    route_request();
  }
  
  disconnect_db();
  
  return EXIT_SUCCESS;
}
