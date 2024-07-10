#include <stdio.h>
#include <string.h>

typedef struct {
    int Koordinat1;
    int Koordinat2;
} data;

int main() {
    data gerak[100]; 
    int i, banyak;

    printf("Masukan banyak gerakan : ");
    scanf("%d", &banyak);

    printf("\nMasukan gerakan (x y): \n");

    for (i = 0; i < banyak; i++) {
        scanf("%d %d", &gerak[i].Koordinat1, &gerak[i].Koordinat2);
    }

    FILE *cetak = fopen("file_tgerak.txt", "w");

    for (i = 0; i < banyak; i++) {
        fprintf(cetak, "%d %d\n", gerak[i].Koordinat1, gerak[i].Koordinat2);
    }
	
    fclose(cetak);

    return 0;
}
