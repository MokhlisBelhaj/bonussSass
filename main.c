#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

struct tache
{
    int id;
    char titre[100];
    char desc[200];
    char deadline[11];
    char status[20];
    char dateDajout[20];
};
struct collaborateur
{
    int id;
    char nom[30];
    char prenom[30];
    char email[30];
};
struct collaboration
{
    int id;
    int idTache;
    int idCollaborateur[30];
};

struct tache taches[100];
struct collaborateur collaborateurs[100];
struct collaboration collaborations[100];

int nombreDeTaches = 0;
int nombreDeCollaborateurs = 0;
int nombreDeCollaborations = 0;
int defCollaboration =0;
int def =1;
int defCollaborateur =1;
int sortie = 1;
int correct;

void ajouterCollaborateur(){
    collaborateurs[nombreDeCollaborateurs].id = nombreDeCollaborateurs + defCollaborateur;
    printf("Nouvelle Collaborateur %d :\n", collaborateurs[nombreDeCollaborateurs].id);
    printf("Veuillez saisir le nom du collaborateur : ");
    scanf("%s", collaborateurs[nombreDeCollaborateurs].nom);
    printf("Veuillez saisir le prenom du collaborateur : ");
    scanf("%s", collaborateurs[nombreDeCollaborateurs].prenom);
    printf("Veuillez saisir l'email du collaborateur : ");
    scanf("%s", collaborateurs[nombreDeCollaborateurs].email);
    nombreDeCollaborateurs++;
}

void affectationSimpleTache(){
    int idCollaborateur,idTache;
    int i,j;

    printf("Veuillez saisir l'id de la tache : ");
    scanf("%d",&idTache);

    for(i = 0; i < nombreDeTaches; i++){
        if(taches[i].id == idTache){
            printf("Veuillez saisir l'id du collaborateur : ");
            scanf("%d",&idCollaborateur);
            for(j=0; j <nombreDeCollaborateurs; j++){
                if (collaborateurs[j].id == idCollaborateur)
                {
                    collaborations[nombreDeCollaborations].id=nombreDeCollaborations+defCollaboration;
                    collaborations[nombreDeCollaborations].idCollaborateur[0]=idCollaborateur;
                    collaborations[nombreDeCollaborations].idTache=idTache;
                    nombreDeCollaborations++;
                    break;
                }else{   
                    printf("collaborateur n'existe pas");
                }
            }
            break;
        }else{
            printf("tache n'existe pas");
        }
    }
}

void affectationMultipleCollaborateur(){
    // int test=0;
    int idCollaborateur,idTache;
    int i,j;

    printf("Veuillez saisir l'id de la tache : ");
    scanf("%d",&idTache);
    for(i = 0; i < nombreDeTaches; i++){
        if(taches[i].id == idTache){
            int sort;
            do{
                printf("Veuillez saisir l'id du collaborateur : ");
                scanf("%d",&idCollaborateur);
                for(j=0; j <nombreDeCollaborateurs; j++){
                    if (collaborateurs[j].id == idCollaborateur)
                    {
                    
                        collaborations[nombreDeCollaborations].id=nombreDeCollaborations+defCollaboration;
                        collaborations[nombreDeCollaborations].idCollaborateur[j]=idCollaborateur;
                        collaborations[nombreDeCollaborations].idTache=idTache;
                        nombreDeCollaborations++;
                        break;
                    }else{
                        printf("collaborateur n'existe pas");
                    }
                }
                printf("voulez-vous ajouter un autre collaborateur\n 0----------->oui 1----------->non\n");
                scanf("%d",&sort);
            }while(sort==0);
            
        }else{
            printf("tache n'existe pas");
            break;
        }
    }
    
}

