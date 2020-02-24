all : 256eq

install:
	mkdir -p ${PREFIX}/${DESTDIR}/bin
	cp 256eq ${PREFIX}/${DESTDIR}/bin
