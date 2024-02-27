#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;
char crt[] = "\n-----------------------------\n";
char crtn[] = "-----------------------------\n";
const int vrijednost[35] = { 0,0,0,0,0,10000,7500,5000,2500,1000,500,300,200,150,100,80,60,40,30,25,20,18,16,14,12,10,9,8,7,6,5,4,3,2,1 };

long long faktorijel(int n) {
	if (n == 0 || n == 1) {
		return 1;
	}
	else {
		return n * faktorijel(n - 1);
	}
}

void unosBrojeva(int* mojiBrojevi, int brVel, float& iznos) {
	for (int i = 0; i < brVel; i++) {
		cout << "[" << i + 1 << "]: ";
		cin >> mojiBrojevi[i];
		if (mojiBrojevi[i] < 1 || mojiBrojevi[i] > 48) {
			cout << "~~Broj mora biti izmedju 1 i 48!~~" << endl;
			i--;
		}
		for (int j = 0; j < i; j++) {
			if (mojiBrojevi[i] == mojiBrojevi[j]) {
				cout << "~~Vec si unio taj broj!~~" << endl;
				i--;
			}
		}
	}
	cout << "Uplata za [iznos]: ";
	cin >> iznos;

	cout << crtn;
}

void duplaIsplata(int& a, int& b) {
	do {
		a = rand() % 30 + 1;
		a += 5;
		b = rand() % 30 + 1;
		b += 5;
	} while (a == b);
}

void izvlacenje(int niz[]) {
	for (int i = 0; i < 35; i++) {
		niz[i] = rand() % 48 + 1;
		for (int j = 0; j < i; j++) {
			if (niz[i] == niz[j]) {
				i--;
			}
		}
	}
}

void ispisIzvlacenja(int niz[], int dupla1, int dupla2) {
	cout << "Izvuceni brojevi su :" << endl;
	for (int j = 0; j < 35; j++) {
		cout << setw(4) << "[" << setw(2) << j + 1 << "]" << setw(3) << niz[j];
		if (vrijednost[j] == 0) {
			cout << setw(7) << "BUBANJ";
		}
		else {
			cout << setw(7) << vrijednost[j] << " KM ";
		}
		if (j == dupla1 || j == dupla2) {
			cout << " | DUPLA ISPLATA";
		}
		cout << endl;
	}
	cout << endl;
}

void brojPogodjenih(int* mojiBrojevi, int izvuceni[], int brVel, int& brojac, int& zadnjaPoz, int a, int b, int duplaVr) {
	cout << crt;
	for (int i = 0; i < brVel; i++) {
		for (int j = 0; j < 35; j++) {
			if (mojiBrojevi[i] == izvuceni[j]) {
				cout << "Vas broj " << mojiBrojevi[i] << " se nalazi na " << j + 1 << " poziciji." << endl;
				brojac++;
				if (zadnjaPoz < j) {
					zadnjaPoz = j;
					if (j == a || j == b) {
						duplaVr++;
					}
				}
			}
		}
	}
}

void ispisVasegDobitka(int brVel, int zadnjaPoz, int duplaVr, float uplata, int brojac) {
	cout << "Ukupno pogodjenih: " << brojac << " od " << brVel << endl;
	int ukupnoBrojeva = 48;
	int odabranoBrojeva = brVel;
	int dodatniBrojevi = brVel - 6;
	int sistemi[] = { 6, 7, 8, 9 };
	long long brojKombinacija;

	for (int i = 0; i < sizeof(sistemi) / sizeof(sistemi[0]); ++i) {
		int k = 6;
		int n = sistemi[i];
		brojKombinacija = faktorijel(n) / (faktorijel(k) * faktorijel(n - k));
	}
	cout << "Zadnji broj se nalazi na " << vrijednost[zadnjaPoz] << " KM." << endl;
	cout << crt;
	cout << "Ostvarena vrijednost:\t" << setw(7) << (float)vrijednost[zadnjaPoz] << endl; //1-9/9  0-9/9   1-6/9 0-6/9
	if (duplaVr > 0 && brojKombinacija == 0) {
		cout << "+Dupla isplata:\t" << setw(7) << duplaVr * (vrijednost[zadnjaPoz]) << endl;
		cout << "Ukupno za isplatiti\t" << setw(7) << fixed << setprecision(2) << duplaVr * uplata * vrijednost[zadnjaPoz];
	}
	else if (duplaVr == 0 && brojKombinacija == 0) {
		cout << "Ukupno za isplatiti\t" << setw(7) << fixed << setprecision(2) << uplata * vrijednost[zadnjaPoz];
	}
	else if (duplaVr == 1 && brojKombinacija != 0) {
		cout << "+Dupla isplata:\t" << setw(7) << duplaVr * (vrijednost[zadnjaPoz]) << endl;
		cout << "Ukupno za isplatiti\t" << setw(7) << fixed << setprecision(2) << (uplata / brojKombinacija) * vrijednost[zadnjaPoz];
	}
	else {
		cout << "Ukupno za isplatiti\t" << setw(7) << fixed << setprecision(2) << (uplata / brojKombinacija) * vrijednost[zadnjaPoz];
	}
}

int main() {
	srand(time(0));
	int brVel, duplaVr = 0;
	float iznos = 0;
	do {
		cout << "Unesi koliko zelis brojeva " << endl;
		cout << "Broj mora biti izmedju 6 i 9!" << endl;
		cout << "Unesi: ";
		cin >> brVel;
		cout << crtn;
	} while (brVel < 6 || brVel > 9);
	int* mojiBrojevi = new int[brVel];

	int d1, d2, brojac = 0, zadnjaPoz = 0;
	int izvuceni[35]{};
	unosBrojeva(mojiBrojevi, brVel, iznos);
	duplaIsplata(d1, d2);
	izvlacenje(izvuceni);
	ispisIzvlacenja(izvuceni, d1, d2);
	brojPogodjenih(mojiBrojevi, izvuceni, brVel, brojac, zadnjaPoz, d1, d2, duplaVr);
	if (brojac > 5) {
		ispisVasegDobitka(brVel, zadnjaPoz, duplaVr, iznos, brojac);
	}
	cout << crt;

	return 0;
}
