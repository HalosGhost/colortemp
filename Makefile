PROGNM =  colortempd
PREFIX ?= /usr/local
ZSHDIR ?= $(DESTDIR)$(PREFIX)/share/zsh
BINDIR ?= $(DESTDIR)$(PREFIX)/bin
MKDIR  ?= mkdir -p

.PHONY: all clean gen clang-analyze cov-build simple install uninstall

all: dist
	@tup upd

clean:
	@rm -rf -- dist cov-int $(PROGNM).tgz make.sh ./src/*.plist

dist:
	@$(MKDIR) ./dist

gen: clean
	@tup generate make.sh

cov-build: gen dist
	@cov-build --dir cov-int ./make.sh
	@tar czvf $(PROGNM).tgz cov-int

clang-analyze:
	@(pushd ./src; clang-check -analyze ./*.c)

simple: gen dist
	@./make.sh

install:
	@install -Dm755 dist/$(PROGNM) $(BINDIR)/$(PROGNM)
	@install -Dm644 dist/zsh       $(ZSHDIR)/site-functions/_$(PROGNM)

uninstall:
	@rm -f $(BINDIR)/$(PROGNM)
	@rm -f $(ZSHDIR)/site-functions/_$(PROGNM)
