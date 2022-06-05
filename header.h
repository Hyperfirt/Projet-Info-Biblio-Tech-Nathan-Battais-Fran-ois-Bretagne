#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<string.h>

//Dans interface.c
void interface();
char AffichageMenudeConnexion();
char AffichageBibliotheque();
int Verification(char login[20], char testid[20]);
int nbrligne(FILE* B);
void reinitialiser_scanf();
int EtuProf(int ligne);

//Dans login.c
char* Connexion(char choix,int ligne);
char* New(char choix,int ligne);

//Dans Biblio.c
char* Emprunt(char livre[200], char livreBiblio[200], FILE *B);
int DansLaBase(char livre[200], char livreBiblio[200], FILE *B);
char* Choisir(char livre[200],char livreBiblio[200], FILE* B);
int VerificationRendu(char check[100], char LivreArendre[100]);
char* RendreLivre( char check[100], char LivreArendre[100], FILE *B);
char* Rendre(char livre[200],char livreBiblio[200], FILE* B);
char *DeposerLivre(int ligne);
