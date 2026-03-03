// ====================== PREPROCESSOR DIRECTIVE ======================

// Preprocessor directive untuk menyertakan library standard input/output
// Digunakan untuk fungsi dasar seperti printf, scanf, fopen, fprintf, dan fclose
#include <stdio.h>

// Preprocessor directive untuk menyertakan library string manipulation
// Digunakan untuk fungsi pengolahan teks seperti strcpy (menyalin) dan sprintf (format string)
#include <string.h>

// ====================== KONSTANTA ======================

// Mendefinisikan konstanta MAX_MAPEL dengan nilai 5 menggunakan preprocessor #define
// Digunakan sebagai acuan jumlah elemen array mata pelajaran di seluruh program
#define MAX_MAPEL 5

// ====================== STRUKTUR DATA ======================

// Definisi struktur data 'Nilai' menggunakan typedef untuk menyimpan atribut tiap mata pelajaran
typedef struct {
    char napel[30];  // Member struct: array karakter untuk menyimpan nama mata pelajaran
    int kkm;         // Member struct: menyimpan nilai standar kelulusan (KKM)
    int nilai;       // Member struct: menyimpan nilai yang diinput oleh pengguna
    char status[30]; // Member struct: menyimpan teks status "LULUS" atau "TIDAK LULUS"
} Nilai;

// Definisi struktur data 'Siswa' untuk menyimpan profil identitas lengkap siswa
typedef struct {
    char nama[30];    // Member struct: menyimpan nama lengkap siswa
    char nisn[15];    // Member struct: menyimpan Nomor Induk Siswa Nasional
    char kelas[15];   // Member struct: menyimpan tingkat dan nama kelas
    char sekolah[30]; // Member struct: menyimpan nama instansi sekolah
} Siswa;

// ====================== VARIABEL GLOBAL ======================

// Deklarasi variabel 'siswa' dengan tipe struct Siswa secara global agar dapat diakses semua fungsi
Siswa siswa;

// Inisialisasi array of struct 'daftar_nilai' sebanyak 5 elemen (MAX_MAPEL)
// Berisi data awal nama mata pelajaran dan nilai KKM masing-masing
Nilai daftar_nilai[MAX_MAPEL] = {
    {"Pemrograman Web", 76, 0},    // Index 0: Mapel Web, KKM 76
    {"Pemrograman Mobile", 76, 0}, // Index 1: Mapel Mobile, KKM 76
    {"Basis Data", 76, 0},         // Index 2: Mapel Basis Data, KKM 76
    {"PBO", 76, 0},                // Index 3: Mapel PBO, KKM 76
    {"Kewirausahaan", 79, 0}       // Index 4: Mapel Kewirausahaan, KKM 79
};

// Deklarasi variabel global untuk keperluan logika dan kalkulasi program
char pilihan;               // Variabel untuk menampung input pilihan (Y/N)
char predikat;              // Variabel untuk menampung hasil nilai huruf (A, B, C, D)
float rata_rata;            // Variabel desimal untuk hasil pembagian rata-rata
float total_nilai;          // Variabel desimal untuk akumulasi penjumlahan nilai
char nama_file[40];         // Variabel array karakter untuk nama file output (.txt)

// ====================== IMPLEMENTASI FUNGSI ======================

// Fungsi untuk menampilkan tabel informasi daftar mata pelajaran dan KKM di awal program
void tampilkanDaftarKKM() {
    printf("================================================\n");
    printf("      DAFTAR MATA PELAJARAN DAN KKM\n");
    printf("================================================\n");
    // Mencetak header tabel dengan format lebar karakter yang ditentukan
    printf("%-4s %-23s %-10s\n", "No.", "Mata Pelajaran", "KKM");
    printf("------------------------------------------------\n");

    // Perulangan for untuk mencetak data tiap mapel dari array global
    for (int i = 0; i < MAX_MAPEL; i++) {
        printf("%-4d %-23s %-10d\n", i + 1, daftar_nilai[i].napel, daftar_nilai[i].kkm);
    }
    printf("================================================\n");
}

// Fungsi untuk mengambil input identitas diri siswa dari pengguna
void inputIdentitasSiswa() {
    printf("\n=== INPUT IDENTITAS SISWA ===\n");
    // Menggunakan format specifier %[^\n] agar scanf dapat membaca string yang mengandung spasi
    printf("Nama Siswa     : "); scanf(" %[^\n]", siswa.nama);
    printf("NISN           : "); scanf(" %[^\n]", siswa.nisn);
    printf("Kelas          : "); scanf(" %[^\n]", siswa.kelas);
    printf("Nama Sekolah   : "); scanf(" %[^\n]", siswa.sekolah);
}

