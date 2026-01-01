#include <stdio.h>
#include <string.h>

#define MAX_ETUD 100
#define MAX_MAT 10
#define MAX_EVAL 20

void saisirEtudiants(char nomsEtudiants[][50], int *nbEtudiants)
{
    int nombreSaisies;
    printf("Combien d'etudiants à ajouter ? ");
    scanf("%d", &nombreSaisies);
    getchar();

    for (int i = 0; i < nombreSaisies; i++)
    {
        if (*nbEtudiants >= MAX_ETUD)
        {
            printf("Tableau plein !\n");
            break;
        }
        printf("Nom et Prenom de l'etudiant %d : ", *nbEtudiants + 1);
        fgets(nomsEtudiants[*nbEtudiants], 50, stdin);

        nomsEtudiants[*nbEtudiants][strcspn(nomsEtudiants[*nbEtudiants], "\n")] = 0;

        (*nbEtudiants)++;
    }
}

void ajouterMatiere(char nomsMatieres[][20], int *nbMatieres)
{
    if (*nbMatieres >= MAX_MAT)
    {
        printf("Max matieres atteint.\n");
        return;
    }
    printf("Nom de la nouvelle matiere : ");
    scanf("%s", nomsMatieres[*nbMatieres]);
    (*nbMatieres)++;
}

void saisirNotes(float notes[MAX_ETUD][MAX_MAT][MAX_EVAL], int nbNotes[MAX_ETUD][MAX_MAT], char nomsEtudiants[][50], char nomsMatieres[][20], int nbEtudiants, int nbMatieres)
{

    int choixEtud, choixMat;
    float note;

    if (nbEtudiants == 0 || nbMatieres == 0)
    {
        printf("\nIl faut au moins un etudiant et une matiere pour saisir des notes.\n");
        return;
    }

    printf("\n--- Saisie de note ---\n");
    for (int i = 0; i < nbEtudiants; i++)
    {
        printf("%d. %s\n", i + 1, nomsEtudiants[i]);
    }
    printf("Choisissez le numero de l'etudiant : ");
    scanf("%d", &choixEtud);
    int i = choixEtud - 1;

    for (int j = 0; j < nbMatieres; j++)
    {
        printf("%d. %s\n", j + 1, nomsMatieres[j]);
    }
    printf("Choisissez le numero de la matiere : ");
    scanf("%d", &choixMat);
    int j = choixMat - 1;

    int k = nbNotes[i][j];

    if (k < MAX_EVAL)
    {
        printf("Entrez la note : ");
        scanf("%f", &note);

        notes[i][j][k] = note;

        nbNotes[i][j]++;
        printf("Note enregistree.\n");
    }
    else
    {
        printf("Plus de place pour des notes dans cette matiere.\n");
    }
}

void afficherResultats(float notes[MAX_ETUD][MAX_MAT][MAX_EVAL], int nbNotes[MAX_ETUD][MAX_MAT], char nomsEtudiants[][50], char nomsMatieres[][20], int nbEtudiants, int nbMatieres)
{

    printf("\n--- Bulletins ---\n");
    for (int i = 0; i < nbEtudiants; i++)
    {
        printf("\nEtudiant : %s\n", nomsEtudiants[i]);
        float sommeGenerale = 0;
        int matieresComptees = 0;

        for (int j = 0; j < nbMatieres; j++)
        {
            float sommeMat = 0;
            int nb = nbNotes[i][j];

            if (nb > 0)
            {
                for (int k = 0; k < nb; k++)
                {
                    sommeMat += notes[i][j][k];
                }
                float moyMat = sommeMat / nb;
                printf("  - %s : %.2f (sur %d notes)\n", nomsMatieres[j], moyMat, nb);

                sommeGenerale += moyMat;
                matieresComptees++;
            }
            else
            {
                printf("  - %s : Pas de notes\n", nomsMatieres[j]);
            }
        }

        if (matieresComptees > 0)
            printf("  >> Moyenne Generale : %.2f\n", sommeGenerale / matieresComptees);
        else
            printf("  >> Pas de moyenne calculee.\n");
    }
}

