
#
#  Flags and stuffs.
#
CFLAGS=-Wall -g -Werror -O0  `pkg-config fuse3 --cflags` -I. -DVERSION=$(VERSION)
LDFLAGS=`pkg-config fuse3 --libs`
LDLIBS := $(shell pkg-config fuse3 --libs)

#
#  Version is only set if building from the top-level directory
#
ifndef VERSION
VERSION=\"unknown\"
endif

#
#  By default make our filesystem.
#
all: link redisfs redisfs-snapshot


#
#  Clean.
#
clean:
	rm redisfs redisfs-snapshot *.o || true
	rm -f fmacros.h || true
	rm -f hiredis.c || true
	rm -f hiredis.h || true
	rm -f read.c || true
	rm -f read.h || true
	rm -f sds.c || true
	rm -f sds.h  || true
	rm -f net.c || true
	rm -f net.h  || true
	rm -f util.h  || true
	rm -f sdsalloc.h || true
	rm -f redisLock.h || true

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
	indent --no-space-after-function-call-names --no-space-after-casts --braces-after-if-line --no-tabs --indent-level 4 -bli0 -cdb -sc redisfs-snapshot.c


#
#  The filesystem
#
redisfs: pathutil.o redisfs.o  hiredis.o sds.o net.o read.o


#
#  The filesystem snapshot utility
#
redisfs-snapshot: pathutil.o redisfs-snapshot.o  hiredis.o sds.o net.o read.o


#
#  Link our C-client library into place
#
link:
	ln -sf ../hiredis/fmacros.h .
	ln -sf ../hiredis/hiredis.c .
	ln -sf ../hiredis/hiredis.h .
	ln -sf ../hiredis/read.c .
	ln -sf ../hiredis/read.h .
	ln -sf ../hiredis/sdsalloc.h .
	ln -sf ../hiredis/sds.c .
	ln -sf ../hiredis/sds.h .
	ln -sf ../hiredis/net.c .
	ln -sf ../hiredis/net.h .
	ln -sf ../hiredis/util.h .
	ln -sf ../redis_lock/redisLock.h

