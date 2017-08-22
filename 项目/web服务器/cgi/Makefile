ROOT_PATH=$(shell pwd)
INCLUDE_PATH=-I${ROOT_PATH}/mysql/include
LIB_PATH=-L${ROOT_PATH}/mysql/lib
LIB=-lmysqlclient
cgi_math:cgi_math.cpp mysql_op.cpp 
	g++ -o $@ $^  ${INCLUDE_PATH} ${LIB_PATH} ${LIB}

.PHONY:clean
clean:
	rm -f cgi_math
.PHONY:output 
output:
	cp cgi_math ..
	cp -rf mysql/lib ..
