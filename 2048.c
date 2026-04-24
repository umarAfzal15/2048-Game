#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

//these are declarations only
void gamePlay(FILE *fptr, char playerNmae[], int grid[4][4]);
void pressedLeft(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]);
void pressedRight(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]);
void pressedUp(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]);
void pressedDown(FILE *fptr, int *moves,int *score, char playerName[],  int grid[4][4]);

//It hides cursor
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

//this is main
int main(){
    system("cls");
    char playerName[50];
    //int score=0;
    int option, i, j, k;
    int grid[4][4];

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

    if(option==1){
        char ok;
        printf("Please Enter Your Name: ");
        fgets(playerName, sizeof(playerName), stdin);
        system("cls");
        printf("\n~~~~~Let's Start a small Tutorial~~~~~\n");

        printf("Press:\nW for Up\nA for Left\nS for Down\nD for right\nPress Y if Understood!\n");
        scanf(" %c", &ok);

        while(1){
            if(ok != 'y' && ok != 'Y'){
                printf("Please Enter Enter \"y\" ");
                //getchar();
                scanf(" %c", &ok);
            }else{
                break;
            }
        }
        hideCursor();
        system("cls");
        //fputs(playerName, fptr);
        gamePlay(fptr, playerName, grid); // function call
    }else if(option==2){

    }else if(option==3){

    }else if(option==4){
        exit(0);
    }

    return 0;
}

//this handles Game Play
void gamePlay(FILE *fptr, char playerName[], int grid[4][4]) {
    // Game Play Here
    //FILE** fptr1 = fptr; 
    int keyPressed;
    int score=0;
    int moves=0;
    int i=0, j;
    int row, col;
    
    while(i<2){
        srand(time(0));
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
    printf("\t\t\tName: %s,       Score: %d,      Moves: %d\n\n", playerName, score, moves);
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
            moves++;
            switch (_getch()) {
                case 72: 
                    //printf("Up Arrow\n");
                    pressedUp(fptr, &moves, &score, playerName, grid);
                    break;
                case 80:
                    //printf("Down Arrow\n");
                    pressedDown(fptr, &moves, &score, playerName, grid);
                    break;
                case 75:
                    //printf("Left Arrow\n");
                    pressedLeft(fptr, &moves, &score, playerName, grid);
                    break;
                case 77:
                    //printf("Right Arrow\n");
                    pressedRight(fptr, &moves, &score, playerName, grid);
                    break;
                default:
                    break;
            }
        }else {
            printf("\nThank you for playing the Game!\n");
            fprintf(fptr, "%s,%d,%d\n", playerName, score, moves);
            fclose(fptr);
            exit(0);
        }
      
        // srand(time(0));
        // row = rand() % 4;
        // col = rand() % 4;
        // if(grid[row][col] == 2){
        //     continue;
        // }else{
        //     grid[row][col] = 2;
        //     i++;
        // }
    }

    printf("Name: %s,       Score: %d,      Moves: %d\n\n", playerName, score, moves);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(grid[i][j]==2){
                printf("%d  ", grid[i][j]);
            }else{
                grid[i][j] = 0;
                printf("%d  ", grid[i][j]);
            }
            
        }
        printf("\n");
    }
    //system("cls");
    //printf("%s", playerName);
}

//this handles left key move
void pressedLeft(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]){

    int mergeCondition=0, tileValue, mergedposition=0;
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
    while(isGenrated){
        srand(time(0));
        row = rand() % 4;
        col = rand() % 4;
        if(grid[row][col] == 0){
            grid[row][col] = 2;
            isGenrated = 0;
        }
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
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            if(grid[i][j] == 0){
                continue;
            }else if(grid[i][j] !=0 && mergeCondition == 0){
                    tileValue = grid[i][j];
                    mergeCondition++;
            }else if (grid[i][j] !=0 && mergeCondition != 0){
                if(tileValue == grid[i][j]){
                    mergeCondition++;
                    break;
                }else {
                    tileValue = grid[i][j];
                } 
            } 
        }
        if(mergeCondition == 2){
            break;
        }
        mergeCondition = 0;
    }

    if(mergeCondition != 0){
        for ( i = 0; i < 4; i++)
        {
            for(j=0; j<4; j++){
                if(grid[i][j] == 0){
                    mergeCondition = 0;
                    break;
                }
            }
            if(mergeCondition == 0){
                break;
            }
        }
    }
    //printing
   // printf("\nThis is the actual printing\n");
    if(mergeCondition == 2 || mergeCondition == 0){
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
    //printf("\nI am in pressedLeft bottom\n");
}


