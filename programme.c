#include <stdio.h>
#include <string.h>
#define N_MAX_ETUD 100
#define N_MAX_MATIERES 4
#define N_MAX_EVALS 15

// Structuration de la structure Etudiant :
// nom, prenom,
// tableau des matières
// (lui-même contenant une structure Matiere contenant la liste des evaluations...)

typedef enum indexMatieres
{
    maths,
    physique,
    SVT,
    Anglais
} indexMatieres;
indexMatieres indexMatiere;

typedef struct Evaluation
{
    float note, coeff; // Le coeff est facultatif
} Evaluation;

typedef struct Matiere
{
    char nom[50]; // nom de la matière (Taille à revoir)
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

void initMatieres(Etudiant etud)
{
    char listeMatieres[N_MAX_MATIERES][15] = {"maths", "physique", "SVT", "anglais"};
    printf("Pour chaque matiere, saisir le nombre d'evaluations : \n");
    for (int i=0; i<N_MAX_MATIERES; i++){
        char *nomMatiere = listeMatieres[i];
        printf("%s\n", nomMatiere);
    }
}

void saisieNouveauEtudiant(Etudiant listeEtudiants[], int *nombreEtudiants)
{
    int nombreSaisies;
    printf("Combien d'etudiants souhaitez-vous enregistrer ? ");
    scanf("%d", &nombreSaisies);
    for (int i = 0; i < nombreSaisies; i++)
    {
        char nom[30], prenom[30];
        Etudiant nouveauEtudiant = listeEtudiants[*nombreEtudiants]; // Insertion du nouveau etudiant dans la liste
        nouveauEtudiant.nombreMatieres = 4;
        printf("Saisissez le NOM et PRENOM de l'etudiant de la saisie %d : ", i + 1);
        scanf("%s%s", &nom, &prenom);
        strcpy(nouveauEtudiant.nom, nom);
        strcpy(nouveauEtudiant.prenom, prenom);
        initMatieres(nouveauEtudiant);
        (*nombreEtudiants)++; // nombreEtudiants permet à la fois de savoir le nbr d'étudiants et l'indice du prochain etudiant dans la liste
    }
}

void afficherEtudiants()
{
    // A faire
}

int main()
{
    Etudiant listeEtudiants[N_MAX_ETUD];
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