CC = cc -Werror -pedantic
HEADERS = bakeutils.h baketypes.h bakeparser.h
OBJECTS = bake.o bakeutils.o baketypes.o bakeparser.o
APPLICATION = bake

$(APPLICATION) : $(OBJECTS)
	$(CC) -o ../$(APPLICATION) $(OBJECTS)
	
%.o : %.c $(HEADERS)
	$(CC) -c $<

clean:
	rm -f ../$(APPLICATION) $(OBJECTS)