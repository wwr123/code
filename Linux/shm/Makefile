cli=client
ser=server
cc=gcc
cliSrc=commont.c client.c
serSrc=commont.c server.c

.PHONY:all
all:$(cli) $(ser)
$(ser):$(serSrc)
	$(cc) -o $@ $^
$(cli):$(cliSrc)
	$(cc) -o $@ $^

.PHONY:clean
clean:
	rm -f $(cli) $(ser)
