#include <stdio.h>
#include <math.h>

int main (void){

    printf("Dobro došli u igricu potapanje brodova.\nU ovoj igrici igraju dva igrača.\n");
    printf("Igrač broj 1: unesite podatke broda u formatu (x,y,z,w), gdje su x=red broda, y=kolona broda, z=duzina broda, w=orijentacija broda gdje je n-north, s-south, e-east i w-west.\n");
    printf("Pazite da duzina broda ne smije prekoračiti van table, u suprotnom se traži ponovni unos.\n");
    printf("Unos: ");
    int row, colon, size;
    char orientation;
    char inputString[20];
    scanf("%s ", inputString);
    sscanf(inputString, "%d,%d,%c,%d", &row, &colon, &orientation, &size);
    
    int polje1[10][10] = {{0}}; 
    for (int j=0; j<10; j++){
            printf(" _");
    }
    printf("\n");
    for (int i=0; i<10; i++){       
        for (int j=0; j<10; j++){
            printf("|_");
        }
        printf("|\n");
    }
    

    return 0;
}