void trierEtudiantsParMoyenne(float notes[MAX_ETUD][MAX_MAT][MAX_EVAL], int nbNotes[MAX_ETUD][MAX_MAT], char nomsEtudiants[][50], int nbEtudiants, int nbMatieres)
{

    // Tableau temporaire pour stocker les moyennes générales le temps du tri
    float moyGen[MAX_ETUD];

    // --- CALCUL PRÉALABLE DES MOYENNES ---
    for (int i = 0; i < nbEtudiants; i++)
    {
        float sommeTotale = 0;
        int matieresComptees = 0;

        for (int m = 0; m < nbMatieres; m++)
        {
            if (nbNotes[i][m] > 0)
            {
                float sommeMat = 0;
                for (int k = 0; k < nbNotes[i][m]; k++)
                {
                    sommeMat += notes[i][m][k];
                }
                sommeTotale += (sommeMat / nbNotes[i][m]);
                matieresComptees++;
            }
        }
        if (matieresComptees > 0)
            moyGen[i] = sommeTotale / matieresComptees;
        else
            moyGen[i] = 0.0;
    }

    // tri à bulles des étudiants selon leurs moyennes générales
    for (int i = 0; i < nbEtudiants - 1; i++)
    {
        for (int j = 0; j < nbEtudiants - i - 1; j++)
        {
            if (moyGen[j] < moyGen[j + 1])
            {
                float tempMoy = moyGen[j];
                moyGen[j] = moyGen[j + 1];
                moyGen[j + 1] = tempMoy;

                char tempNom[50];
                strcpy(tempNom, nomsEtudiants[j]);
                strcpy(nomsEtudiants[j], nomsEtudiants[j + 1]);
                strcpy(nomsEtudiants[j + 1], tempNom);

                for (int m = 0; m < MAX_MAT; m++)
                {
                    int tempNb = nbNotes[j][m];
                    nbNotes[j][m] = nbNotes[j + 1][m];
                    nbNotes[j + 1][m] = tempNb;

                    for (int k = 0; k < MAX_EVAL; k++)
                    {
                        float tempNote = notes[j][m][k];
                        notes[j][m][k] = notes[j + 1][m][k];
                        notes[j + 1][m][k] = tempNote;
                    }
                }
            }
        }
    }
    printf("\nTri effectue avec succes !\n");
}

void trierEtudiantsParMatiere(float notes[MAX_ETUD][MAX_MAT][MAX_EVAL], int nbNotes[MAX_ETUD][MAX_MAT], char nomsEtudiants[][50], char nomsMatieres[][20], int nbEtudiants, int nbMatieres)
{
    int choixMat;
    printf("\n--- Tri par matiere ---\n");
    for (int j = 0; j < nbMatieres; j++)
    {
        printf("%d. %s\n", j + 1, nomsMatieres[j]);
    }
    printf("Choisissez la matiere pour le tri : ");
    scanf("%d", &choixMat);
    int indexMat = choixMat - 1;

    if (indexMat < 0 || indexMat >= nbMatieres)
    {
        printf("Matiere invalide.\n");
        return;
    }

    float moyMatiere[MAX_ETUD];

    for (int i = 0; i < nbEtudiants; i++)
    {
        int nb = nbNotes[i][indexMat];
        if (nb > 0)
        {
            float somme = 0;
            for (int k = 0; k < nb; k++)
            {
                somme += notes[i][indexMat][k];
            }
            moyMatiere[i] = somme / nb;
        }
        else
        {
            moyMatiere[i] = -1.0; // Indicateur d'absence de notes
        }
    }

    // 3. TRI A BULLES (Décroissant)
    for (int i = 0; i < nbEtudiants - 1; i++)
    {
        for (int j = 0; j < nbEtudiants - i - 1; j++)
        {

            if (moyMatiere[j] < moyMatiere[j + 1])
            {
                float tempMoy = moyMatiere[j];
                moyMatiere[j] = moyMatiere[j + 1];
                moyMatiere[j + 1] = tempMoy;

                char tempNom[50];
                strcpy(tempNom, nomsEtudiants[j]);
                strcpy(nomsEtudiants[j], nomsEtudiants[j + 1]);
                strcpy(nomsEtudiants[j + 1], tempNom);

                for (int m = 0; m < MAX_MAT; m++)
                {
                    int tempNb = nbNotes[j][m];
                    nbNotes[j][m] = nbNotes[j + 1][m];
                    nbNotes[j + 1][m] = tempNb;

                    for (int k = 0; k < MAX_EVAL; k++)
                    {
                        float tempNote = notes[j][m][k];
                        notes[j][m][k] = notes[j + 1][m][k];
                        notes[j + 1][m][k] = tempNote;
                    }
                }
            }
        }
    }
    printf("\nTri par %s effectue !\n", nomsMatieres[indexMat]);
}

int main()
{
    char nomsEtudiants[MAX_ETUD][50];
    char nomsMatieres[MAX_MAT][20];

    float notes[MAX_ETUD][MAX_MAT][MAX_EVAL];

    int nbNotes[MAX_ETUD][MAX_MAT] = {0};

    int nbEtudiants = 0;
    int nbMatieres = 0;
    int choix;

    do
    {
        printf("\n--- MENU ---\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Creer une matiere\n");
        printf("3. Saisir une note\n");
        printf("4. Afficher les resultats\n");
        printf("5. Trier les etudiants par moyenne generale\n");
        printf("6. Trier les etudiants par moyenne d'une matiere\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            saisirEtudiants(nomsEtudiants, &nbEtudiants);
            break;
        case 2:
            ajouterMatiere(nomsMatieres, &nbMatieres);
            break;
        case 3:
            saisirNotes(notes, nbNotes, nomsEtudiants, nomsMatieres, nbEtudiants, nbMatieres);
            break;
        case 4:
            afficherResultats(notes, nbNotes, nomsEtudiants, nomsMatieres, nbEtudiants, nbMatieres);
            break;
        case 5:
            trierEtudiantsParMoyenne(notes, nbNotes, nomsEtudiants, nbEtudiants, nbMatieres);
            break;
        case 6:
            trierEtudiantsParMatiere(notes, nbNotes, nomsEtudiants, nomsMatieres, nbEtudiants, nbMatieres);
            break;
        }
    } while (choix != 0);

    return 0;
}