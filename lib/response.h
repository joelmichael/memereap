#ifndef response_h
#define response_h

#define DEFAULT_CONTENT_TYPE "text/plain"

void print_headers();

void redirect_to(const char* url);

void set_response_code(int code);

void set_content_type(const char* type);

void print_404();

#endif