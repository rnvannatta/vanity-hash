vpath %.h include src
.PHONY : clean

a.out : test.c vhash.h wyhash.h pcg_variants.h
	$(CC) $< -o $@ -lm -Iinclude -std=c99 -Wall
include/vhash.h : vhash-decl.h wyhash.h pcg_variants.h vhash-impl.h 
	cat $^ >$@
clean:
	-rm -f a.out
