CC ?= cc
CFLAGS ?= -O3 -Wall -Wextra -pedantic -ansi
PREFIX ?= /usr/local/bin

all: cqotdd-tcp cqotdd-udp

cqotdd-%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f cqotdd-tcp cqotdd-udp

install: all
	cp -f cqotdd-tcp $(PREFIX)/cqotdd-tcp
	cp -f cqotdd-udp $(PREFIX)/cqotdd-udp
	cp -f cqotdd-tcp.service /etc/systemd/system/cqotdd-tcp.service
	cp -f cqotdd-udp.service /etc/systemd/system/cqotdd-udp.service

test: all
	@python3 test.py

.PHONY: all clean install test
