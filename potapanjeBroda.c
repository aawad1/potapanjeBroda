#include <stdio.h>
#include <math.h>
#include <string.h>


void unesi(char niz[], int velicina) {
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

void iscrtajPolje(){

    printf("  0 1 2 3 4 5 6 7 8 9\n");
    printf("  _ _ _ _ _ _ _ _ _ _\n");

    for (int i=0; i<10; i++){     
        printf("%d", i);  
        for (int j=0; j<10; j++){
            printf("|_");
        }
        printf("|\n");
    }
}

void opisIgre(){
    printf("Dobro došli u igricu potapanje brodova.\nU ovoj igrici igraju dva igraca.\n");
    printf("Igrač broj 1: unesite podatke za 3 broda velicina 5, 4 i 3 u formatu (x,y,z), gdje su x=red broda, y=kolona broda, z=orijentacija broda gdje je n-north, s-south, e-east i w-west.\n");
    printf("Obavezni uslovi: | x>=0 i x<10 | - | y>=0 i y<10 | - | z = n/s/e/w |");
    printf("Pazite da duzina broda ne smije prekoraciti van table, u suprotnom se trazi ponovni unos.\n");
}

int main (void){

    opisIgre();
    char row, colon, orientation;
    char inputString[20];
    
    
    //unosi podatke i dodijeli ih parametrima red, kolona, duzina broda i orijentacija
    iscrtajPolje();
    unesi(inputString, strlen(inputString));
    sscanf(inputString, "%c,%c,%c", &row, &colon, &orientation);
    
    int polje1[10][10] = {{0}};   

    return 0;
}