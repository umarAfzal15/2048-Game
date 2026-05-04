#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void gamePlay(FILE *fptr, int *moves, int *score, char playerNmae[], int grid[4][4]);
void pressedLeft(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]);
void pressedRight(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]);
void pressedUp(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]);
void pressedDown(FILE *fptr, int *moves,int *score, char playerName[],  int grid[4][4]);
void isGameContinue(int *mergeCondition, int *checkZero, int grid[4][4]);
void showTopThreePlayes(FILE* fptr);
void gameInsights(FILE* fptr);

//It hides or shows cursor
void hideCursor(int visible) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void resetCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(hConsole, cursorPosition);
}

//this is main
int main(){
    system("cls");
    int score=0;
    int moves=0;
    char playerName[50];
    //int score=0;
    int option, i, j, k;
    int grid[4][4];
    srand(time(0));

    FILE* fptr;
    fptr= fopen("2048_Game.txt", "a");

    if(fptr == NULL){
        printf("something Wrong happened while opening file.");
        return 0;
    }

    printf("\n~~~~~~Please Select From The Menu~~~~~~\n");
    printf("1. Play 2048 Game\n");
    printf("2. Show Top Three players\n");
    printf("3. Search Your Game Insights\n");
    printf("4. Exit The Game\n");
    printf("Type Here ==> ");
    scanf("%d", &option);
    getchar();
    system("cls");

    while(1){
        if(option==1){
        printf("Please Enter Your Name: ");
        fgets(playerName, sizeof(playerName), stdin);

        i = 0;
        while(1){
            if(playerName[i] == '\0'){
                break;
            }
            if((playerName[i] >= 'a' && playerName[i] <= 'z') || (playerName[i] >= 'A' && playerName[i] <= 'Z') || playerName[i] == ' ' || playerName[i] == '\n'){
                i++;
                continue;
            }else {
                printf("ERROR: Name cannot have numbers or any Other characters\n");
                printf("Please Enter Your Name: ");
                fgets(playerName, sizeof(playerName), stdin);
                i = 0;
            }
        }

        system("cls");
        printf("\n~~~~~Let's Start a small Tutorial~~~~~\n");

        printf("==>Press: Arrow keys to Play the Game.\n");
        printf("NOTE: During Game pressing other keys will stop the Game\n");
        printf("==>Now Click Enter To Start The Game\n");
        hideCursor(0);
        char ok = getchar();

        while(1){

            if (ok != '\n') {
                printf("Please press \"Enter\" ");
                 ok = getchar();
            }else{
                break;
            }
        }

        system("cls");
        gamePlay(fptr, &moves, &score, playerName, grid); // function call
        }else if(option==2){
            showTopThreePlayes(fptr);
        }else if(option==3){
            gameInsights(fptr);
        }else if(option==4){
            printf("Thank You for Playing the Game!");
            exit(0);
        }

        printf("\n~~~~~~Please Select From The Menu~~~~~~\n");
        printf("1. Play 2048 Game\n");
        printf("2. Show Top Three players\n");
        printf("3. Search Your Game Insights\n");
        printf("4. Exit The Game\n");
        printf("Type Here ==> ");
        scanf("%d", &option);
        getchar();
        system("cls");
    }
    return 0;
}

//this handles Game Play
void gamePlay(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]) { 
    int keyPressed;
    int i=0, j;
    int row, col;
    
    while(i<2){
        row = rand() % 4;
        col = rand() % 4;
        if(grid[row][col] == 2){
            continue;
        }else{
            grid[row][col] = 2;
            i++;
        }
    }

    playerName[strcspn(playerName, "\n")] = '\0';
    printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
    for(int i=0; i<4; i++){
        printf("\t\t\t\t");
        for(int j=0; j<4; j++){
            if(grid[i][j]==2){
                printf("%d\t\b", grid[i][j]);
            }else{
                grid[i][j] = 0;
                printf("%d\t\b", grid[i][j]);
            } 
        }
        printf("\n\n");
    }

    i=0;
    j=0;

    while(1){
        keyPressed = _getch();
        if(keyPressed == 0 || keyPressed == 224){
            (*moves)++;
            switch (_getch()) {
                case 72: 
                    pressedUp(fptr, moves, score, playerName, grid);
                    break;
                case 80:
                    pressedDown(fptr, moves, score, playerName, grid);
                    break;
                case 75:
                    pressedLeft(fptr, moves, score, playerName, grid);
                    break;
                case 77:
                    pressedRight(fptr, moves, score, playerName, grid);
                    break;
                default:
                    break;
            }
        }else {
            printf("\n\t\t:::::::The Game has Finished!:::::::\n");
            fprintf(fptr, "%s,%d,%d\n", playerName, *score, *moves);
            fclose(fptr);
            return;
        }
    }

    return;
}