void ajouterTache()
{
    taches[nombreDeTaches].id = nombreDeTaches + def;
    printf("Nouvelle tache %d :\n", taches[nombreDeTaches].id);

    printf("Titre : ");
    scanf(" %[^\n]s", taches[nombreDeTaches].titre);

    printf("Description : ");
    scanf(" %[^\n]s", taches[nombreDeTaches].desc);

    // printf("Deadline (format YYYY-MM-DD) : ");
    // scanf("%s", taches[nombreDeTaches].deadline);
    do
    {
        correct = 0;
        printf("Deadline (format YYYY-MM-DD) : ");
        scanf("%s", taches[nombreDeTaches].deadline);

        if (strlen(taches[nombreDeTaches].deadline) != 10)
        {
            printf("L'entree n'est pas au format correct (YYYY-MM-DD).\n");
            correct = 1;
            continue;
        }

        if (taches[nombreDeTaches].deadline[4] != '-' || taches[nombreDeTaches].deadline[7] != '-')
        {
            printf("L'entree n'est pas au format correct (YYYY-MM-DD).\n");
            correct = 1;
            continue;
        }

        for (int i = 0; i < 10; i++)
        {
            if (i == 4 || i == 7)
            {
                continue;
            }
            if (!isdigit(taches[nombreDeTaches].deadline[i]))
            {
                printf("L'entree n'est pas au format correct (YYYY-MM-DD).\n");
                correct = 1;
                break; 
            }
        }

        if (correct == 0)
        {
            printf("L'entree est au format correct.\n");
        }
    } while (correct != 0);

    // bonus
    // Obtenir la date actuelle
    time_t tempsActuel;
    struct tm *tempsInfo;
    time(&tempsActuel);
    tempsInfo = localtime(&tempsActuel);

    // Formater la date  au format YYYY-MM-DD
    strftime(taches[nombreDeTaches].dateDajout, sizeof(taches[nombreDeTaches].dateDajout), "%Y-%m-%d", tempsInfo);

    strcpy(taches[nombreDeTaches].status, "aRealiser");

    nombreDeTaches++;
}
void trierTachesParTitre()
{
    if (nombreDeTaches <= 0)
    {
        printf("Aucune tache à trier.\n");
        return;
    }

    // TriSelection
    for (int i = 0; i < nombreDeTaches - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < nombreDeTaches; j++)
        {
            if (strcmp(taches[j].titre, taches[minIndex].titre) < 0)
            {
                minIndex = j;
            }
        }
        // swap
        if (minIndex != i)
        {
            struct tache temp = taches[i];
            taches[i] = taches[minIndex];
            taches[minIndex] = temp;
        }
    }
    printf("******Taches trie3es par titre****** :\n");
    int i;
    for (i = 0; i < nombreDeTaches; i++)
    {
        // printf("Tache %d\n", i + 1);
        printf("ID : %d\n", taches[i].id);
        printf("Titre : %s\n", taches[i].titre);
        printf("Description : %s\n", taches[i].desc);
        printf("Deadline : %s\n", taches[i].deadline);
        printf("date D'ajout : %s\n", taches[i].dateDajout);
        printf("Statut : %s\n", taches[i].status);
        printf("\n");
    }
}
void trierTachesParDeadline()
{
    if (nombreDeTaches <= 0)
    {
        printf("Aucune tache à trier.\n");
        return;
    }

    // Tri par sélection
    for (int i = 0; i < nombreDeTaches - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < nombreDeTaches; j++)
        {
            // Comparer les deadlines directement
            if (strcmp(taches[j].deadline, taches[minIndex].deadline) < 0)
            {
                minIndex = j;
            }
        }
        // Échanger les taches
        if (minIndex != i)
        {
            struct tache temp = taches[i];
            taches[i] = taches[minIndex];
            taches[minIndex] = temp;
        }
    }

    // Afficher
    printf("Taches triees par deadline :\n");
    int i;
    for (i = 0; i < nombreDeTaches; i++)
    {
        // printf("Tache %d\n", i + 1);
        printf("ID : %d\n", taches[i].id);
        printf("Titre : %s\n", taches[i].titre);
        printf("Description : %s\n", taches[i].desc);
        printf("Deadline : %s\n", taches[i].deadline);
        printf("date D'ajout : %s\n", taches[i].dateDajout);
        printf("Statut : %s\n", taches[i].status);
        printf("\n");
    }
}

