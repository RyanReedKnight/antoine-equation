CC = g++
CFLAGS = -I include

antoine-eos: main.o AntoineEOS.o get_x.o
	$(CC) $(CFLAGS) -o antoine-eos main.o AntoineEOS.o get_x.o

main.o: src/main.cpp include/AntoineEOS.hpp include/get_x.hpp
	$(CC) $(CFLAGS) -c src/main.cpp

AntoineEOS.o: src/AntoineEOS.cpp include/AntoineEOS.hpp
	$(CC) $(CFLAGS) -c src/AntoineEOS.cpp

get_x.o: src/get_x.cpp include/get_x.hpp
	$(CC) $(CFLAGS) -c src/get_x.cpp
