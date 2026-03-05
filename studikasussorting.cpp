#include <iostream>
using namespace std;

void bubbleSort(string nama[], int n){
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(nama[j] > nama[j+1]){
                string temp = nama[j];
                nama[j] = nama[j+1];
                nama[j+1] = temp;}}}}

void quickSort(string nama[], int low, int high){
    for(int i = low; i <= high; i++){
        for(int j = i+1; j <= high; j++){
            if(nama[i] < nama[j]){ //descending
                string temp = nama[i];
                nama[i] = nama[j];
                nama[j] = temp;}
			}
		}
	}

int main(){

    int n;
    cout << "Masukkan jumlah mahasiswa: ";
    cin >> n;
    string nama[n];
    cout << "Masukkan nama mahasiswa:" << endl;
    for(int i = 0; i < n; i++){
        cin >> nama[i];
    }
    bubbleSort(nama, n);
    cout << "Urutan Ascending (Bubble Sort):" << endl;
    for(int i = 0; i < n; i++){
        cout << nama[i] << endl;
    }
    quickSort(nama, 0, n-1);
    cout << "Urutan Descending (Quick Sort):" << endl;
    for(int i = 0; i < n; i++){
        cout << nama[i] << endl;
    }
}
