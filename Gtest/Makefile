#.PHONY:all
#all:hello test
#
#hello:hello.cpp
#	g++ -o $@ $^
#test:test.cpp hello.cpp
#	g++ -o $@ $^ -I/home/wwr/third_part/include -L/home/wwr/third_part/lib -lgtest -lgtest_main -lpthread

hello:hello.cpp
	g++ -o $@ $^ -I/home/wwr/third_part/include -L/home/wwr/third_part/lib -lgtest  -lpthread
.PHONY:clean
clean:
	rm -f hello



