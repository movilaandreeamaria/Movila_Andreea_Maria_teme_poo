#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

//Să se implementeze în C++ clasa Biblioteca care gestionează informațiile despre o bibliotecă 
// și repartizarea cărților pe rafturile acesteia.

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

	Biblioteca() :id(++nrBiblioteci) {
		this->denumire = "Default";
		this->nrRafturi = 0;
		this->denumiriRafturi = nullptr;
		this->nrCarti = 0;
		this->titluriCarti = nullptr;
	}

	Biblioteca(string denumire, int nrRafturi, string* denumiriRafturi, int nrCarti, string* titluriCarti) :id(++nrBiblioteci) {
		this->denumire = denumire;
		this->nrRafturi = nrRafturi;
		this->nrCarti = nrCarti;

		if (this->nrRafturi > 0 && denumiriRafturi != nullptr) {
			this->denumiriRafturi = new string[this->nrRafturi];
			for (int i = 0; i < this->nrRafturi; i++)
			{
				this->denumiriRafturi[i] = denumiriRafturi[i];
			}
		}
		else {
			this->denumiriRafturi = nullptr;
		}

		if (this->nrCarti > 0 && titluriCarti != nullptr) {
			this->titluriCarti = new string[this->nrCarti];
			for (int j = 0; j < this->nrCarti; j++)
			{
				this->titluriCarti[j] = titluriCarti[j];
			}
		}
		else {
			this->titluriCarti = nullptr;
		}
	}

	int getNrCarti() {
		return this->nrCarti;
	}

	void setNrCarti(int nrCartiNou) {
		if (nrCartiNou >= 0) {
			this->nrCarti = nrCartiNou;
		}
		else {
			throw "Numarul de carti nu poate fi negativ!";
		}
	}

	string* getTitluriCarti() {
		if (this->nrCarti == 0 || this->titluriCarti == nullptr) {
			return nullptr;
		}
		string* vectorCopie = new string[this->nrCarti];
		for (int i = 0; i < this->nrCarti; i++) {
			vectorCopie[i] = this->titluriCarti[i];
		}
		return vectorCopie;
	}

	void setTitluriCarti(string* vector, int nrC) {
		setNrCarti(nrC); 

		if (this->titluriCarti != nullptr) {
			delete[] this->titluriCarti;
		}

		if (this->nrCarti > 0 && vector != nullptr) {
			this->titluriCarti = new string[this->nrCarti];
			for (int i = 0; i < this->nrCarti; i++) {
				this->titluriCarti[i] = vector[i];
			}
		}
		else {
			this->titluriCarti = nullptr;
		}

		delete[] vector;
	}

	void afisareBiblioteca() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Nr rafturi: " << this->nrRafturi;
		cout << endl << "Nr carti: " << this->nrCarti;
		
		if (this->nrRafturi > 0 && this->denumiriRafturi != nullptr) {
			cout << endl << "Categorii de carti in biblioteca: ";
			for (int i = 0; i < this->nrRafturi - 1; i++)
			{
				cout << this->denumiriRafturi[i] << ", ";
			}
			cout << this->denumiriRafturi[this->nrRafturi - 1] << ".";
		}

		if (this->nrCarti > 0 && this->titluriCarti != nullptr) {
			cout << endl << "Titluri de carti in biblioteca: ";
			for (int j = 0; j < this->nrCarti - 1; j++)
			{
				cout << this->titluriCarti[j] << ", ";
			}
			cout << this->titluriCarti[this->nrCarti - 1] << ".";
		}
	}

	~Biblioteca() {
		if (this->denumiriRafturi != nullptr)
		{
			delete[] this->denumiriRafturi;
		}
		if (this->titluriCarti != nullptr)
		{
			delete[] this->titluriCarti;
		}
	}
};

int Biblioteca::nrBiblioteci = 0;

int main() {
	Biblioteca Biblioteca_Centrala;
	Biblioteca_Centrala.afisareBiblioteca();

	try {
		Biblioteca_Centrala.setNrCarti(-2);
	}
	catch (int cod) {
		cout << endl << "Cod eroare: " << cod;
	}
	catch (const char* mesaj) {
		cout << endl << "Eroare: " << mesaj;
	}
	catch (...) {
		cout << endl << "Valoare invalida pentru numarul de carti!";
	}

	cout << endl << "Noul numar de carti este: " << Biblioteca_Centrala.getNrCarti();

	Biblioteca_Centrala.setTitluriCarti(new string[3]{ "Poezii", "Maitreyi", "Ion" }, 3);
	string* vectorCartiCopie = Biblioteca_Centrala.getTitluriCarti();

	cout << endl << "Noile titluri din biblioteca sunt: ";
	for (int i = 0; i < Biblioteca_Centrala.getNrCarti(); i++)
	{
		cout << vectorCartiCopie[i] << ", ";
	}

	Biblioteca_Centrala.afisareBiblioteca();
	delete[] vectorCartiCopie; // curatam copia

	string* denumiriRafturi = new string[3] {"Istorie", "Geografie", "SF"};
	string* titluriCarti = new string[3] {"Istoria vikingilor", "Atlas geografic", "Harry Potter"};
	
	Biblioteca* Carturesti = new Biblioteca("Carturesti", 3, denumiriRafturi, 3, titluriCarti);
	Carturesti->afisareBiblioteca();

	delete Carturesti;
	delete[] denumiriRafturi;
	delete[] titluriCarti;

	cout << endl << "Am construit " << Biblioteca::nrBiblioteci << " biblioteca/i.";

	return 0;
}
