###############################################################################
# SpaceGame Makefile
###############################################################################

CC = i686-pc-mingw32-g++

CFLAGS = -Wall -mwindows

DIRECTX_LIBS = -ldxguid  \
               -ld3d9

LIBS = $(DIRECTX_LIBS)

SRCS = winmain.cpp

OBJS = $(SRCS:.c=.o)

MAIN = spacegame.exe

##############################################################################
# Generic Makefile Part
##############################################################################

all:	$(MAIN)
	@echo Spacegame compiled.


$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)


.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@


clean:
	$(RM) *.o *~ $(MAIN)
