#!/usr/bin/env python3

from subprocess import Popen
from socket import *
from time import sleep

tcp = Popen(
    ['./cqotdd-tcp', 'This message should be wholly displayed if TCP works.'])
udp = Popen([
    './cqotdd-udp',
    (s := 'This message should be visible twice if UDP works.\n'
     'If this message is visible twice, we are a DDoS amplifier.\n'
     'If there is anything other than spaces after this message, we have a security problem.'
     ) + (511 - len(s)) * ' '
])

try:
    sleep(0.25)

    sock = socket(AF_INET, SOCK_STREAM)
    sock.connect(('127.0.0.1', 17))
    print(sock.recv(512).decode('UTF-8'), end='')
    sock.close()

    sock = socket(AF_INET, SOCK_DGRAM)
    sock.sendto(b'\0' * 51, ('127.0.0.1', 17))
    print(sock.recv(512).decode('UTF-8'), end='')
    sock.close()

    sock = socket(AF_INET, SOCK_DGRAM)
    sock.sendto(b'\0' * 600, ('127.0.0.1', 17))
    print(sock.recv(600).decode('UTF-8'), end='')
    sock.close()
finally:
    tcp.kill()
    udp.kill()
