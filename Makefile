CC=g++
CFLAGS = -c -Wall
problem1.exe: problem1.o matrix.o
	$(CC) problem1.o matrix.o -o problem1.exe
problem1.o: problem1.cpp matrix.hpp
	$(CC) $(CFLAGS) problem1.cpp -o problem1.o
matrix.o: matrix.cpp matrix.hpp
	$(CC) $(CFLAGS) matrix.cpp -o matrix.o
clean:
	rm -rf *.o
	rm -rf *.exe