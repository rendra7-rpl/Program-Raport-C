// ====================== PREPROCESSOR DIRECTIVE ======================

// Preprocessor directive untuk menyertakan library standard input/output
// Library ini menyediakan fungsi dasar seperti printf, scanf, fopen, fprintf, dan fclose
#include <stdio.h>

// Preprocessor directive untuk menyertakan library standard library
// Library ini digunakan untuk fungsi umum seperti system("pause"), exit(), dan manajemen memori
#include <stdlib.h>

// Preprocessor directive untuk menyertakan library string manipulation
// Library ini menyediakan fungsi untuk mengolah teks seperti strcpy (menyalin string)
#include <string.h>

// ====================== KONSTANTA ======================

// Preprocessor directive #define untuk mendefinisikan konstanta simbolik MAX_MAPEL
// Macro ini akan mengganti semua kata MAX_MAPEL menjadi nilai 5 saat proses kompilasi
// Memudahkan pemeliharaan kode jika ingin menambah atau mengurangi jumlah mata pelajaran
#define MAX_MAPEL 5

// ====================== STRUKTUR DATA ======================

// Deklarasi struktur data menggunakan typedef untuk membuat alias tipe data
// Struktur ini mendefinisikan blueprint (kerangka) untuk menyimpan data tiap mata pelajaran
typedef struct {
    char nama[30];   // Member struct: array karakter untuk nama mapel (maksimal 29 karakter + null terminator)
    int kkm;         // Member struct: menyimpan nilai standar kelulusan (KKM) dalam integer
    int nilai;       // Member struct: menyimpan nilai aktual yang didapat siswa
} Mapel; // Alias "Mapel" digunakan agar tidak perlu menulis "struct Mapel" setiap saat

// ====================== PROTOTYPE FUNCTION ======================
// Forward declaration fungsi-fungsi agar bisa dikenali oleh fungsi main() sebelum didefinisikan

// Deklarasi fungsi void untuk menampilkan tabel daftar mata pelajaran dan KKM
void tampilMapel(Mapel mapel[]);

// Deklarasi fungsi void untuk proses input nilai dengan validasi rentang 0-100
void inputNilai(Mapel mapel[]);

// Deklarasi fungsi float untuk menghitung rata-rata nilai (mengembalikan nilai desimal)
float hitungRata(Mapel mapel[]);

// Deklarasi fungsi char untuk menentukan predikat (A, B, C, D) berdasarkan rata-rata
char tentukanPredikat(float rata);

// Deklarasi fungsi void untuk menampilkan hasil rapot lengkap ke layar terminal
void tampilRapot(Mapel mapel[], char nama[], char kelas[], char nis[], char sekolah[], float rata, char predikat);

// Deklarasi fungsi void untuk menyimpan data rapot ke dalam file eksternal (.txt)
void simpanFile(Mapel mapel[], char nama[], char kelas[], char nis[], char sekolah[], float rata, char predikat);

