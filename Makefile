#
#  Simple makefile for redisfs
#


#
#  Used for "make release".
#
DIST_PREFIX = ${TMP}
VERSION     = 0.3
BASE        = redisfs


all:
	cd ./src     && make link && make


clean:
	cd ./src     && make clean || true
	cd ./tests   && make clean || true


test:
	cd ./tests    && make link && make
	./tests/tests

tidy:
	cd ./src && make tidy clean

install: all
	cd ./src && make install


refresh:
	rm -rf ./hiredis/
	git clone https://github.com/antirez/hiredis.git


#
#  Make a new release tarball, and make a GPG signature.
#
release: tidy clean
	rm -rf $(DIST_PREFIX)/$(BASE)-$(VERSION)
	rm -f $(DIST_PREFIX)/$(BASE)-$(VERSION).tar.gz
	cp -R . $(DIST_PREFIX)/$(BASE)-$(VERSION)
	rm -rf $(DIST_PREFIX)/$(BASE)-$(VERSION)/debian
	find  $(DIST_PREFIX)/$(BASE)-$(VERSION) -name ".hg*" -print | xargs rm -rf
	find  $(DIST_PREFIX)/$(BASE)-$(VERSION) -name ".release" -print | xargs rm -rf
	cd $(DIST_PREFIX) && tar -cvf $(DIST_PREFIX)/$(BASE)-$(VERSION).tar $(BASE)-$(VERSION)/
	gzip $(DIST_PREFIX)/$(BASE)-$(VERSION).tar
	mv $(DIST_PREFIX)/$(BASE)-$(VERSION).tar.gz .
	rm -rf $(DIST_PREFIX)/$(BASE)-$(VERSION)
	gpg --armour --detach-sign $(BASE)-$(VERSION).tar.gz
	echo $(VERSION) > .version