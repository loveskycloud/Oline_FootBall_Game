PORT=
P=
IP=
all:
	g++ -I ./include ./src/* ./server.c -o start -lcurses -pthread 
	mv ./start ./bin
run:
	./bin/start ${P} ${IP} ${PORT}
clean:
	rm ./bin/*

