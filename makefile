all: program clean

program: main.o auxiliar.o crew.o spaceship.o user.o project.o voyage.o interface.o readData.o
  gcc -o programa main.o auxiliar.o crew.o spaceship.o user.o project.o voyage.o interface.o readData.o

main.o:
  gcc -c main.c

auxiliar.o:
  gcc -c auxiliar.c auxiliar.h

crew.o:
  gcc -c crew.c crew.h

spaceship.o:
  gcc -c spaceship.c spaceship.h

user.o:
  gcc -c user.c user.h

project.o:
  gcc -c project.c project.h

voyage.o:
  gcc -c voyage.c voyage.h

interface.o:
  gcc -c interface.c interface.h

readData.o:
  gcc -c readData/readData.c readData/readData.h

clean:
  rm -f *.o
