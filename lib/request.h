#ifndef request_h
#define request_h

#define VARNAME_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

void process_request();

void make_cookie_list();

char* get_cookie(char* name);

void route_request();

int set_param(char* name, char* value);

char* get_param(char* name);

void free_params_and_cookies();

#endif
