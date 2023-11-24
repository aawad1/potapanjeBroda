#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum Options {
    HIT,
    MISS,
    BLANK
};

bool** allocateMatrix(int rows, int cols) {
    bool** matrix = (bool**)malloc(rows * sizeof(bool*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (bool*)malloc(cols * sizeof(bool));
    }
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            matrix[i][j]=false;
        }
    }
    return matrix;
}

enum Options** allocateOptionsMatrix(int rows, int cols) {
    enum Options** matrix = (enum Options**)malloc(rows * sizeof(enum Options*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (enum Options*)malloc(cols * sizeof(enum Options));
    }
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            matrix[i][j] = BLANK;
        }
    }
    return matrix;
}

void stringInput(char niz[], int velicina) {
    char znak = getchar();
    if (znak == '\n') znak = getchar();
    int i = 0;
    while (i < velicina-1 && znak != '\n') {
        niz[i] = znak;
        i++;
        znak = getchar();
    }
    niz[i] = '\0';
 }

void drawBoard(bool **field){
    
    printf("\n");
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    printf("  _ _ _ _ _ _ _ _ _ _\n");

    for (int i=0; i<10; i++){     
        printf("%d", i);  
        for (int j=0; j<10; j++){
            if(field[i][j]==true) 
                printf("|X");
            else 
                printf("|_");
        }
        printf("|\n");
    }
}

void drawOptionsBoard(enum Options **field){
    
    printf("\n");
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    printf("  _ _ _ _ _ _ _ _ _ _\n");

    for (int i=0; i<10; i++){     
        printf("%d", i);  
        for (int j=0; j<10; j++){
            if(field[i][j] == HIT) 
                printf("|X");
            else if(field[i][j] == MISS)
                printf("|O");
            else 
                printf("|_");
        }
        printf("|\n");
    }
}

void gameDetails(){
    printf("________________________________________________________________________\n");
    printf("Welcome to the BATTLESHIP GAME.\nThis is a two player game.\n");
    printf("How To Play: \nFirst player enters 3 locations of his ships in format (row colon orientation). You must look out that ships have to be ON BOARD and NOT CROSS EACH OTHER.\n");
    printf("Size of the board are 10x10 which means that row and colon must not be below 0 or over 9.\n");
    printf("Orientation of the ship can be n/s/e/w which represent north/south/east/west.\n");
    printf("So, basically you enter the starting position of your ship using (row colon) and the orientation of the ship from that location using (orientation).\n");
    printf("After a succesful input, player two does the same.\n");
    printf("The game finishes when either player sinks all ships.\nGOOD LUCK!\n");
    printf("________________________________________________________________________\n");
}

bool checkInput(char row, char colon, char size, char orientation){
    if(row<0 || row>10 || colon<0 || colon>10 || (orientation!='n' && orientation!='s' && orientation!='e' && orientation!='w')) 
        return false;

    switch (orientation)
    {
    case 'n':
        if((row-size)<0) return false;
        break;
    case 's':
        if((row+size)>10) return false;
        break;
    case 'e':
        if((colon+size)>10) return false;
        break;
    case 'w':
        if((colon-size)<0) return false;
        break;
        
    default:
        break;
        
    }
    return true;
}

bool checkBoardValues(bool **field, char row, char colon, char size, char orientation){
    
    switch (orientation)
    {
    case 'n':
        for(int i=row; i>row-size; i--){
            if(field[i][colon]) return false;
        }
        break;
    case 's':
        for(int i=row; i<row+size; i++){
            if(field[i][colon]) return false;
        }
        break;
    case 'e':
        for(int j=colon; j<colon+size; j++){
            if(field[row][j]) return false;
        }
        break;
    case 'w':
        for(int j=colon; j>colon-size; j--){
            if(field[row][j]) return false;
        }
        break;
        
    default:
        break;
        
    }
    return true;
}

