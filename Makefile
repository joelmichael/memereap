CFLAGS = -std=c99 -pedantic -g -I.
MYSQL_LDFLAGS = -L/opt/local/lib/mysql5/mysql -lmysqlclient
FCGI_LDFLAGS = -L/opt/local/lib -lfcgi

all:	public/memereap.fcgi

public/memereap.fcgi:	lib/fcgi.o lib/db.o lib/response.o lib/routes.o lib/template.o\
			models/user.o\
			controllers/user_controller.o\
			views/user_views.o
			cc $(MYSQL_LDFLAGS) $(FCGI_LDFLAGS) -o $@ $^
						
check:	tests/bin/db_test tests/bin/user_test reload
	tests/bin/db_test
	tests/bin/user_test

tests/bin/db_test:	tests/db_test.o lib/db.o
			cc $(MYSQL_LDFLAGS) -o $@ $^

tests/bin/user_test:	tests/user_test.o lib/db.o models/user.o
			cc $(MYSQL_LDFLAGS) -o $@ $^
				

lib/db.o:	lib/mysql.c
		cc $(CFLAGS) -I/opt/local/include/mysql5/mysql -c -o $@ $<

lib/fcgi.o:	lib/fcgi.c
		cc $(CFLAGS) -I/opt/local/include -c -o $@ $<

reload:		
	mysql -u root memereap_test < db/memereap_test.sql
		
dump:	
	mysqldump -u root memereap_test > db/memereap_test.sql
			
clean:	
	rm -f public/memereap.fcgi tests/bin/* lib/*.o models/*.o controllers/*.o views/*.o tests/*.o

