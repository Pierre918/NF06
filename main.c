#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
const char *SOINS[7]={"Accouchement", "Bilan de sante", "Opération du canal carpien", "ORL", "Echographie", "Coloscopie", "IRM"}; 
//utilisé pour décrire les soins
typedef struct patient patient;
struct patient{
    char service[20];
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
    //int nb_soins ; 
    int soin[7]; //indice correspond à : Accouchement(0), Bilan de sante(1), Opération du canal carpien(2), ORL(3), Echographie(4), Coloscopie(5), IRM(6)");

    int nbNuit;
    int prix ; 

};

patient DemanderInfosPatient(){
    
    char choix;
    patient p;

    printf("service (consultation : c | urgence : u) : ");
    scanf(" %c",&choix);
    if (choix=='c'){
        strcpy(p.service, "consultation");
    }
    else{
        strcpy(p.service, "urgence");
    }
    printf("nom : ");
    scanf(" %[^\n]",p.nom);
    printf("prenom : ");
    scanf(" %[^\n]",p.prenom);
    printf("numero d'immatriculation : ");
    scanf(" %d",&p.matricule);
    printf("adresse : ");
    scanf(" %[^\n]",p.adresse);
    printf("age : ");
    scanf(" %d",&p.age);
    printf("sexe (f/h) : ");
    scanf(" %c",&p.sexe);
    printf("description de la maladie : ");
    scanf(" %[^\n]",p.maladie);
    printf("Numero de chambre : ");
    scanf(" %d",&p.nChambre);
    printf("Specialisation du medecin : ");
    scanf(" %[^\n]",p.medecin_spec);
    printf("Coordonnees du medecin : ");
    scanf(" %[^\n]",p.medecin_coord);
    printf("Date d'entree et heure (jj/mm/aaaa hh:mm): ");
    scanf(" %[^\n]",p.dateHeure);
    char saisir='o';
    int soin;
    for (int i=0;i<7;i++)
    p.soin[i]=0; //sinon il y a des valeurs aléatoires
    while (saisir=='o'){
        printf("Saisissez un soins subis par le patient : \nAccouchement (1), Bilan de sante(2), Opération du canal carpien(3), ORL(4), Echographie(5), Coloscopie(6), IRM(7)");
        scanf(" %d", &soin);
        printf("Combien de fois ce soin a été subis ?");
        scanf(" %d",&p.soin[soin-1]);
        printf("Avez vous un autre soin à enregistrer ? oui : o | non : n ");
        scanf(" %c",&saisir);
    }
    printf("Nombre de nuit : ");
    scanf(" %d",&p.nbNuit);

    return p;
}

