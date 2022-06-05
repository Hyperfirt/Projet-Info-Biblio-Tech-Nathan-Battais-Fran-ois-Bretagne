#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include"header.h"

char* Connexion(char choix,int ligne);
char *New(char choix,int ligne);


//this function is used to connect if the user chooses 1 in the connection menu, otherwise it returns 0.
char* Connexion(char choix,int ligne){
	int  i=0,j=0,k=0,same=0;           //i,j and k are variables to run loops. same is equal to 0 or 1 and returns the information given by the check.                       
	int theligne=1,good=0,goodmdp=0; //theline is the line where you can find all the information about the user. good allows you to know if the given login exists and goodmdp allows you to check if the password exists.
	char login[20], testid[20];     // login is the identifier written by the user and testid will be equal to all lines until the line of the identifier is found or if it is the end of the file.
	char password[20],testpass[20]; // password is the password entered by the user and testpass checks if the password is the same as the username in the file "password.txt" .
	FILE* B=NULL;
	FILE* A=NULL;
	B=fopen("identifiant.txt","r");
	if(B==NULL){
		  printf("error");
		  exit(2);
	}
	if (choix == '1'){// if the variable is equal to 1 it means that the user wants to connect. This function will just be used if the user has already his logins.
		printf("Entrez votre identifiant: ");
		scanf("%s", login);
		reinitialiser_scanf();
		fgets(testid,20,B);
		same = Verification(login, testid);//We check that the identifier given by the user is in the "identifier.txt" file.
		while(same==0 && j<ligne){//When the function "Verification" returns 0 and the file "identifier.txt" is not entirely read, we check if the identifier given by the user is equal to one of the lines of the file "identifier.txt
			  fgets(testid,20,B);
			  same = Verification(login, testid);
			  theligne++;
			  j++;
		}
		for(i=0; i<strlen(testid); i++){// to avoid that the identifier entered by the user is a piece of the one if (ex: hype and hyperfirt ), we will measure the length between the identifier entered by the user and the one found in "identifier.txt" and if there is a difference, the identifier will be considered as not existing.
			if(login[i]!=testid[i]){
				good++;
			}
		}
		fclose(B);
		if(good>1){
			printf("Cet identifiant n'existe pas.\nDéconnexion\n");
			return 0;
		}
		else if(j>= ligne){
			printf("Cet identifiant n'existe pas.\nDéconnexion\n");
			return 0;
		}
		else{
			A=fopen("motdepasse.txt","r");// open the file containing the passwords and repeat the same process as with the identifiers.
			if(A==NULL){
				printf("error");
				exit(2);
			}
			printf("\nEntrez votre mot de passe: ");
			scanf("%s", password);
			reinitialiser_scanf();
			while(k<theligne){
				fgets(testpass,20,A);
				k++;
			}
			same = Verification(password, testpass);
			for(i=0; i<strlen(testpass); i++){
				if(password[i]!=testpass[i]){
					goodmdp++;
				}
			}
			if(goodmdp>1){
				printf("Ce mot de passe n'existe pas.\nDéconnexion\n");// If the password is not valid, the program terminates.
			}
			else if (same ==0){
				printf("Mauvais mot de passe.\nDéconnexion\n");// If the password is not valid, the program terminates.
			}
			else{
				printf("Bon mot de passe.\n");// If the password is valid, the menu of the library's possibilities is displayed.
				fclose(A);
				AffichageBibliotheque();
			}
		}

	}
	else{
		return 0;
	}
	return 0;
}
//😀️


//this function is used to create a login and a password if the user is not registered.
char *New(char choix,int ligne){
	int i=0,j=0,k=0;//i,j and k are variables to run loops.
	char newpassword[200],newlogin[200];// These variables will take as values the values given by the user and will be written in their associated files.
	char tampon1[200],tampon2[200],tampon3[200],retourmenu;//Buffers are intended to take an unimportant value and move from line to line to count them
	char role='0';//will allow to know if the newly created user is a student or a teacher.
	FILE* B=NULL;
	FILE* A=NULL;
	FILE* EtuProf= NULL;
   	EtuProf = fopen("ProfEtu.txt", "r+");
	B=fopen("identifiant.txt","r+");
	if(B==NULL){//prevent the uvert file from not being opened and the program from bugging.
		  printf("error");
		  exit(2);
	}
	if (choix == '2'){//allows the new user to say whether he is a student or a teacher.
		printf("Etes vous un:\n1. élève\n 2. professeur?");
		scanf("%c",&role);
		reinitialiser_scanf();
		while(i<ligne){//will count the lines.
				fgets(tampon3,20,EtuProf);
				i++;
		}
		fprintf(EtuProf,"%c\n",role);	
		fclose(EtuProf);
		printf("Entrez l'identifiant que vous voulez avoir:  ");
		scanf("%s", newlogin);
		do{
		if(strlen(newlogin)>20){//allows to avoid that the identifier is longer than 20 characters.
			printf("votre login est trop long, veuillez en choisir un ne dépassant pas les 20 caractères\n");
			printf("Entrez l'identifiant que vous voulez avoir:  ");
			scanf("%s", newlogin);
		}
		}while(strlen(newlogin)>20);//will count the lines.
		while(k<ligne){
				fgets(tampon1,20,B);
				k++;
			}
		fprintf(B,"%s\n",newlogin);
		fclose(B);
		A=fopen("motdepasse.txt","r+");
		if(A==NULL){
			  printf("error");
			  exit(2);
		}
		printf("\nEntrez le mot de passe que vous souhaitez:  ");
		scanf("%s",newpassword);
		do{
		if(strlen(newpassword)>20){//allows you to prevent a password from being longer than 20 characters.
			printf("votre mot de passe est trop long, veuillez en choisir un ne dépassant pas les 20 caractères\n");
			printf("Entrez le mot de passe que vous voulez avoir:  ");
			scanf("%s", newpassword);
		}
		}while(strlen(newlogin)>20);//will count the lines.
		while(j<ligne){
				fgets(tampon2,20,A);
				j++;
		}
		fprintf(B,"%s\n",newpassword);
		fclose(A);
		ligne++;
		choix='1';
		printf("\n************************************\n");//return to the login menu where the user will have to identify himself with his new login and password before being able to access the library menu.
		printf("     Retour au menu de connexion\n");
		printf("************************************\n");
		Connexion(choix,ligne);
	}
	else{
		return 0;
	}
}




