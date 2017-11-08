CC= gcc
CFLAGS = -Wall -g
LFLAGS = -lSDL2 -lm

test_obj: wireframe.c objread.c perspect.c graphics.c
	$(CC) $(CFLAGS) wireframe.c objread.c perspect.c graphics.c $(LFLAGS) -o test
	./test cubo.obj
	# ./test teapot.obj
	# ./test bunny.obj