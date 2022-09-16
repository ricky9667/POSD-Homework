.PHONY: dirs clean stat

SRC = src/point.h src/two_dimensional_vector.h src/triangle.h

TEST = test/ut_point.h test/ut_two_dimensional_vector.h test/ut_triangle.h

all: dirs ut_all

ut_all: test/ut_main.cpp $(TEST) $(SRC)
	g++ -std=c++11 -Wfatal-errors -Wall test/ut_main.cpp -o bin/ut_all -lgtest -lpthread

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/* obj/*

stat:
	wc -l src/* test/*.h test/*.cpp
