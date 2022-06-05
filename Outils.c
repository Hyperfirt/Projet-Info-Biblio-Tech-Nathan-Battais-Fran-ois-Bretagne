#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include"header.h"

//this function will allow to reset scanf because we needed to scan with spaces and so we used scanf("%[^\n]"); and the program could not restart another scanf behind.
void reinitialiser_scanf()
{
    scanf("%*[^\n]");
    getchar();
}

//this function allows us to check if the user name exists in the text file when a user tries to connect.
//this function also allows us to check if the password matches the username in question.
int Verification(char login[200], char testid[200]){
    int i;
    	for(i=0; i<strlen(login); i++){//we will check until i smaller than the number of characters of login that theidentifier, password etc.. is similar.
				if (testid[i]!=login[i] ){//As soon as one of the characters is not equal to the other one, the function stops and returns 0 to, in some functions, start again with the line below. 
		  	  	    return 0;
		  	  	}
	  	}
	return 1;
}

//This function will allow us to count the lines because we have several text files and all the information of the same user is found on the same line but on different files.
int nbrligne(FILE* B){
    int ligne=0,i;
    char Ligne[200];
    
    while (fgets(Ligne,200,B)!=NULL) {//line will take +1 for each line passed until the end of the file.
        ligne++;
    }
    return ligne;
}

int EtuProf(int ligne){ // We declare a function "EtuProf" which will at the end return 1 or 2, 1 for a student and 2 for a teacher
    int i, role;// We declare variable, i in order to make a loop and role to get the number 1 or 2 which is representative of your statu
    char r[100];// We declare a string of caracter r[100] in order to browse the file
    FILE* EtuProf= NULL; // // We open here the file "ProfEtu.txt" in access reading because we just want to select an information
    EtuProf = fopen("ProfEtu.txt", "r+");// We open here the file "ProfEtu.txt" in access reading because we just want to select an information
    for(i=0;i<ligne-1;i++){// Before when you enter your login and identifiant a line as been associate to you. So we will browse the file untill we arrive to this line
        fgets(r, 99, EtuProf);// So we do the function fgets ligne times in order to be at the line that correspond to your login
    }
    role = fgetc(EtuProf); // we jump a line to put our pointer like this: |role: 1/2
    fscanf(EtuProf,"%d",&role); // with the function fscanf we work on the line so with %*s we select "role:" and with the %d we just put the number 1 or 2 in the variable role.
    if(role==1){
        printf("Vous êtes un étudiant, vous pouvez emprunter 3 livres\n");// so if role==1 you are a student
    }
    else if(role==2){
        printf("Vous êtes un Professeur, vous pouvez emprunter 5 livres");// else if role ==2 you are a teacher
    }
    return role; // We return role because we are going to use it in other functions
}

