PROGNM =  colortempd
PREFIX ?= /usr/local
ZSHDIR ?= $(DESTDIR)$(PREFIX)/share/zsh
BINDIR ?= $(DESTDIR)$(PREFIX)/bin
MKDIR  ?= mkdir -p

include Makerules

.PHONY: all complexity clean clang-analyze cov-build install uninstall

all: dist
	$(CC) $(CFLAGS) $(LDFLAGS) ./src/*.c -o ./dist/$(PROGNM)

clean:
	@rm -rf -- dist cov-int $(PROGNM).tgz make.sh ./src/*.plist

complexity:
	complexity -h ./src/*

dist:
	@$(MKDIR) ./dist

cov-build: gen dist
	@cov-build --dir cov-int ./make.sh
	@tar czvf $(PROGNM).tgz cov-int

clang-analyze:
	@(pushd ./src; clang-check -analyze ./*.c)

install:
	@install -Dm755 dist/$(PROGNM) $(BINDIR)/$(PROGNM)
	@install -Dm644 dist/zsh       $(ZSHDIR)/site-functions/_$(PROGNM)

uninstall:
	@rm -f $(BINDIR)/$(PROGNM)
	@rm -f $(ZSHDIR)/site-functions/_$(PROGNM)
