CC = gcc 
CFLAGS = -g -std=c11 -pedantic -Wall -Werror -Wextra -Winline -O2
LDFLAGS = -lm 
ZIP_NAME = xkrizja00.zip

all: primes primes-i steg-decode

primes: primes.o error.o
	$(CC) $(CFLAGS) -o primes primes.o error.o $(LDFLAGS)

primes.o: primes.c bitset.h eratosthenes.h
	$(CC) $(CFLAGS) -c -o $@ primes.c

primes-i: primes-i.o  error.o
	$(CC) $(CFLAGS) -DUSE_INLINE -o primes-i primes.o error.o  $(LDFLAGS)

primes-i.o: primes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

steg-decode: steg-decode.o ppm.o error.o 
	$(CC) $(CFLAGS) -o steg-decode steg-decode.o ppm.o error.o   $(LDFLAGS)

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

ppm.o: ppm.c ppm.h
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: primes primes-i steg-decode
	bash -c "ulimit -s 10240 && ./primes"
	bash -c "ulimit -s 10240 && ./primes-i"
	bash -c "./steg-decode du1-obrazek.ppm"


clean:
	rm -f *.o primes primes-i steg-decode $(ZIP_NAME)

xkrizja00.zip: *.c *.h *.ppm Makefile
	zip $@ $^
	
