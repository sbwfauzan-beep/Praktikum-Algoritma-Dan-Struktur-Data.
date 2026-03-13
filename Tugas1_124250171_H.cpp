#include <iostream>
#include <stdio.h>
using namespace std;

struct Produk{
    char name[60];
    char category[30];
    double price;
    int stock;
    float rating;
};

Produk arr[100];
int n = 0;

int banding(char a[], char b[]){
    int i=0;

    while(a[i] != '\0' && b[i] != '\0'){

        if(a[i] > b[i]) return 1;
        if(a[i] < b[i]) return -1;

        i++;
    }

    return 0;
}

void loadFile(){

    FILE *pf;

    pf = fopen("produk.txt","r");

    if(pf == NULL){
        return;
    }

    while(fscanf(pf," %[^|]|%[^|]|%lf|%d|%f\n",
    arr[n].name,
    arr[n].category,
    &arr[n].price,
    &arr[n].stock,
    &arr[n].rating)!=EOF){

        n++;
    }

    fclose(pf);
}

void saveFile(){

    FILE *pf;

    pf = fopen("shopease_db.txt","w");

    for(int i=0;i<n;i++){

        fprintf(pf,"%s|%s|%.0lf|%d|%.1f\n",
        arr[i].name,
        arr[i].category,
        arr[i].price,
        arr[i].stock,
        arr[i].rating);
    }

    fclose(pf);
}

void tambahProduk(){

    cin.ignore();

    cout<<"Nama produk : ";
    cin.getline(arr[n].name,60);

    cout<<"Kategori : ";
    cin.getline(arr[n].category,30);

    cout<<"Harga : ";
    cin>>arr[n].price;

    cout<<"Stok : ";
    cin>>arr[n].stock;

    cout<<"Rating : ";
    cin>>arr[n].rating;

    n++;

    saveFile();

    cout<<"Produk berhasil ditambahkan" << endl;
}

void bubbleSort(){

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){

            if(banding(arr[j].name,arr[j+1].name) > 0){

                Produk temp;

                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;

            }
        }
    }
}

void quickSort(int kiri,int kanan){

    int i = kiri;
    int j = kanan;

    float pivot = arr[(kiri+kanan)/2].rating;

    while(i<=j){

        while(arr[i].rating > pivot){
            i++;
        }

        while(arr[j].rating < pivot){
            j--;
        }

        if(i<=j){

            Produk temp;

            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            i++;
            j--;
        }
    }

    if(kiri < j){
        quickSort(kiri,j);
    }

    if(i < kanan){
        quickSort(i,kanan);
    }
}

void tampilProduk(){

    int mode;

    cout<<"\n1. Urutkan Nama (Bubble Sort)";
    cout<<"\n2. Urutkan Rating (Quick Sort)";
    cout<<"\nPilih mode : ";
    cin>>mode;

    if(mode==1){
        bubbleSort();
    }

    else if(mode==2){
        quickSort(0,n-1);
    }

    cout<<"===== DAFTAR PRODUK =====" << endl;

    for(int i=0;i<n;i++){

        cout<<"Nama : "<<arr[i].name<<endl;
        cout<<"Kategori : "<<arr[i].category<<endl;
        cout<<"Harga : "<<arr[i].price<<endl;
        cout<<"Stok : "<<arr[i].stock<<endl;
        cout<<"Rating : "<<arr[i].rating<<endl;

        cout<<"-------------------------\n";
    }
}

void cariProduk(){

    char cari[60];
    bool ketemu=false;

    cin.ignore();

    cout<<"Masukkan nama produk : ";
    cin.getline(cari,60);

    for(int i=0;i<n;i++){

        if(banding(arr[i].name,cari)==0){

            cout<<"Produk ditemukan\n";
            cout<<"Nama : "<<arr[i].name<<endl;
            cout<<"Kategori : "<<arr[i].category<<endl;
            cout<<"Harga : "<<arr[i].price<<endl;
            cout<<"Stok : "<<arr[i].stock<<endl;
            cout<<"Rating : "<<arr[i].rating<<endl;

            ketemu=true;
        }
    }

    if(!ketemu){
        cout<<"Produk tidak ditemukan!\n";
    }
}

int main(){

    int pilih;

    loadFile();

    do{

        cout<<"--- MENU SHOPEASE ---" << endl;
        cout<<"1. Tambah Produk" << endl;
        cout<<"2. Tampilkan Produk" << endl;
        cout<<"3. Cari Produk" << endl;
        cout<<"4. Keluar" << endl;
        cout<<"Pilih : " << endl;
        cin>>pilih;

        if(pilih==1){
            tambahProduk();
        }

        else if(pilih==2){
            tampilProduk();
        }

        else if(pilih==3){
            cariProduk();
        }

    }while(pilih!=4);

    saveFile();

    cout<<"Program selesai";

}
