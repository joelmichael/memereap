CFLAGS = -I. -I/opt/local/include/mysql5/mysql -std=c99 -pedantic -g
LDFLAGS = -L/opt/local/lib/mysql5/mysql -lmysqlclient

all:	check public/memereap.cgi


public/memereap.cgi:	lib/cgi.c
			cc $(CFLAGS) $(LDFLAGS) -o $@ $^

check:	tests/bin/db_test tests/bin/user_test reload
	tests/bin/db_test
	tests/bin/user_test

tests/bin/db_test:	tests/db_test.c
			cc $(CFLAGS) $(LDFLAGS) -o $@ $^

tests/bin/user_test:	tests/user_test.c
			cc $(CFLAGS) $(LDFLAGS) -o $@ $^
				
reload:		
	mysql -u root memereap_test < db/memereap_test.sql
		
dump:		
	mysqldump -u root memereap_test > db/memereap_test.sql
			
clean:	
	rm -rf public/memereap.cgi* tests/bin/*
