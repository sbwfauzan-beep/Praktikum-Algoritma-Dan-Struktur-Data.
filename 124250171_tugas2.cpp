#include <iostream>
using namespace std;

// ============================================================
// NODE BST - menyimpan data kendaraan
// ============================================================
struct Node {
    string nopol;
    string pemilik;
    bool diParkiran; // true = di parkiran, false = di luar
    Node* left;
    Node* right;
};

Node* buatNode(string nopol, string pemilik) {
    Node* baru = new Node();
    baru->nopol = nopol;
    baru->pemilik = pemilik;
    baru->diParkiran = false;
    baru->left = nullptr;
    baru->right = nullptr;
    return baru;
}

// ============================================================
// OPERASI BST
// ============================================================
Node* insertBST(Node* root, string nopol, string pemilik) {
    if (root == nullptr) return buatNode(nopol, pemilik);
    if (nopol < root->nopol)
        root->left = insertBST(root->left, nopol, pemilik);
    else if (nopol > root->nopol)
        root->right = insertBST(root->right, nopol, pemilik);
    return root;
}

Node* searchBST(Node* root, string nopol) {
    if (root == nullptr || root->nopol == nopol) return root;
    if (nopol < root->nopol) return searchBST(root->left, nopol);
    return searchBST(root->right, nopol);
}

Node* minNode(Node* n) {
    while (n->left != nullptr) n = n->left;
    return n;
}

Node* deleteBST(Node* root, string nopol, bool& ditemukan) {
    if (root == nullptr) {
        ditemukan = false;
        return nullptr;
    }
    if (nopol < root->nopol) {
        root->left = deleteBST(root->left, nopol, ditemukan);
    } else if (nopol > root->nopol) {
        root->right = deleteBST(root->right, nopol, ditemukan);
    } else {
        ditemukan = true;
        if (root->left == nullptr) {
            Node* tmp = root->right;
            delete root;
            return tmp;
        } else if (root->right == nullptr) {
            Node* tmp = root->left;
            delete root;
            return tmp;
        }
        Node* pengganti = minNode(root->right);
        root->nopol = pengganti->nopol;
        root->pemilik = pengganti->pemilik;
        root->diParkiran = pengganti->diParkiran;
        root->right = deleteBST(root->right, pengganti->nopol, ditemukan);
    }
    return root;
}

void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    string statusStr = root->diParkiran ? "Di Parkiran" : "Di Luar Parkiran";
    cout << "  " << root->nopol << "\t\t" << root->pemilik << "\t\t" << statusStr << endl;
    inorder(root->right);
}

// ============================================================
// STACK LINKED LIST - untuk undo aksi
// ============================================================
struct StackNode {
    string nopol;
    string tipeAksi; // "masuk" / "keluar"
    StackNode* next;
};

struct Stack {
    StackNode* top;
    Stack() { top = nullptr; }
};

void push(Stack& s, string nopol, string aksi) {
    StackNode* baru = new StackNode();
    baru->nopol = nopol;
    baru->tipeAksi = aksi;
    baru->next = s.top;
    s.top = baru;
}

StackNode* pop(Stack& s) {
    if (s.top == nullptr) return nullptr;
    StackNode* tmp = s.top;
    s.top = s.top->next;
    return tmp;
}

bool stackKosong(Stack& s) {
    return s.top == nullptr;
}

// ============================================================
// QUEUE LINKED LIST - untuk antrian kendaraan
// ============================================================
struct QueueNode {
    string nopol;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
    Queue() { front = rear = nullptr; }
};

void enqueue(Queue& q, string nopol) {
    QueueNode* baru = new QueueNode();
    baru->nopol = nopol;
    baru->next = nullptr;
    if (q.rear == nullptr) {
        q.front = q.rear = baru;
    } else {
        q.rear->next = baru;
        q.rear = baru;
    }
}

string dequeue(Queue& q) {
    if (q.front == nullptr) return "";
    QueueNode* tmp = q.front;
    string np = tmp->nopol;
    q.front = q.front->next;
    if (q.front == nullptr) q.rear = nullptr;
    delete tmp;
    return np;
}

bool queueKosong(Queue& q) {
    return q.front == nullptr;
}

void tampilQueue(Queue& q) {
    if (queueKosong(q)) {
        cout << "Antrian kosong." << endl;
        return;
    }
    QueueNode* curr = q.front;
    cout << "--- Daftar Antrian Parkir ---" << endl;
    int no = 1;
    while (curr != nullptr) {
        cout << no++ << ". " << curr->nopol << " menunggu giliran masuk parkiran." << endl;
        curr = curr->next;
    }
}

// ============================================================
// PROGRAM UTAMA
// ============================================================
const int MAX_PARKIR = 5;
int slotTerpakai = 0;

Node* root = nullptr;
Stack histori;
Queue antrianParkir;

void tambahKendaraan() {
    string nopol, pemilik;
    cout << "Nomor Polisi: ";
    cin.ignore();
    getline(cin, nopol);
    cout << "Nama Pemilik: ";
    getline(cin, pemilik);

    if (searchBST(root, nopol) != nullptr) {
        cout << "Kendaraan dengan nomor polisi tersebut sudah terdaftar!" << endl;
        return;
    }
    root = insertBST(root, nopol, pemilik);
    cout << "Data kendaraan berhasil ditambahkan." << endl;
}

