PREFIX ?= /usr/local
BINDIR ?= $(DESTDIR)$(PREFIX)/bin

.PHONY: install uninstall

install:
	@install -Dm755 src/colortempd $(BINDIR)/colortempd

uninstall:
	@rm -f $(BINDIR)/colortempd