//this handles left key move
void pressedLeft(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]){

    int mergeCondition=0, tileValue, checkZero = 0;
    int i, j, k, swap = 0;

    for(k=0; k<4; k++){
        for(i=0; i<4; i++){
            for(j=0; j<4; j++){
                if(j<=2){
                    if(grid[k][j+1] != 0 && grid[k][j] == 0){
                        swap = grid[k][j+1];
                        grid[k][j+1] = grid[k][j];
                        grid[k][j] = swap;
                    }
                }
            }
        }
    }

    //this is merging
    for (i = 0; i < 4; i++){
        for ( j = 0; j < 4; j++)
        {
            if (grid[i][j] == grid[i][j+1])
            {
                grid[i][j] *=2;
                *score += grid[i][j];
                grid[i][j+1] = 0; 
            }
            
        }
        
    }

    //swaping again
    for(k=0; k<4; k++){
        for(i=0; i<4; i++){
            for(j=0; j<4; j++){
                if(j<=2){
                    if(grid[k][j+1] != 0 && grid[k][j] == 0){
                        swap = grid[k][j+1];
                        grid[k][j+1] = grid[k][j];
                        grid[k][j] = swap;
                    }
                }
            }
        }
    }

    int empty[16][2];
    int count = 0;

    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(grid[i][j] == 0){
                empty[count][0] = i;
                empty[count][1] = j;
                count++;
            }
        }
    }

    if(count > 0){
        int r = rand() % count;
        grid[empty[r][0]][empty[r][1]] = 2;
    }

    //checking if merging is possible
    isGameContinue(&mergeCondition, &checkZero, grid);

    if(checkZero == 1 || mergeCondition == 1){
        system("cls");
        printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
        for(i=0; i<4; i++){
            printf("\t\t\t\t");
            for(j=0; j<4; j++){
                printf("%d\t\b", grid[i][j]);
            }
            printf("\n\n");
        }
    }else {
        system("cls");
        printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
        for(i=0; i<4; i++){
            printf("\t\t\t\t");
            for(j=0; j<4; j++){
                printf("%d\t\b", grid[i][j]);
            }
            printf("\n\n");
        }
        printf("\n\t\t  :::::::The Game has Finished NO Possible Moves!:::::::\n");
        fprintf(fptr, "%s,%d,%d\n", playerName, *score, *moves);
        fclose(fptr);
        exit(0);
    }

    return;
}


