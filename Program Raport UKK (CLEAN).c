#include <stdio.h>
#include <string.h>

#define MAX_MAPEL 5

typedef struct {
    char napel[30];
    int kkm;
    int nilai;
    char status[30];
} Nilai;

typedef struct {
    char nama[30];
    char nisn[15];
    char kelas[15];
    char sekolah[30];
} Siswa;

Siswa siswa;

Nilai daftar_nilai[MAX_MAPEL] = {
    {"Pemrograman Web", 76, 0},
    {"Pemrograman Mobile", 76, 0},
    {"Basis Data", 76, 0},
    {"PBO", 76, 0},
    {"Kewirausahaan", 79, 0}
};

char pilihan;
char predikat;
float rata_rata;
float total_nilai;
char nama_file[40];

void tampilkanDaftarKKM() {
    printf("================================================\n");
    printf("      DAFTAR MATA PELAJARAN DAN KKM\n");
    printf("================================================\n");
    printf("%-4s %-23s %-10s\n", "No.", "Mata Pelajaran", "KKM");
    printf("------------------------------------------------\n");

    for (int i = 0; i < MAX_MAPEL; i++) {
        printf("%-4d %-23s %-10d\n", i + 1, daftar_nilai[i].napel, daftar_nilai[i].kkm);
    }
    printf("================================================\n");
}

void inputIdentitasSiswa() {
    printf("\n=== INPUT IDENTITAS SISWA ===\n");
    printf("Nama Siswa     : ");
    scanf(" %[^\n]", siswa.nama);
    printf("NISN           : ");
    scanf(" %[^\n]", siswa.nisn);
    printf("Kelas          : ");
    scanf(" %[^\n]", siswa.kelas);
    printf("Nama Sekolah   : ");
    scanf(" %[^\n]", siswa.sekolah);
}

void prosesKalkulasiNilai() {
    total_nilai = 0;
    printf("\n=== INPUT NILAI MATA PELAJARAN ===\n");

    for (int i = 0; i < MAX_MAPEL; i++) {
        int input_valid = 0;

        while (!input_valid) {
            printf("Nilai %-23s : ", daftar_nilai[i].napel);

            if (scanf("%d", &daftar_nilai[i].nilai) != 1) {
                printf("Input harus berupa ANGKA!\n");
                while (getchar() != '\n');
            }
            else if (daftar_nilai[i].nilai < 0 || daftar_nilai[i].nilai > 100) {
                printf("Nilai harus antara 0 - 100!\n");
            }
            else {
                input_valid = 1;
            }
        }

        total_nilai += daftar_nilai[i].nilai;

        if (daftar_nilai[i].nilai >= daftar_nilai[i].kkm) {
            strcpy(daftar_nilai[i].status, "LULUS");
        } else {
            strcpy(daftar_nilai[i].status, "TIDAK LULUS");
        }
    }

    rata_rata = total_nilai / MAX_MAPEL;

    if (rata_rata >= 86) predikat = 'A';
    else if (rata_rata >= 80) predikat = 'B';
    else if (rata_rata >= 76) predikat = 'C';
    else predikat = 'D';
}

void cetakStrukturRapor(FILE *output) {
    fprintf(output, "\n=======================================================\n");
    fprintf(output, "              RAPORT SMK NEGERI 1 DENPASAR              \n");
    fprintf(output, "=======================================================\n");
    fprintf(output, "Nama Siswa     : %s\n", siswa.nama);
    fprintf(output, "NISN           : %s\n", siswa.nisn);
    fprintf(output, "Kelas          : %s\n", siswa.kelas);
    fprintf(output, "Nama Sekolah   : %s\n", siswa.sekolah);
    fprintf(output, "=======================================================\n");
    fprintf(output, "%-4s %-23s %-5s %-7s %s\n", "No.", "Mata Pelajaran", "KKM", "NILAI", "STATUS");
    fprintf(output, "-------------------------------------------------------\n");

    for (int i = 0; i < MAX_MAPEL; i++) {
        fprintf(output, "%-4d %-23s %-5d %-7d %s\n",
                i + 1, daftar_nilai[i].napel, daftar_nilai[i].kkm,
                daftar_nilai[i].nilai, daftar_nilai[i].status);
    }

    fprintf(output, "=======================================================\n");
    fprintf(output, "Rata-rata Nilai : %0.2f\n", rata_rata);
    fprintf(output, "Predikat         : %c\n", predikat);
    fprintf(output, "=======================================================\n");
}

void simpanKeFile() {
    sprintf(nama_file, "Rapor_%s.txt", siswa.nisn);

    FILE *file_ptr = fopen(nama_file, "w");

    if (file_ptr != NULL) {
        cetakStrukturRapor(file_ptr);
        fclose(file_ptr);
        printf("\nBerhasil! Data disimpan dalam: %s\n", nama_file);
    }
}

int main() {
    tampilkanDaftarKKM();
    inputIdentitasSiswa();

    do {
        prosesKalkulasiNilai();
        cetakStrukturRapor(stdout);

        while (1) {
            printf("\nApakah data sudah benar?\n");
            printf("Tekan Y untuk cetak rapor\n");
            printf("Tekan N untuk input ulang nilai\n");
            printf("Pilihan Anda: ");
            scanf(" %c", &pilihan);

            if (pilihan == 'Y' || pilihan == 'y') {
                simpanKeFile();
                return 0;
            }

            if (pilihan == 'N' || pilihan == 'n') {
                break;
            }

            printf("Input tidak valid. Gunakan Y atau N.\n");
            while (getchar() != '\n');
        }

    } while (pilihan == 'N' || pilihan == 'n');

    return 0;
}