void putOnBoard(bool **field, int row, int colon, int size,  char orientation){
    if(checkInput(row, colon, size, orientation) && checkBoardValues(field, row, colon, size, orientation)){

        switch (orientation)
        {
        case 'n':
            for(int i=row; i>row-size; i--){
                field[i][colon]=true;
            }
            break;
        case 's':
            for(int i=row; i<row+size; i++){
                field[i][colon]=true;
            }
            break;
        case 'e':
            for(int j=colon; j<colon+size; j++){
                field[row][j]=true;
            }
            break;
        case 'w':
            for(int j=colon; j>colon-size; j--){
                field[row][j]=true;
            }
            break;
            
        default:
            break;
        }
    }
    else printf("Can't put on board");
}

void inputBoard(bool **field, int size) {
    int row = 0, colon = 0;
    char orientation = '0';
    char inputString[20];

    while (1) {
       
        printf("Input ship size %d in a field (row colon): ", size);
        
        stringInput(inputString, sizeof(inputString));
        // Note: sscanf returns the number of successfully read items.
        if (sscanf(inputString, "%d %d %c", &row, &colon, &orientation) == 3) {

            if (checkInput(row, colon, size, orientation) && checkBoardValues(field, row, colon, size, orientation)) {    
                printf("Input valid :) \n");
                putOnBoard(field, row, colon, size, orientation);
                break;  // Break out of the loop when conditions are met
            } else {
                printf("\nInvalid input format. Try again.\n");
            }
        } else {
            printf("\nInvalid input format. Try again.\n");
        }

        //printf("\n\n%d %d %c\n\n", row, colon, orientation);
    }
}

void hitTarget(bool **field, enum Options **field_player, int *target){
    int row, colon;
    char inputString[8];
    while(1){
        printf("Input target hit (row colon): ");
        stringInput(inputString, sizeof(inputString));
        if (sscanf(inputString, "%d %d ", &row, &colon) == 2){
            if(row>=0 && row<=9 && colon>=0 && colon<=9){
                if(field_player[row][colon] == HIT || field_player[row][colon] == MISS){
                    printf("Field already hit. Try again!\n");
                } else 
                    break;
            } else {
                printf("Invalid field. Try again!\n");
            }
        } else {
            printf("Input values are not correct. Try again. \n");
        }
        
    }
    if(field[row][colon] == false) {
        field_player[row][colon] = MISS;
        printf("You have missed :( \n)");
    }
    else {
        field_player[row][colon] = HIT;
        (*target)++;
        printf("You have hit a field :D \n Targets hit: %d", *target);
    }
    printf("Your board: \n");
    drawOptionsBoard(field_player);
}

bool checkWinner(int target){
    if(target == 13){
        printf("------------------------------------\n");
        printf("PLAYER 1 HAS WON. CONGRATULATIONS!!!\n");
        printf("------------------------------------\n");
        return true;
    }
    return false;
}

int main (void){
    
    gameDetails();
    char inputString[20];
    bool **field1 = allocateMatrix(10,10);
    bool **field2 = allocateMatrix(10,10);
    
    printf("\nEnter player 1: \n");
    drawBoard(field1);
    inputBoard(field1, 5);
    //drawBoard(field1);
    inputBoard(field1, 4);
    //drawBoard(field1);
    inputBoard(field1, 2);
    //drawBoard(field1);

    //drawBoard(field1)/;

    printf("\nEnter player 2: \n");
    drawBoard(field2);
    inputBoard(field2, 5);
    //drawBoard(field2);
    inputBoard(field2, 4);
    //drawBoard(field2);
    inputBoard(field2, 3);
    //drawBoard(field2);

    enum Options **field_player1 = allocateOptionsMatrix(10,10);
    enum Options **field_player2 = allocateOptionsMatrix(10,10);
    int targeted1=0, targeted2=0;

    while(1){

        printf("\n\n\nPLAYER 1 GO: ");
        hitTarget(field2, field_player1, &targeted1);
        if(checkWinner(targeted1)) break;
        
        printf("\n\n\nPLAYER 2 GO: ");
        hitTarget(field1, field_player2, &targeted2);
        if(checkWinner(targeted2)) break;
        
    }       
    
  
    return 0;
}