// Preprocessor directive untuk menyertakan library standard input/output
// Library ini menyediakan fungsi dasar seperti printf, scanf, fopen, fprintf, fclose, dll
#include <stdio.h>

// Preprocessor directive untuk menyertakan library standard library
// Digunakan untuk fungsi sistem seperti system("cls") untuk membersihkan layar
#include <stdlib.h>

// Preprocessor directive untuk menyertakan library string manipulation
// Digunakan untuk fungsi strcpy (copy teks) dalam menentukan status kelulusan
#include <string.h>

// Preprocessor directive #define untuk mendefinisikan konstanta simbolik
// MAX_MAPEL adalah macro yang menentukan jumlah mata pelajaran dalam array
// Keuntungan: Memudahkan perubahan jumlah mapel di seluruh kode hanya dengan mengubah nilai ini
#define MAX_MAPEL 5

// Deklarasi struktur data menggunakan typedef untuk membuat alias tipe data 'Mapel'
// Struktur ini mendefinisikan blueprint untuk menyimpan data penilaian setiap mata pelajaran
typedef struct {
    char nama[30];    // Member struct: array karakter untuk nama mata pelajaran (kapasitas 30 byte)
    int kkm;          // Member struct: menyimpan nilai KKM (Kriteria Ketuntasan Minimal) dalam integer
    int nilai;        // Member struct: menyimpan nilai asli yang didapat siswa
} Mapel; // Alias 'Mapel' memungkinkan deklarasi tanpa kata kunci "struct" lagi

// Forward declaration (prototipe fungsi) agar fungsi bisa dikenali oleh compiler sebelum didefinisikan
void tampilMapel(Mapel mapel[]);
void inputNilai(Mapel mapel[]);
float hitungRata(Mapel mapel[]);
char tentukanPredikat(float rata);
void tampilRapot(Mapel mapel[], char nama[], char kelas[], char nis[], char sekolah[], float rata, char predikat);
void simpanFile(Mapel mapel[], char nama[], char kelas[], char nis[], char sekolah[], float rata, char predikat);

// Fungsi main: Entry point atau titik masuk utama eksekusi program
// Return type int mengembalikan status kode ke Operating System (0 = sukses)
int main() {
    // Deklarasi dan inisialisasi array of struct Mapel dengan jumlah elemen MAX_MAPEL
    // Menggunakan aggregate initialization untuk mengisi data awal (Nama Mapel & KKM)
    // Field 'nilai' diinisialisasi 0 sebagai nilai default
    Mapel mapel[MAX_MAPEL] = {
        {"Agama", 78, 0},
        {"Bahasa Indonesia", 78, 0},
        {"Bahasa Inggris", 78, 0},
        {"Pancasila", 78, 0},
        {"Matematika", 78, 0}
    };

    // Deklarasi array karakter (string) untuk menyimpan identitas siswa
    // Dialokasikan di stack memory dengan ukuran tertentu
    char nama[50], kelas[20], nis[20], sekolah[50];
    char ulang; // Variabel karakter untuk mengontrol perulangan program

    // Memanggil command system untuk membersihkan tampilan console/terminal
    system("cls");

    // Memanggil fungsi untuk menampilkan daftar KKM awal ke layar
    tampilMapel(mapel);

    // Proses input identitas menggunakan formatted input scanf
    printf("\n========= INPUT IDENTITAS SISWA =========\n");
    // Format specifier %[^\n] digunakan agar scanf membaca seluruh baris termasuk spasi hingga bertemu Enter
    printf("Nama         : "); scanf(" %[^\n]", nama);
    printf("Kelas        : "); scanf(" %[^\n]", kelas);
    printf("NIS          : "); scanf(" %[^\n]", nis);
    printf("Nama Sekolah : "); scanf(" %[^\n]", sekolah);

    // Struktur kontrol perulangan do-while (pasti dieksekusi minimal 1 kali)
    do {
        // Memanggil prosedur untuk mengisi nilai setiap mata pelajaran
        inputNilai(mapel);

        // Memanggil fungsi hitungRata yang mengembalikan tipe float (bilangan desimal)
        float rata = hitungRata(mapel);

        // Memanggil fungsi tentukanPredikat yang mengembalikan tipe char (karakter A-D)
        char predikat = tentukanPredikat(rata);

        // Menampilkan output rapot ke layar console
        tampilRapot(mapel, nama, kelas, nis, sekolah, rata, predikat);

        // Meminta input user untuk menentukan apakah loop akan berlanjut
        printf("\nIngin input ulang nilai? (Y/T): ");
        // %c membaca satu karakter, spasi sebelum %c untuk mengabaikan karakter newline (\n) di buffer
        scanf(" %c", &ulang);

        // Percabangan if untuk mengecek kondisi keluar
        // Operator || (logical OR) mengecek jika user menginput 'T' besar atau 't' kecil
        if(ulang == 'T' || ulang == 't') {
            // Memanggil fungsi File I/O untuk menyimpan hasil rapot ke dalam file .txt
            simpanFile(mapel, nama, kelas, nis, sekolah, rata, predikat);
        }

    } while(ulang == 'Y' || ulang == 'y'); // Loop berulang jika kondisi true

    printf("\nProgram selesai.\n");
    return 0; // Mengindikasikan program berakhir dengan normal
}