void EnregistrerInfosPatient(patient p){
    FILE *ptr;
    ptr = fopen("patients_python.txt", "a");
    FILE *ptr1;
    ptr1 = fopen("patients_C.bin", "ab");
    if (ptr1 == NULL) {
        printf("Failed to open file for writing\n");
    }

    
    //vérifier par la suite que le patient n'existe pas déjà
    //on fait un fichier pour la communication avec python avec les données écrites en txt
    //et un fichier où l'on utilise fwrite pour écrire les objets et donc les récupérer plus facilement en C
    size_t w=fwrite(&p, sizeof(patient), 1, ptr1);
    if (w < 1) {
        printf("Failed to write to file\n");
    }
    fprintf(ptr, "%c|",p.service);
    fprintf(ptr, "%s|",p.nom);
    fprintf(ptr, "%s|",p.prenom);
    fprintf(ptr, "%d|",p.matricule);
    fprintf(ptr, "%s|",p.adresse);
    fprintf(ptr, "%d|",p.age);
    fprintf(ptr, "%c|",p.sexe);
    fprintf(ptr, "%s|",p.maladie);
    fprintf(ptr, "%d|",p.nChambre);
    fprintf(ptr, "%s|",p.medecin_spec);
    fprintf(ptr, "%s|",p.medecin_coord);
    fprintf(ptr, "%s|",p.dateHeure);
    fprintf(ptr, "%d|",p.dateHeure);
    //fprintf(ptr, "%s|",p.nb_soins);
    // Inscire les soins subis 
    
    for(int i=0; i<7; i+=1){
        fprintf(ptr, "%d-",p.soin[i]); 
    }
    fprintf(ptr, "|%d|\n",p.nbNuit);

    //on réenregistre qqn ?

    fclose(ptr);
    fclose(ptr1);
}
void EnregistrerNouveauPatient(){
    patient p;
    char continuer='n';
    while (continuer=='n'){
        p=DemanderInfosPatient();
        EnregistrerInfosPatient(p);
        printf("quitter(o), continuer(n): ");scanf(" %c",&continuer);
        if (continuer=='o'){
            break;
        }
    }
}
void AfficherPatient(patient p){
            printf("\nnom : %s\n",p.nom);
            printf("prenom : %s\n",p.prenom);
            printf("matricule : %d\n",p.matricule);

            printf("adresse : %s\n",p.adresse);

            printf("age : %d\n",p.age);
            printf("sexe (f/h) : %c\n",p.sexe);
            printf("description de la maladie : %s\n",p.maladie);
            printf("Numero de chambre : %d\n",p.nChambre);
            printf("Specialisation du medecin : %s\n",p.medecin_spec);
            printf("Coordonnees du medecin : %s\n",p.medecin_coord);
            printf("Date d'entree et heure (jj/mm/aaaa hh:mm): %s\n",p.dateHeure);
            printf("Soin effectués : \n");
            for (int i=0;i<7;i++){
                if (p.soin[i]!=0){
                    printf("\t- %s : %d\n",SOINS[i],p.soin[i]);
                }
            }
            printf("Nombre de nuit : %d\n",p.nbNuit);
            printf("Prix : %d\n",p.prix);
}
patient RechercherFichierPatient(char id[], char MorN){ //Matricule ou nom
    FILE *ptr;
    patient p;
    ptr = fopen("patients_C.bin", "r+b");
    if (MorN=='m'){
        int num;
        num = atoi(id);
        printf("coucou");
        while (!feof(ptr)){
            fread (&p ,sizeof (patient) ,1 , ptr);
            printf("%d\n",p.matricule);
            if (p.matricule==num){ 
                printf("Le dossier du patient a ete trouvé"); 
                return p; 
            }      
        }
    }

    while (!feof(ptr)){
        fread (&p ,sizeof (patient) ,1 , ptr);
        
        if (strcmp(p.nom, id) == 0){ 
            printf("Le dossier du patient a ete trouvé"); 
            return p; 
        }      
    }
    printf("Le dossier du patient n'a pas ete trouve ");
    strcpy(p.nom, "erreur pas de dossier trouve");
    return p;
}
void ModifierPatient(patient p){
    int elt=0;
    while (elt<1 && elt>20){
        printf("Element a modifier : service(1), nom(2), prenom(3), matricule(4), adresse(5), age(6), sexe(7), maladie(8), numero de chambre(9), specifications du medecin(10), coordonnees du medecin(11), date et heure(12), soins : \n\t- nombre d'accouchement (13)\n\t-nombre de bilan de sante(14)\n\t-nombre d'operation du canal carpien(15)\n\t-nombre d'ORL(16)\n\t-nombre d'echographie(17)\n\t-nombre de coloscopie(18)\n\t-nombre d'IRM(19)\nnombre de nuit(20)");
        scanf(" %d",&elt);
    }
    switch(elt){
        case 1:
            printf("Ancienne valeur : %s. Nouvelle : ",p.service);
            scanf(" %c", p.service);
        case 2:
            printf("Ancienne valeur : %s. Nouvelle : ",p.nom);
            scanf(" %s", p.nom);
        case 3:
            printf("Ancienne valeur : %s. Nouvelle : ",p.prenom);
            scanf(" %s", p.nom);
        case 4:
            printf("Ancienne valeur : %d. Nouvelle : ",p.matricule);
            scanf(" %d", p.matricule);
        case 5:
            printf("Ancienne valeur : %d. Nouvelle : ",p.age);
            scanf(" %d", p.age);
        case 6:
            printf("Ancienne valeur : %c. Nouvelle (f/h) : ",p.sexe);
            scanf(" %c", p.sexe);
        case 7:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 8:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 9:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 10:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 11:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 12:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 13:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 14:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 15:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 16:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 17:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 18:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 19:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
        case 20:
            printf("Ancienne valeur : %s. Nouvelle : ",p.adresse);
            scanf(" %s", p.adresse);
    }

}
void RechercherModifier(){
    char id[100];
    char MorN='c';
    patient p;
    strcpy(p.nom,"erreur pas de dossier trouve");
    while (MorN!='m' && MorN!='n'){
        printf("Recherche par Numéro de dossier (m) ou nom complet (n) ? ");
        scanf(" %c", &MorN);
    }
    if (MorN=='m'){
        printf("Entrer le numero de dossier : ");
    }
    else{
        printf("Entrer le nom du patient : ");
    }
    scanf(" %s",id); //scanf ajoute \0 à la fin de la saisie, donc uniquemnt les lettres tapées par l'utilisateur seront comparées 
    p = RechercherFichierPatient(id,MorN);
    if (strcmp(p.nom, "erreur pas de dossier trouve") != 0){
        AfficherPatient(p);
        char choice='c';
        while (choice!='o' && choice!='n'){
            printf("souhaitez vous modifier ce dossier ? (o/n) ");
            scanf(" %c",choice);
        }
        if (choice=='o')
            ModifierPatient(p);
    }
/*
    int compteur_nom = 0; 
    int compteur_matricule = 0 ; 
    char nom_recherche[20] ;  
    int n;
    int compteur = 0 ; 
    int matricule ; 
    FILE *ptr;
    patient p;
    ptr = fopen("patients_C.txt", "r");
    printf("Numéro de dossier (1) ou nom complet (2) :");
    scanf(" %d", &n);
    if (n==1){
        printf("Numéro de dossier : ");
        scanf(" %[^\n]", &matricule);
        while (!feof(ptr)){
            fread (&p ,sizeof (patient) ,1 , ptr);
            
            if (p.matricule==n){
                compteur_matricule +=1 ; 
                printf("Le dossier du patient a ete trouvé"); 
                return p;
                break;   
            }      
        }
    }
    
    else{
        printf("Nom de famille du patient : "); 
        scanf("%s", &nom_recherche); 

        while (!feof(ptr)){
            fread (&p ,sizeof (patient) ,1 , ptr);
            if (strcmp(nom_recherche, p.nom) == 0){
                compteur_nom+=1 ; 
                printf("Le dossier du patient a ete trouve");
                return p; 
                break ; 
            }   
        }
    }
    if (compteur_matricule == 0 && compteur_nom == 0){
        printf("Le dossier n'a pas été trouvé"); 
    }
    */
}

