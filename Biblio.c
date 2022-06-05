#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"header.h"



int DansLaBase(char livre[200], char livreBiblio[200], FILE *B){ // We declare a "DanslaBase" function with int because it will return a %d,   We declare livre[200] which will be the variable we compare with livreBiblio[200] which will check line by line if livre=livreBiblio and we declare FILE *B in a lot of our function in order to just open file.txt in the main.
    int i,l=0;
    int Ligne, same;
   
    Ligne=nbrligne(B);// We call the function NombreLigne which will return the files line.
    rewind(B);// we use rewind to be back at the beginning of our files
    fgets(livreBiblio,200,B);// using fgets will associate here the first line of the file to livreBiblio.
    same = Verification(livre, livreBiblio);// We call the function "Verifiction" which will compare the first line of the files here livreBiblio with the string of caracters we will associate to livre . The function will return 0 if livreBibio different of livre and one if there are equal.
    while(same==0 && l<Ligne){// so while same = 0 and we haven't check the whole file(number of line), we will do the same as just before.
        fgets(livreBiblio,200,B);// we will use this function fgets until we find livre equal livreBiblio or we've just browsed the entire file.--> associating livreBiblio with the line we are.
        same = Verification(livre, livreBiblio);// we will compare livreBiblio with livre at each line
        l++;//we increment l to have a stop at the end of the files if we don't find anything that prouves that livre equal livreBiblio
    }
    return same;// we return if we find the book or not --> meaning we return 0 or 1
}

char* Emprunt(char livre[200], char livreBiblio[200], FILE *B){// We declare a "Emprunt" function with char* in order to be able to manage strings of characters --> return a string of caracters  
int i,emprunt,same; // we declare variables
for(i=0; i<2; i++){// when we find the book his number of borrow will be 3 lines under the titles so we do fgets 2 times
    fgets(livreBiblio,20,B);
}
fgetc(B); // we jump a line in order to place the pointeur just in front of : |emprunt: 0 --> the pointeur is representate by |
fscanf(B,"%*s%d",&emprunt);// we select the whole line with %*s --> emprunt:|     and with %d we select if there is a 0 or an other number. 0 means you can borrow it and another number means it is already borrow by you or someone else


if(emprunt==0){
    printf("Livre emprunté !\n\n");
    fseek(B,-1,1); // the pointeur is before this function here--> emprunt: 0| --> so we use fseek to place him there--> emprunt: |0
    fputc('1',B); // The user borrow the book so we put the number 1 instead of the 0 meanings you borrow this book.
 }
else{
    printf("Ce livre est déja emprunté par un utilisateur.\n\n"); // if emprunt!= 0 we just demand to the user to reenter the book he wants to borrow.
    printf("Quel livre voulez vous emprunter?");
    scanf("%s", livre); // we associate here the string of caracter --> which normaly would be a book present in our Biblioteque
    same = DansLaBase(livre, livreBiblio,B); // We call the function which check if livre is in the base
    while(same==0){ // If livre still not in the base we just recall the function "DansLaBase" until same=1, meanings until you enter a Book which is present in the base
        printf("Ce livre n'est pas présent dans notre bibliothèque.\n");
        printf("Quel livre voulez vous emprunter? :  ");
        scanf("%s", livre);
        rewind(B); // we use rewind to go back at the biginning of the files
        same = DansLaBase(livre, livreBiblio,B);
    }
    Emprunt(livre, livreBiblio, B); // we use recursivity in order to when the user put the right Book to change the Borrowing aspect meanings replace the one 0 by a one.
}
return livreBiblio; // we return the string of caracter which browsed the files
}

   


char* Choisir(char livre[200],char livreBiblio[200], FILE* B){ // We declare a function "Choisir" which will initiate the string of caracter livre and will call the function "Emprunt", this function will globaly be our central function for borrowing books
    int same;// We declare the variable

    printf("Quel livre voulez vous emprunter?  ");
    scanf("%[^\n]", livre); // we use here "%[^\n]" in order to select the whole string of caracter we enter for exemple if we enter Dune a %s would be enough but if you enter "Le seigneur des anneaux" the function scanf will with the %s just associate "Le" with livre--> which will provocate confusion. So here we use "%[^\n]"
    reinitialiser_scanf(); // We needs to use here this function initialised before in order to clear the function scanf and enables us to reuse "%[^\n]" later.
    same = DansLaBase(livre, livreBiblio,B); // Like before we check if the book is in the base
    while(same==0){ // While same is equal to 0 we just do the same again and again until same is equal to one and the string of caracter you enter match with a book in the files
        printf("Ce livre n'est pas présent dans notre bibliothèque.\n");
        printf("Quel livre voulez vous emprunter?  ");
        scanf("%[^\n]", livre);
        reinitialiser_scanf();
        same = DansLaBase(livre, livreBiblio,B);
        rewind(B); // We use rewind to go back at the beginning of our files
    }
    printf("\nCe livre est présent dans notre bibliothèque.\n"); // We print when same equal to one meanings we found the book in the library that we have the book
    Emprunt(livre, livreBiblio, B); // So we call the function "Emprunt" in order to borrow the book as explain before
    return livre;
}



