CC=g++
CFLAGS=-Wall			 	\
	-std=c++11              \
	-Wshadow				\
	-Wnon-virtual-dtor		
GTKFLAGS=-DG_DISABLE_DEPRECATED 	 	\
			-DGDK_DISABLE_DEPRECATED 	\
			-DGDK_PIXBUF_DISABLE_DEPRECATED \
	        -DGTK_DISABLE_DEPRECATED
PVMFLAGS=-lpvm3
GTKCONF=`pkg-config gtk+-3.0 --cflags --libs`


run:all
	./main.o
all: mainapp gui callbacks libpvm
	$(CC) MainGui.o mainapp.o callbacks.o pvmcontainer.o -o main.o $(CFLAGS) $(GTKFLAGS) $(GTKCONF) $(PVMFLAGS)

mainapp:
	$(CC) mainapp.cpp -c -o mainapp.o $(CFLAGS) $(GTKFLAGS) $(GTKCONF)
gui:
	$(CC) MainGui.cpp -c -o MainGui.o $(CFLAGS) $(GTKFLAGS) $(GTKCONF)
callbacks:
	$(CC) callbacks.cpp -c -o callbacks.o $(CFLAGS) $(GTKFLAGS) $(GTKCONF)
libpvm:
	$(CC) pvmcontainer.cpp -c -o pvmcontainer.o $(CFLAGS) $(PVMFLAGS) -L/usr/lib/pvm3/lib -I/usr/include -lpvm3
clean:
	rm *.o