// ----------------------------------------------------------------
// Fonctonpour donner les taches a deadline moins de 3 jours
void afficherTachesAvecDeadlineProche()
{
    printf("\nTaches avec un delai de 3 jours ou moins :\n");
    int i;
    for (i = 0; i < nombreDeTaches; i++)
    {
        struct tm deadline_tm = {0};
        struct tm current_tm = {0};
        int joursRestants;

        // Convertisse
        sscanf(taches[i].deadline, "%d-%d-%d", &deadline_tm.tm_year, &deadline_tm.tm_mon, &deadline_tm.tm_mday);
        deadline_tm.tm_year -= 1900;
        deadline_tm.tm_mon -= 1;

        // date actuelle
        time_t now;
        time(&now);
        current_tm = *localtime(&now);
        // printf("%d-%d-%d", current_tm.tm_year,current_tm.tm_mon,current_tm.tm_mday);

        // Calculez la différence entre la date limite et la date actuelle en jours
        time_t deadline_time = mktime(&deadline_tm);
        time_t current_time = mktime(&current_tm);
        joursRestants = (int)((deadline_time - current_time) / (60 * 60 * 24));

        if (joursRestants >= 0 && joursRestants <= 3)
        {
            printf("Tache %d\n", i + 1);
            printf("ID : %d\n", taches[i].id);
            printf("Titre : %s\n", taches[i].titre);
            printf("Description : %s\n", taches[i].desc);
            printf("date D'ajout : %s\n", taches[i].dateDajout);
            printf("Deadline : %s\n", taches[i].deadline);
            printf("Statut : %s\n", taches[i].status);
            printf("\n");
        }
    }
}
// ------------------------------------------------------------------
// bonus
// afficher Taches Par Statut

    //  ----------------------------------------------------------------
    void rechercherTacheParStatut(char a[9])
    {
       printf("*******************les taches %s*******************\n", a);
int test=0;
        for (int i = 0; i < nombreDeTaches; i++)
        {
            if (strcmp(taches[i].status, a) == 0)
            {
                printf("Tache %d\n", i + 1);
                printf("ID : %d\n", taches[i].id);
                printf("Titre : %s\n", taches[i].titre);
                printf("Description : %s\n", taches[i].desc);
                printf("date D'ajout : %s\n", taches[i].dateDajout);
                printf("Deadline : %s\n", taches[i].deadline);
                printf("Statut : %s\n", taches[i].status);
                printf("\n");
               
 test++;
            }
        }
        if (test == 0)
        printf("aucune tache %s\n",a);
    }
    //  ----------------------------------------------------------------
void afficherTachesParStatut()
{
    int Souschoix;

    int soustest = 0;
    do
    {
        printf("*******************rechercher tous les taches par statut*******************\n");
        printf("1- aRealiser \n");
        printf("2 en cours de realisation.\n");
        printf("3 finalisee.\n");
        printf("4- retour \n");

        int sousResultt;

        do
        {
            printf("Entrez votre choix : ");
            sousResultt = scanf("%d", &Souschoix);

            if (sousResultt == 0)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }
        } while (sousResultt == 0);
        switch (Souschoix)
        {

        case 1:
            rechercherTacheParStatut("aRealiser");
            break;
        case 2:
            rechercherTacheParStatut("EnCours");
            break;
        case 3:
            rechercherTacheParStatut("finalisee");
            break;
        case 4:
       system("cls");
            soustest = 1;
            break;
        default:
            printf("choix invalid \n");
            break;
        }

    } while (soustest == 0);

    //  ----------------------------------------------------------------
    //  ----------------------------------------------------------------
}
// Afficher  les taches
void AfficherTousTaches()
{ 
    int souschoix;
    int soustest = 0;
    do
    {

        printf("*******************Afficher tous les taches*******************\n");
        printf("1 Trier les taches par ordre alphabetique.\n");
        printf("2 Trier les taches par deadline.\n");
        printf("3 Afficher les taches dont le deadline est dans 3 jours ou moins.\n");
        printf("4  Menu principale \n");
        int sousResultt;

        do
        {
            printf("Entrez votre choix : ");
            sousResultt = scanf("%d", &souschoix);

            if (sousResultt == 0)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }
        } while (sousResultt == 0);

        switch (souschoix)
        {
        case 1:
            trierTachesParTitre();
            break;
        case 2:
            trierTachesParDeadline();
            break;
        case 3:
            afficherTachesAvecDeadlineProche();

            break;
        
        case 4:
            system("cls");
            soustest = 1;

            break;

        default:
            printf("choix invalid\n");
            break;
        }
    } while (soustest == 0);
}

