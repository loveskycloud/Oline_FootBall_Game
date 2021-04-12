all:
	g++ -I ./include ./src/common/* ./src/server/udp.c ./server.c -o start -lcurses -pthread 
	mv ./start ./bin
clean:
	rm ./bin/*

