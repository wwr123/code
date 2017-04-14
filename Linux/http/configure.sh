#!/bin/bash


ROOT_PATH=$(pwd)
SRC=$(ls *.c | tr '\n' ' ')
OBJ=$(ls *.c | sed 's/\.c$/\.o/g' | tr '\n' ' ')
INCLUDE="-lpthread"
SERVER_NAME=httpd
cc=gcc

CGI_PATH=${ROOT_PATH}/cgi/
MATH_SRC=$(ls $CGI_PATH | grep 'math' | grep -E '.c$')
MATH_CGI_BIN=cgi_math

cat<<EOF >$CGI_PATH/Makefile
${MATH_CGI_BIN}:$MATH_SRC
	${cc} -o \$@ \$^
.PHONY:clean
clean:
	rm -f $MATH_CGI_BIN
.PHONY:output 
output:
	cp $MATH_CGI_BIN ..
EOF


cat <<EOF  >Makefile
.PHONY:all
all:${SERVER_NAME} cgi

${SERVER_NAME}:${OBJ}
	${cc} -o \$@ \$^ $INCLUDE
%.o:%.c
	$cc -c \$<
.PHONY:cgi
cgi:
	cd cgi;make;make output;cd -

.PHONY:clean
clean:
	rm -rf $SERVER_NAME *.o output $MATH_CGI_BIN;cd cgi;make clean;cd -

.PHONY:output
output:all
	mkdir output
	cp ${SERVER_NAME} output/
	cp -rf log output/
	cp -rf conf output/
	cp -rf wwwroot output/
	cp -r http_ctl.sh output/
	mkdir -p output/wwwroot/cgi_bin
	cp -f cgi_math output/wwwroot/cgi_bin/
EOF

