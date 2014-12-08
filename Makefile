build: main.c pixel.o ppm.o
	gcc -ansi -Wall -pedantic main.c pixel.o ppm.o -lm
ppm.o: ppm.h ppm.c pixel.o
	gcc -ansi -Wall -pedantic -c ppm.c ppm.h -lm
pixel.o: pixel.h pixel.c
	gcc -ansi -Wall -pedantic -c pixel.c pixel.h -lm
