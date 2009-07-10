#include "response.h"

#include <fcgi_stdio.h>
#include <string.h>

static int response_code = 200;
static char content_type[32] = "text/html";
static char redirect_location[256];

void print_headers() {
  printf("Status: ");
  
  switch(response_code) {
    case 200:
    printf("200 OK\n");
    break;
    
    case 302:
    printf("302 Found\n");
    printf("Location: %s\n", redirect_location);
    break;
    
    case 403:
    printf("403 Forbidden\n");
    
    case 404:
    printf("404 Not Found\n");
  }
  
  printf("Content-type: %s\n", content_type);
  printf("\n");
}

void redirect_to(const char* url) {
  strcpy(redirect_location, url);
  response_code = 302;
}

void set_response_code(int code) {
  response_code = code;
}

void set_content_type(const char* type) {
  strcpy(content_type, type);
}

void print_404() {
  set_response_code(404);
  print_headers();
  printf("404 Not Found");
}
