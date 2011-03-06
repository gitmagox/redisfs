
#
#  Flags and stuffs.
#
CFLAGS=-ggdb -Wall -Werror  -I.
LDFLAGS=


#
#  By default make our filesystem.
#
all: link tests


#
#  Clean.
#
clean:
	rm tests *.o     || true
	rm -f pathutil.h || true
	rm -f pathutil.c || true
	rm -f fastlz.c   || true
	rm -f fastlz.h   || true

#
#  Symlink
#
link: 
	ln -sf ../src/pathutil.c .
	ln -sf ../src/pathutil.h .
	ln -sf ../fastlz/fastlz.h .
	ln -sf ../fastlz/fastlz.c .

#
#  Test code
#
tests: pathutil.o AllTests.o CuTest.o pathutil_test.o fastlz_test.o fastlz.o
	gcc -o tests pathutil.o AllTests.o CuTest.o  pathutil_test.o fastlz_test.o fastlz.o
