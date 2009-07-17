#ifndef request_h
#define request_h

void free_cookie_list();

void make_cookie_list();

int get_cookie(char* buf, const char* name);

void route_request();

void process_request();

#endif