// Fungsi inti untuk memproses input nilai siswa, melakukan validasi, dan kalkulasi rata-rata
void prosesKalkulasiNilai() {
    total_nilai = 0; // Mereset nilai total menjadi nol setiap kali fungsi dipanggil
    printf("\n=== INPUT NILAI MATA PELAJARAN ===\n");

    for (int i = 0; i < MAX_MAPEL; i++) {
        int input_valid = 0; // Variabel flag sebagai penanda validitas input

        // Loop while untuk menjamin input yang masuk harus benar-benar valid
        while (!input_valid) {
            printf("Nilai %-23s : ", daftar_nilai[i].napel);

            // Validasi 1: Mengecek apakah input yang dimasukkan adalah tipe data angka (integer)
            if (scanf("%d", &daftar_nilai[i].nilai) != 1) {
                printf("Input harus berupa ANGKA!\n");
                // Membersihkan buffer input jika user salah memasukkan karakter huruf/simbol
                while (getchar() != '\n');
            }
            // Validasi 2: Mengecek apakah angka berada pada rentang nilai raport yang logis (0-100)
            else if (daftar_nilai[i].nilai < 0 || daftar_nilai[i].nilai > 100) {
                printf("Nilai harus antara 0 - 100!\n");
            }
            else {
                input_valid = 1; // Jika lolos semua validasi, set flag menjadi 1 untuk keluar loop
            }
        }

        // Akumulasi nilai yang valid ke dalam variabel total_nilai
        total_nilai += daftar_nilai[i].nilai;

        // Logika penentuan status kelulusan berdasarkan perbandingan Nilai dengan KKM tiap mapel
        if (daftar_nilai[i].nilai >= daftar_nilai[i].kkm) {
            strcpy(daftar_nilai[i].status, "LULUS"); // Menyalin string "LULUS" ke member status
        } else {
            strcpy(daftar_nilai[i].status, "TIDAK LULUS"); // Menyalin string "TIDAK LULUS"
        }
    }

    // Menghitung nilai rata-rata dengan membagi total nilai terhadap jumlah mata pelajaran
    rata_rata = total_nilai / MAX_MAPEL;

    // Struktur kontrol if-else-if untuk menentukan predikat berdasarkan rentang nilai rata-rata
    if (rata_rata >= 86) predikat = 'A';      // Predikat A untuk rata-rata 86 - 100
    else if (rata_rata >= 80) predikat = 'B'; // Predikat B untuk rata-rata 80 - 85
    else if (rata_rata >= 76) predikat = 'C'; // Predikat C untuk rata-rata 76 - 79
    else predikat = 'D';                      // Predikat D untuk rata-rata di bawah 76
}

// Fungsi modular untuk mencetak output raport baik ke layar (stdout) maupun ke file teks
void cetakStrukturRapor(FILE *output) {
    // Menggunakan fprintf dengan pointer 'output' agar fungsi ini bersifat fleksibel
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
        // Mencetak baris tabel berisi detail per mata pelajaran
        fprintf(output, "%-4d %-23s %-5d %-7d %s\n",
                i + 1, daftar_nilai[i].napel, daftar_nilai[i].kkm,
                daftar_nilai[i].nilai, daftar_nilai[i].status);
    }

    fprintf(output, "=======================================================\n");
    // Mencetak ringkasan hasil akhir rata-rata dan predikat
    fprintf(output, "Rata-rata Nilai : %0.2f\n", rata_rata);
    fprintf(output, "Predikat         : %c\n", predikat);
    fprintf(output, "=======================================================\n");
}

// Fungsi untuk melakukan prosedur penyimpanan data rapor ke dalam file permanen (.txt)
void simpanKeFile() {
    // Membuat nama file secara dinamis menggunakan NISN siswa agar unik (Contoh: Rapor_12345.txt)
    sprintf(nama_file, "Rapor_%s.txt", siswa.nisn);

    // Membuka koneksi file dengan mode "w" (write/menulis ulang)
    FILE *file_ptr = fopen(nama_file, "w");

    // Mengecek apakah sistem berhasil membuat/mengakses file tersebut
    if (file_ptr != NULL) {
        // Memanggil fungsi cetak dengan argumen pointer file_ptr (menulis ke file)
        cetakStrukturRapor(file_ptr);
        // Menutup koneksi file untuk memastikan data tersimpan dengan aman di penyimpanan
        fclose(file_ptr);
        printf("\nBerhasil! Data disimpan dalam: %s\n", nama_file);
    }
}

// ====================== FUNGSI UTAMA ======================
// Titik awal eksekusi program C
int main() {
    tampilkanDaftarKKM();  // Memanggil fungsi untuk menampilkan daftar KKM
    inputIdentitasSiswa(); // Memanggil fungsi untuk menginput profil siswa

    // Loop do-while untuk menangani alur proses input nilai yang dapat diulang
    do {
        prosesKalkulasiNilai();     // Melakukan input nilai, validasi, dan hitung
        cetakStrukturRapor(stdout); // Menampilkan pratinjau hasil di layar (stdout)

        // Loop while(1) untuk memastikan interaksi konfirmasi user (Y/N) benar
        while (1) {
            printf("\nApakah data sudah benar?\n");
            printf("Tekan Y untuk cetak rapor\n");
            printf("Tekan N untuk input ulang nilai\n");
            printf("Pilihan Anda: ");
            scanf(" %c", &pilihan);

            // Jika user memilih 'Y' atau 'y' (Setuju), jalankan prosedur simpan dan keluar
            if (pilihan == 'Y' || pilihan == 'y') {
                simpanKeFile();
                return 0; // Keluar dari program dengan kode sukses (0)
            }

            // Jika user memilih 'N' atau 'n' (Ulang), keluar dari loop internal menuju loop do-while
            if (pilihan == 'N' || pilihan == 'n') {
                break;
            }

            // Pesan peringatan jika user memasukkan karakter selain Y atau N
            printf("Input tidak valid. Gunakan Y atau N.\n");
            // Membersihkan sisa input di buffer sistem
            while (getchar() != '\n');
        }

    // Kondisi: Program akan mengulang proses input nilai jika variabel pilihan adalah 'N'
    } while (pilihan == 'N' || pilihan == 'n');

    return 0; // Selesai
}
