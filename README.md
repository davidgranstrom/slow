# slow

A small command line utility that slows down text output.

## Building

```
mkdir build && cd build
cmake ..
make
```

## Usage

```
usage: slow [-djl] [file]

example: ls | slow

options:
-d --delay    [default 15] Delay time in milliseconds
-j --jitter   [default 0] Apply random delay jitter
-l --lines    Display line by line output instead of char by char
-h --help     Show this help
```
