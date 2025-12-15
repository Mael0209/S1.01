#include <stdio.h>
#include <string.h>
#define N_MAX 100
#define N_MAX_MATIERES 15
#define N_MAX_EVALS 15

// Structuration de la structure Etudiant : 
// nom, prenom, 
// tableau des matières 
// (lui-même contenant une structure Matiere contenant la liste des evaluations...)

typedef struct Evaluation{
    float note, coeff; // Le coeff est facultatif
}Evaluation;

typedef struct Matiere
{
    char nom[50]; // nom de la amtière (Taille à revoir)
    int nombreEvaluations; 
    float moyenne; // Moyenne de la matière (A voir comment la calculer)
    Evaluation listeEvaluations[N_MAX_EVALS]; // Liste des évaluations, utilise uen constante pour la taille
}Matiere;

typedef struct Etudiant
{
    char nom[30], prenom[30];
    int nombreMatieres;
    Matiere matieres[N_MAX_MATIERES];
}Etudiant;

void saisieNouveauEtudiant(Etudiant listeEtudiants[], int *nombreEtudiants)
{
    printf("Saisie nouveau etudiant\n");
}

int main()
{
    Etudiant listeEtudiants[N_MAX];
    int nombreEtudiants = 0;
    int reponse;
    do
    {
        printf("Saisissez un chiffre correspondant a une option: \n1 - Saisir un nouvel etudiant \n0 - Quitter le programme \n");
        scanf("%d", &reponse);
        switch(reponse){
            case 1:
                saisieNouveauEtudiant(listeEtudiants, &nombreEtudiants);
                break;
            case 0: 
                break;
            default:
                printf("Choix invalide. \n");
                break;
        }
    } while (reponse != 0);
    return 0;
}