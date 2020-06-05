# build examples using libshttpd.a
#
# revised by:  350137278@qq.com
# last update: 2020-06-05
###############################################################
PREFIX=.

# Default build config for Linux
LIBS?=   -ldl -lpthread

WIN32_LIBS= user32.lib shell32.lib ws2_32.lib advapi32.lib ..\src\shttpd.lib

CL_FLAGS= /MD /DNDEBUG /nologo /Zi /I ..\src


all:
	@echo "-- Build examples usage:"
	@echo '   # make (linux|msvc)'
	@echo '   # LIBS="-ldl -lpthread" CFLAGS="-DNO_SSL" make linux'
	@echo '   # CFLAGS="-DNO_SSL" make linux'
	@echo '   # make linux'

../src/libshttpd.a:
	cd ../src && $(MAKE) linux


linux: ../src/libshttpd.a
	$(CC) $(CFLAGS) example.c -I ../src  ../src/libshttpd.a $(LIBS) -o example


msvc:
	cl $(CL_FLAGS) example.c $(WIN32_LIBS)
	rc dialog.rc
	cl $(CL_FLAGS) example_win32_dialog_app.c dialog.res $(WIN32_LIBS)

clean:
	rm -f ./example