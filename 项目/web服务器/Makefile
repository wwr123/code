.PHONY:all
all:httpd cgi

httpd:httpd.o main.o 
	g++ -o $@ $^ -lpthread
%.o:%.cpp
	g++ -c $<
.PHONY:cgi
cgi:
	cd cgi;make;make output;cd -

.PHONY:clean
clean:
	rm -rf httpd *.o output cgi_math;cd cgi;make clean;cd -

.PHONY:output
output:all
	mkdir output
	cp httpd output/
	cp -rf log output/
	cp -rf conf output/
	cp -rf wwwroot output/
	cp -rf http_ctl.sh output/
	mkdir -p output/wwwroot/cgi_bin
	cp -f cgi_math output/wwwroot/cgi_bin/
	cp -rf lib output/wwwroot/cgi_bin/
