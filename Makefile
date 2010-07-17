CFLAGS = -std=c99 -pedantic -g -I.
LDFLAGS = -L/opt/local/lib/mysql5/mysql -lmysqlclient -L/opt/local/lib -lfcgi

all:	public/memereap.fcgi

public/memereap.fcgi:	lib/fastcgi.o lib/db.o lib/mysql.o lib/response.o lib/request.o lib/template.o lib/routes.o\
			config/routes.o\
			models/user.o\
			controllers/user_controller.o\
			views/user_views.o
			cc $(LDFLAGS) -o $@ $^
						
check:	tests/bin/db_test tests/bin/user_test reload
	tests/bin/db_test
	tests/bin/user_test

tests/bin/db_test:	tests/db_test.o lib/db.o lib/mysql.o
			cc $(LDFLAGS) -o $@ $^

tests/bin/user_test:	tests/user_test.o lib/db.o lib/mysql.o models/user.o
			cc $(LDFLAGS) -o $@ $^
				

lib/mysql.o:	lib/mysql.c
		cc $(CFLAGS) -I/opt/local/include/mysql5/mysql -c -o $@ $<

lib/fastcgi.o:	lib/fastcgi.c
		cc $(CFLAGS) -I/opt/local/include -c -o $@ $<
		
config/routes.o:	config/routes.c
			cc $(CFLAGS) -c -o $@ $<

reload:		
	mysql -u root memereap_test < db/memereap_test.sql
		
dump:	
	mysqldump -u root memereap_test > db/memereap_test.sql
			
clean:	
	rm -f public/memereap.fcgi tests/bin/* lib/*.o config/*.o models/*.o controllers/*.o views/*.o tests/*.o