void pressedRight(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]){

    int mergeCondition=0, tileValue, mergedposition=0;
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
    while(isGenrated){
        srand(time(0));
        row = rand() % 4;
        col = rand() % 4;
        if(grid[row][col] == 0){
            grid[row][col] = 2;
            isGenrated = 0;
        }
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
    for(i=0; i<4; i++){
        for(j = 3; j >= 0; j--){
            if(grid[i][j] == 0){
                continue;
            }else if(grid[i][j] !=0 && mergeCondition == 0){
                    tileValue = grid[i][j];
                    mergeCondition++;
            }else if (grid[i][j] !=0 && mergeCondition != 0){
                if(tileValue == grid[i][j]){
                    mergeCondition++;
                    break;
                }else {
                    tileValue = grid[i][j];
                }
            } 
        }
        if(mergeCondition == 2){
            break;
        }
        mergeCondition = 0;
    }

    if(mergeCondition != 0){
        for ( i = 0; i < 4; i++)
        {
            for(j=3; j>=0; j--){
                if(grid[i][j] == 0){
                    mergeCondition = 0;
                    break;
                }
            }
            if(mergeCondition == 0){
                break;
            }
        }
    }

    //printing
   // printf("\nThis is the actual printing\n");
    if(mergeCondition == 2 || mergeCondition == 0){
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
    //printf("\nI am in pressedRight bottom\n");
}
void pressedUp(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]){

    int mergeCondition=0, tileValue, mergedposition=0;
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
    while(isGenrated){
        srand(time(0));
        row = rand() % 4;
        col = rand() % 4;
        if(grid[row][col] == 0){
            grid[row][col] = 2;
            isGenrated = 0;
        }
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
    mergeCondition = 0;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            if(grid[j][i] == 0){
                continue;
            }else if(grid[j][i] !=0 && mergeCondition == 0){
                    tileValue = grid[j][i];
                    mergeCondition++;
            }else if (grid[j][i] !=0 && mergeCondition != 0){
                if(tileValue == grid[j][i]){
                    mergeCondition++;
                    break;
                }else {
                    tileValue = grid[j][i];
                }
            } 
        }
        if(mergeCondition == 2){
            break;
        }
        mergeCondition = 0; 
    }

    if(mergeCondition != 0){
        for ( i = 0; i < 4; i++)
        {
            for(j=0; j<4; j++){
                if(grid[j][i] == 0){
                    mergeCondition = 0;
                    break;
                }
            }
            if(mergeCondition == 0){
                break;
            }
        }
    }

    //printing
   // printf("\nThis is the actual printing\n");
    if(mergeCondition == 2 || mergeCondition == 0){
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
    //printf("\nI am in pressedUp bottom\n");
}
void pressedDown(FILE *fptr, int *moves, int *score, char playerName[], int grid[4][4]){
    int mergeCondition=0, tileValue, mergedposition=0;
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
        for ( j = 3; j >= 0; j--)
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
    while(isGenrated){
        srand(time(0));
        row = rand() % 4;
        col = rand() % 4;
        if(grid[row][col] == 0){
            grid[row][col] = 2;
            isGenrated = 0;
        }
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

    for(i=0; i<4; i++){
        for(j = 3; j >= 0; j--){
            if(grid[j][i] == 0){
                continue;
            }else if(grid[j][i] !=0 && mergeCondition == 0){
                tileValue = grid[j][i];
                mergeCondition++;
            }else if (grid[j][i] !=0 && mergeCondition != 0){
                if(tileValue == grid[j][i]){
                    mergeCondition++;
                    break;
                }else {
                    tileValue = grid[j][i];
                }
            } 
        }
        if(mergeCondition == 2){
            break;
        }
        mergeCondition = 0;
    }

    if(mergeCondition != 0){
        for ( i = 0; i < 4; i++)
        {
            for(j=3; j>=0; j--){
                if(grid[j][i] == 0){
                    mergeCondition = 0;
                    break;
                }
            }
            if(mergeCondition == 0){
                break;
            }
        }
    }

    //printing
    if(mergeCondition == 2 || mergeCondition == 0){
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
    //printf("\nI am in pressedLeft bottom\n");
}