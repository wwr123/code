.PHONY:all 
all: select_tcp client

select_tcp:select_tcp.c
	gcc -o $@ $^
client:client.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f select_tcp client

