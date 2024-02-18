#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int ** InitTab(){
    int ** T = calloc(4, sizeof(int *));
    if (T == NULL){
        printf("Erreur d'initialisation de la grille.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 4; i++){
        T[i] = calloc(4, sizeof(int));
        if (T[i] == NULL){
            printf("Erreur d'initialisation de la grille.\n");
            exit(EXIT_FAILURE);
        }
    }
    //Une fois le tableau initialisé à 0, on lui ajoute deux cases valant 2 dont les coordonnées sont générés aléatoirement.
    int i1, j1, i2, j2;
    i1 = rand() % 4;
    j1 = rand() % 4;
    i2 = rand() % 4;
    j2 = rand() % 4;
    while(T[i1][j1] != 0){
        i1 = rand() % 4;
        j1 = rand() % 4;
    }
    T[i1][j1] = 2;
    while(T[i2][j2] != 0){
        i2 = rand() % 4;
        j2 = rand() % 4;
    }
    T[i2][j2] = 2;
    return T;
}

int CaseDispo(int ** T){
    int compteur = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (T[i][j] == 0){
                compteur++;
            }
        }
    }
    return compteur;
}

int CaseAdj(int ** T, int i, int j){
    //Les coins
    if ((i == 0) && (j == 0)){
        if (T[i+1][j] == T[i][j]){
            return 1;
        }
        if (T[i][j+1] == T[i][j]){
            return 1;
        }
    }
    else if ((i == 3) && (j == 0)){
        if (T[i][j+1] == T[i][j]){
            return 1;
        }
        if (T[i-1][j] == T[i][j]){
            return 1;
        }
    }
    else if ((i == 0) && (j == 3)){
        if (T[i][j-1] == T[i][j]){
            return 1;
        }
        if (T[i+1][j] == T[i][j]){
            return 1;
        }
    }
    else if ((i == 3) && (j == 3)){
        if (T[i][j-1] == T[i][j]){
            return 1;
        }
        if (T[i-1][j] == T[i][j]){
            return 1;
        }
    }
    //Première ou dernière ligne / colonne
    else if ((i == 0) && (j != 0) && (j != 3)){
        if (T[i+1][j] == T[i][j]){
            return 1;
        }
        if (T[i][j-1] == T[i][j]){
            return 1;
        }
        if (T[i][j+1] == T[i][j]){
            return 1;
        }
    }
    else if ((i == 3) && (j != 0) && (j != 3)){
        if (T[i-1][j] == T[i][j]){
            return 1;
        }
        if (T[i][j-1] == T[i][j]){
            return 1;
        }
        if (T[i][j+1] == T[i][j]){
            return 1;
        }
    }
    else if ((j == 0) && (i != 0) && (i != 3)){
        if (T[i+1][j] == T[i][j]){
            return 1;
        }
        if (T[i-1][j] == T[i][j]){
            return 1;
        }
        if (T[i][j+1] == T[i][j]){
            return 1;
        }
    }
    else if ((j == 3) && (i != 0) && (i != 3)){
        if (T[i+1][j] == T[i][j]){
            return 1;
        }
        if (T[i-1][j] == T[i][j]){
            return 1;
        }
        if (T[i][j-1] == T[i][j]){
            return 1;
        }
    }
    //Enfin, le reste des cases.
    else {
        if (T[i-1][j] == T[i][j]){
            return 1;
        }
        if (T[i][j-1] == T[i][j]){
            return 1;
        }
        if (T[i+1][j] == T[i][j]){
            return 1;
        }
        if (T[i-1][j] == T[i][j]){
            return 1;
        }
    }
    return 0;
}

void Randomizer(int ** T){
    if (CaseDispo(T) >= 1){
        int i1, j1;
        i1 = rand() % 4;
        j1 = rand() % 4;
        while (T[i1][j1] != 0){
            i1 = rand() % 4;
            j1 = rand() % 4;
        }
        int val = rand () % 2;
        if (val == 0){
            T[i1][j1] = 2;
        }
        else {
            T[i1][j1] = 4;
        }
    }
    
}

