#include <stdio.h>
#include <string.h>

typedef struct {
    int koordinat1;
    int koordinat2;
    char huruf[30];
    int skor;
} data;

int main() {
    data hadiah[100]; 
    int i, banyak;

    printf("Masukan banyak hadiah : ");
    scanf("%d", &banyak);

    printf("\nMasukkan posisi (x y), nama, dan skor hadiah: \n");

    for (i = 0; i < banyak; i++) {
        scanf("%d %d %s %d", &hadiah[i].koordinat1, &hadiah[i].koordinat2, &hadiah[i].huruf, &hadiah[i].skor);
    }

    FILE *cetak = fopen("file_thadiah.txt", "w");

    for (i = 0; i < banyak; i++) {
        fprintf(cetak, "%d %d %s %d\n", hadiah[i].koordinat1, hadiah[i].koordinat2, hadiah[i].huruf, hadiah[i].skor);
    }

    fclose(cetak);

    return 0;
}
