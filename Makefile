CFLAGS = -I. -I/opt/local/include/mysql5/mysql -std=c99 -pedantic -g
LDFLAGS = -L/opt/local/lib/mysql5/mysql -lmysqlclient

all:	public/memereap.cgi


public/memereap.cgi:	lib/cgi.o lib/db.o lib/model.o lib/response.o lib/routes.o lib/template.o\
			models/user.o\
			controllers/user_controller.o
			cc $(LDFLAGS) -o $@ $^

check:	tests/bin/db_test tests/bin/user_test reload
	tests/bin/db_test
	tests/bin/user_test

tests/bin/db_test:	tests/db_test.o lib/db.o
			cc $(LDFLAGS) -o $@ $^

tests/bin/user_test:	tests/user_test.o lib/db.o lib/model.o models/user.o
			cc $(LDFLAGS) -o $@ $^
				
reload:		
	mysql -u root memereap_test < db/memereap_test.sql
		
dump:	
	mysqldump -u root memereap_test > db/memereap_test.sql
			
clean:	
	rm -f public/memereap.cgi tests/bin/* lib/*.o models/*.o controllers/*.o tests/*.o