// modifier la description d'une tache
void modifierDescription()
{
    printf("Entrez l'ID de la tache que vous souhaitez modifier : ");
    int id;
    scanf("%d", &id);
    int i;

    for (i = 0; i < nombreDeTaches; i++)
    {
        if (taches[i].id == id)
        {
            printf("Nouvelle description : ");
            scanf("%s", taches[i].desc);
            break;
        }
    }
    printf("La description de la tache a ete mise à jour.\n");
}
// modifier le status d'une tache
void modifierStatut()
{
    int i, test = 0;
    printf("Entrez l'ID de la tache dont vous souhaitez modifier le statut : ");
    int id;
    scanf("%d", &id);

    for (i = 0; i < nombreDeTaches; i++)
    {
        if (taches[i].id == id)
        {
            int souschoix;

            int soustest = 0;
            do
            {
                printf("*******************Afficher tous les taches*******************\n");
                printf("1 en cours de realisation.\n");
                printf("2 finalisee.\n");
                printf("3- retour \n");
                int sousResultt;

                do
                {
                    printf("Entrez votre choix : ");
                    sousResultt = scanf("%d", &souschoix);

                    if (sousResultt == 0)
                    {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF)
                            ;
                    }
                } while (sousResultt == 0);
                switch (souschoix)
                {

                case 1:
                    strcpy(taches[i].status, "EnCours");
                    break;
                case 2:
                    strcpy(taches[i].status, "finalisee");
                    break;
                case 3:
                    soustest = 1;
                    break;
                default:
                    printf("choix invalid \n");
                    break;
                }

            } while (soustest == 0);

            printf("Nouveau statut :%s \n", taches[i].status);
            break;
            test = 0;
        }
        else
        {
            test = 1;
        }
    }

    if (test == 0)
    {
        printf("Le statut de la tache a ete mis a jour.\n");
    }
    else
    {
        printf("Aucune tache avec l'ID %d n'a ete trouvee.\n", id);
    }
}
// modifier la date de deadline d'une tache
void modifierDeadline()
{
    int i, test = 0;
    printf("Entrez l'ID de la tache dont vous souhaitez modifier la deadline : ");
    int id;
    scanf("%d", &id);

    for (i = 0; i < nombreDeTaches; i++)
    {
        if (taches[i].id == id)
        {
            printf("Nouvelle deadline (format YYYY-MM-DD) : ");
            scanf("%s", taches[i].deadline);
            break;
            test = 0;
        }
        else
        {
            test = 1;
        }
    }

    if (test == 0)
    {
        printf("La deadline de la tache a ete mise a jour.\n");
    }
    else
    {
        printf("Aucune tache avec l'ID %d n'a ete trouvee.\n", id);
    }
}
// Modifier Une Tache
void ModifierUneTache()
{
    int soustest = 0;
    int souschoix;
    do
    {
        printf("*******************Modifier une tache*******************\n");
        printf("1-Modifier la description d'une tache.\n");
        printf("2-Modifier le statut d'une tache.\n");
        printf("3-Modifier le deadline d'une tache.\n");
        printf("4- Menu principale.\n");
        int sousResultt;

        do
        {
            printf("Entrez votre choix : ");
            sousResultt = scanf("%d", &souschoix);

            if (sousResultt == 0)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }
        } while (sousResultt == 0);
        switch (souschoix)
        {
        case 1:
            modifierDescription();
            break;
        case 2:
            modifierStatut();
            break;
        case 3:
            modifierDeadline();
            break;
        case 4:
            system("cls");
            soustest = 1;
            break;
        default:
            printf("choix invalid\n");
            break;
        }
    } while (soustest == 0);
}
// Supprimer une tache par identifiant
void SupprimerTacheParID()
{
    int tacheTrouvee = 0;

    printf("Entrez l'ID de la tache que vous souhaitez supprimer : ");
    int id;
    scanf("%d", &id);

    for (int i = 0; i < nombreDeTaches; i++)
    {
        if (taches[i].id == id)
        {
            for (int j = i; j < nombreDeTaches - 1; j++)
            {
                taches[j] = taches[j + 1];
            }

            nombreDeTaches--;
            def++;

            tacheTrouvee = 1;
            printf("La tache avec l'ID %d a ete supprimee.\n", id);
            break;
        }
    }

    if (!tacheTrouvee)
    {
        printf("Aucune tache avec l'ID %d n'a ete trouvee.\n", id);
    }
}
// Rechercher une tache par Identifiant
void rechercherTacheParID()
{
    int tacheTrouvee = 0;

    printf("Entrez l'ID de la tache dont vous souhaitez rechercher : ");
    int id, i;
    scanf("%d", &id);

    for (i = 0; i < nombreDeTaches; i++)
    {
        if (taches[i].id == id)
        {
            printf("Tache trouvee :\n");
            printf("ID : %d\n", taches[i].id);
            printf("Titre : %s\n", taches[i].titre);
            printf("Description : %s\n", taches[i].desc);
            printf("date D'ajout : %s\n", taches[i].dateDajout);
            printf("Deadline : %s\n", taches[i].deadline);
            printf("Statut : %s\n", taches[i].status);
            tacheTrouvee = 1;
            break;
        }
    }

    if (!tacheTrouvee)
    {
        printf("Aucune tache avec l'ID %d n'a ete trouvee.\n", id);
    }
}
// Rechercher une tache par titre
void rechercherTacheParTitre()
{
    int i, tachesTrouvees = 0;
    char titre[200];

    printf("Entrez le titre de la tache dont vous souhaitez rechercher : ");
    scanf("%s", titre);

    for (i = 0; i < nombreDeTaches; i++)
    {
        if (strcmp(taches[i].titre, titre) == 0)
        {
            printf("ID : %d\n", taches[i].id);
            printf("Titre : %s\n", taches[i].titre);
            printf("Description : %s\n", taches[i].desc);
            printf("date D'ajout : %s\n", taches[i].dateDajout);
            printf("Deadline : %s\n", taches[i].deadline);
            printf("Statut : %s\n", taches[i].status);
            printf("\n");
            tachesTrouvees = 1;
        }
    }

    if (!tachesTrouvees)
    {
        printf("Aucune tache avec le titre \"%s\" n'a ete trouvee.\n", titre);
    }
}
// recherch une tache
void RechercherTache()
{
    int souschoix;

    int soustest = 0;

    do
    {
        printf("*******************Rechercher une tache*******************\n");
        printf("1 Rechercher une tache par son Identifiant\n");
        printf("2 Rechercher une tache par son Titre\n");
        printf("3 Rechercher Taches Par Statut\n");
        printf("4- Menu principale \n");
        // scanf("%d", &souschoix);
        int sousResultt;

        do
        {
            printf("Entrez votre choix : ");
            sousResultt = scanf("%d", &souschoix);

            if (sousResultt == 0)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }
        } while (sousResultt == 0);

        switch (souschoix)
        {
        case 1:
            rechercherTacheParID();
            break;
        case 2:
            rechercherTacheParTitre();
            break;
        case 3:
            afficherTachesParStatut();
            break;
        case 4:
            system("cls");
            soustest = 1;
            break;

        default:
            printf("choix invalid\n");
            break;
        }
    } while (soustest == 0);
}
// Calculer le nombre des taches completes et incompletes
void afficherNombreTachesCompletesEtIncompletes()
{
    int complet = 0;
    int incomplet = 0;
    int i;

    for (i = 0; i < nombreDeTaches; i++)
    {
        if (strcmp(taches[i].status, "aRealiser") == 0 || strcmp(taches[i].status, "EnCours") == 0)
        {
            incomplet++;
        }
        else
        {
            complet++;
        }
    }
    printf("Nombre de taches completes : %d\n", complet);
    printf("Nombre de taches incompletes : %d\n", incomplet);
} // Statistique
  // Le nombre de jours restants jusqu au deadline
