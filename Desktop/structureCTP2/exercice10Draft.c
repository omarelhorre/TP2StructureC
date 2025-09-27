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

void validerDateNaissance(EtudiantRepere *e){
       // extraction de l'année depuis la libraire time.h
    time_t t = time(NULL);
    struct tm date = *localtime(&t); //??
    int year = date.tm_year + 1900;
    int diff;
    //boucle tant que l'annee de naissance ne coincide pas avec l'age
     do {printf("Entrer la date de naissance (jours mois annee) : ");
     scanf("%d %d %d",&(e->dateNaissance.jour),&(e->dateNaissance.mois),&(e->dateNaissance.annee));
     diff = year - e->dateNaissance.annee;
     if(diff!=e->age) printf("veuillez Ressasir \n");
     } while (diff != e->age);
    
}

//fonction de lecture des information de l'etudiant
void lireEtudiant(EtudiantRepere *etu, int i){
    // entree des donnees
    printf("Lecture des informations pour le %d'%s etudiant\n",i+1, i==0? "er":"eme");
     printf("entrer le nom du l'etudiant : ");
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
    validerDateNaissance(etu); 

    }


float calculerMoyennePonderee(EtudiantRepere e){
    return (float) (e.note[0] * 2 + e.note[1] + e.note[2]) / 4 ;
}


void afficherEtudiant(EtudiantRepere *etu,int i){
    printf("Information pour le %d'%s etudiant : \n ",i+1,i==0?"er":"eme");
    printf("%s %s, %d ans, né(e)) le %d/%d/%d \n  ",etu->nom,etu->prenom,etu->age,etu->dateNaissance.jour,etu->dateNaissance.mois,etu->dateNaissance.annee); 
}

void lireTableauEtudiants(EtudiantRepere *etu, int taille){
    for(int i=0; i<taille; i++) lireEtudiant(etu+i,i); 
    printf("\n \n \n");
} 




void afficherTableauEtudiants(EtudiantRepere *etu,int taille){
     float Moy;
    for(int i = 0 ; i < taille ; i++) {afficherEtudiant(etu+i,i) ; 
    Moy = calculerMoyennePonderee((etu[i])); 
printf("maths %d, physique %d, science %d\n",etu[i].note[0],etu[i].note[1],etu[i].note[2]);
printf("La moyenne ponderee est : %.2f",Moy );
printf("\n \n \n"); //retour a la ligne apres chaque etudiant

}


}





//fonction Recursive qui calcule la somme des moyennes ponderees afin de les diviser sur la taille a l'aide de la fonction CalculerMoyenne
float sommeNotesRecursif(EtudiantRepere *tab, int taille){
    if (taille == 1) return calculerMoyennePonderee(tab[0]);
    else return (float) (calculerMoyennePonderee(tab[taille - 1]) + sommeNotesRecursif(tab,taille-1));

}

float calculerMoyenne(EtudiantRepere *tab, int taille){
    return (float)(sommeNotesRecursif(tab,taille) / taille);
}

// MAIN //////////////////
int main(void){
    int taille;
    do{
    printf("entrer le nombre d'etudiants : ");
    scanf("%d",&taille);
    if (taille < 1 )printf("FORMAT INCORRECTE, RESSAYER \n "); 
    } while (taille<1);
    EtudiantRepere *tab = (EtudiantRepere *) calloc(taille,sizeof(EtudiantRepere)); if(tab==NULL) exit(1);
    lireTableauEtudiants(tab,taille);
    printf("\n \n \n");
    afficherTableauEtudiants(tab,taille);
    printf("\n \n \n");
    printf("la moyenne de la classe est %.2f \n \n \n ",calculerMoyenne(tab,taille));
    
    // partie reallocation
    int CasesAjoutee;
   
//boucle infinie 
     while(1 /* la condition est toujours vraie car vraie est vraie on peut aussi ajouter la librairie stdbool pour utiliser le mot "TRUE" a la place de 1*/){

//boucle infinie qui force l'entrée d'un chifre superieur ou egale a 0
        do {
        printf("voulez vous ajouter des etudiants ? : (combien) ");
        scanf("%d",&CasesAjoutee);
        }while(CasesAjoutee<0);

// si on veut 0 pour proteger la memoire on libere tab
        if(CasesAjoutee == 0){
        free(tab);
        break;
     }
//sinon si c'est pas 0 on realloue notre tableau
        else {
    EtudiantRepere *tmp = (EtudiantRepere *) realloc(tab,sizeof(EtudiantRepere)*(taille+CasesAjoutee));
    //cas memoire saturee
    if(tmp == NULL) {
        printf("Memoire saturee!!");
        free(tab); 
        exit(1);
    }

//si la memoire est saturee le programme va s'arrete donc pas la necessité d'utiliser un else ( NB on a utiliser exit(1) si on a juste afficher un mechage d'erreur faut changer le traitement)
     
        lireTableauEtudiants(tmp+taille,CasesAjoutee);
        printf("\n \n \n");
        afficherTableauEtudiants(tmp,taille+CasesAjoutee);
        printf("\n \n \n");
        printf("la moyenne de la classe est %.2f \n \n \n ",calculerMoyenne(tmp,taille+CasesAjoutee));
        // on a fait avant realloc(tab....) donc pour effectuer le traitement il faut que tab recoit tmp
        tab = tmp;
        //la nouvelle taille mantenant est l ancienne taille apres
        taille = taille + CasesAjoutee;
     }
        
    }
//on peut ajoutee un free mais c'est deja fait dans la boucle tab et tmp pointe sur le meme tableau il suffit de libere 1 des deux


   return 0;
}

