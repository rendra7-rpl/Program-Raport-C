#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAPEL 5

typedef struct {
    char nama[30];
    int kkm;
    int nilai;
} Mapel;

void tampilkanDaftarMapel(Mapel daftarMapel[]);
void inputNilaiSiswa(Mapel daftarMapel[]);
float hitungRataRata(Mapel daftarMapel[]);
char tentukanPredikat(float rataRata, int kkmMinimal);
void tampilkanRaport(Mapel daftarMapel[], char nama[], char kelas[], char nisn[], char sekolah[], float rataRata, char predikat);
void eksporKeFile(Mapel daftarMapel[], char nama[], char kelas[], char nisn[], char sekolah[], float rataRata, char predikat);

int main() {
    Mapel daftarMapel[MAX_MAPEL] = {
        {"Pemrograman Web", 76, 0},
        {"Pemrograman Mobile", 76, 0},
        {"Basis Data", 76, 0},
        {"PBO", 76, 0},
        {"Kewirausahaan", 79, 0}
    };

    char nama[50], kelas[20], nisn[20], sekolah[50], pilihanUlang;

    tampilkanDaftarMapel(daftarMapel);

    printf("\n========= INPUT IDENTITAS SISWA =========\n");
    printf("Nama         : "); 
    scanf(" %[^\n]", nama);
    printf("Kelas        : "); 
    scanf(" %[^\n]", kelas);
    printf("NISN         : "); 
    scanf(" %[^\n]", nisn);
    printf("Nama Sekolah : "); 
    scanf(" %[^\n]", sekolah);

    do {
        inputNilaiSiswa(daftarMapel);

        float rataRata = hitungRataRata(daftarMapel);
        char predikat = tentukanPredikat(rataRata, 76);

        tampilkanRaport(daftarMapel, nama, kelas, nisn, sekolah, rataRata, predikat);

        printf("\nApakah data sudah benar?\n");
        printf("Tekan T untuk cetak rapor (Selesai)\n");
        printf("Tekan Y untuk input ulang nilai\n");
        printf("Pilihan Anda: ");
        scanf(" %c", &pilihanUlang);

        if (pilihanUlang == 'T' || pilihanUlang == 't') {
            eksporKeFile(daftarMapel, nama, kelas, nisn, sekolah, rataRata, predikat);
        }

    } while (pilihanUlang == 'Y' || pilihanUlang == 'y');

    printf("\nProgram selesai. Terima Kasih!\n");
    return 0;
}

void tampilkanDaftarMapel(Mapel daftarMapel[]) {
    printf("========= DAFTAR MATA PELAJARAN =========\n");
    printf("------------------------------------------\n");
    printf("| %-3s | %-20s | %-4s |\n", "No", "Mata Pelajaran", "KKM");
    printf("------------------------------------------\n");

    for (int i = 0; i < MAX_MAPEL; i++) {
        printf("| %-3d | %-20s | %-4d |\n", i + 1, daftarMapel[i].nama, daftarMapel[i].kkm);
    }
    printf("------------------------------------------\n");
}

void inputNilaiSiswa(Mapel daftarMapel[]) {
    printf("\n========= INPUT NILAI =========\n");
    for (int i = 0; i < MAX_MAPEL; i++) {
        int isInputValid;
        do {
            printf("Nilai %s (0-100): ", daftarMapel[i].nama);
            isInputValid = scanf("%d", &daftarMapel[i].nilai);

            if (isInputValid != 1) {
                printf("Error: Input harus berupa angka.\n");
                while (getchar() != '\n');
            } else if (daftarMapel[i].nilai < 0 || daftarMapel[i].nilai > 100) {
                printf("Error: Rentang nilai 0 - 100.\n");
                isInputValid = 0;
            }
        } while (!isInputValid);
    }
}

float hitungRataRata(Mapel daftarMapel[]) {
    float totalNilai = 0;
    for (int i = 0; i < MAX_MAPEL; i++) {
        totalNilai += daftarMapel[i].nilai;
    }
    return totalNilai / MAX_MAPEL;
}

char tentukanPredikat(float rataRata, int kkmMinimal) {
    if (rataRata >= 86) return 'A';
    if (rataRata >= 80) return 'B';
    if (rataRata >= kkmMinimal) return 'C';
    return 'D';
}

void tampilkanRaport(Mapel daftarMapel[], char nama[], char kelas[], char nisn[], char sekolah[], float rataRata, char predikat) {
    printf("\n================== RAPORT SISWA ==================\n");
    printf("Nama    : %s\nKelas   : %s\nNISN    : %s\nSekolah : %s\n", nama, kelas, nisn, sekolah);
    printf("--------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-6s | %-4s | %-12s |\n", "No", "Mata Pelajaran", "Nilai", "KKM", "Status");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < MAX_MAPEL; i++) {
        char* status = (daftarMapel[i].nilai >= daftarMapel[i].kkm) ? "Lulus" : "Tidak Lulus";
        printf("| %-3d | %-20s | %-6d | %-4d | %-12s |\n", i + 1, daftarMapel[i].nama, daftarMapel[i].nilai, daftarMapel[i].kkm, status);
    }

    printf("--------------------------------------------------------------\n");
    printf("Rata-rata : %.2f\nPredikat  : %c\n", rataRata, predikat);
}

void simpanFile(Mapel mapel[], char nama[], char kelas[], char nisn[], char sekolah[], float rata, char predikat) {
    char namaFile[100]; 
    
    sprintf(namaFile, "Raport_%s.txt", nisn);

    FILE *fp = fopen(namaFile, "w");

    if(fp == NULL) {
        printf("Gagal membuat file!\n");
        return; 
    }

    fprintf(fp, "======================= RAPORT SISWA =======================\n");
    fprintf(fp, "Nama    : %-30s\n", nama);
    fprintf(fp, "Kelas   : %-20s\n", kelas);
    fprintf(fp, "NISN    : %-20s\n", nisn);
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

        fprintf(fp, "| %-3d | %-20s | %-6d | %-4d | %-12s |\n",
                i + 1, mapel[i].nama, mapel[i].nilai, mapel[i].kkm, status);
    }

    fprintf(fp, "============================================================\n");
    fprintf(fp, "Rata-rata : %-10.2f\n", rata);
    fprintf(fp, "Predikat  : %-5c\n", predikat);
    fprintf(fp, "============================================================\n");

    fclose(fp);
    printf("\nRaport berhasil disimpan dengan format tabel di: %s\n", namaFile);
}
