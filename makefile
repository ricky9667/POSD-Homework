.PHONY: dirs clean stat

SRC = src/point.h src/two_dimensional_vector.h src/triangle.h src/rectangle.h src/circle.h src/shape.h src/compound_shape.h src/bounding_box.h \
		src/iterator/null_iterator.h src/iterator/dfs_compound_iterator.h src/iterator/bfs_compound_iterator.h src/iterator/list_compound_iterator.h \
		src/iterator/factory/iterator_factory.h src/iterator/factory/dfs_iterator_factory.h src/iterator/factory/bfs_iterator_factory.h src/iterator/factory/list_iterator_factory.h \
		src/visitor/shape_visitor.h src/visitor/collision_detector.h \

TEST = test/ut_point.h test/ut_two_dimensional_vector.h test/ut_triangle.h test/ut_rectangle.h test/ut_circle.h test/ut_shape.h test/ut_compound_shape.h test/ut_bounding_box.h \
		test/iterator/ut_null_iterator.h test/iterator/ut_dfs_compound_iterator.h test/iterator/ut_bfs_compound_iterator.h test/iterator/ut_list_compound_iterator.h \
		test/visitor/ut_collision_detector.h \

FACTORY = obj/dfs_iterator_factory.o obj/bfs_iterator_factory.o

all: dirs ut_all

test: dirs ut_all
	bin/ut_all

ut_all: test/ut_main.cpp $(TEST) $(SRC) $(FACTORY)
	g++ -std=c++17 -Wfatal-errors -Wall test/ut_main.cpp $(FACTORY) -o bin/ut_all -lgtest -lpthread

obj/dfs_iterator_factory.o: src/iterator/factory/dfs_iterator_factory.h src/iterator/factory/dfs_iterator_factory.cpp
	g++ -std=c++17 -c src/iterator/factory/dfs_iterator_factory.cpp -o obj/dfs_iterator_factory.o

obj/bfs_iterator_factory.o: src/iterator/factory/bfs_iterator_factory.h src/iterator/factory/bfs_iterator_factory.cpp
	g++ -std=c++17 -c src/iterator/factory/bfs_iterator_factory.cpp -o obj/bfs_iterator_factory.o

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/* obj/*

stat:
	wc -l src/* test/*.h test/*.cpp