int Taille(int ** T){
    int taille = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            //Valeur ayant 2 chiffres
            if ( (T[i][j] >= 16) && (T[i][j] < 128) ){
                taille = 1;
            }
            //Valeur ayant 3 chiffres
            else if ((T[i][j] >= 128) && (T[i][j] < 1024)){
                taille = 2;
            }
            else if (T[i][j] >= 1024){
                taille = 3;
            }
        }
    }
    return taille;
}

void Affiche(int ** T, int * score){
    int t = Taille(T);
    if (t == 0){
        printf("-----------------\n");
        for (int i = 0; i < 4; i++){
            printf("| %d | %d | %d | %d |\n", T[i][0], T[i][1], T[i][2], T[i][3]);
            printf("-----------------\n");
        }
        printf("Score : %d\n", (*score));
    }
    else if (t == 1){
        printf("-------------------------\n");
        for (int i = 0; i < 4; i++){
            printf("|  %d  |  %d  |  %d  |  %d  |\n", T[i][0], T[i][1], T[i][2], T[i][3]);
            printf("-------------------------\n");
        }
        printf("Score : %d\n", (*score));
    }
    else if (t == 2){
        printf("---------------------------------\n");
        for (int i = 0; i < 4; i++){
            printf("|   %d   |   %d   |   %d   |   %d   |\n", T[i][0], T[i][1], T[i][2], T[i][3]);
            printf("---------------------------------\n");
        }
        printf("Score : %d\n", (*score));
    }
    else if (t == 3){
        printf("-----------------------------------------\n");
        for (int i = 0; i < 4; i++){
            printf("|    %d    |    %d    |    %d    |    %d    |\n", T[i][0], T[i][1], T[i][2], T[i][3]);
            printf("-----------------------------------------\n");
        }
        printf("Score : %d\n", (*score));
    }
}

void Clear(){
    system("clear");
}

