#!/usr/bin/python3

from subprocess import Popen
from socket import *

tcp = Popen(['./cqotdd-tcp', 'This is a test purely intended to test.'])
udp = Popen(['./cqotdd-udp', 'This is a test purely intended to test.'])

sock = socket(AF_INET, SOCK_STREAM)
sock.connect(('127.0.0.1', 17))
print(sock.recv(512).decode('UTF-8'), end='')
sock.close()

sock = socket(AF_INET, SOCK_DGRAM)
sock.sendto(b'\0'*22, ('127.0.0.1', 17))
print(sock.recv(512).decode('UTF-8'), end='')
sock.close()

tcp.kill()
udp.kill()
