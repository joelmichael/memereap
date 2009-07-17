#ifndef request_h
#define request_h

void free_cookie_list();

void make_cookie_list();

char* get_cookie(const char* name);

void route_request();

#endif
