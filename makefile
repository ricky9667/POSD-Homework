.PHONY: dirs clean stat

SRC = src/point.h src/two_dimensional_vector.h src/triangle.h src/rectangle.h src/circle.h src/shape.h src/compound_shape.h src/iterator/null_iterator.h

TEST = test/ut_point.h test/ut_two_dimensional_vector.h test/ut_triangle.h test/ut_rectangle.h test/ut_circle.h test/ut_shape.h test/ut_compound_shape.h test/iterator/ut_null_iterator.h

all: dirs ut_all

test: dirs ut_all
	bin/ut_all

ut_all: test/ut_main.cpp $(TEST) $(SRC)
	g++ -std=c++17 -Wfatal-errors -Wall test/ut_main.cpp -o bin/ut_all -lgtest -lpthread

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/* obj/*

stat:
	wc -l src/* test/*.h test/*.cpp
