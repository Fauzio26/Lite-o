#include <stdio.h>
#include <string.h>

// Fungsi untuk mendapatkan nilai berdasarkan rata-rata nilai rapot
float nilaiRapot(float rataRapot) {
    if (rataRapot > 95) {
        return 100.0;
    } else if (rataRapot > 90 && rataRapot <= 95) {
        return 95.0;
    } else if (rataRapot > 87.5 && rataRapot <= 90) {
        return 90.0;
    } else if (rataRapot > 85 && rataRapot <= 87.5) {
        return 85.0;
    } else if (rataRapot > 82.5 && rataRapot <= 85) {
        return 80.0;
    } else if (rataRapot > 80 && rataRapot <= 82.5) {
        return 75.0;
    } else {
        return 50.0;  // Asumsi untuk nilai rapot di bawah 80
    }
}

// Fungsi untuk mendapatkan nilai berdasarkan prestasi non-akademik
float nilaiPrestasi(char prestasi[]) {
    if (strcmp(prestasi, "Nasional") == 0) {
        return 90.0;
    } else if (strcmp(prestasi, "Provinsi") == 0) {
        return 70.0;
    } else if (strcmp(prestasi, "Tidak ada") == 0) {
        return 50.0;
    } else {
        return 50.0;  // Asumsi jika tidak memiliki prestasi atau prestasi lain
    }
}

// Fungsi untuk memeriksa apakah asal SMA dan pilihan universitas berada di kota yang sama
float nilaiAsalSMA(char asalSMA[], char pilihanUniversitas[]) {
    FILE *file;
    char line[256];
    char kotaSMA[50], kotaUniv[50];
    char *token;

    file = fopen("sma.txt", "r");
    if (file == NULL) {
        printf("Error membuka file sma.txt\n");
        return 75.0;  // nilai return kalau file sma tidak bisa dibuka
    }

    while (fgets(line, sizeof(line), file)) {
        token = strtok(line, ":");
        strcpy(kotaSMA, token);
        token = strtok(NULL, ",");

        while (token != NULL) {
            if (strstr(token, asalSMA) != NULL) {
                fclose(file);

                file = fopen("universitas.txt", "r");
                if (file == NULL) {
                    printf("Error membuka file universitas.txt\n");
                    return 75.0;  // nilai return kalau file universitas tidak bisa dibuka
                }

                while (fgets(line, sizeof(line), file)) {
                    token = strtok(line, ":");
                    strcpy(kotaUniv, token);
                    token = strtok(NULL, ",");

                    while (token != NULL) {
                        if (strstr(token, pilihanUniversitas) != NULL) {
                            fclose(file);
                            if (strcmp(kotaSMA, kotaUniv) == 0) {
                                return 90.0;
                            } else {
                                return 75.0;
                            }
                        }
                        token = strtok(NULL, ",");
                    }
                }
                fclose(file);
                return 75.0;  // nilai return kalau nama universitas tidak ditemukan
            }
            token = strtok(NULL, ",");
        }
    }
    fclose(file);
    return 75.0;  // nilai return kalau nama sma tidak ditemukan
}

// Fungsi untuk mendapatkan nilai berdasarkan pilihan jurusan
float nilaiJurusan(char pilihanJurusan[]) {
    FILE *file;
    char line[256];
    char fakultas[50];
    char *token;

    file = fopen("pilihanjurusan.txt", "r");
    if (file == NULL) {
        printf("Error membuka file pilihanjurusan.txt\n");
        return 75.0;  // nilai return kalau file pilihanjurusan tidak bisa dibuka
    }

    while (fgets(line, sizeof(line), file)) {
        token = strtok(line, ":");
        strcpy(fakultas, token);
        token = strtok(NULL, ",");

        while (token != NULL) {
            if (strstr(token, pilihanJurusan) != NULL) {
                fclose(file);

                if (strcmp(fakultas, "FK") == 0) {
                    return 75.0;
                } else if (strcmp(fakultas, "FIK") == 0) {
                    return 77.5;
                } else if (strcmp(fakultas, "FEB") == 0) {
                    return 80.0;
                } else if (strcmp(fakultas, "FT") == 0) {
                    return 82.5;
                } else if (strcmp(fakultas, "FH") == 0) {
                    return 85.0;
                } else if (strcmp(fakultas, "FIKES") == 0) {
                    return 87.5;
                } else if (strcmp(fakultas, "FISIP") == 0) {
                    return 90.0;
                } else if (strcmp(fakultas, "FIB") == 0) {
                    return 92.5;
                } else {
                    return 75.0;  // nilai return kalau nama fakultas pilihan tidak ditemukan
                }
            }
            token = strtok(NULL, ",");
        }
    }
    fclose(file);
    return 75.0;  // nilai return kalau nama pilihan jurusan tidak ditemukan
}

