#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAPEL 5

typedef struct {
    char nama[30];
    int kkm;
    int nilai;
} Mapel;

void tampilMapel(Mapel mapel[]);
void inputNilai(Mapel mapel[]);
float hitungRata(Mapel mapel[]);
char tentukanPredikat(float rata);
void tampilRapot(Mapel mapel[], char nama[], char kelas[], char nis[], char sekolah[], float rata, char predikat);
void simpanFile(Mapel mapel[], char nama[], char kelas[], char nis[], char sekolah[], float rata, char predikat);

int main() {
    Mapel mapel[MAX_MAPEL] = {
        {"Agama", 78, 0},
        {"Bahasa Indonesia", 78, 0},
        {"Bahasa Inggris", 78, 0},
        {"Pancasila", 78, 0},
        {"Matematika", 78, 0}
    };

    char nama[50], kelas[20], nis[20], sekolah[50];
    char ulang;

    tampilMapel(mapel);

    printf("\n========= INPUT IDENTITAS SISWA =========\n");
    printf("Nama         : ");
    scanf(" %[^\n]", nama);
    printf("Kelas        : ");
    scanf(" %[^\n]", kelas);
    printf("NIS          : ");
    scanf(" %[^\n]", nis);
    printf("Nama Sekolah : ");
    scanf(" %[^\n]", sekolah);

    do {
        inputNilai(mapel);
        float rata = hitungRata(mapel);
        char predikat = tentukanPredikat(rata);

        tampilRapot(mapel, nama, kelas, nis, sekolah, rata, predikat);

        printf("\nIngin input ulang nilai? (Y/T): ");
        scanf(" %c", &ulang);

        if(ulang == 'T' || ulang == 't') {
            simpanFile(mapel, nama, kelas, nis, sekolah, rata, predikat);
        }

    } while(ulang == 'Y' || ulang == 'y');

    printf("\nProgram selesai.\n");
    return 0;
}

void tampilMapel(Mapel mapel[]) {
    printf("========= DAFTAR MATA PELAJARAN =========\n");
    printf("==========================================\n");
    printf("| %-3s | %-20s | %-4s |\n", "No", "Mata Pelajaran", "KKM");
    printf("==========================================\n");

    for(int i = 0; i < MAX_MAPEL; i++) {
        printf("| %-3d | %-20s | %-4d |\n", i+1, mapel[i].nama, mapel[i].kkm);
    }
    printf("==========================================\n");
}

void inputNilai(Mapel mapel[]) {
    printf("\n========= INPUT NILAI =========\n");
    for(int i = 0; i < MAX_MAPEL; i++) {
        int valid;
        do {
            printf("Nilai %s (0-100): ", mapel[i].nama);
            valid = scanf("%d", &mapel[i].nilai);

            if(valid != 1) {
                printf("Input harus berupa ANGKA!\n");
                while(getchar() != '\n');
                continue;
            }

            if(mapel[i].nilai < 0 || mapel[i].nilai > 100) {
                printf("Nilai harus antara 0 - 100!\n");
            }
        } while(valid != 1 || mapel[i].nilai < 0 || mapel[i].nilai > 100);
    }
}

float hitungRata(Mapel mapel[]) {
    float total = 0;
    for(int i = 0; i < MAX_MAPEL; i++) {
        total += mapel[i].nilai;
    }
    return total / MAX_MAPEL;
}

char tentukanPredikat(float rata) {
    if(rata >= 90) return 'A';
    else if(rata >= 80) return 'B';
    else if(rata >= 70) return 'C';
    else return 'D';
}

void tampilRapot(Mapel mapel[], char nama[], char kelas[], char nis[], char sekolah[], float rata, char predikat) {
    printf("\n================== RAPORT SISWA ==================\n");
    printf("Nama    : %s\n", nama);
    printf("Kelas   : %s\n", kelas);
    printf("NIS     : %s\n", nis);
    printf("Sekolah : %s\n\n", sekolah);

    printf("==============================================================\n");
    printf("| %-3s | %-20s | %-6s | %-4s | %-12s |\n", "No", "Mata Pelajaran", "Nilai", "KKM", "Status");
    printf("==============================================================\n");

    for(int i = 0; i < MAX_MAPEL; i++) {
        char status[15];
        if(mapel[i].nilai >= mapel[i].kkm)
            strcpy(status, "Lulus");
        else
            strcpy(status, "Tidak Lulus");

        printf("| %-3d | %-20s | %-6d | %-4d | %-12s |\n", i+1, mapel[i].nama, mapel[i].nilai, mapel[i].kkm, status);
    }

    printf("==============================================================\n");
    printf("Rata-rata : %.2f\n", rata);
    printf("Predikat  : %c\n", predikat);
}

void simpanFile(Mapel mapel[], char nama[], char kelas[], char nis[], char sekolah[], float rata, char predikat) {
    char namaFile[100];
    sprintf(namaFile, "Raport_%s.txt", nis);

    FILE *fp = fopen(namaFile, "w");
    if(fp == NULL) {
        printf("Gagal membuat file!\n");
        return;
    }

    fprintf(fp, "======================= RAPORT SISWA =======================\n");
    fprintf(fp, "Nama    : %-30s\n", nama);
    fprintf(fp, "Kelas   : %-20s\n", kelas);
    fprintf(fp, "NIS     : %-20s\n", nis);
    fprintf(fp, "Sekolah : %-30s\n", sekolah);
    fprintf(fp, "============================================================\n\n");

    fprintf(fp, "============================================================\n");
    fprintf(fp, "| %-3s | %-20s | %-6s | %-4s | %-12s |\n", "No", "Mata Pelajaran", "Nilai", "KKM", "Status");
    fprintf(fp, "============================================================\n");

    for(int i = 0; i < MAX_MAPEL; i++) {
        char status[15];
        if(mapel[i].nilai >= mapel[i].kkm)
            strcpy(status, "Lulus");
        else
            strcpy(status, "Tidak Lulus");

        fprintf(fp, "| %-3d | %-20s | %-6d | %-4d | %-12s |\n", i + 1, mapel[i].nama, mapel[i].nilai, mapel[i].kkm, status);
    }

    fprintf(fp, "============================================================\n");
    fprintf(fp, "Rata-rata : %-10.2f\n", rata);
    fprintf(fp, "Predikat  : %-5c\n", predikat);
    fprintf(fp, "============================================================\n");

    fclose(fp);
    printf("\nRaport berhasil disimpan di: %s\n", namaFile);
}
