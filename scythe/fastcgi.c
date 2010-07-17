#include <fcgi_stdio.h>
#include <stdlib.h>
#include "scythe/request.h"
#include "scythe/routes.h"
#include "scythe/db.h"

int main(int argc, char** argv) {
  connect_db("memereap");
  
  init_routes();
  
  while(FCGI_Accept() >= 0) {
    process_request();
  }
  
  disconnect_db();
  
  return EXIT_SUCCESS;
}