char* RendreLivre(char livre[200], char livreBiblio[200], FILE *B){ //We declare a function "RendreLivre", which will aim to give back the book to our library      As before we declare livre and livreBiblio in the function --> commun between function and we open the file Biblio.txt trough B already open in the main
int i,emprunt,same; // We declare variable, i in order to make loup, emprunt which will say if the book is borrow or not, and same as in all our function will check if the book is in the base (The Library)
for(i=0; i<2; i++){ // We do 2 times the function fgets in order to arrive juste before the information on the borrow. Indeed this information is 3 lines after the Title
    fgets(livreBiblio,20,B);
}
fgetc(B);//That's the reason why we use the function fgetc in order to put the pointer here: |emprunt: 0/1
fscanf(B,"%*s%d",&emprunt); // // we select the whole line with %*s --> emprunt:|     and with %d we select if there is a 0 or a 1. 0 means it is not borrow by anyone and 1 means it's borrow so you can give it back
if(emprunt==1){ // If emprunt ==1 you can give back the book
    printf("Livre rendu!\n");
    fseek(B,-1,1);// The pointeur before the utilisation of fseek was like that: emprunt: 1|  and with the function fseek we put it here: emprunt: |1
    fputc('0',B); // We just replace here the 1 meaning the book is borrowed by someone by a 0 meaning you give it back to the library so someone can borrow it as well
 }
else{// --> implies that emprunt==1 -->meaning that's the book is free to borrow so you can't give it back
    printf("Vous n'avez pas emprunté ce livre.\n");
    printf("Quel livre voulez vous rendre?  ");
    scanf("%s", livre);// We demand again to the user to give back another book
    same = DansLaBase(livre, livreBiblio,B);// We check the book is in the base (Library)
    while(same==0){// While we don't find the book in the library you are going to give another book until we foud the book
        printf("Ce livre n'est pas présent dans notre bibliothèque.\n");
        printf("Quel livre voulez vous rendre?  ");
        scanf("%s", livre);
        rewind(B);// We go back at the beginning of the files
        same = DansLaBase(livre, livreBiblio,B);
    }
    RendreLivre(livre, livreBiblio, B);// We use recursivity in order do the function again and give back the book you just put when you've enterred in the "else"
}
return livreBiblio;
}



char* Rendre(char livre[200],char livreBiblio[200], FILE* B){ // We declare a function "Rendre" which will call the function RendreLivre in order to give back to the library the book you borrowed
    int same;// We declare the variable "same" which will be used to see if the book is present in the library

    printf("Quel livre voulez vous rendre?  ");
    scanf("%[^\n]", livre);
    reinitialiser_scanf();
    same = DansLaBase(livre, livreBiblio,B);// We verify that's the book is present in the base(library)
    while(same==0){// If not we recall the function until you enter a book that is present in the base
        printf("Ce livre n'est pas présent dans notre bibliothèque.\n");
        printf("Quel livre voulez vous rendre?  ");
        scanf("%[^\n]", livre);
        reinitialiser_scanf();
        same = DansLaBase(livre, livreBiblio,B);
        rewind(B);// We just go back to the beginning of the file
    }
    printf("Ce livre est présent dans votre bibliotèque.\n");
    RendreLivre(livre, livreBiblio, B);// We call the function "RendreLivre" which will give back to the library the book you've borrowed
    return livre;
}



//this function will allow you to put a book in the library.
char *DeposerLivre(int ligne){
	int k=0,j=0;//variable to rotate the loops.
	char newlivre[200],newauteur[200];//variables that will store the name of the book and the author given by the user.
	char tampon1[200],tampon2[200],retourmenu;//buffer to count the lines
	FILE* B=NULL;
	B=fopen("biblio.txt","r+");
	if(B==NULL){
		  printf("error");
		  exit(2);
	}
	printf("Entrez le livre que vous voulez deposer  ");
	scanf("%50[^\n]", newlivre);
	reinitialiser_scanf();
	do{
	if(strlen(newlivre)>200){//allows you to avoid the name of the book being too long.
		printf("Le titre de votre livre contient trop de caractère, veuillez en choisir un ne depassant pas les 200 caractères\n");
		printf("Entrez le livre que vous voulez deposer  ");
		scanf("%[^\n]", newlivre);
		reinitialiser_scanf();
	}
	}while(strlen(newlivre)>200);
	
	
	printf("Entrez l'auteur du livre à deposer  ");
	scanf("%50[^\n]", newauteur);
	reinitialiser_scanf();
	if(strlen(newauteur)>200){//avoids the author's name to be too long.
		printf("Le nom de votre auteur contient trop de caractère, veuillez en choisir un ne depassant pas les 200 caractères\n");
		printf("Entrez l'auteur du livre  ");
		scanf("%50[^\n]", newlivre);
		reinitialiser_scanf();
	}while(strlen(newauteur)>200);
	while(k<ligne){
			fgets(tampon2,200,B);
			k++;
		}
	fprintf(B,"%s\n%s\nn°:%d\nemprunt:0\n\n",newlivre,newauteur,ligne);//We will put at the end of the file "biblio.txt" all the information in the same format as the other books so that the text file is clean.
	fclose(B);
	ligne=ligne+4;
}	
