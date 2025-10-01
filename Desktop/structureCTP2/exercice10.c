//exercice 1
#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int jour;
    int mois;
    int annee;
}DateNaisRepere; // definition d'un nouveau type appele DateNaisRepere
typedef struct{
    char nom[50];
    char prenom[50];
    int age;
    int note[3];
    DateNaisRepere dateNaissance;
}EtudiantRepere; //definition d'un nouveau type appelé EtudiantRepere
//exercice 2
void lireEtudiant(EtudiantRepere *etu){
     printf("entrer le nom de l'etudiant : ");
     scanf("%s",etu->nom);
     printf("entrer le prenom de l'etudiant : ");
     scanf("%s",etu->prenom);
     printf("son age :");
     scanf("%d",&(etu->age));
     printf("entrer la note des mathematiques :");
     scanf("%d",&(etu->note[0]));
     printf("entrer la note de physiques:");
     scanf("%d",&(etu->note[1]));
     printf("entrer la note de science:");
     scanf("%d",&(etu->note[2]));
    int diff;
     do {printf("sa date de naissance JJ/MM/ANNEE : ");
     scanf("%d %d %d",&(etu->dateNaissance.jour),&(etu->dateNaissance.mois),&(etu->dateNaissance.annee));
     diff = 2025 - etu->dateNaissance.annee;
     if(diff!=etu->age) printf("ERREUR RESSAYER \n");
     } while (diff != etu->age);

    }
// float calculerMoyenne(EtudiantRepere *tab, int taille);

void afficherEtudiant(EtudiantRepere *etu){
    printf("le nom de l'etudiant est %s \n son prenom est %s \n son age est %d \n sa date de naissance est %d/%d/%d \n \n \n ",etu->nom,etu->prenom,etu->age,etu->dateNaissance.jour,etu->dateNaissance.mois,etu->dateNaissance.annee); 
}

void lireTableauEtudiants(EtudiantRepere *etu, int taille){
    for(int i=0; i<taille; i++) lireEtudiant(etu+i); 
} 

float calculerMoyennePonderee(EtudiantRepere *e){
    return (e->note[0] * 2 + e->note[1] + e->note[2]) / 3 ;
}
void afficherTableauEtudiants(EtudiantRepere *etu,int taille){
     float Moy;
    for(int i = 0 ; i < taille ; i++) {afficherEtudiant(etu+i) ; 
    Moy = calculerMoyennePonderee(&(etu[i]));
printf("La Moyenne est : %.2f ",Moy );}
}

// MAIN //////////////////
void main(void){
    int taille;
    do{
    printf("entrer la taille de votre tableau : ");
    scanf("%d",&taille);
    if (taille < 1 )printf("FORMAT INCORRECTE, RESSAYER \n "); 
    } while (taille<1);
    EtudiantRepere *tab = (EtudiantRepere *) calloc(taille,sizeof(EtudiantRepere)); if(tab==NULL) exit(1);
    lireTableauEtudiants(tab,taille);
    afficherTableauEtudiants(tab,taille);
    free(tab);
}

