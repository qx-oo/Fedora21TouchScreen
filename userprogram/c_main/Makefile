OBJ=main
OBJS=touchScreenControl.o line.o
CC=gcc
$(OBJ):$(OBJS)
	$(CC) $(OBJS) -o $(OBJ)
touchScreenControl.o:touchScreenControl.c line.h prodefine.h
	$(CC) -c touchScreenControl.c
line.o:line.c line.h
	$(CC) -c line.c
clean:
	rm -rf *.o
