# cqotdd

The C QOTD Deamon is an implementation of the QOTD protocol.

## Building

```sh
make -j2
```

## Installing on systemd Linux

```sh
sudo make install
```

## Installing without cloning

```sh
netsh -c -C 'sudo make install' pixelcmtd/cqotdd
```
