bin=sem
cc=gcc
src=common.c sem.c
$(bin):$(src)
	$(cc) -o $@ $^

.PHONY:clean
clean:
	rm -f $(bin)
