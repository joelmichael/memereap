CFLAGS = -std=c99 -pedantic -g -I.
LDFLAGS = -L/opt/local/lib/mysql5/mysql -lmysqlclient -L/opt/local/lib -lfcgi

all:	public/memereap.fcgi

public/memereap.fcgi:	scythe/fastcgi.o scythe/db.o scythe/mysql.o scythe/response.o\
			scythe/request.o scythe/template.o scythe/routes.o\
			config/routes.o\
			models/user.o\
			controllers/user_controller.o\
			views/user_views.o
			cc $(LDFLAGS) -o $@ $^

scythe/mysql.o:		scythe/mysql.c
			cc $(CFLAGS) -I/opt/local/include/mysql5/mysql -c -o $@ $<

scythe/fastcgi.o:	scythe/fastcgi.c
			cc $(CFLAGS) -I/opt/local/include -c -o $@ $<

config/routes.o:	config/routes.c
			cc $(CFLAGS) -c -o $@ $<
												
check:	tests/bin/db_test tests/bin/user_test tests/bin/route_test reload
	tests/bin/db_test
	tests/bin/user_test
	tests/bin/route_test

tests/bin/db_test:	tests/db_test.o scythe/db.o scythe/mysql.o
			cc $(LDFLAGS) -o $@ $^

tests/bin/user_test:	tests/user_test.o scythe/db.o scythe/mysql.o models/user.o
			cc $(LDFLAGS) -o $@ $^

tests/bin/route_test:	tests/route_test.o scythe/routes.o scythe/request.o scythe/response.o
			cc $(LDFLAGS) -o $@ $^

reload:		
	mysql -u root memereap_test < db/memereap_test.sql
		
dump:	
	mysqldump -u root memereap_test > db/memereap_test.sql
			
clean:	
	rm -f public/memereap.fcgi tests/bin/* scythe/*.o config/*.o
	rm -f models/*.o controllers/*.o views/*.o tests/*.o
