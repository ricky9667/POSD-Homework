.PHONY: dirs clean stat

SRC = $(shell ls src/*.h src/**/*.h)
TEST = $(shell ls test/*.h test/**/*.h)
FACTORY = obj/dfs_iterator_factory.o obj/bfs_iterator_factory.o

all: dirs ut_all

test: dirs ut_all
	bin/ut_all

ut_all: test/ut_main.cpp $(TEST) $(SRC) $(FACTORY)
	g++ -std=c++11 -Wfatal-errors -Wall test/ut_main.cpp $(FACTORY) -o bin/ut_all -lgtest -lpthread

obj/dfs_iterator_factory.o: src/iterator/factory/dfs_iterator_factory.h src/iterator/factory/dfs_iterator_factory.cpp
	g++ -std=c++11 -c src/iterator/factory/dfs_iterator_factory.cpp -o obj/dfs_iterator_factory.o

obj/bfs_iterator_factory.o: src/iterator/factory/bfs_iterator_factory.h src/iterator/factory/bfs_iterator_factory.cpp
	g++ -std=c++11 -c src/iterator/factory/bfs_iterator_factory.cpp -o obj/bfs_iterator_factory.o

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/* obj/*

stat:
	wc -l src/* test/*.h test/*.cpp
