#include <iostream>
#include <string>
using namespace std;

// Struct untuk menyimpan informasi makanan dan minuman
struct MenuItem {
    string nama;
    double harga;
    string deskripsi;
};

// Struct untuk menyimpan pesanan makanan dan minuman
struct Order {
    string namaCustomer;
    MenuItem *menuMakanan;
    MenuItem *menuMinuman;
    int jumlahMakanan;
    int jumlahMinuman;
};

// Struct untuk node dalam double linked list
struct OrderNode {
    Order order;
    OrderNode *next;
    OrderNode *prev;
};

// Fungsi untuk menambahkan pesanan ke double linked list
void tambahPesanan(OrderNode *&head, Order newOrder) {
    OrderNode *newNode = new OrderNode;
    newNode->order = newOrder;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        head = newNode;
    } else {
        OrderNode *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Fungsi untuk mencetak semua pesanan dan menghitung total harga
double printPesanan(OrderNode *head) {
    OrderNode *temp = head;
    double total = 0.0;
    while (temp != NULL) {
        cout << "Customer: " << temp->order.namaCustomer << endl;
        cout << "List Pesanan Makanan:" << endl;
        for (int i = 0; i < temp->order.jumlahMakanan; ++i) {
            cout << temp->order.menuMakanan[i].nama << " - Rp." << temp->order.menuMakanan[i].harga << endl;
            total += temp->order.menuMakanan[i].harga;
        }
        cout << "List Pesanan Minuman:" << endl;
        for (int i = 0; i < temp->order.jumlahMinuman; ++i) {
            cout << temp->order.menuMinuman[i].nama << " - Rp." << temp->order.menuMinuman[i].harga << endl;
            total += temp->order.menuMinuman[i].harga;
        }
        cout << endl;
        temp = temp->next;
    }
    return total;
}

// Fungsi untuk menghapus pesanan dari double linked list
void hapusPesanan(OrderNode *&head, string namaCustomer) {
    OrderNode *current = head;
    while (current != NULL) {
        if (current->order.namaCustomer == namaCustomer) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            delete[] current->order.menuMakanan;
            delete[] current->order.menuMinuman;
            delete current;
            return;
        }
        current = current->next;
    }
}

// Fungsi untuk mengedit pesanan dalam double linked list
void editPesanan(OrderNode *&head, string namaCustomer, MenuItem menuMakanan[], int jumlahMenuMakanan, MenuItem menuMinuman[], int jumlahMenuMinuman) {
    OrderNode *current = head;
    while (current != NULL) {
        if (current->order.namaCustomer == namaCustomer) {
            cout << "Edit pesanan untuk " << namaCustomer << endl;

            // Input pesanan baru untuk makanan
            cout << "Makanan:" << endl;
            cout << "Berapa jumlah pesanan makanan yang ingin anda ubah: ";
            cin >> current->order.jumlahMakanan;
            current->order.menuMakanan = new MenuItem[current->order.jumlahMakanan];
            cout << "Apa saja yang ingin anda pesan (masukkan nomor menu):" << endl;
            for (int i = 0; i < current->order.jumlahMakanan; ++i) {
                int menuItemIndex;
                cout << i + 1 << ". ";
                cin >> menuItemIndex;
                current->order.menuMakanan[i] = menuMakanan[menuItemIndex - 1];
            }

            // Input pesanan baru untuk minuman
            cout << "Minuman:" << endl;
            cout << "Berapa jumlah pesanan minuman yang ingin anda ubah: ";
            cin >> current->order.jumlahMinuman;
            current->order.menuMinuman = new MenuItem[current->order.jumlahMinuman];
            cout << "Apa saja yang ingin anda pesan (masukkan nomor menu):" << endl;
            for (int i = 0; i < current->order.jumlahMinuman; ++i) {
                int menuItemIndex;
                cout << i + 1 << ". ";
                cin >> menuItemIndex;
                current->order.menuMinuman[i] = menuMinuman[menuItemIndex - 1];
            }

            cout << "Pesanan berhasil diubah." << endl;
            return;
        }
        current = current->next;
    }
    cout << "Pesanan untuk " << namaCustomer << " tidak ditemukan." << endl;
}