// ====================== FUNGSI UTAMA ======================
// Entry point utama program di mana eksekusi kode dimulai
int main() {

    // ====================== INISIALISASI DATA ======================

    // Deklarasi dan inisialisasi array of struct Mapel dengan 5 elemen awal
    // Menggunakan aggregate initialization untuk mengisi nama dan KKM standar
    Mapel mapel[MAX_MAPEL] = {
        {"Agama", 78, 0},            // Index 0: Mapel Agama, KKM 78, nilai awal 0
        {"Bahasa Indonesia", 78, 0}, // Index 1: Mapel B.Indo, KKM 78
        {"Bahasa Inggris", 78, 0},   // Index 2: Mapel B.Inggris, KKM 78
        {"Pancasila", 78, 0},        // Index 3: Mapel Pancasila, KKM 78
        {"Matematika", 78, 0}        // Index 4: Mapel Matematika, KKM 78
    };

    // Deklarasi array karakter (string) untuk menyimpan identitas siswa
    char nama[50], kelas[20], nis[20], sekolah[50];

    // Deklarasi variabel karakter untuk menampung pilihan perulangan (Y/T)
    char ulang;

    // ====================== TAMPIL MAPEL ======================

    // Memanggil fungsi tampilMapel untuk memperlihatkan daftar pelajaran di awal program
    tampilMapel(mapel);

    // ====================== INPUT IDENTITAS ======================

    // Mencetak header untuk bagian input identitas
    printf("\n========= INPUT IDENTITAS SISWA =========\n");

    // Membaca input Nama menggunakan format specifier %[^\n] agar bisa menerima spasi
    printf("Nama         : ");
    scanf(" %[^\n]", nama);

    // Membaca input Kelas
    printf("Kelas        : ");
    scanf(" %[^\n]", kelas);

    // Membaca input NIS (Nomor Induk Siswa)
    printf("NIS          : ");
    scanf(" %[^\n]", nis);

    // Membaca input Nama Sekolah
    printf("Nama Sekolah : ");
    scanf(" %[^\n]", sekolah);

    // ====================== PERULANGAN INPUT NILAI ======================

    // Loop do-while: blok kode ini akan dijalankan minimal satu kali
    // Loop akan berulang selama user menginput 'Y' atau 'y' di akhir proses
    do {
        // Memanggil fungsi inputNilai untuk mengisi data nilai siswa ke dalam array struct
        inputNilai(mapel);

        // Memanggil fungsi hitungRata dan menyimpan hasilnya ke variabel rata (tipe float)
        float rata = hitungRata(mapel);

        // Memanggil fungsi tentukanPredikat berdasarkan rata-rata yang sudah dihitung
        char predikat = tentukanPredikat(rata);

        // Memanggil fungsi tampilRapot untuk menyajikan data identitas dan nilai secara rapi
        tampilRapot(mapel, nama, kelas, nis, sekolah, rata, predikat);

        // Meminta input dari user apakah ingin melakukan input nilai ulang
        printf("\nIngin input ulang nilai? (Y/T): ");
        scanf(" %c", &ulang); // Spasi sebelum %c digunakan untuk mengabaikan karakter newline (\n)

        // Struktur kontrol if untuk mengecek jika user memilih 'T' atau 't' (Tidak)
        if(ulang == 'T' || ulang == 't') {
            // Memanggil fungsi simpanFile untuk menyimpan hasil akhir ke file teks
            simpanFile(mapel, nama, kelas, nis, sekolah, rata, predikat);
        }

    // Kondisi perulangan: kembali ke 'do' jika variabel ulang bernilai 'Y' atau 'y'
    } while(ulang == 'Y' || ulang == 'y');

    // Mencetak pesan akhir saat program selesai
    printf("\nProgram selesai.\n");

    // Mengembalikan nilai 0 ke sistem operasi sebagai tanda program berakhir normal
    return 0;
}

// ====================== IMPLEMENTASI FUNGSI ======================

// Fungsi untuk menampilkan daftar mata pelajaran dalam bentuk tabel
void tampilMapel(Mapel mapel[]) {
    printf("========= DAFTAR MATA PELAJARAN =========\n");
    printf("==========================================\n");
    // %-20s : string dengan lebar 20 karakter, rata kiri (left-aligned)
    printf("| %-3s | %-20s | %-4s |\n", "No", "Mata Pelajaran", "KKM");
    printf("==========================================\n");

    // Loop for untuk mencetak tiap elemen array mapel
    for(int i = 0; i < MAX_MAPEL; i++) {
        // Menggunakan i+1 untuk nomor urut manusia (mulai dari 1)
        printf("| %-3d | %-20s | %-4d |\n", i+1, mapel[i].nama, mapel[i].kkm);
    }
    printf("==========================================\n");
}

// Fungsi untuk menginput nilai dengan validasi angka 0 hingga 100
void inputNilai(Mapel mapel[]) {
    printf("\n========= INPUT NILAI =========\n");

    for(int i = 0; i < MAX_MAPEL; i++) {

        int valid; // untuk cek keberhasilan scanf

        do {
            printf("Nilai %s (0-100): ", mapel[i].nama);

            // scanf akan mengembalikan jumlah data yang berhasil dibaca
            valid = scanf("%d", &mapel[i].nilai);

            // Jika bukan angka
            if(valid != 1) {
                printf("Input harus berupa ANGKA!\n");

                // Membersihkan buffer sampai newline
                while(getchar() != '\n');

                continue;
            }

            // Jika angka tapi di luar range
            if(mapel[i].nilai < 0 || mapel[i].nilai > 100) {
                printf("Nilai harus antara 0 - 100!\n");
            }

        } while(valid != 1 || mapel[i].nilai < 0 || mapel[i].nilai > 100);
    }
}

// Fungsi untuk menghitung nilai rata-rata dari seluruh mata pelajaran
float hitungRata(Mapel mapel[]) {
    float total = 0; // Inisialisasi variabel akumulator total nilai
    for(int i = 0; i < MAX_MAPEL; i++) {
        // Operator += menjumlahkan nilai tiap mapel ke variabel total
        total += mapel[i].nilai;
    }
    // Mengembalikan hasil pembagian total nilai dengan jumlah mapel (rata-rata)
    return total / MAX_MAPEL;
}