void tampilKendaraan() {
    if (root == nullptr) {
        cout << "Tidak ada data kendaraan." << endl;
        return;
    }
    cout << "------------------------------------------------------------" << endl;
    cout << "  Nomor Polisi\t\tNama Pemilik\t\tStatus" << endl;
    cout << "------------------------------------------------------------" << endl;
    inorder(root);
    cout << "------------------------------------------------------------" << endl;
}

void kendaraanMasuk() {
    string nopol;
    cout << "Nomor Polisi kendaraan masuk: ";
    cin.ignore();
    getline(cin, nopol);

    Node* k = searchBST(root, nopol);
    if (k == nullptr) {
        cout << "Kendaraan tidak ditemukan!" << endl;
        return;
    }
    if (k->diParkiran) {
        cout << "Kendaraan sudah berada di dalam parkiran!" << endl;
        return;
    }
    if (slotTerpakai >= MAX_PARKIR) {
        enqueue(antrianParkir, nopol);
        cout << "Parkiran penuh, kendaraan masuk ke dalam antrian." << endl;
    } else {
        k->diParkiran = true;
        slotTerpakai++;
        push(histori, nopol, "masuk");
        cout << "Kendaraan berhasil masuk." << endl;
    }
}

void kendaraanKeluar() {
    string nopol;
    cout << "Nomor Polisi kendaraan keluar: ";
    cin.ignore();
    getline(cin, nopol);

    Node* k = searchBST(root, nopol);
    if (k == nullptr) {
        cout << "Kendaraan tidak ditemukan!" << endl;
        return;
    }
    if (!k->diParkiran) {
        cout << "Kendaraan tidak sedang berada di parkiran!" << endl;
        return;
    }

    k->diParkiran = false;
    slotTerpakai--;
    push(histori, nopol, "keluar");
    cout << "Kendaraan berhasil keluar." << endl;

    if (!queueKosong(antrianParkir)) {
        string berikutnya = dequeue(antrianParkir);
        Node* nxt = searchBST(root, berikutnya);
        if (nxt != nullptr) {
            nxt->diParkiran = true;
            slotTerpakai++;
            push(histori, berikutnya, "masuk");
            cout << "Kendaraan berikutnya langsung masuk ke area parkir dari antrian." << endl;
        }
    }
}

void hapusKendaraan() {
    string nopol;
    cout << "Nomor Polisi kendaraan yang akan dihapus: ";
    cin.ignore();
    getline(cin, nopol);

    Node* k = searchBST(root, nopol);
    if (k != nullptr && k->diParkiran) slotTerpakai--;

    bool ditemukan = true;
    root = deleteBST(root, nopol, ditemukan);
    if (ditemukan) {
        cout << "Data kendaraan berhasil dihapus." << endl;
    } else {
        cout << "Kendaraan tidak ditemukan!" << endl;
    }
}

void undoAksi() {
    if (stackKosong(histori)) {
        cout << "Tidak ada aksi untuk di-undo." << endl;
        return;
    }
    StackNode* aksi = pop(histori);
    Node* k = searchBST(root, aksi->nopol);

    if (k == nullptr) {
        cout << "Data kendaraan tidak ditemukan." << endl;
        delete aksi;
        return;
    }

    if (aksi->tipeAksi == "masuk") {
        k->diParkiran = false;
        slotTerpakai--;
        cout << "Undo: Kendaraan keluar dari parkiran." << endl;
    } else {
        k->diParkiran = true;
        slotTerpakai++;
        cout << "Undo: Kendaraan masuk kembali ke parkiran." << endl;
    }
    delete aksi;
}

int main() {
    int menu;
    cout << "==========================================" << endl;
    cout << "  MANAJEMEN PARKIR INAP - BANDARA GSA     " << endl;
    cout << "  Kapasitas Parkir: " << MAX_PARKIR << " kendaraan          " << endl;
    cout << "==========================================" << endl;

    do {
        cout << "\n[ MENU ]" << endl;
        cout << "1. Daftarkan Kendaraan" << endl;
        cout << "2. Lihat Semua Kendaraan" << endl;
        cout << "3. Catat Kendaraan Masuk" << endl;
        cout << "4. Catat Kendaraan Keluar" << endl;
        cout << "5. Hapus Data Kendaraan" << endl;
        cout << "6. Undo Aksi Terakhir" << endl;
        cout << "7. Lihat Antrian Parkir" << endl;
        cout << "0. Keluar Program" << endl;
        cout << ">> Pilihan: ";
        cin >> menu;

        switch (menu) {
            case 1: tambahKendaraan(); break;
            case 2: tampilKendaraan(); break;
            case 3: kendaraanMasuk(); break;
            case 4: kendaraanKeluar(); break;
            case 5: hapusKendaraan(); break;
            case 6: undoAksi(); break;
            case 7: tampilQueue(antrianParkir); break;
            case 0: cout << "Program selesai. Terima kasih!" << endl; break;
            default: cout << "Menu tidak tersedia, coba lagi." << endl;
        }
    } while (menu != 0);

    return 0;
}