//0 : La partie continue | 1 : Game Over | 2: 2048 atteint
int Fin(int ** T){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (T[i][j] == 2048){
                return 2;
            }
        }
    }
    if (CaseDispo(T) == 0){
        int compteur = 0;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                compteur += CaseAdj(T,i,j);
            }
        }
        if (compteur > 0){
            return 0;
        }
        else {
            return 1;
        }
    }
    return 0;
}
// Retourne 1 si un décalage a été effectué, 0 si ce n'est pas possible
int Decalage(int ** T, char c, int * score){
    // Création d'une copie du tableau avant l'exécution du décalage afin de savoir si le tableau a été changé ou non (si le tableau a subis une modification, on executera Randomizer() ).
    int ** Copie = calloc(4, sizeof(int *));
    for (int i = 0; i < 4; i++){
        Copie[i] = calloc(4, sizeof(int));
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            Copie[i][j] = T[i][j];
        }
    }
    //Exécution du décalage des cases
    if(c == 'h'){
        //On déplace juste les éléments
        for (int i = 1; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (T[i][j] != 0){
                    for(int k = i; k >= 1; k--){
                        if (T[k-1][j] == 0){
                            T[k-1][j] = T[k][j];
                            T[k][j] = 0;
                        }
                    }
                }
            }
        }
        //Fusionner et arranger 
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 4; j++){
                if (T[i][j] == T[i+1][j]){
                    T[i][j] *= 2;
                    (*score) += T[i][j]; 
                    T[i+1][j] = 0;
                    for (int k = i+1; k < 3; k++){
                        T[k][j] = T[k+1][j];
                    }
                    T[3][j] = 0;
                }
            }
        }
    }
    else if(c == 'b'){
        //On déplace juste les éléments
        for (int i = 2; i >=0; i--){
            for (int j = 0; j < 4; j++){
                if (T[i][j] != 0){
                    for(int k = i; k < 3; k++){
                        if (T[k+1][j] == 0){
                            T[k+1][j] = T[k][j];
                            T[k][j] = 0;
                        }
                    }
                }
            }
        }
        //Fusionner et arranger 
        for (int i = 3; i >=1; i--){
            for (int j = 0; j < 4; j++){
                if (T[i][j] == T[i-1][j]){
                    T[i][j] *= 2;
                    (*score) += T[i][j]; 
                    T[i-1][j] = 0;
                    for (int k = i-1; k >=1 ; k--){
                        T[k][j] = T[k-1][j];
                    }
                    T[0][j] = 0;
                }
            }
        }
    }
    else if(c == 'g'){
        //On déplace juste les éléments
        for (int i = 0; i < 4; i++){
            for (int j = 1; j < 4; j++){
                if (T[i][j] != 0){
                    for(int k = j; k > 0; k--){
                        if (T[i][k-1] == 0){
                            T[i][k-1] = T[i][k];
                            T[i][k] = 0;
                        }
                    }
                }
            }
        }
        //Fusionner et arranger 
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 3; j++){
                if (T[i][j] == T[i][j+1]){
                    T[i][j] *= 2;
                    (*score) += T[i][j]; 
                    T[i][j+1] = 0;
                    for (int k = j+1; k <3 ; k++){
                        T[i][k] = T[i][k+1];
                    }
                    T[i][3] = 0;
                }
            }
        }
    }
    else if(c == 'd'){
        //On déplace juste les éléments
        for (int i = 0; i < 4; i++){
            for (int j = 2; j >= 0; j--){
                if (T[i][j] != 0){
                    for(int k = j; k < 3; k++){
                        if (T[i][k+1] == 0){
                            T[i][k+1] = T[i][k];
                            T[i][k] = 0;
                        }
                    }
                }
            }
        }
        //Fusionner et arranger 
        for (int i = 0; i < 4; i++){
            for (int j = 3; j > 0; j--){
                if (T[i][j] == T[i][j-1]){
                    T[i][j] *= 2;
                    (*score) += T[i][j]; 
                    T[i][j-1] = 0;
                    for (int k = j-1; k >0 ; k--){
                        T[i][k] = T[i][k-1];
                    }
                    T[i][0] = 0;
                }
            }
        }
    }
    //Vérification des deux tableaux
    int compteur = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (Copie[i][j] != T[i][j]){
                compteur++;
            }
        }
    }
    if (compteur == 0){
        return 0; //Cas où aucune modification n'a été effectué sur T
    }
    else {
        return 1;
    }
}

