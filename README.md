# Benoes' utilities: Configuration Library
A pure C library meant for parsing simple config files with ease.

## Features
Currently the library supports the following option (field) types:
* Integer
* Floating point number
* RGB color
* RGBA color

Comments in the configurationfiles are not yet supported.

For an example configuration check out `example_config.conf`.

The code has plenty of comments, so it _should_ be mostly understandable even for beginner C programmers.

## Compilation
### Prerequisites
* CMake
* Ninja (If you wish to use the given compile script)

### Compilation process
* Clone the repo.
* Run `compile.sh` (after using `chmod +x' on it)
\
_It is assumed that you know how to deal with CMake if you do not use Ninja._

### Running
If you want to run the test program given you may do so by using `run.sh` or by running it with a separate command. Do make sure, however, that the directory from which you are running it contains `example_config.conf` (i.e run it from the repo's main directory).

## Planned features
* Support for comments
* Support for strings
