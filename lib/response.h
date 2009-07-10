#ifndef response_h
#define response_h

void print_headers();

void redirect_to(const char* url);

void set_response_code(int code);

void set_content_type(const char* type);

void print_404();

void add_cookie(const char* name, const char* value);

#endif