void pressedRight(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]){

    int mergeCondition=0, tileValue, checkZero = 0;
    int i, j, k, swap = 0;

    for(k=0; k<4; k++){
        for(i=0; i<4; i++){
            for(j=0; j<4; j++){
                if(j<=2){
                    if(grid[k][j+1] == 0 && grid[k][j] != 0){
                        swap = grid[k][j+1];
                        grid[k][j+1] = grid[k][j];
                        grid[k][j] = swap;
                    }
                }
            }
        }
    }

    //this is merging
    for (i = 0; i < 4; i++){
        for ( j = 3; j >= 0; j--)
        {
            if (grid[i][j] == grid[i][j-1])
            {
                grid[i][j] *=2;
                *score += grid[i][j];
                grid[i][j-1] = 0; 
            }
            
        }
        
    }

    //swaping again
    for(k=0; k<4; k++){
        for(i=0; i<4; i++){
            for(j=0; j<4; j++){
                if(j<=2){
                    if(grid[k][j+1] == 0 && grid[k][j] != 0){
                        swap = grid[k][j+1];
                        grid[k][j+1] = grid[k][j];
                        grid[k][j] = swap;
                    }
                }
            }
        }
    }

    int empty[16][2];
    int count = 0;

    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(grid[i][j] == 0){
                empty[count][0] = i;
                empty[count][1] = j;
                count++;
            }
        }
    }

    if(count > 0){
        int r = rand() % count;
        grid[empty[r][0]][empty[r][1]] = 2;
    }

    //checking if merging is possible
    isGameContinue(&mergeCondition, &checkZero, grid);

    if(checkZero == 1 || mergeCondition == 1){
        system("cls");
        printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
        for(i=0; i<4; i++){
            printf("\t\t\t\t");
            for(j=0; j<4; j++){
                printf("%d\t\b", grid[i][j]);  
            }
            printf("\n\n");
        }
    }else {
        system("cls");
        printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
        for(i=0; i<4; i++){
            printf("\t\t\t\t");
            for(j=0; j<4; j++){
                printf("%d\t\b", grid[i][j]);
            }
            printf("\n\n");
        }
        printf("\n\t\t  :::::::The Game has Finished NO Possible Moves!:::::::\n");
        fprintf(fptr, "%s,%d,%d\n", playerName, *score, *moves);
        fclose(fptr);
        exit(0);
    }

    return;
}
void pressedUp(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]){

   int mergeCondition=0, tileValue, checkZero = 0;
    int i, j, k, swap = 0;

    //swapping
    for(k=0; k<4; k++){
        for(i=0; i<4; i++){
            for(j=0; j<4; j++){
                if(j<=2){
                    if(grid[j+1][k] != 0 && grid[j][k] == 0){
                        swap = grid[j+1][k];
                        grid[j+1][k] = grid[j][k];
                        grid[j][k] = swap;
                    }
                }
            }
        }
    }

    //merging
    for (i = 0; i < 4; i++){
        for ( j = 0; j < 4; j++)
        {
            if (grid[j][i] == grid[j+1][i])
            {
                grid[j][i] *=2;
                *score += grid[j][i];
                grid[j+1][i] = 0; 
            }
            
        }
        
    }
    
    //swapping again
    for(k=0; k<4; k++){
        for(i=0; i<4; i++){
            for(j=0; j<4; j++){
                if(j<=2){
                    if(grid[j+1][k] != 0 && grid[j][k] == 0){
                        swap = grid[j+1][k];
                        grid[j+1][k] = grid[j][k];
                        grid[j][k] = swap;
                    }
                }
            }
        }
    }

    int empty[16][2];
    int count = 0;

    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(grid[i][j] == 0){
                empty[count][0] = i;
                empty[count][1] = j;
                count++;
            }
        }
    }

    if(count > 0){
        int r = rand() % count;
        grid[empty[r][0]][empty[r][1]] = 2;
    }

    //checking game continuity
    isGameContinue(&mergeCondition, &checkZero, grid);

    if(checkZero == 1 || mergeCondition == 1){
        system("cls");
        printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
        for(i=0; i<4; i++){
            printf("\t\t\t\t");
            for(j=0; j<4; j++){
                printf("%d\t\b", grid[i][j]);
            }
            printf("\n\n");
        }
    }else {
        system("cls");
        printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
        for(i=0; i<4; i++){
            printf("\t\t\t\t");
            for(j=0; j<4; j++){
                printf("%d\t\b", grid[i][j]);
            }
            printf("\n\n");
        }
        printf("\n\t\t  :::::::The Game has Finished NO Possible Moves!:::::::\n");
        fprintf(fptr, "%s,%d,%d\n", playerName, *score, *moves);
        fclose(fptr);
        exit(0);
    }

    return;
}
void pressedDown(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]){
    int mergeCondition=0, tileValue, checkZero = 0;
    int i, j, k, swap = 0;

    for(k=0; k<4; k++){
        for(i=0; i<4; i++){
            for(j=0; j<4; j++){
                if(j<=2){
                    if(grid[j+1][k] == 0 && grid[j][k] != 0){
                        swap = grid[j+1][k];
                        grid[j+1][k] = grid[j][k];
                        grid[j][k] = swap;
                    }
                }
            }
        }
    }

    for (i = 0; i < 4; i++){
        for ( j = 3; j > 0; j--)
        {
            if (grid[j][i] == grid[j-1][i])
            {
                grid[j][i] *=2;
                *score += grid[j][i];
                grid[j-1][i] = 0; 
            }
            
        }
        
    }

    //swapping again
    for(k=0; k<4; k++){
        for(i=0; i<4; i++){
            for(j=0; j<4; j++){
                if(j<=2){
                    if(grid[j+1][k] == 0 && grid[j][k] != 0){
                        swap = grid[j+1][k];
                        grid[j+1][k] = grid[j][k];
                        grid[j][k] = swap;
                    }
                }
            }
        }
    }

    int empty[16][2];
    int count = 0;

    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(grid[i][j] == 0){
                empty[count][0] = i;
                empty[count][1] = j;
                count++;
            }
        }
    }

    if(count > 0){
        int r = rand() % count;
        grid[empty[r][0]][empty[r][1]] = 2;
    }

    //checking game continuity
    isGameContinue(&mergeCondition, &checkZero, grid);

    if(checkZero == 1 || mergeCondition == 1){
        system("cls");
        printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
        for(i=0; i<4; i++){
            printf("\t\t\t\t");
            for(j=0; j<4; j++){
                printf("%d\t\b", grid[i][j]);
            }
            printf("\n\n");
        }
    }else {
        system("cls");
        printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
        for(i=0; i<4; i++){
            printf("\t\t\t\t");
            for(j=0; j<4; j++){
                printf("%d\t\b", grid[i][j]);
            }
            printf("\n\n");
        }
        printf("\n\t\t  :::::::The Game has Finished NO Possible Moves!:::::::\n");
        fprintf(fptr, "%s,%d,%d\n", playerName, *score, *moves);
        fclose(fptr);
        exit(0);
    }
    return;
}

