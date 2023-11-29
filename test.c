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
    int nb_soins ; 
    char soin[7]; 
    int nbNuit;
    int prix ; 

    // Ajouter le soin : accouchement, ORL....
};
int main(){
    FILE *ptr;
    patient p;
    ptr = fopen("patients_C.bin", "r+b");

    fread (&p ,sizeof (patient) ,1 , ptr);
    
    printf("%s",p.nom);
    printf("%d",p.nb_soins);
}