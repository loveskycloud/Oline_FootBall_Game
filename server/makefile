all:
	g++ -I ./include ./src/* ./server.c -o start -lcurses -pthread -D _D
	mv ./start ./bin
run:
	./bin/start
clean:
	rm ./bin/*

