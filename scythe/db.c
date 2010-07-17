#include "db.h"

#include <fcgi_stdio.h>
#include <string.h>
#include <stdlib.h>

int insert_model(void* model, const char* stmt) {
  struct model* m = model;
  
  if(query(stmt) == 0) {
    m->id_ul = last_insert_id();
    sprintf(m->id, "%lu", m->id_ul);
    return 0;
  }
  else {
    return -1;
  }
}

void set_model_id(void* model, const char* id) {  
  struct model* m = model;
  
  strcpy(m->id, id);
  m->id_ul = strtoul(id, NULL, 10);
}
