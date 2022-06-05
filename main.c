
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include"header.h"



int main(){
	int ligne=0;
	char newuser, Affichage=0;
	FILE* B=NULL;
		B=fopen("identifiant.txt","r");
		if(B==NULL){
			  printf("error");
			  exit(2);
		}
	//char testidentifiant[20];
	interface();
	Affichage=AffichageMenudeConnexion();
	ligne= nbrligne(B);
	Connexion(Affichage,ligne);
	New(Affichage,ligne);
}