// Fungsi untuk menentukan huruf predikat berdasarkan angka rata-rata
char tentukanPredikat(float rata) {
    // Struktur percabangan if-else-if untuk pengkategorian predikat
    if(rata >= 90) return 'A';      // Jika 90 ke atas mendapat A
    else if(rata >= 80) return 'B'; // Jika 80 - 89 mendapat B
    else if(rata >= 70) return 'C'; // Jika 70 - 79 mendapat C
    else return 'D';                // Di bawah 70 mendapat D
}

// Fungsi untuk menampilkan rapot siswa ke layar (Output Terminal)
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
        char status[15]; // Variabel lokal untuk menyimpan teks status lulus/tidak

        // Perbandingan antara nilai siswa dengan KKM mapel
        if(mapel[i].nilai >= mapel[i].kkm)
            strcpy(status, "Lulus"); // Fungsi strcpy untuk menyalin teks "Lulus" ke variabel status
        else
            strcpy(status, "Tidak Lulus");

        // Mencetak baris detail nilai tiap mata pelajaran
        printf("| %-3d | %-20s | %-6d | %-4d | %-12s |\n", i+1, mapel[i].nama, mapel[i].nilai, mapel[i].kkm, status);
    }

    printf("==============================================================\n");
    // %.2f membatasi tampilan nilai desimal hanya 2 angka di belakang koma
    printf("Rata-rata : %.2f\n", rata);
    printf("Predikat  : %c\n", predikat);
}

// Fungsi untuk mengekspor data rapot ke dalam file teks secara permanen
void simpanFile(Mapel mapel[], char nama[], char kelas[], char nis[], char sekolah[], float rata, char predikat) {
    char namaFile[100]; // Array karakter untuk menampung nama file yang akan dibuat

    // sprintf: memformat string dan menyimpannya ke variabel namaFile
    // Nama file akan dinamis mengikuti NIS siswa, contoh: Raport_12345.txt
    sprintf(namaFile, "Raport_%s.txt", nis);

    // fopen: membuka file dengan mode "w" (write/tulis)
    // Jika file belum ada, sistem akan membuatnya. Jika sudah ada, isinya akan ditimpa.
    FILE *fp = fopen(namaFile, "w");

    // Pengecekan apakah file berhasil dibuka (pointer fp tidak bernilai NULL)
    if(fp == NULL) {
        printf("Gagal membuat file!\n");
        return; // Menghentikan fungsi jika terjadi error pada file
    }

    // fprintf: menulis data ke dalam file (formatnya mirip dengan printf)
    fprintf(fp, "======================= RAPORT SISWA =======================\n");
    fprintf(fp, "Nama    : %-30s\n", nama);
    fprintf(fp, "Kelas   : %-20s\n", kelas);
    fprintf(fp, "NIS     : %-20s\n", nis);
    fprintf(fp, "Sekolah : %-30s\n", sekolah);
    fprintf(fp, "============================================================\n\n");

    // Menulis Header Tabel ke File
    fprintf(fp, "============================================================\n");
    fprintf(fp, "| %-3s | %-20s | %-6s | %-4s | %-12s |\n", "No", "Mata Pelajaran", "Nilai", "KKM", "Status");
    fprintf(fp, "============================================================\n");

    // Menulis Isi Tabel (Looping Data Mapel)
    for(int i = 0; i < MAX_MAPEL; i++) {
        char status[15];
        if(mapel[i].nilai >= mapel[i].kkm)
            strcpy(status, "Lulus");
        else
            strcpy(status, "Tidak Lulus");

        // Menggunakan format yang sama dengan tampilRapot agar simetris
        fprintf(fp, "| %-3d | %-20s | %-6d | %-4d | %-12s |\n",
                i + 1, mapel[i].nama, mapel[i].nilai, mapel[i].kkm, status);
    }

    // Menulis Footer Tabel dan Ringkasan
    fprintf(fp, "============================================================\n");
    fprintf(fp, "Rata-rata : %-10.2f\n", rata);
    fprintf(fp, "Predikat  : %-5c\n", predikat);
    fprintf(fp, "============================================================\n");

    fclose(fp);
    printf("\nRaport berhasil disimpan dengan format tabel di: %s\n", namaFile);

}
