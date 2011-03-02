
#
#  Flags and stuffs.
#
CFLAGS=-ggdb -Wall -Werror `pkg-config fuse --cflags` -I.
LDFLAGS=`pkg-config fuse --libs`


#
#  By default make our filesystem.
#
all: link redisfs


#
#  Clean.
#
clean:
	rm redisfs *.o || true
	rm -f fmacros.h || true
	rm -f hiredis.c || true
	rm -f hiredis.h || true
	rm -f sds.c || true
	rm -f sds.h  || true
	rm -f net.c || true
	rm -f net.h  || true
	rm -f util.h  || true

#
#  Install the binary
#
install:
	mkdir -p $(prefix)/sbin
	cp ./redisfs $(prefix)/sbin/

#
#  Indent & tidy.
#
tidy:
	indent --no-space-after-function-call-names --no-space-after-casts --braces-after-if-line --no-tabs --indent-level 4 -bli0 -cdb -sc redisfs.c


#
#  The filesystem
#
redisfs: pathutil.o redisfs.o hiredis.o sds.o net.o

link:
	ln -sf ../hiredis/fmacros.h .
	ln -sf ../hiredis/hiredis.c .
	ln -sf ../hiredis/hiredis.h .
	ln -sf ../hiredis/sds.c .
	ln -sf ../hiredis/sds.h .
	ln -sf ../hiredis/net.c .
	ln -sf ../hiredis/net.h .
	ln -sf ../hiredis/util.h .


