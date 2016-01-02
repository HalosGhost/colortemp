PREFIX ?= /usr/local
ZSHDIR ?= $(DESTDIR)$(PREFIX)/share/zsh
BINDIR ?= $(DESTDIR)$(PREFIX)/bin

.PHONY: install uninstall

install:
	@install -Dm755 src/colortempd $(BINDIR)/colortempd
	@install -Dm644 cmp/zsh        $(ZSHDIR)/site-functions/_colortempd

uninstall:
	@rm -f $(BINDIR)/colortempd
	@rm -f $(ZSHDIR)/site-functions/_colortempd