void isGameContinue(int *mergeCondition, int *checkZero, int grid[4][4]){
    *mergeCondition = 0;
    *checkZero = 0;
    int i, j;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){

            if(grid[i][j] == 0){
                *checkZero = 1;
            }

            if(j < 3 && grid[i][j] == grid[i][j+1]){
                *mergeCondition = 1;
            }

            if(i < 3 && grid[i][j] == grid[i+1][j]){
                *mergeCondition = 1;
            }

            if(*mergeCondition && *checkZero){
                return;
            }
        }
    }

    return;
}

void showTopThreePlayes(FILE* fptr){
    char name[50];
    int Moves;
    char topPlayers[3][50] = {"None", "None", "None"};
    int score[3] = {0}, i, Score;
    int moves[3] = {0};

    fptr = fopen("2048_Game.txt", "r");

    while (fscanf(fptr, " %49[^,],%d,%d", name, &Score, &Moves) == 3) {
        
        if (Score > score[0]) {
            score[2] = score[1]; 
            score[1] = score[0];
            moves[2] = moves[1]; 
            moves[1] = moves[0];
            strcpy(topPlayers[2], topPlayers[1]); 
            strcpy(topPlayers[1], topPlayers[0]);
            
            score[0] = Score;
            moves[0] = Moves;
            strcpy(topPlayers[0], name);
        } 
        else if (Score > score[1]) {
            score[2] = score[1];
            moves[2] = moves[1];
            strcpy(topPlayers[2], topPlayers[1]);
            
            score[1] = Score;
            moves[1] = Moves;
            strcpy(topPlayers[1], name);
        } 
        else if (Score > score[2]) {
            score[2] = Score;
            moves[2] = Moves;
            strcpy(topPlayers[2], name);
        }
    }

    printf("Top Three Player Are:\n");
    for(i=0; i<3; i++){
        printf("%d). Name: %s,\t\tScore: %d,\t\tMoves: %d\n",i+1, topPlayers[i], score[i], moves[i]);
    }

    fclose(fptr);
    hideCursor(0);
    getchar();
    system("cls");
    return;
}

void gameInsights(FILE* fptr){
    hideCursor(1);
    char name[50];
    char searchName[50];

    int Score, Moves, played=0;

    fptr = fopen("2048_Game.txt", "r");

    printf("Enter your Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int i = 0;
    while(1){
        if(name[i] == '\0'){
            break;
        }
        if((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || name[i] == ' ' || name[i] == '\n'){
            i++;
            continue;
        }else {
            printf("ERROR: Name cannot have numbers or any Other characters\n");
            printf("Please Enter Your Name: ");
            fgets(name, sizeof(name), stdin);
            i = 0;
        }
    }

    printf("~~~~~Your insights~~~~~\n");
    i=1;
    while (fscanf(fptr, " %49[^,],%d,%d", searchName, &Score, &Moves) == 3){
        if (strcmp(searchName, name) == 0) {
            printf("Game No.%d): Name: %s,\tScore: %d,\tMoves: %d\n", i, searchName, Score, Moves);
            played++;
            i++;
        }
    }

    if(played == 0){
        printf("You have not played any Game Yet\n");
    }

    printf("Total Games Played: %d", played);
    fclose(fptr);
    hideCursor(0);
    getchar();
    system("cls");
    return;
}