#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Biblioteca {
private:
	const int id;
	string denumire;
	int nrRafturi;
	string* denumiriRafturi;
	int nrCarti;
	string* titluriCarti;

public:
	static int nrBiblioteci;

	// GETTER și SETTER pentru variabila statică nrBiblioteci
	static int getNrBiblioteci() {
		return nrBiblioteci;
	}

	static void setNrBiblioteci(int nr) {
		nrBiblioteci = nr;
	}

	// GETTER și SETTER pentru pointerul denumiriRafturi
	string* getDenumiriRafturi() {
		return this->denumiriRafturi;
	}

	void setDenumiriRafturi(int nrRafturi, string* denumiriRafturi) {
		if (this->denumiriRafturi != nullptr) {
			delete[] this->denumiriRafturi;
		}
		this->nrRafturi = nrRafturi;
		this->denumiriRafturi = new string[this->nrRafturi];
		for (int i = 0; i < this->nrRafturi; i++) {
			this->denumiriRafturi[i] = denumiriRafturi[i];
		}
	}

	Biblioteca() : id(++nrBiblioteci) {
		this->denumire = "Default";
		this->nrRafturi = 0;
		this->denumiriRafturi = nullptr;
		this->nrCarti = 0;
		this->titluriCarti = nullptr;
	}

	Biblioteca(int id, string denumire, int nrRafturi, string* denumiriRafturi, int nrCarti, string* titluriCarti) : id(++nrBiblioteci) {
		this->denumire = denumire;
		this->nrRafturi = nrRafturi;
		this->nrCarti = nrCarti;
		this->denumiriRafturi = new string[this->nrRafturi];
		this->titluriCarti = new string[this->nrCarti];
		for (int i = 0; i < this->nrRafturi; i++) {
			this->denumiriRafturi[i] = denumiriRafturi[i];
		}
		for (int j = 0; j < this->nrCarti; j++) {
			this->titluriCarti[j] = titluriCarti[j];
		}
	}

	void afisareBiblioteca() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Nr rafturi: " << this->nrRafturi;
		cout << endl << "Nr carti: " << this->nrCarti;
		if (this->nrRafturi > 0 && this->denumiriRafturi != nullptr) {
			cout << endl << "Categorii de carti in biblioteca: ";
			for (int i = 0; i < this->nrRafturi - 1; i++) {
				cout << this->denumiriRafturi[i] << ", ";
			}
			cout << this->denumiriRafturi[this->nrRafturi - 1] << ".";
		}

		if (this->nrCarti > 0 && this->titluriCarti != nullptr) {
			cout << endl << "Titluri de carti in biblioteca: ";
			for (int j = 0; j < this->nrCarti - 1; j++) {
				cout << this->titluriCarti[j] << ", ";
			}
			cout << this->titluriCarti[this->nrCarti - 1] << ".";
		}
	}

	~Biblioteca() {
		if (this->denumiriRafturi != nullptr) {
			delete[] this->denumiriRafturi;
		}
		if (this->titluriCarti != nullptr) {
			delete[] this->titluriCarti;
		}
	}
};

int Biblioteca::nrBiblioteci = 0;

void main() {
	Biblioteca::setNrBiblioteci(0);
	cout << "Numar biblioteci setat initial prin setter static: " << Biblioteca::getNrBiblioteci();

	Biblioteca Biblioteca_Centrala;
	Biblioteca_Centrala.afisareBiblioteca();
	cout << endl << "Am construit " << Biblioteca::getNrBiblioteci() << " biblioteca/i.";

	string* denumiriRafturi = new string[3] { "Istorie", "Geografie", "SF" };
	string* titluriCarti = new string[3] { "Istoria vikingilor", "Atlas geografic", "Harry Potter" };
	Biblioteca* Carturesti = new Biblioteca(2, "Carturesti", 3, denumiriRafturi, 3, titluriCarti);
	
	Carturesti->afisareBiblioteca();

	// Apelare setter pentru pointerul denumiriRafturi
	string* rafturiNoi = new string[2] { "Literatură", "Știință" };
	Carturesti->setDenumiriRafturi(2, rafturiNoi);

	cout << endl << " Dupa modificarea rafturilor prin setter ";
	Carturesti->afisareBiblioteca();

	// Apelare getter pentru pointerul denumiriRafturi
	string* rafturiReturnate = Carturesti->getDenumiriRafturi();
	cout << endl << " Primul raft returnat este: " << rafturiReturnate[0];

	delete Carturesti;
	delete[] denumiriRafturi;
	delete[] titluriCarti;
	delete[] rafturiNoi;
}
