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
    //int nb_soins ; 
    int soin[7]; //indice correspond à : Accouchement(0), Bilan de sante(1), Opération du canal carpien(2), ORL(3), Echographie(4), Coloscopie(5), IRM(6)");

    int nbNuit;
    int prix ; 

    // Ajouter le soin : accouchement, ORL....
};
void EnregistrerInfosPatient(){
    char continuer='n';
    char choix;
    char soin_alternatif[100]; 
    int i; 
    patient p;   
    FILE *ptr;
    ptr = fopen("patients_python.txt", "a");
    FILE *ptr1;
    ptr1 = fopen("patients_C.bin", "ab");
    if (ptr1 == NULL) {
        printf("Failed to open file for writing\n");
    }
    while (continuer=='n'){


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
        while (saisir=='o'){
            printf("Saisissez un soins subis par le patient : \nAccouchement (1), Bilan de sante(2), Opération du canal carpien(3), ORL(4), Echographie(5), Coloscopie(6), IRM(7)");
            scanf(" %d", soin);
            printf("Combien de fois ce soin a été subis ?");
            scanf("%d",p.soin[soin-1]);
            printf("Avez vous un autre soin à enregistrer ? oui : o | non : n");
            scanf(" %c",saisir);
        }
        /*
        for(i=0; i<p.nb_soins; i+=1){
            printf("Saisir les soins : Accouchement, Bilan de sante, Opération du canal carpien, ORL, Echographie, Coloscopie, IRM");
            scanf(" %[^\n]",soin_alternatif);
            if (soin_alternatif == "Accouchement"){
                p.soin[i] = 'a';
            }
            if (soin_alternatif == "Bilan de sante"){
                p.soin[i] = 'b';
            }
            if (soin_alternatif == "Opération du canal carpien"){
                p.soin[i] = 'z';
            }
            if (soin_alternatif == "ORL"){
                p.soin[i] = 'o';
            }
            if (soin_alternatif == "Echographie"){
                p.soin[i] = 'e';
            }
            if (soin_alternatif == "Coloscopie"){
                p.soin[i] = 'c';
            }
            if (soin_alternatif == "IRM"){
                p.soin[i] = 'i';
            }
        }
    */
        printf("Nombre de nuit : ");
        scanf(" %d",&p.nbNuit);
        
        //vérifier par la suite que le patient n'existe pas déjà
        //on fait un fichier pour la communication avec python avec les données écrites en txt
        //et un fichier où l'on utilise fwrite pour écrire les objets et donc les récupérer plus facilement en C
        size_t w=fwrite(&p, sizeof(patient), 1, ptr1);
        if (w < 1) {
            printf("Failed to write to file\n");
        }
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
        fprintf(ptr, "%s|",p.nb_soins);
        // Inscire les soins subis 
        for(i=0; i<p.nb_soins; i+=1){
            fprintf(ptr, "%c-",p.soin[i]); 
        }
        fprintf(ptr, "%d|\n",p.nbNuit);

        //on réenregistre qqn ?
        printf("quitter(o), continuer(n): ");scanf(" %c",&continuer);
        if (continuer=='o'){
            break;
        }
    }
    fclose(ptr);
    fclose(ptr1);
}
void afficherPatient(patient p){
            printf("\n%s\n",p.nom);
            printf("%s\n",p.prenom);
            printf("%d\n",p.matricule);
            scanf(" %d",&p.matricule);
            printf("adresse : ");
            scanf(" %[^\n]",p.adresse);
            printf("age : ");
            scanf(" %d",&p.age);
            printf("sexe (f/h) : ");
            scanf(" %[^\n]",&p.sexe);
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
            printf("Nombre de nuit : ");
            scanf(" %d",&p.nbNuit);
}
patient RechercherFichierPatient(){
    int manip ; 
    printf("Vous souhaitez modifier(1) ou rechercher(2) un fichier patient ? ");
    scanf("%d", &manip); 
    int n;
    int compteur = 0 ; 
    FILE *ptr;
    patient p;
    ptr = fopen("patients_C.bin", "r+b");
    if (manip == 2){
        
    }
    printf("Numéro de dossier (1) ou nom complet (2) :");
    scanf(" %d", &n);
    if (n==1){
        printf("Numéro de dossier : ");
        scanf(" %[^\n]", &n);
        while (!feof(ptr)){
            fread (&p ,sizeof (patient) ,1 , ptr);
            if (p.matricule==n){//complete lena
                printf("Le dossier du patient a ete trouvé"); 
                return p;
                break;   
            }
                 
        }
    }
    else{
        
    }
}

patient modifier_info_patient(){
    FILE *ptr ; 
    ptr = fopen("patients_python.txt", "r");
    int matricule ; 
    patient p; 

    printf("Saisir le donnée  modifier ");
    p = RechercherFichierPatient();
    

}







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







}














int main(){
int selec = 1;
while (selec!=7){
    printf("-------------------------------------------------------\nSelectionnez le numero correspondant a l'action que vous voulez réaliser : \n1. Enregistrer un nouveau dossier patient\n2. Rechercher ou modifier le dossier patient\n3. Liste des dossiers des patients\n4. Supprimer des dossiers patients\n5. Calculer le devis\n6. Afficher les statistiques\n7. Sortir de l'application\n");
    scanf("%d",&selec);
    if (selec>7 || selec<1){
        printf("\nVeuillez saisir un nombre entre 1 et 7");
    }
    else{
        if (selec==1){
            EnregistrerInfosPatient();
        }
        else if (selec==2)
            RechercherFichierPatient();
        // ....
        else if (selec==7){
            break;
        } 
    }
}
}