void afficherNombreJourTachesAuDeadline()
{
    printf("\nListe des taches :\n");
    int i;
    for (i = 0; i < nombreDeTaches; i++)
    {
        printf("Tache %d\n", i + 1);
        printf("ID : %d\n", taches[i].id);
        printf("Titre : %s\n", taches[i].titre);
        printf("Description : %s\n", taches[i].desc);
        printf("Deadline : %s\n", taches[i].deadline);
        printf("Deadline : %s\n", taches[i].dateDajout);
        printf("Statut : %s\n", taches[i].status);

        // Calcul du nombre de jours restants jusqu'à la date limite
        struct tm deadline_tm = {0};
        struct tm current_tm = {0};
        int joursRestants;

        // Convertissez la date limite en structure tm
        sscanf(taches[i].deadline, "%d-%d-%d", &deadline_tm.tm_year, &deadline_tm.tm_mon, &deadline_tm.tm_mday);
        deadline_tm.tm_year -= 1900;
        deadline_tm.tm_mon -= 1;

        // Obtenez la date actuelle
        time_t now;
        time(&now);
        current_tm = *localtime(&now);

        // Calculez la différence entre la date limite et la date actuelle
        time_t deadline_time = mktime(&deadline_tm);
        time_t current_time = mktime(&current_tm);
        joursRestants = (int)((deadline_time - current_time) / (60 * 60 * 24));

        printf("Jours restants jusqu'à la deadline : %d\n", joursRestants);

        printf("\n");
    }
}
void Statistique()
{
    int souschoix;

    int soustest = 0;

    do
    {
        printf("*******************Statistique*******************\n");
        printf("1 Afficher le nombre total des taches.\n");
        printf("2 Afficher le nombre de taches completes et incompletes\n");
        printf("3 Afficher le nombre de jours restants jusqu'au delai de chaque tache\n");
        printf("4- Menu principale \n");
        int sousResultt;

        do
        {
            printf("Entrez votre choix : ");
            sousResultt = scanf("%d", &souschoix);
            if (sousResultt == 0)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }
        } while (sousResultt == 0);

        switch (souschoix)
        {
        case 1:
            printf("le nombre total des taches est %d \n", nombreDeTaches);
            break;
        case 2:
            afficherNombreTachesCompletesEtIncompletes();
            break;
        case 3:
            afficherNombreJourTachesAuDeadline();
            break;
        case 4:
            system("cls");
            soustest = 1;

            break;

        default:
            printf("choix invalid\n");
            break;
        }
    } while (soustest == 0);
}