int main() {
    const int JUMLAH_MENU_MAKANAN = 5;
    MenuItem menuMakanan[JUMLAH_MENU_MAKANAN] = {{"1. Nasi Goreng", 15000, "Nasi goreng dengan telur"},
                                                  {"2. Mie Goreng", 15000, "Mie goreng pedas dengan telur dan sayuran"},
                                                  {"3. Sate Ayam", 18000, "Sate ayam dengan bumbu kacang"},
                                                  {"4. Bakso", 15000, "Bakso sapi dengan kuah bening"},
                                                  {"5. Mie Ayam", 10000, "Mie dengan potongan daging ayam"}};

    const int JUMLAH_MENU_MINUMAN = 5;
    MenuItem menuMinuman[JUMLAH_MENU_MINUMAN] = {{"1. Es Teh", 5000, "Es teh manis"},
                                                  {"2. Es Jeruk", 7000, "Minuman perasan jeruk "},
                                                  {"3. Kopi Hitam", 5000, "Kopi hitam tanpa gula"},
                                                  {"4. Susu Soda", 7000, "Minuman soda segar dicampur susu"},
                                                  {"5. Jus Buah", 15000, "Jus buah segar"}};

    OrderNode *pesanan = NULL;
    string namaPelanggan;
    char ulangiPesan;

    // Input nama pelanggan
    cout << "Masukkan nama anda: ";
    getline(cin, namaPelanggan);
    system("cls");

    do {
        // Menampilkan menu makanan
        cout << "Menu Makanan:" << endl;
        for (int i = 0; i < JUMLAH_MENU_MAKANAN; ++i) {
            cout << menuMakanan[i].nama << " - Rp." << menuMakanan[i].harga << endl;
            cout << "    " << menuMakanan[i].deskripsi << endl;
        }
        cout << endl;

        // Menampilkan menu minuman
        cout << "Menu Minuman:" << endl;
        for (int i = 0; i < JUMLAH_MENU_MINUMAN; ++i) {
            cout << menuMinuman[i].nama << " - Rp." << menuMinuman[i].harga << endl;
            cout << "    " << menuMinuman[i].deskripsi << endl;
        }
        cout << endl;

        // Input pesanan makanan dan minuman
        Order pesananBaru;
        pesananBaru.namaCustomer = namaPelanggan;

        cout << "Selamat Datang, " << pesananBaru.namaCustomer << "!" << endl;
        cout << "Berapa jumlah pesanan makanan yang ingin anda buat: ";
        cin >> pesananBaru.jumlahMakanan;
        pesananBaru.menuMakanan = new MenuItem[pesananBaru.jumlahMakanan];
        cout << "Apa saja yang ingin anda pesan (masukkan nomor menu):" << endl;
        for (int i = 0; i < pesananBaru.jumlahMakanan; ++i) {
            int indeksMenu;
            cout << "Makanan " << i + 1 << ": ";
            cin >> indeksMenu;
            pesananBaru.menuMakanan[i] = menuMakanan[indeksMenu - 1];
        }

        cout << "Berapa jumlah pesanan minuman yang ingin anda buat: ";
        cin >> pesananBaru.jumlahMinuman;
        pesananBaru.menuMinuman = new MenuItem[pesananBaru.jumlahMinuman];
        cout << "Apa saja yang ingin anda pesan (masukkan nomor menu):" << endl;
        for (int i = 0; i < pesananBaru.jumlahMinuman; ++i) {
            int indeksMenu;
            cout << "Minuman " << i + 1 << ": ";
            cin >> indeksMenu;
            pesananBaru.menuMinuman[i] = menuMinuman[indeksMenu - 1];
        }

        // Menambahkan pesanan ke double linked list
        tambahPesanan(pesanan, pesananBaru);

        // Menanyakan apakah ingin mengedit, menghapus pesanan, atau menyelesaikan pesanan
        cout << "Apakah anda ingin:" << endl;
        cout << "1. Mengedit pesanan" << endl;
        cout << "2. Menghapus pesanan" << endl;
        cout << "3. Menyelesaikan pesanan" << endl;
        int pilihan;
        cin >> pilihan;

        if (pilihan == 1) {
            editPesanan(pesanan, namaPelanggan, menuMakanan, JUMLAH_MENU_MAKANAN, menuMinuman, JUMLAH_MENU_MINUMAN);
        } else if (pilihan == 2) {
            hapusPesanan(pesanan, namaPelanggan);
        }

        // Mengulangi pesanan
        cout << "Apakah anda ingin membuat pesanan lagi? (y/n): ";
        cin >> ulangiPesan;

        system("cls");
    } while (ulangiPesan == 'y' || ulangiPesan == 'Y');

    // Mencetak semua pesanan dan total harga
    cout << "Pesanan:" << endl;
    double totalBiaya = printPesanan(pesanan);
    cout << "Total: Rp." << totalBiaya << endl;

    // Membersihkan memori
    OrderNode *temp = pesanan;
    while (temp != NULL) {
        OrderNode *sebelumnya = temp;
        temp = temp->next;
        delete[] sebelumnya->order.menuMakanan;
        delete[] sebelumnya->order.menuMinuman;
        delete sebelumnya;
    }

    return 0;
}
