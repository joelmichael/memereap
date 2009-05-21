mysqlheaders = /opt/local/include/mysql5/mysql
mysqllibs = /opt/local/lib/mysql5/mysql

CFLAGS = -I. -std=c99 -pedantic -g

all:	check
	

lib/db.o:	lib/db.c
		cc $(CFLAGS) -I$(mysqlheaders) -c -o $@ $^

models/user.o:	models/user.c
		cc $(CFLAGS) -I$(mysqlheaders) -c -o $@ $^

check:		tests/bin/db_test tests/bin/user_test reload
		tests/bin/db_test
		tests/bin/user_test

reload:		
		mysql -u root memereap_test < db/memereap_test.sql
		
dump:		
		mysqldump -u root memereap_test > db/memereap_test.sql

tests/bin/db_test:	tests/db_test.o lib/db.o
			cc $(LDFLAGS) -L$(mysqllibs) -lmysqlclient -o $@ $^
					
tests/bin/user_test:	tests/user_test.o models/user.o lib/db.o
			cc $(LDFLAGS) -L$(mysqllibs) -lmysqlclient -o $@ $^

tests/db_test.o:	tests/db_test.c
			cc $(CFLAGS) -I$(mysqlheaders) -c -o $@ $^
			
tests/user_test.o:	tests/user_test.c
			cc $(CFLAGS) -I$(mysqlheaders) -c -o $@ $^
			
clean:	
	rm -f bin/* lib/*.o models/*.o tests/*.o tests/bin/*
