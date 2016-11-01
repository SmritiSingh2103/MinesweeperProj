program: program.c init.h
	gcc program.c -lncurses -lm -lmenu
clean: 
	rm -f *.o program *~
