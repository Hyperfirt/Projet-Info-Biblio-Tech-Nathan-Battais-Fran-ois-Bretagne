#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include"header.h"

void reinitialiser_scanf();

//displays the header of the program.
void interface(){
	printf("************************************\n");
	printf("     Application CY-BiblioTECH      \n");
	printf("************************************\n");
	}
	

//The purpose of this function is to display the connection menu.
char AffichageMenudeConnexion(){
	char choix='t';
	
	printf("1. Se connecter\n");
	printf("2. Nouvel utilisateur\n");
	//The user must choose 1 or 2, 1 if he is already registered or 2 if he is a new user.
		do{
		printf("choisissez 1 ou 2: ");
		scanf("%c",&choix);
		reinitialiser_scanf();
		if(choix== '1'){
			printf("\nVous avez choisis : Se connecter\n\n");
			
		}
		else if(choix == '2'){
			printf("\nVous avez choisis : Nouvel utilisateur\n");
		}
		// To avoid that the program bugs if the user does not use 1 or 2, we added a loop asking him to choose between 1 or 2.
		else {
			printf("\nCe caractère n'est pas accepté.\n");
		}
	}while(choix!= '1' && choix!= '2');
	return choix;
}




//This function will display the menu when the user is logged in.
char AffichageBibliotheque(){
	int laligne=0; //variable that will take the number of lines of the file "biblio.txt" that will allow us to deposit books.
	char faire='t';// variable that will allow the user to choose what he wants to do. We have chosen a char variable and not an int variable because the user could press a letter instead of a number which would make the program buggy.
	char livre[200],livreBiblio[200];// variable to borrow a book: one will take the value that will be entered by the user, while the other will compare each line of the file "biblio.txt" to see if it matches the string entered by the user.
	char check[100], LivreArendre[100];// exactly the same as the 2 previous variables but in order to return a book.
	printf("Quelle action voulez vous faire ?\n\n");
	printf(" 1. Emprunter un livre\n");
	printf(" 2. Rendre un livre\n");
	printf(" 3. Déposer livre\n");
	printf(" 4. Déconnexion, Retour au menu de connexion\n");
	printf("Choisissez 1, 2, 3 ou 4:  ");
	FILE* B=NULL;
	FILE* A=NULL;
		A=fopen("biblio.txt","r+");
		laligne=nbrligne(A);// count the number of lines in the "biblio.txt" file
	do{
		scanf("%c", &faire);
		reinitialiser_scanf();
		if(faire=='1'){// the user wants to borrow a book.
			B=fopen("biblio.txt","r+");
			if(B==NULL){
				  printf("error");
				  exit(2);
			}
			rewind(B);
			Choisir(livre, livreBiblio, B); // function to borrow a book.
			fclose(B);
			AffichageBibliotheque();//allows you to return to the menu.
		}
		else if(faire=='2'){// the user wants to return a book
			B=fopen("biblio.txt","r+");
			if(B==NULL){
				  printf("error");
				  exit(2);
			}
			rewind(B);
			Rendre( check, LivreArendre, B);//function to return a book.
			fclose(B);
			AffichageBibliotheque();//allows you to return to the menu.
		}
		else if(faire=='3'){//the user wants to deposit a book
			DeposerLivre(laligne);//function to deposit a book
			AffichageBibliotheque();//allows you to return to the menu.
		}
		else if(faire=='4'){
			printf("Déconnexion\n");
			return 0;
		}
		else{
			printf("\nCe caractère n'est pas accepté.\n");
		}
	}while(faire!= '1' && faire!= '2' && faire!= '3' && faire != '4');// if the entered characters are not 1,2,3 or 4 the function will wait until scanning one of these characters.
	return faire;
}







