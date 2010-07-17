#ifndef request_h
#define request_h

#define VARNAME_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

void process_request();

void set_cookies();

char* cookie(char* name);

void route_request();

int set_param(char* name, char* value);

char* param(char* name);

void free_params();

#endif
