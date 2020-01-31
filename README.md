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

## License

```
slow - like cat but slower
Copyright (C) 2020 David Granström

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
```
