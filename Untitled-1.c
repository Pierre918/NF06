#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct patient patient;
struct patient{
    char service[10];
    char nom[20];
    char prenom[20];
    int matricule;
    char adresse[50];
    int age;
    char sexe; // 'h' ou 'f'
    char maladie[200];
    int nChambre;
    char medecin_spec[30];
    char medecin_coord[50];
    char dateHeure[20];
    int nbNuit;
};

void calculerDevis(){
    int matricule ;
    int nb_nuit ; 
    
    printf("Saisir le matricule du patient : ");
    scanf("%d", &matricule); 
    FILE *ptr;
    patient p;
    ptr = fopen("patients_C.txt", "r");
    while(feof(ptr)!=0){
        if ()               // Mettre une partie de afficher dossier
    }




}

int main(){

    return 0; 
}