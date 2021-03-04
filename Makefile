CC = gcc
USEMEMWATCH = -DMEMWATCH -DMW_STDIO 
CFLAGS = -Wall -g $(USEMEMWATCH)

all: bank

bank: bank.o account.o memwatch.o
	$(CC) $(CFLAGS) bank.o account.o memwatch.o -o bank 

bank.o: bank.c account.h memwatch.h
	$(CC) $(CFLAGS) -c bank.c  

account.o: account.c account.h memwatch.h
	$(CC) $(CFLAGS) -c account.c 

memwatch.o: memwatch.c memwatch.h
	$(CC) $(USEMEMWATCH) -c memwatch.c 

memwatch.h:
	ln -s /home/class_projects/memwatch-2.71/memwatch.h

memwatch.c:
	ln -s /home/class_projects/memwatch-2.71/memwatch.c

.PHONY: clean
clean:
	rm -f *.o bank memwatch.log

.PHONY: test
test: bank
	./bank acct.dat

