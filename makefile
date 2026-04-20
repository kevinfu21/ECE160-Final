# this will compile all files everytime make is run
make: UNO_main.c UNO_functions.c UNO_functions_2.c UNO.h
	gcc -o play.out UNO_main.c UNO_functions.c UNO_functions_2.c cards.c -I.

# this will clean or remove compiled files so you can start fresh
clean:
	rm -f *.o *.out
