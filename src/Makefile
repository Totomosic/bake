CC = cc -Wall -Werror -pedantic
HEADERS = bakeutils.h
OBJECTS = bake.o bakeutils.o
APPLICATION = bake

$(APPLICATION) : $(OBJECTS)
	$(CC) -o ../$(APPLICATION) $(OBJECTS)
	
%.o : %.c $(HEADERS)
	$(CC) -c $<

clean:
	rm -f ../$(APPLICATION) $(OBJECTS)