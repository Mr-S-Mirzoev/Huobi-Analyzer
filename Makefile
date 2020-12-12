all: huobi-analyzer

huobi-analyzer: main.o update.o snapshot.o
	g++ main.o update.o snapshot.o -o huobi-analyzer

main.o: main.cpp
	g++ -c main.cpp

snapshot.o: update.o snapshot.cpp
	g++ -c snapshot.cpp

update.o: update.cpp
	g++ -c update.cpp

clean:
	rm -rf *.o huobi-analyzer