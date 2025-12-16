#include <stdio.h>
#include <string.h>

#define N_MAX_ETUD 100
#define N_MAX_MATIERES 5
#define N_MAX_EVALS 30

typedef struct Evaluation
{
    float note, coeff;
} Evaluation;

typedef struct Matiere
{
    char nom[50];
    float moyenne;
    Evaluation listeEvaluations[N_MAX_EVALS];
} Matiere;

typedef struct Etudiant
{
    char nom[30], prenom[30];
    int nombreMatieres;
    Matiere matieres[N_MAX_MATIERES];
} Etudiant;

// CORRECTION : Passage par pointeur (*etud) et ajout de la liste globale pour copier les noms
void initMatieres(Etudiant *etud, char listeMatieresGlobale[][15], int nbMatieresActuelles)
{
    etud->nombreMatieres = nbMatieresActuelles;
    for (int i = 0; i < nbMatieresActuelles; i++)
    {
        strcpy(etud->matieres[i].nom, listeMatieresGlobale[i]);
        etud->matieres[i].moyenne = 0;
    }
}

void saisieNouveauEtudiant(Etudiant listeEtudiants[], int *nombreEtudiants, char listeMatieresGlobale[][15], int nbMatieres)
{
    int nombreSaisies;
    printf("Combien d'etudiants souhaitez-vous enregistrer ? ");
    scanf("%d", &nombreSaisies);
    for (int i = 0; i < nombreSaisies; i++)
    {
        char nom[30], prenom[30];
        Etudiant *nouveauEtudiant = &listeEtudiants[*nombreEtudiants];
        
        printf("Saisissez le NOM et PRENOM de l'etudiant de la saisie %d : ", i + 1);
        scanf("%s%s", nom, prenom);
        
        strcpy(nouveauEtudiant->nom, nom);
        strcpy(nouveauEtudiant->prenom, prenom);
        
        initMatieres(nouveauEtudiant, listeMatieresGlobale, nbMatieres);
        
        (*nombreEtudiants)++;
    }
}

void creerMatiere(char listeMatieres[N_MAX_MATIERES][15], int *nombreMatieres, int nombreEtudiants, Etudiant listeEtudiants[N_MAX_ETUD])
{
    char nomNouvelleMatiere[15];
    printf("Matieres deja existantes : \n");
    if (*(nombreMatieres) == 0)
    {
        printf("Aucune matiere enregistree.\n");
    }
    else
    {
        for (int i = 0; i < *nombreMatieres; i++)
        {
            printf("-  %s\n", listeMatieres[i]);
        }
    }
    printf("Entrez le nom de la nouvelle matiere :\n");
    scanf("%s", nomNouvelleMatiere);
    
    strcpy(listeMatieres[*nombreMatieres], nomNouvelleMatiere);

    if (nombreEtudiants > 0)
    {
        for (int i = 0; i < nombreEtudiants; i++)
        {
            Etudiant *pEtud = &listeEtudiants[i];
            Matiere *pNouvelleMatiere = &pEtud->matieres[*(nombreMatieres)];
            
            strcpy(pNouvelleMatiere->nom, nomNouvelleMatiere);
            pNouvelleMatiere->moyenne = 0;
            
            pEtud->nombreMatieres++; 
            
            printf("Ajoute pour %s %s : %s %f\n", pEtud->prenom, pEtud->nom, pNouvelleMatiere->nom, pNouvelleMatiere->moyenne);
        }
    }

    *(nombreMatieres) = *(nombreMatieres) + 1;
}

void afficherEtudiants()
{
    // A faire
}

int main()
{
    Etudiant listeEtudiants[N_MAX_ETUD];
    int nombreEtudiants = 0;
    char listeMatieres[N_MAX_MATIERES][15] = {"maths", "physique", "SVT", "anglais"};
    int nombreMatieres = 4;
    int reponse;
    do
    {
        if (nombreMatieres == 0)
        {
            creerMatiere(listeMatieres, &nombreMatieres, nombreEtudiants, listeEtudiants);
        }
        
        printf("Saisissez un chiffre correspondant a une option: \n1 - Creer une nouvelle matiere\n2 - Saisir un nouvel etudiant \n3 - Afficher tous les etudiants\n0 - Quitter le programme \n");
        scanf("%d", &reponse);
        switch (reponse)
        {
        case 1:
            creerMatiere(listeMatieres, &nombreMatieres, nombreEtudiants, listeEtudiants);
            break;
        case 2:
            saisieNouveauEtudiant(listeEtudiants, &nombreEtudiants, listeMatieres, nombreMatieres);
            break;
        case 3:
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