/**
 * Prosedur untuk menampilkan tabel mata pelajaran dan KKM
 * @param mapel Array of struct (Pass by reference secara implisit)
 */
void tampilMapel(Mapel mapel[]) {
    printf("========= DAFTAR MATA PELAJARAN =========\n");
    printf("==========================================\n");
    // %-20s : string dengan lebar 20 karakter, rata kiri (left-aligned)
    printf("| %-3s | %-20s | %-4s |\n", "No", "Mata Pelajaran", "KKM");
    printf("==========================================\n");

    // Loop for untuk iterasi array berdasarkan index i
    for(int i = 0; i < MAX_MAPEL; i++) {
        // Operator [] (subscript) untuk akses elemen, dan . (dot) untuk akses member struct
        printf("| %-3d | %-20s | %-4d |\n", i+1, mapel[i].nama, mapel[i].kkm);
    }
    printf("==========================================\n");
}

/**
 * Prosedur untuk input nilai dengan validasi ganda
 */
void inputNilai(Mapel mapel[]) {
    printf("\n========= INPUT NILAI =========\n");
    for(int i = 0; i < MAX_MAPEL; i++) {
        int valid;
        // Nested loop do-while untuk memvalidasi input per mata pelajaran
        do {
            printf("Nilai %s (0-100): ", mapel[i].nama);
            // scanf mengembalikan nilai int yang menunjukkan jumlah input sukses
            valid = scanf("%d", &mapel[i].nilai);

            // Validasi: Cek apakah input bukan angka (tipe data salah)
            if(valid != 1) {
                printf("Input harus berupa ANGKA!\n");
                // Membersihkan buffer stdin menggunakan getchar() hingga bertemu newline
                while(getchar() != '\n');
                continue; // Melompat ke iterasi loop berikutnya
            }

            // Validasi: Cek rentang nilai menggunakan operator logical OR (||)
            if(mapel[i].nilai < 0 || mapel[i].nilai > 100) {
                printf("Nilai harus antara 0 - 100!\n");
            }

        } while(valid != 1 || mapel[i].nilai < 0 || mapel[i].nilai > 100);
    }
}

/**
 * Fungsi untuk menghitung nilai rata-rata
 * @return Nilai rata-rata dalam tipe float (bilangan berkoma)
 */
float hitungRata(Mapel mapel[]) {
    float total = 0; // Inisialisasi akumulator nilai
    for(int i = 0; i < MAX_MAPEL; i++) {
        // Operator += menambahkan nilai mapel ke variabel total
        total += mapel[i].nilai;
    }
    // Operator / (division) membagi total dengan jumlah mapel
    return total / MAX_MAPEL;
}

/**
 * Fungsi untuk menentukan grade predikat
 * @param rata Nilai rata-rata siswa
 * @return Karakter A, B, C, atau D
 */
char tentukanPredikat(float rata) {
    // Struktur if-else-if untuk menentukan range nilai (Logika Grading)
    if(rata >= 90) return 'A';
    else if(rata >= 80) return 'B';
    else if(rata >= 70) return 'C';
    else return 'D';
}

