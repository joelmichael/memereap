#ifndef request_h
#define request_h

#define VARNAME_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

void make_cookie_list();

int get_cookie(char* buf, const char* name);

void route_request();

void process_request();

int add_param(char* name, char* value);

int get_param(char* buf, const char* name);

void free_param_lists();

#endif
