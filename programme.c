#include <stdio.h>
#include <string.h>
#define N_MAX 100
#define N_MAX_MATIERES 15
#define N_MAX_EVALS 15

// Structuration de la structure Etudiant :
// nom, prenom,
// tableau des matières
// (lui-même contenant une structure Matiere contenant la liste des evaluations...)

typedef enum nomMatieres
{
    maths,
    physique,
    SVT,
    Anglais
} indexMatieres;
indexMatieres indexMatiere = maths;

typedef struct Evaluation
{
    float note, coeff; // Le coeff est facultatif
} Evaluation;

typedef struct Matiere
{
    char nom[50]; // nom de la amtière (Taille à revoir)
    int nombreEvaluations;
    float moyenne;                            // Moyenne de la matière (A voir comment la calculer)
    Evaluation listeEvaluations[N_MAX_EVALS]; // Liste des évaluations, utilise uen constante pour la taille
} Matiere;

typedef struct Etudiant
{
    char nom[30], prenom[30];
    int nombreMatieres;
    Matiere matieres[N_MAX_MATIERES];
} Etudiant;

void saisieNouveauEtudiant(Etudiant listeEtudiants[], int *nombreEtudiants)
{
    int nombreSaisies;
    printf("Combien d'etudiants souhaitez-vous enregistrer ? ");
    scanf("%d", &nombreSaisies);
    for (int i = 0; i < nombreSaisies; i++)
    {
        char nom[30], prenom[30];
        printf("Saisissez le nom et prenom de l'etudiant de la saisie %d : ", i+1);
        scanf("%s%s", &nom, &prenom);
        strcpy(listeEtudiants[*nombreEtudiants].nom, nom);
        strcpy(listeEtudiants[*nombreEtudiants].prenom, prenom);
        (*nombreEtudiants)++;
    }
}

void afficherEtudiants()
{
    // A faire
}

int main()
{
    Etudiant listeEtudiants[N_MAX];
    int nombreEtudiants = 0;
    int reponse;
    do
    {
        printf("Saisissez un chiffre correspondant a une option: \n1 - Saisir un nouvel etudiant \n2 - Afficher tous les etudiants\n0 - Quitter le programme \n");
        scanf("%d", &reponse);
        switch (reponse)
        {
        case 1:
            saisieNouveauEtudiant(listeEtudiants, &nombreEtudiants);
            break;
        case 2:
            afficherEtudiants();
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