void peluangMasukUniversitas() {
    float rataRapot;
    char asalSMA[50];
    char pilihanUniversitas1[50];
    char pilihanUniversitas2[50];
    char prestasi[50];
    char pilihanJurusan1[50];
    char pilihanJurusan2[50];

    printf("Masukkan rata-rata nilai Rapot semester 1 - 5 : ");
    scanf("%f", &rataRapot);

    printf("Masukkan asal SMA : ");
    scanf(" %[^\n]%*c", asalSMA);

    printf("Masukkan prestasi non-akademik (Nasional/Provinsi/Tidak ada): ");
    scanf(" %[^\n]%*c", prestasi);

    printf("Masukkan pilihan Universitas ke-1 : ");
    scanf(" %[^\n]%*c", pilihanUniversitas1);

    printf("Masukkan pilihan Jurusan ke-1 : ");
    scanf(" %[^\n]%*c", pilihanJurusan1);

    printf("Masukkan pilihan Universitas ke-2 : ");
    scanf(" %[^\n]%*c", pilihanUniversitas2);

    printf("Masukkan pilihan Jurusan ke-2 : ");
    scanf(" %[^\n]%*c", pilihanJurusan2);

    float rataNilaiRapot = nilaiRapot(rataRapot);
    float nilaiAsalSMA1 = nilaiAsalSMA(asalSMA, pilihanUniversitas1);
    float nilaiAsalSMA2 = nilaiAsalSMA(asalSMA, pilihanUniversitas2);
    float nilaiPrestasiValue = nilaiPrestasi(prestasi);
    float nilaiJurusan1 = nilaiJurusan(pilihanJurusan1);
    float nilaiJurusan2 = nilaiJurusan(pilihanJurusan2);

    float totalNilai1 = (rataNilaiRapot + nilaiAsalSMA1 + nilaiPrestasiValue + nilaiJurusan1 + 100.0) / 5.0;
    float totalNilai2 = (rataNilaiRapot + nilaiAsalSMA2 + nilaiPrestasiValue + nilaiJurusan2 + 85.0) / 5.0;

    printf("\n");
    printf("+--------------------------------------------------------------------------------------------------+\n");
    printf("| %-50s | %-30s | %-10s |\n", "Universitas", "Jurusan", "Peluang(%)");
    printf("+--------------------------------------------------------------------------------------------------+\n");
    printf("| %-50s | %-30s | %-10.2f |\n", pilihanUniversitas1, pilihanJurusan1, totalNilai1);
    printf("| %-50s | %-30s | %-10.2f |\n", pilihanUniversitas2, pilihanJurusan2, totalNilai2);
    printf("+--------------------------------------------------------------------------------------------------+\n");
}

int main() {
    int pilihan;

    while (1) {
        printf("\n>> EDUCHECK : For those who passed the SNBP selection <<\n");
        printf("Know your limits and make the right choices for yourself.\n");
        printf("\nMenu:\n");
        printf("1. Program Peluang Masuk Universitas Jalur SNBP\n");
        printf("2. Keluar Program\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("\n");
                peluangMasukUniversitas();
                break;
            case 2:
                printf("\n");
                printf("Terima Kasih sudah menggunakan EDUCHECK. Hopefully you get the best results.\n");
                return 0;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }
}
