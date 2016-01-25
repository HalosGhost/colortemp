PREFIX ?= /usr/local
ZSHDIR ?= $(DESTDIR)$(PREFIX)/share/zsh
BINDIR ?= $(DESTDIR)$(PREFIX)/bin

.PHONY: all clean cov-build install uninstall

all:
	@mkdir -p dist
	@tup upd

clean:
	@rm -rf -- dist cov-int colortemp.tgz make.sh

cov-build: clean
	@tup generate make.sh
	@mkdir -p ./dist
	@cov-build --dir cov-int ./make.sh
	@tar czvf colortemp.tgz cov-int

install:
	@install -Dm755 dist/colortempd $(BINDIR)/colortempd
	@install -Dm644 dist/zsh        $(ZSHDIR)/site-functions/_colortempd

uninstall:
	@rm -f $(BINDIR)/colortempd
	@rm -f $(ZSHDIR)/site-functions/_colortempd
