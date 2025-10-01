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
    int note;
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
     printf("sa note :");
     scanf("%d",&(etu->note));
     printf("sa date de naissance JJ/MM/ANNEE : ");
     scanf("%d %d %d",&(etu->dateNaissance.jour),&(etu->dateNaissance.mois),&(etu->dateNaissance.annee)); //on peut faire un fleche?

    }
float calculerMoyenne(EtudiantRepere *tab, int taille);

void afficherEtudiant(EtudiantRepere *etu){
    printf("le nom de l'etudiant est %s \n son prenom est %s \n son age est %d \n sa note globale est %d \n sa date de naissance est %d/%d/%d \n \n \n ",etu->nom,etu->prenom,etu->age,etu->note,etu->dateNaissance.jour,etu->dateNaissance.mois,etu->dateNaissance.annee); 
}

void lireTableauEtudiants(EtudiantRepere *etu, int taille){
    for(int i=0; i<taille; i++) lireEtudiant(etu+i); 
} 
void afficherTableauEtudiants(EtudiantRepere *etu,int taille){
    for(int i = 0 ; i < taille ; i++) afficherEtudiant(etu+i);
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
   
    printf("la moyenne des notes est : %f ",calculerMoyenne(tab,taille));
free(tab);

}
int sommeNotesRecursif(EtudiantRepere *tab, int taille){
    if (taille == 1) return tab->note;
    else return ( (tab+(taille-1))->note + sommeNotesRecursif(tab,(taille-1)));
}

float calculerMoyenne(EtudiantRepere *tab, int taille){
    return (float) sommeNotesRecursif(tab,taille) / taille;
}