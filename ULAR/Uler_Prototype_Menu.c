#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PANJANG 50
#define LEBAR 20

#define YELLOW "\e[0;33m"
#define WHITE "\e[0;37m"
#define GREEN "\e[0;32m"
#define CYAN "\e[0;36m"
#define MAGENTA "\e[0;35m"
#define RED "\e[0;31m"

typedef struct{
    int x;
    int y;
    char nama[100];
    int skor;
    int aktif;
} TitikData;

void tunggu(float x){
    time_t mulai;
    time_t sekarang;
    time(&mulai);
    do {
        time(&sekarang);
    } while (difftime(sekarang, mulai) < x);
}

void inisialisasiPapan(char papan[LEBAR][PANJANG], char papanSimpan[LEBAR][PANJANG]){
    int i, j;

    for (i = 0; i < LEBAR; i++) {
        for (j = 0; j < PANJANG; j++) {
            papan[i][j] = ' ';
        }
    }

    for (i = 0; i < PANJANG; i++) {
        papan[0][i] = '-';
        papan[LEBAR - 1][i] = '-';
    }

    for (i = 1; i < LEBAR - 1; i++) {
        papan[i][0] = '|';
        papan[i][PANJANG - 1] = '|';
    }

    papan[0][0] = '+';
    papan[0][PANJANG - 1] = '+';
    papan[LEBAR - 1][0] = '+';
    papan[LEBAR - 1][PANJANG - 1] = '+';

    for (i = 0; i < LEBAR; i++) {
        strcpy(papanSimpan[i], papan[i]);
    }
}

void cetakHadiah(TitikData titikData[], int jumlah){
    printf(CYAN);
    int i;
    printf("Daftar Hadiah:\n");
    printf("+-------+-------+-------+-------+\n");
    printf("| X\t| Y\t| Nama\t| Skor\t|\n");
    printf("+-------+-------+-------+-------+\n");
    for (i = 0; i < jumlah; i++) {
        printf("| %d\t| %d\t| %s\t| %d\t|\n", titikData[i].x, titikData[i].y, titikData[i].nama, titikData[i].skor);
    }
    printf("+-------+-------+-------+-------+\n");
    printf(WHITE);
}

void cetakGerak(int gerakX[], int gerakY[], int jumlahGerak){
    printf(CYAN);
    int i;
    printf("Daftar Gerakan:\n");
    printf("+-------+-------+\n");
    printf("| X\t| Y\t|\n");
    printf("+-------+-------+\n");
    for (i = 0; i < jumlahGerak; i++) {
        printf("| %d\t| %d\t|\n", gerakX[i], gerakY[i]);
    }
    printf("+-------+-------+\n");
    printf(WHITE);
}

void tambahHadiah(TitikData titikData[], int jumlah){
    cetakHadiah(titikData, jumlah);

    printf(MAGENTA);
    printf("Masukkan posisi (x y), nama, dan skor hadiah: ");
    scanf("%d %d %s %d", &titikData[jumlah].x, &titikData[jumlah].y, titikData[jumlah].nama, &titikData[jumlah].skor);
    printf(WHITE);
    titikData[jumlah].aktif = 1;

    FILE *file = fopen("file_thadiah.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d %d %s %d\n", titikData[jumlah].x, titikData[jumlah].y, titikData[jumlah].nama, titikData[jumlah].skor);
    } else {
        printf("Tidak dapat membuka file untuk menulis.\n");
    }
	fclose(file);
	
    jumlah++;
}

void tambahGerak(int gerakX[], int gerakY[], int jumlahGerak){
    cetakGerak(gerakX, gerakY, jumlahGerak);

    printf(MAGENTA);
    printf("Masukkan posisi baru (x y): ");
    scanf("%d %d", &gerakX[jumlahGerak], &gerakY[jumlahGerak]);
	printf(WHITE);
	
    FILE *file = fopen("file_tgerak.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d %d\n", gerakX[jumlahGerak], gerakY[jumlahGerak]);
    } else {
        printf("Tidak dapat membuka file untuk menulis.\n");
    }
    fclose(file);
    
    jumlahGerak++;
}