/**
 * Prosedur untuk menampilkan output rapot ke layar (UI)
 */
void tampilRapot(Mapel mapel[], char nama[], char kelas[], char nis[], char sekolah[], float rata, char predikat) {
    printf("\n======================= RAPORT SISWA =======================\n");
    printf("Nama    : %s\n", nama);
    printf("Kelas   : %s\n", kelas);
    printf("NIS     : %s\n", nis);
    printf("Sekolah : %s\n", sekolah);
    printf("============================================================\n");
    printf("| %-3s | %-20s | %-6s | %-4s | %-12s |\n", "No", "Mata Pelajaran", "Nilai", "KKM", "Status");
    printf("============================================================\n");

    for(int i = 0; i < MAX_MAPEL; i++) {
        char status[15]; // String lokal untuk menyimpan status kelulusan

        // Logika kelulusan: Membandingkan nilai dengan KKM menggunakan operator >=
        if(mapel[i].nilai >= mapel[i].kkm)
            strcpy(status, "Lulus"); // Fungsi string copy untuk mengisi array status
        else
            strcpy(status, "Tidak Lulus");

        printf("| %-3d | %-20s | %-6d | %-4d | %-12s |\n", i+1, mapel[i].nama, mapel[i].nilai, mapel[i].kkm, status);
    }

    printf("============================================================\n");
    // %.2f membatasi tampilan float hanya 2 angka di belakang koma (presisi)
    printf("Rata-rata : %.2f\n", rata);
    printf("Predikat  : %c\n", predikat);
    printf("============================================================\n");
}

/**
 * Prosedur untuk menyimpan data rapot ke file fisik .txt
 * Menjelaskan mekanisme File I/O dalam bahasa C
 */
void simpanFile(Mapel mapel[], char nama[], char kelas[], char nis[], char sekolah[], float rata, char predikat) {
    char namaFile[100];
    // Fungsi sprintf (string print formatted) untuk membuat nama file dinamis berdasarkan NIS siswa
    // Contoh: Jika NIS 101, maka nama file menjadi "Raport_101.txt"
    sprintf(namaFile, "Raport_%s.txt", nis);

    // Fungsi fopen membuka file. Mode "w" (write) akan membuat file baru atau menimpa jika sudah ada
    // Pointer *fp (File Pointer) digunakan sebagai handle akses file
    FILE *fp = fopen(namaFile, "w");

    // Error handling: Cek apakah pointer NULL (gagal akses folder/disk)
    if(fp == NULL) return;

    // Fungsi fprintf menulis data ke file stream (fp) bukan ke layar (stdout)
    // Parameter pertama adalah pointer ke file yang dituju
    fprintf(fp, "======================= RAPORT SISWA =======================\n");
    fprintf(fp, "Nama    : %s\n", nama);
    fprintf(fp, "Kelas   : %s\n", kelas);
    fprintf(fp, "NIS     : %s\n", nis);
    fprintf(fp, "Sekolah : %s\n", sekolah);
    fprintf(fp, "============================================================\n\n");

    fprintf(fp, "| %-3s | %-20s | %-6s | %-4s | %-12s |\n", "No", "Mata Pelajaran", "Nilai", "KKM", "Status");
    fprintf(fp, "------------------------------------------------------------\n");

    for(int i = 0; i < MAX_MAPEL; i++) {
        char status[15];
        if(mapel[i].nilai >= mapel[i].kkm) strcpy(status, "Lulus");
        else strcpy(status, "Tidak Lulus");

        fprintf(fp, "| %-3d | %-20s | %-6d | %-4d | %-12s |\n", i+1, mapel[i].nama, mapel[i].nilai, mapel[i].kkm, status);
    }

    fprintf(fp, "------------------------------------------------------------\n");
    fprintf(fp, "Rata-rata : %.2f\n", rata);
    fprintf(fp, "Predikat  : %c\n", predikat);
    fprintf(fp, "============================================================\n");

    // Fungsi fclose sangat penting untuk menutup aliran data dan memastikan data benar-benar tersimpan ke disk
    fclose(fp);
    printf("\n[SUCCESS] Raport tersimpan: %s\n", namaFile);
}
