CC = g++

all:
	$(CC) main.cpp optimization.cpp -g3 -o main

clean:
	rm main