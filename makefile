
EXO : exe

interface.o : interface.c header.h
	gcc -c $< -o $@

login.o : login.c header.h
	gcc -c $< -o $@

Biblio.o : Biblio.c header.h
	gcc -c $< -o $@
	
Outils.o : Outils.c header.h
	gcc -c $< -o $@
	

main.o : main.c header.h
	gcc -c $< -o $@


exe : interface.o login.o Biblio.o Outils.c main.o
	gcc  $^ -o $@

clean:
	rm -f *.o
	rm exe


