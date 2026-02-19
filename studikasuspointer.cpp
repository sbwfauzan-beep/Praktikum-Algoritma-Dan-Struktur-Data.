#include <iostream>
using namespace std;
int main()
{

int n;
    cout << "Masukkan jumlah data: ";
    cin >> n;

    int array[n];
    int *p = array;
    cout << "Masukkan nilai:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> *(p + i);
        
    }

    cout << "Isi array: ";
    for (int i = 0; i < n; i++) {
        cout << *(p + i) << " " << endl;
    }

    int max = *p;
    int min = *p;
    int jumlah = 0;

    for (int i = 0; i < n; i++) {
        if (*(p + i) > max) {
            max = *(p + i);
        }

        if (*(p + i) < min) {
            min = *(p + i);
        }

        jumlah = jumlah + *(p + i);
    }

    int rata = jumlah / n;

    cout << "Nilai maksimum = "<< max << endl;
    cout << "Nilai minimum = " << min << endl;
    cout << "Jumlah = " << jumlah << endl;
    cout << "Rata-rata = " <<rata << endl;
}