int main(){
    FILE * fd = fopen("save/save_board.txt", "r+");
    FILE * ff = fopen("save/save_score.txt", "r+");
    char * warning = calloc(30, sizeof(char));
    memset(warning, '\0', sizeof(warning));
    if (fd == NULL){
        fd = fopen("save/save_board.txt", "w+");
        warning = " ( /!\\ Lors du demarrage, aucune sauvegarde n'a ete trouve, nous vous recommandons de lancer une nouvelle partie )";
    }
    if (ff == NULL){
        ff = fopen("save/save_score.txt", "w+");
    }
    srand(time(NULL));
    int score = 0;
    int choix = 0;
    char * save = calloc(100, sizeof(char));
    char * last_score = calloc(50, sizeof(char));
    Clear(); 
    //Menu du jeu
    printf("Jeu 2048 par ABDUL-SALAM Sami et PACHOLIK Anthony.\n");
    printf("\n\n");
    printf("Choisissez une option :\n1) Lancer une nouvelle partie.\n");
    printf("2) Charger une sauvegarde%s.\n", warning);
    int k = fread(save, sizeof(char), 100, fd);
    int u = fread(last_score, sizeof(char), 50, ff);
    while ( (choix != 1) && (choix != 2) ){
        scanf("%d", &choix);
    }
    Clear(); 
    
    int ** T = NULL;
    if (choix == 1){
        T = InitTab();
        //Le lancement d'une nouvelle partie implique la suppression de la sauvegarde précédente si elle existe.
        if ((ff != NULL) && (fd != NULL)){
            remove("save/save_board.txt");
            remove("save/save_score.txt");
            fd = fopen("save/save_board.txt", "w+");
            ff = fopen("save/save_score.txt", "w+");
        }

    }
    //Charge une sauvegarde par la lecture du fichier
    else {
        if (k == 0){
            printf("Aucune sauvegarde n'a pu être trouvé :(\nVeuillez redémarrer le jeu en lançant une nouvelle partie.\n");
            exit(EXIT_FAILURE);
        }
        else{
            score = atoi(last_score);
            int * tab = calloc(16, sizeof(int)); //Tableau unidimensionnel contenant les entiers de la dernière partie sauvegardé.
            int indice = 0;
            char * e = calloc(4, sizeof(char)); //Chaîne de caractère qui va récupérer les entiers et les transmettres au tableau.
            char * aux = calloc(4, sizeof(char));
            memset(e, '\0', sizeof(e)); //memset permet de ré-initialiser le pointeur à une valeur donner.
            memset(aux, '\0', sizeof(aux));
            for (int i = 0; i < k; i++){
                if ((save[i] != ' ') && (save[i] != '\n')){
                    sprintf(aux, "%c", save[i]);
                    strcat(e, aux);
                    memset(aux, '\0', sizeof(aux));
                }
                else {
                    tab[indice] = atoi(e);
                    indice++;
                    memset(e, '\0', sizeof(e));
                }
            }
            //On transmet les valeurs dans la grille
            T = InitTab(); // On utilise quand même InitTab car la fonction effectue l'allocation dynamique de la mémoire.
            int j = 0;
            for (int i = 0; i < 16; i++){
                if ((i != 0) && (i % 4 == 0)){
                    j++;
                    T[j][i%4] = tab[i];
                }
                else {
                    T[j][i%4] = tab[i];
                }
            }
        }
    }
    fseek(fd,0,SEEK_SET);
    fseek(ff,0,SEEK_SET);
    while(Fin(T) == 0){
        char c = ' ';
        Affiche(T, &score);
        printf("Choisissez une option : h, b, g, d\nEntrez q pour quitter.\n");
        while((c != 'h') && (c != 'b') && (c != 'g') && (c != 'd') && (c != 'q')){
            scanf("%c", &c);
        }
        if (c == 'q'){
            Clear();
            exit(EXIT_SUCCESS);

        }
        int v = Decalage(T, c, &score);
        if (v == 1){
            Randomizer(T);
        }
        //Ecriture de la sauvegarde
        char * ecrit = calloc(20, sizeof(char));
        sprintf(last_score, "%d", score);
        fputs(last_score, ff);
        fseek(ff,0,SEEK_SET);
        for (int i = 0; i < 3; i++){
            sprintf(ecrit, "%d %d %d %d\n", T[i][0], T[i][1], T[i][2], T[i][3]);
            fputs(ecrit, fd);
            memset(ecrit, '\0', sizeof(ecrit));
        }
        //Pour la dernière ligne, on ne souhaite plus avoir le caractère '\n' à la fin.
        sprintf(ecrit, "%d %d %d %d", T[3][0], T[3][1], T[3][2], T[3][3]);
        fputs(ecrit, fd);
        memset(ecrit, '\0', sizeof(ecrit));
        fseek(fd,0,SEEK_SET);
        Clear();
    }
    if (Fin(T) == 2){
        Clear();
        printf("Victoire, le nombre 2048 a ete atteint !\n");
        printf("Votre score : %d\n", score);
        remove("save/save_board.txt");
        remove("save/save_score.txt");
    }
    else{
        Clear();
        printf("Game Over.\n");
        printf("Votre score : %d\n", score);
        remove("save/save_board.txt");
        remove("save/save_score.txt");
    }
    fclose(fd);
    fclose(ff);
    return 0;
}