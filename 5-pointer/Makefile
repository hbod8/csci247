
CFLAGS=-g

.PHONY=check

all: sort_strings sort_struct

sort.o: sort.c sort.h

sort_strings.o: sort_strings.c sort.h

sort_strings: sort_strings.o sort.o 
	gcc $(CFLAGS) -o sort_strings sort_strings.o sort.o 

sort_struct.o: sort_struct.c sort.h

sort_struct: sort_struct.o sort.o 
	gcc $(CFLAGS) -o sort_struct sort_struct.o sort.o 

check: sort_strings sort_struct
	./sort_strings
	./sort_struct

clean:
	@echo -n Cleaning...
	@rm *~ *.o sort_struct sort_strings 2>/dev/null || true
	@echo done