int main() {
    int choix;
    int test = 0;
    do
    {
        printf("*******************MENU*******************\n");
        printf("1- Ajouter une tache\n");
        printf("2- Ajouter plusieurs taches\n");
        printf("3- Afficher tous les taches\n");
        printf("4- Modifier une tache\n");
        printf("5- Supprimer une tache par identifiant\n");
        printf("6- Rechercher une tache\n");
        printf("7- Statistique\n");
        printf("8- Ajouter Collaborateur\n");
        printf("9- Affecter Collaboration\n");
        printf("10- Affecter Collaboration multiple\n");
        printf("11- Exit\n\n\n");
        int sousResultt;
        do
        {
            printf("Saisir votre choix : ");
            sousResultt = scanf("%d", &choix);
            if (sousResultt == 0)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
        } while (sousResultt == 0);
        switch (choix)
        {
        case 1:
            ajouterTache();
            break;
        case 2:
            do
            {
                ajouterTache();
                int sousresult;
                do
                {
                    printf("voulez-vous ajouter une nouvelle tache? \n0--->oui  1--->non\n");
                    sousresult = scanf("%d", &sortie);

                    if (sousresult == 0 || sortie < 0 || sortie > 1)
                        printf("choix invalid \n");
                    {

                        int c;
                        while ((c = getchar()) != '\n' && c != EOF)
                            ;
                    }
                } while (sousresult == 0 || sortie < 0 || sortie > 1);

            } while (sortie == 0);
            break;
        case 3:
            AfficherTousTaches();
            break;
        case 4:
            ModifierUneTache();
            break;
        case 5:
            SupprimerTacheParID();
            break;
        case 6:
            RechercherTache();
            break;
        case 7:
            Statistique();
            break;
        case 8:
            ajouterCollaborateur();
            break;
        case 9:
            affectationSimpleTache();
            break;
        case 10:
            affectationMultipleCollaborateur();
            break;
        case 11:
            system("cls");
            printf("termine");
            test = 1;
            break;
        default:
            printf("Choix invalide\n");
            break;
        }
    } while (test == 0);

    return 0;
}
