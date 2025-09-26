//exercice 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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



//fonction de lecture des information de l'etudiant
void lireEtudiant(EtudiantRepere *etu, int i){
    // entree des donnees
     printf("entrer le nom du %d'%s etudiant : ",i+1, i==0? "er":"eme");
     scanf("%s",etu->nom);
     printf("entrer le prenom de l'etudiant : ");
     scanf("%s",etu->prenom);
     printf("entrer son age :");
     scanf("%d",&(etu->age));
     printf("entrer la note des mathematiques :");
     scanf("%d",&(etu->note[0]));
     printf("entrer la note de physiques:");
     scanf("%d",&(etu->note[1]));
     printf("entrer la note de science:");
     scanf("%d",&(etu->note[2]));
     // extraction de l'année depuis la libraire time.h
    time_t t = time(NULL);
    struct tm date = *localtime(&t); //??
    int year = date.tm_year + 1900;
    int diff;
    //boucle tant que l'annee de naissance ne coincide pas avec l'age
     do {printf("sa date de naissance JJ/MM/ANNEE (vous pouvez les separer par un espace ou entrer apres chaque champ) : ");
     scanf("%d %d %d",&(etu->dateNaissance.jour),&(etu->dateNaissance.mois),&(etu->dateNaissance.annee));
     diff = year - etu->dateNaissance.annee;
     if(diff!=etu->age) printf("veuillez Ressasir \n");
     } while (diff != etu->age);

    }

void afficherEtudiant(EtudiantRepere *etu,int i){
    printf("le nom du %d'%s etudiant est %s \n son prenom est %s \n son age est %d \n sa date de naissance est %d/%d/%d \n \n \n ",i+1,i==0?"er":"eme",etu->nom,etu->prenom,etu->age,etu->dateNaissance.jour,etu->dateNaissance.mois,etu->dateNaissance.annee); 
}

void lireTableauEtudiants(EtudiantRepere *etu, int taille){
    for(int i=0; i<taille; i++) lireEtudiant(etu+i,i); 
} 

float calculerMoyennePonderee(EtudiantRepere e){
    return (e.note[0] * 2 + e.note[1] + e.note[2]) / 4 ;
}
void afficherTableauEtudiants(EtudiantRepere *etu,int taille){
     float Moy,Moya;
    for(int i = 0 ; i < taille ; i++) {afficherEtudiant(etu+i,i) ; 
    Moy = calculerMoyennePonderee((etu[i]));
printf("La moyenne ponderee est : %.2f \n ",Moy );}
}

int sommeNotesRecursif(EtudiantRepere *tab, int taille){
    if (taille == 1) return calculerMoyennePonderee(tab[0]);
    else return calculerMoyennePonderee(tab[taille - 1]) + sommeNotesRecursif(tab,taille-1);

}

float calculerMoyenne(EtudiantRepere *tab, int taille){
    return (float) sommeNotesRecursif(tab,taille) / taille;
}

// MAIN //////////////////
int main(void){
    int taille;
    do{
    printf("entrer la taille de votre tableau : ");
    scanf("%d",&taille);
    if (taille < 1 )printf("FORMAT INCORRECTE, RESSAYER \n "); 
    } while (taille<1);
    EtudiantRepere *tab = (EtudiantRepere *) calloc(taille,sizeof(EtudiantRepere)); if(tab==NULL) exit(1);
    lireTableauEtudiants(tab,taille);
    afficherTableauEtudiants(tab,taille);
    printf("la moyenne de la classe est %.2f \n ",calculerMoyenne(tab,taille));
    
    // partie reallocation
    int CasesAjoutee;
   

     do{


        do {
        printf("voulez vous ajouter des etudiants ? : (combien) ");
        scanf("%d",&CasesAjoutee);
        }while(CasesAjoutee<0);


        if(CasesAjoutee == 0){
        return 0;
     }
        else {
    EtudiantRepere *tmp = (EtudiantRepere *) realloc(tab,sizeof(EtudiantRepere)*(taille+CasesAjoutee));
    if(tmp == NULL) {
        free(tab); 
        exit(1);
    }
     
     
        lireTableauEtudiants(tmp+taille,CasesAjoutee);
        afficherTableauEtudiants(tmp,taille+CasesAjoutee);
        printf("la moyenne de la classe est %.2f ",calculerMoyenne(tmp,taille+CasesAjoutee));
        tab = tmp;
        taille = taille + CasesAjoutee;
     }
        
    } while(CasesAjoutee !=0); 



   
}

