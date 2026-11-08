#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>

using namespace std;

enum TipSpital{DE_STAT=1, PRIVAT=2};

class Spital {
private:
	const int id;
	string denumire;
	int nrSectii;
	TipSpital tip;
	int* nrPacientiSectie;

public:
	static int nrSpitale;

	Spital() :id(++nrSpitale) {
		this->denumire = "Anonim";
		this->nrSectii = 0;
		this->tip = DE_STAT;
		this->nrPacientiSectie = nullptr;
	}

	Spital(int id, string denumire, int nrSectii, TipSpital tip, int* nrPacientiSectie) :id(id) {
		this->denumire = denumire;
		this->nrSectii = nrSectii;
		this->tip = tip;
		this->nrPacientiSectie = new int [nrSectii];
		for (int i = 0; i < this->nrSectii; i++) {
			this->nrPacientiSectie[i] = nrPacientiSectie[i];	
		}
		nrSpitale++;
	}

	Spital(const Spital& s) :id(s.id) {
		this->denumire = s.denumire;
		this->nrSectii = s.nrSectii;
		this->tip = s.tip;
		if (s.nrPacientiSectie != nullptr) {
			this->nrPacientiSectie = new int[s.nrSectii];
			for (int i = 0; i < s.nrSectii; i++) {
				this->nrPacientiSectie[i] = s.nrPacientiSectie[i];
			}
		}
		else {
			this->nrPacientiSectie = nullptr;
		}
	}

	void operator=(const Spital& s) {
		this->denumire = s.denumire;
		this->nrSectii = s.nrSectii;
		this->tip = s.tip;
		if (nrPacientiSectie != nullptr) {
			delete[] this->nrPacientiSectie;
			this->nrPacientiSectie = nullptr;
		}
		if (s.nrPacientiSectie != nullptr) {
			this->nrPacientiSectie = new int[s.nrSectii];
			for (int i = 0; i < s.nrSectii; i++) {
				this->nrPacientiSectie[i] = s.nrPacientiSectie[i];
			}
		}
		else {
			this->nrPacientiSectie = nullptr;
		}
	}

	int getNrSectii() {
		return this->nrSectii;
	}

	void setNrSectii(int nrS) {
		if (nrS >= 0) {
			this->nrSectii = nrS;
		}
		else {
			throw "Numarul este negativ!";
		}
	}

	int* getNrPacientiSectie() {
		int* vector = new int[this->nrSectii];
		for (int i = 0; i < this->nrSectii; i++) {
			vector[i] = nrPacientiSectie[i];
		}
		return vector;
	}

	void setNrPacientiSectie(int* vector, int nrS) {
		setNrSectii(nrS);
		if (nrPacientiSectie != nullptr) {
			delete[] this->nrPacientiSectie;
		}
		int* nrPacientiSectie = new int[this->nrSectii];
		for (int i = 0; i < nrSectii; i++) {
			this->nrPacientiSectie[i] = vector[i];
		}
		delete[] vector;
	}

	void afisareSpital() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Numar sectii: " << this->nrSectii;
		cout << endl << "Tip spital: ";
		if (tip == 1) {
			cout << "DE STAT";
		}
		else {
			cout << "PRIVATA";
		}
		if (nrSectii > 0) {
			cout <<endl<< "Numarul pacientilor pe fiecare sectie este: ";
			for (int i = 0; i < nrSectii; i++) {
				cout << endl << nrPacientiSectie[i] << " pe sectia " << i + 1;
			}
		}
	}

	bool operator<(const Spital& s) {
		return this->nrSectii < s.nrSectii;
	}

	~Spital() {
		if (this->nrPacientiSectie != nullptr) {
			delete[] this->nrPacientiSectie;
		}
	}
};

int Spital::nrSpitale = 0;

void main() {
	Spital sMunicipal;
	sMunicipal.afisareSpital();

	int* nrPacientiSectie = new int[3] {56, 30, 12};
	Spital* pJudetean=new Spital(2, "Spitalul Judetean", 3, PRIVAT, nrPacientiSectie);
	pJudetean->afisareSpital();

	try {
		sMunicipal.setNrSectii(-3);
	}
	catch (...) {
		cout <<endl<< "Nr sectii negativ!";
	}

	Spital sObregia = *pJudetean; Spital::nrSpitale++;
	sObregia.afisareSpital();

	cout<<endl << "Am construit " << Spital::nrSpitale << " spitale.";

	delete[] nrPacientiSectie;
	delete pJudetean;
}