void simulasi(char papan[LEBAR][PANJANG], char papanSimpan[LEBAR][PANJANG], TitikData titikData[], int jumlah, int gerakX[], int gerakY[], int jumlahGerak, int totalSkor){
    int i, j, k;

    for (i = 0; i < jumlahGerak; i++) {
        for (j = 0; j < LEBAR; j++) {
            strcpy(papan[j], papanSimpan[j]);
        }

        for (j = 0; j < jumlah; j++) {
            if (titikData[j].aktif) {
                char skorString[5];
                sprintf(skorString, "%d", titikData[j].skor);
                int jumlahSkor = strlen(skorString);

                papan[titikData[j].y + 1][titikData[j].x + 1] = titikData[j].nama[0];
                papan[titikData[j].y + 1][titikData[j].x + 2] = titikData[j].nama[1];

                for (k = 0; k < jumlahSkor; k++) {
                    papan[titikData[j].y + 1][titikData[j].x + k + 3] = skorString[k];
                }
            }
        }

        papan[gerakY[i] + 1][gerakX[i] + 1] = 'O';

        for (j = 0; j < LEBAR; j++) {
            for (k = 0; k < PANJANG; k++) {
                if (papan[j][k] == 'O') {
                    printf(RED);
                    printf("%c", papan[j][k]);
                    printf(WHITE);
                } else if (papan[j][k] == '+' || papan[j][k] == '-' || papan[j][k] == '|') {
                    printf(YELLOW);
                    printf("%c", papan[j][k]);
                    printf(WHITE);
                } else if ((papan[j][k] >= 'a' && papan[j][k] <= 'z') || (papan[j][k] >= '0' && papan[j][k] <= '9')) {
                    printf(GREEN);
                    printf("%c", papan[j][k]);
                    printf(WHITE);
                } else {
                    printf(WHITE);
                    printf("%c", papan[j][k]);
                }
            }
            printf("\n");
        }

        printf(YELLOW);
        printf("Skor: %d\n", totalSkor);
        printf(WHITE);
        
        for (j = 0; j < jumlah; j++) {
            if (gerakX[i] == titikData[j].x && gerakY[i] == titikData[j].y && titikData[j].aktif) {
                totalSkor += titikData[j].skor; 
                titikData[j].aktif = 0;
            }
        }
        
		tunggu(0.5);
        system("cls");
    }
}

int main(){
    TitikData titikData[100];
    char papan[LEBAR][PANJANG];
    char papanSimpan[LEBAR][PANJANG];
    int jumlah = 0;
    int totalSkor = 0;

    FILE *file = fopen("file_thadiah.txt", "r");
    if (file == NULL) {
        printf("Tidak dapat membuka file.\n");
        return 1;
    }

    while (fscanf(file, "%d %d %s %d", &titikData[jumlah].x, &titikData[jumlah].y, titikData[jumlah].nama, &titikData[jumlah].skor) == 4) {
        titikData[jumlah].aktif = 1;
        jumlah++;
    }
    fclose(file);

    int gerakX[100];
    int gerakY[100];
    int jumlahGerak = 0;

    FILE *gerakFile = fopen("file_tgerak.txt", "r");
    if (gerakFile == NULL) {
        printf("Tidak dapat membuka file tgerak.txt.\n");
        return 1;
    }

    while (fscanf(gerakFile, "%d %d", &gerakX[jumlahGerak], &gerakY[jumlahGerak]) == 2) {
        jumlahGerak++;
    }
    fclose(gerakFile);
    
    int pilihan;
    do {
        printf(YELLOW);
        printf("#         #####     #####     #####            #####  \n");
        printf("#           #         #       #                #   #  \n");
        printf("#           #         #       #####    ###     #   #  \n");
        printf("#           #         #       #                #   #  \n");
        printf("#####     #####       #       #####            #####  \n\n");
        printf(WHITE);

        printf(MAGENTA);
        printf("Menu:\n");
        printf("1. Tambah hadiah\n");
        printf("2. Tambah gerak O\n");
        printf("3. Simulasi Lite O\n");
        printf("4. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);
        printf(WHITE);

        switch (pilihan) {
            case 1:
                system("cls");
                tambahHadiah(titikData, jumlah);
                system("cls");
                break;
            case 2:
                system("cls");
                tambahGerak(gerakX, gerakY, jumlahGerak);
                system("cls");
                break;
            case 3:
                inisialisasiPapan(papan, papanSimpan);
                simulasi(papan, papanSimpan, titikData, jumlah, gerakX, gerakY, jumlahGerak, totalSkor);
                break;
            case 4:
                printf("Keluar...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 4);

    return 0;
}

