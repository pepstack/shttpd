# SHTTPD

SHTTPD is small, fast and easy to use web server written in C which supports CGI, SSL, Digest Authorization.

The unique feature of SHTTPD is it could be embed into an existing C/C++ application.

Embedded API is very clean and simple.

SHTTPD has small memory footprint.

Use it when other web servers like Apache are too heavy for your tasks.

It originated from:

    http://shttpd.sourceforge.net

Chinese reference:

    https://blog.csdn.net/dijkstar/article/details/81981851


## Build shttpd on Linux

    - gcc-4.4.7
    
    - rhel6.4


### Build libshttpd.a static lib on Linux without SSL

    $ cd shttpd/src/

    $ LIBS="-ldl -lpthread" CFLAGS="-DNO_SSL" make linux

### Build libshttpd.a static lib on Linux with SSL

    $ cd shttpd/src/

    $ LIBS="-ldl -lpthread" make linux

### Build libshttpd.so on Linux with SSL

    $ cd shttpd/src/

    $ LIBS="-ldl -lpthread" make linuxso

## Build example on Linux

example is an embeded http server in C.

    $ cd shttpd/examples/
 
    $ CFLAGS="-DNO_SSL" make linux

## Run example (default port is 8080)

    $ example

or:

    $ example -ports 8080

## Build on Windows with vs2015

    Visual Studio 2015 Open:
    
    ./shttpd/msvc/shttpd.sln

    Build All.