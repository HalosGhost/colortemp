PREFIX ?= /usr/local
ZSHDIR ?= $(DESTDIR)$(PREFIX)/share/zsh
BINDIR ?= $(DESTDIR)$(PREFIX)/bin

.PHONY: all clean install uninstall

all:
	@mkdir -p dist
	@tup upd

clean:
	@rm -r dist

install:
	@install -Dm755 dist/colortempd $(BINDIR)/colortempd
	@install -Dm644 dist/zsh        $(ZSHDIR)/site-functions/_colortempd

uninstall:
	@rm -f $(BINDIR)/colortempd
	@rm -f $(ZSHDIR)/site-functions/_colortempd
