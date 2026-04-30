//need to debug end game logic
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

//It hides cursor
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
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
        system("cls");
        printf("\n~~~~~Let's Start a small Tutorial~~~~~\n");

        printf("==>Press: Arrow keys to Play the Game.\n");
        printf("NOTE: During Game pressing other keys will stop the Game\n");
        printf("==>Now Click Enter To Start The Game\n");
        hideCursor();
        //scanf(" %c", &ok);
        char ok = getchar();

        while(1){

            if (ok != '\n') {
                printf("Please press \"Enter\" ");
                 ok = getchar();
            }else{
                break;
            }
        }
        //hideCursor();
        system("cls");
        //fputs(playerName, fptr);
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
    // Game Play Here
    //FILE** fptr1 = fptr; 
    int keyPressed;
    //int score=0;
    //int moves=0;
    int i=0, j;
    int row, col;
    
    while(i<2){
        //srand(time(0));
        row = rand() % 4;
        col = rand() % 4;
        if(grid[row][col] == 2){
            continue;
        }else{
            grid[row][col] = 2;
            i++;
        }
    }
    //printf("%d%d\n", grid[row][col]);
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
            //printf("I am in if\n");
            (*moves)++;
            switch (_getch()) {
                case 72: 
                    //printf("Up Arrow\n");
                    pressedUp(fptr, moves, score, playerName, grid);
                    break;
                case 80:
                    //printf("Down Arrow\n");
                    pressedDown(fptr, moves, score, playerName, grid);
                    break;
                case 75:
                    //printf("Left Arrow\n");
                    pressedLeft(fptr, moves, score, playerName, grid);
                    break;
                case 77:
                    //printf("Right Arrow\n");
                    pressedRight(fptr, moves, score, playerName, grid);
                    break;
                default:
                    break;
            }
        }else {
            printf("\n\t\t\t  Thank you for playing the Game!\n");
            fprintf(fptr, "%s,%d,%d\n", playerName, *score, *moves);
            fclose(fptr);
            return;
        }
    }
    return;

}

//this handles left key move
void pressedLeft(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]){

    int mergeCondition=0, tileValue, mergedposition=0, checkZero = 0;
    int i, j, k, row, col, swap=0, isGenrated=1;

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

    //("this is swaping\n");

    /*for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }*/

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
    
    /*printf("this is merging\n");

    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }*/

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

    /*printf("this is swaping again\n");

    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }*/

    //generating 2 on random spot


    // while(isGenrated){
    //    // srand(time(0));
    //     row = rand() % 4;
    //     col = rand() % 4;
    //     if(grid[row][col] == 0){
    //         grid[row][col] = 2;
    //         isGenrated = 0;
    //     }
    // }

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

    //printf("this is generating 2 in random\n");
    // printf("Name: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

    //checking if merging is possible
    isGameContinue(&mergeCondition, &checkZero, grid);

    // if(mergeCondition != 0){
    //     for ( i = 0; i < 4; i++)
    //     {
    //         for(j=0; j<4; j++){
    //             if(grid[i][j] == 0){
    //                 mergeCondition = 0;
    //                 break;
    //             }
    //         }
    //         if(mergeCondition == 0){
    //             break;
    //         }
    //     }
    // }
    //printing
   // printf("\nThis is the actual printing\n");
    if(checkZero == 1 || mergeCondition == 1){
        system("cls");
        //printf("\nThis is the actual printing\n");
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
        //printf("\nThis is the actual printing\n");
        printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
        for(i=0; i<4; i++){
            printf("\t\t\t\t");
            for(j=0; j<4; j++){
                printf("%d\t\b", grid[i][j]);
            }
            printf("\n\n");
        }
        printf("The Game has Finished!\n");
        fprintf(fptr, "%s,%d,%d\n", playerName, *score, *moves);
        fclose(fptr);
        exit(0);
    }
    return;
    //printf("\nI am in pressedLeft bottom\n");
}


