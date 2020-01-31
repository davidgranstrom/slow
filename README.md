# slow

Like `cat`, but slower.

## Installation

```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
make install
```

## Usage

```
usage: slow [file] [-djlh]

example: ls | slow

options:
-d --delay    [default 15] Delay time in milliseconds
-j --jitter   [default 0] Apply random delay jitter
-l --line     Display line by line output instead of char by char
-h --help     Show this help
```
