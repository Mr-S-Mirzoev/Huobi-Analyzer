all: benchmark

flags = -std=c++11 -lbenchmark -lpthread -O2

benchmark:
	g++ mybenchmark.cc $(flags) -o benchmark

clean:
	rm -rf *.o benchmark