void pressedRight(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]){

    int mergeCondition=0, tileValue, mergedposition=0, checkZero = 0;
    int i, j, k, row, col, swap=0, isGenrated=1;

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

    // printf("this is swaping\n");

    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

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
    
    // printf("this is merging\n");

    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

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

    // printf("this is swaping again\n");

    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

    //generating 2 on random spot

    // while(isGenrated){
    //     srand(time(0));
    //     row = rand() % 4;
    //     col = rand() % 4;
    //     if(grid[row][col] == 0){
    //         grid[row][col] = 2;
    //         isGenrated = 0;
    //     }
    // }

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

    //printf("this is generating 2 in random\n");
    // printf("Name: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

    //checking if merging is possible
    isGameContinue(&mergeCondition, &checkZero, grid);

    // if(mergeCondition != 0){
    //     for ( i = 0; i < 4; i++)
    //     {
    //         for(j=3; j>=0; j--){
    //             if(grid[i][j] == 0){
    //                 mergeCondition = 0;
    //                 break;
    //             }
    //         }
    //         if(mergeCondition == 0){
    //             break;
    //         }
    //     }
    // }

    //printing
   // printf("\nThis is the actual printing\n");
    if(checkZero == 1 || mergeCondition == 1){
        system("cls");
        //printf("\nThis is the actual printing\n");
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
        //printf("\nThis is the actual printing\n");
        printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
        for(i=0; i<4; i++){
            printf("\t\t\t\t");
            for(j=0; j<4; j++){
                printf("%d\t\b", grid[i][j]);
            }
            printf("\n\n");
        }
        printf("The Game has Finished!\n");
        fprintf(fptr, "%s,%d,%d\n", playerName, *score, *moves);
        fclose(fptr);
        exit(0);
    }
    return;
    //printf("\nI am in pressedRight bottom\n");
}
void pressedUp(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]){

    int mergeCondition=0, tileValue, mergedposition=0, checkZero = 0;
    int i, j, k, row, col, swap=0, isGenrated=1;

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

    // printf("this is swaping\n");

    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

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
    
    // printf("this is merging\n");

    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

    //swaping again
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

    // printf("this is swaping again\n");

    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

    //generating 2 on random spot

    // while(isGenrated){
    //     srand(time(0));
    //     row = rand() % 4;
    //     col = rand() % 4;
    //     if(grid[row][col] == 0){
    //         grid[row][col] = 2;
    //         isGenrated = 0;
    //     }
    // }

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

    //printf("this is generating 2 in random\n");
    // printf("Name: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

    //checking if merging is posible
    isGameContinue(&mergeCondition, &checkZero, grid);

    // if(mergeCondition != 0){
    //     for ( i = 0; i < 4; i++)
    //     {
    //         for(j=0; j<4; j++){
    //             if(grid[j][i] == 0){
    //                 mergeCondition = 0;
    //                 break;
    //             }
    //         }
    //         if(mergeCondition == 0){
    //             break;
    //         }
    //     }
    // }

    //printing
   // printf("\nThis is the actual printing\n");
    if(checkZero == 1 || mergeCondition == 1){
        system("cls");
        //printf("\nThis is the actual printing\n");
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
        //printf("\nThis is the actual printing\n");
        printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
        for(i=0; i<4; i++){
            printf("\t\t\t\t");
            for(j=0; j<4; j++){
                printf("%d\t\b", grid[i][j]);
            }
            printf("\n\n");
        }
        printf("The Game has Finished!\n");
        fprintf(fptr, "%s,%d,%d\n", playerName, *score, *moves);
        fclose(fptr);
        exit(0);
    }
    return;
    //printf("\nI am in pressedUp bottom\n");
}
void pressedDown(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]){
    int mergeCondition=0, tileValue, mergedposition=0, checkZero = 0;
    int i, j, k, row, col, swap=0, isGenrated=1;

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

    // printf("this is swaping\n");

    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

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
    
    // printf("this is merging\n");

    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

    //swaping again
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

    // printf("this is swaping again\n");

    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

    //generating 2 on random spot

    // while(isGenrated){
    //     srand(time(0));
    //     row = rand() % 4;
    //     col = rand() % 4;
    //     if(grid[row][col] == 0){
    //         grid[row][col] = 2;
    //         isGenrated = 0;
    //     }
    // }

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

    //printf("this is generating 2 in random\n");
    // printf("Name: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }

    //checking if merging is possible
    mergeCondition = 0;
    isGameContinue(&mergeCondition, &checkZero, grid);

    // if(mergeCondition != 0){
    //     for ( i = 0; i < 4; i++)
    //     {
    //         for(j=3; j>=0; j--){
    //             if(grid[j][i] == 0){
    //                 mergeCondition = 0;
    //                 break;
    //             }
    //         }
    //         if(mergeCondition == 0){
    //             break;
    //         }
    //     }
    // }

    //printing
    if(checkZero == 1 || mergeCondition == 1){
        system("cls");
        //printf("\nThis is the actual printing\n");
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
        //printf("\nThis is the actual printing\n");
        printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, *score, *moves);
        for(i=0; i<4; i++){
            printf("\t\t\t\t");
            for(j=0; j<4; j++){
                printf("%d\t\b", grid[i][j]);
            }
            printf("\n\n");
        }
        printf("The Game has Finished!\n");
        fprintf(fptr, "%s,%d,%d\n", playerName, *score, *moves);
        fclose(fptr);
        exit(0);
    }
    return;
    //printf("\nI am in pressedLeft bottom\n");
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

    // for(i=0; i<4; i++){
    //     for(j = 3; j > 0; j--){
    //         // if(grid[i][j] == 0){
    //         //     continue;
    //         // }else if(grid[i][j] !=0 && mergeCondition == 0){
    //         //         tileValue = grid[i][j];
    //         //         mergeCondition++;
    //         // }else if (grid[i][j] !=0 && mergeCondition != 0){
    //         //     if(tileValue == grid[i][j]){
    //         //         mergeCondition++;
    //         //         break;
    //         //     }else {
    //         //         tileValue = grid[i][j];
    //         //     }
    //         // } 

    //         // if(grid[i][j] == 0){
    //         //     mergeCondition = 1;
    //         //     break;
    //         // }else 
    //         if(grid[i][j] == grid[i][j-1]){
    //             *mergeCondition = 1;
    //             break;
    //         }
    //     }
    //     // if(mergeCondition == 2){
    //     //     break;
    //     // }else if(i<3){
    //     //     mergeCondition = 0;
    //     // }
    //     if(*mergeCondition == 1){
    //         break;
    //     }
    //     // else if(mergeCondition = 2){
    //     //     break;
    //     // }
    // }

    // for(i=0; i<4; i++){
    //     for(j = 3; j >= 0; j--){
    //         if(grid[i][j] == 0){
    //             *checkZero = 1;
    //             break;
    //         }
    //     }
    //     if(*checkZero == 1){
    //         break;
    //     }
    // }

    // for(i=0; i<4; i++){
    //     for(j=0; j<3; j++){
    //         // if(grid[j][i] == 0){
    //         //     continue;
    //         // }else if(grid[j][i] !=0 && mergeCondition == 0){
    //         //         tileValue = grid[j][i];
    //         //         mergeCondition++;
    //         // }else if (grid[j][i] !=0 && mergeCondition != 0){
    //         //     if(tileValue == grid[j][i]){
    //         //         mergeCondition++;
    //         //         break;
    //         //     }else {
    //         //         tileValue = grid[j][i];
    //         //     }
    //         // } 

    //         // if(grid[j][i] == 0){
    //         //     mergeCondition = 1;
    //         //     break;
    //         // }else 
    //         if(grid[j][i] == grid[j+1][i]){
    //             *mergeCondition = 1;
    //             break;
    //         }
    //     } 
    //     if(*mergeCondition == 1){
    //         break;
    //     }
    // }

    // for(i=0; i<4; i++){
    //     for(j=0; j<4; j++){
    //         if(grid[j][i] == 0){
    //             *checkZero = 1;
    //             break;
    //         }
    //     }
    //     if(*checkZero == 1){
    //         break;
    //     }
    // }

    // for(i=0; i<4; i++){
    //     for(j = 3; j > 0; j--){
    //         // if(grid[j][i] == 0){
    //         //     continue;
    //         // }else if(grid[j][i] !=0 && mergeCondition == 0){
    //         //     tileValue = grid[j][i];
    //         //     mergeCondition++;
    //         // }else if (grid[j][i] !=0 && mergeCondition != 0){
    //         //     if(tileValue == grid[j][i]){
    //         //         mergeCondition++;
    //         //         break;
    //         //     }else {
    //         //         tileValue = grid[j][i];
    //         //     }
    //         // } 
    //         // if(grid[j][i] == 0){
                
    //         //     break;
    //         // }else 
    //         if(grid[j][i] == grid[j-1][i]){
    //             *mergeCondition = 1;
    //             break;
    //         }
    //     }
    //     // if(mergeCondition == 2){
    //     //     break;
    //     // }else if(i<3){
    //     //     mergeCondition = 0;
    //     // }
    //     if(*mergeCondition == 1){
    //         break;
    //     }
    //     // else if(mergeCondition = 2){
    //     //     break;
    //     // }
    // }

    // for(i=0; i<4; i++){
    //     for(j = 3; j >= 0; j--){ 
    //         if(grid[j][i] == 0){
    //             *checkZero = 1;
    //             break;
    //         }
    //     }
    //     if(*checkZero == 1){
    //         break;
    //     }
    // }
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
    hideCursor();
    getchar();
    system("cls");
    return;
}

void gameInsights(FILE* fptr){
    showCursor();
    char name[50];
    char searchName[50];

    int Score, Moves, played=0;

    fptr = fopen("2048_Game.txt", "r");

    printf("Enter your Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("~~~~~Your insights~~~~~\n");
    int i=1;
    while (fscanf(fptr, " %49[^,],%d,%d", searchName, &Score, &Moves) == 3){
        if (strcmp(searchName, name) == 0) {
            printf("Game No.%d): Name: %s,\tScore: %d,\tMoves: %d\n", i, searchName, Score, Moves);
            played++;
            i++;
        }
    }

    printf("Total Games Played: %d", played);
    fclose(fptr);
    hideCursor();
    getchar();
    system("cls");
    return;
}