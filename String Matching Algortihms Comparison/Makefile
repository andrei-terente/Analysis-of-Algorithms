CC = g++ -std=c++11
CFLAGS = -O2

build: algo.o

run:
	./tester

build_best: algo.o tester.o
	$(CC) algo.o tester.o -o tester $(CFLAGS)

build_snd_best: algo2.o tester.o
	$(CC) algo2.o tester.o -o tester $(CFLAGS)

build_naive: algo_naive.o tester.o
	$(CC) algo_naive.o tester.o -o tester $(CFLAGS)

algo_naive.o: algo_naive.cpp
	$(CC) algo_naive.cpp -c $(CFLAGS)

algo.o: algo.cpp
	$(CC) algo.cpp -c $(CFLAGS)

algo2.o: algo2.cpp
	$(CC) algo2.cpp -c $(CFLAGS)

tester.o: tester.cpp
	$(CC) tester.cpp -c $(CFLAGS)

.PHONY: clean

clean:
	 rm -rf *.o tester
