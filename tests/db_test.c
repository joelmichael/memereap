#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "lib/db.h"

void test_escape_str() {
  const char* str = "foo'bar\\;\"";
  char escaped[32];
  
  escape_str(escaped, str);
  assert(strcmp(escaped, "foo\\'bar\\\\;\\\"") == 0);
}

void test_select_str() {
  char buf[8];
  
  assert(select_str(buf, "select 'foo'") == 0);
  assert(strcmp(buf, "foo") == 0);
  
  assert(select_str(buf, "bad sql") == 2);
}

void test_mysql_time() {
  struct tm tm;
  char str[20];
  
  parse_mysql_time(&tm, "2009-05-20 19:45:06");
  
  assert(tm.tm_year == 2009 - 1900);
  assert(tm.tm_mon == 5 - 1);
  assert(tm.tm_mday == 20);
  assert(tm.tm_hour == 19);
  assert(tm.tm_min == 45);
  assert(tm.tm_sec == 6);
  
  make_mysql_time(str, &tm);
  
  assert(strcmp(str, "2009-05-20 19:45:06") == 0);
}

int main(int argc, char** argv) {
  connect_db("memereap_test");
  
  test_escape_str();
  test_select_str();
  test_mysql_time();
  
  mysql_close(&mysql);
  
  return EXIT_SUCCESS;
}