patient modifierFichier(){
    FILE *ptr ; 
    ptr = fopen("patients_python.txt", "r");
    int matricule ; 
    patient p; 

    printf("Saisir le donnée  modifier ");
    //p = RechercherFichierPatient();

    //printf("Saisir la donnée a modifier : Service (S), Nom (N), Prenom (P), Matricule (M), Age(A), Adresse (Ad), Sexe (S), Maladie (Ma), Numero de chambre (nbC), le prix paye (prix), le nombre de nuits passees (nbN), le nombre de soins et les soins(soins), le medecin (med), les coordonnees du medecin(medC), la date et l'heure (d)");
    //scanf("%s", &val_modif); 



}










/*

patient calculerDevis(){
    patient p ; 
    int i;
    p = RechercherFichierPatient();
    int prix_chambre ; 
    int prix_total = 0 ;
    int nb_soins = p.nb_soins;
    int nb_nuit = p.nbNuit ; 
    nb_nuit = p.nbNuit ;

    prix_total += nb_nuit * 68 ;
    for (i=0;i<nb_soins; i+=1){
        if(p.soin[i] == 'a'){
            prix_total += 2600; 
        }
        else if(p.soin[i] == 'b'){
            prix_total += 50; 
        }
        else if(p.soin[i] == 'z'){
            prix_total += 1250; 
        }
        else if(p.soin[i] == 'o'){
            prix_total += 35; 
        }
        else if(p.soin[i] == 'e'){
            prix_total += 85; 
        }
        else if(p.soin[i] == 'c'){
            prix_total += 190; 
        }
        else if(p.soin[i] == 'i'){
            prix_total += 400; 
        }
    }

    p.prix = prix_total ; 

    return p ;  

*/






int main(){
    int selec = 1;
    while (selec!=7){
        printf("-------------------------------------------------------\nSelectionnez le numero correspondant a l'action que vous voulez réaliser : \n1. Enregistrer un nouveau dossier patient\n2. Rechercher ou modifier le dossier patient\n3. Liste des dossiers des patients\n4. Supprimer des dossiers patients\n5. Afficher les statistiques\n6. Sortir de l'application\n");
        scanf("%d",&selec);
        if (selec>7 || selec<1){
            printf("\nVeuillez saisir un nombre entre 1 et 7");
        }
        else{
            if (selec==1){
                EnregistrerNouveauPatient();
            }
            else if (selec==2)
                RechercherModifier();

            // ....
            else if (selec==6){
                break;
    }
    }
    }
}