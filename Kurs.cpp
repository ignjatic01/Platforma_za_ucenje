#include "Kurs.h"

Kurs::Kurs() : imeKursa("err") ,polaznici(nullptr), brojPolaznika(0), predavacKursa("err"), brojBodova(0)
{
}

Kurs::Kurs(std::string imeKursa, std::string predavacKursa, std::string* polaznici, int brojBodova, int brojPolaznika) : imeKursa(imeKursa),
brojBodova(brojBodova), brojPolaznika(brojPolaznika), polaznici(new std::string[brojPolaznika]), predavacKursa(predavacKursa)
{
	for (int i = 0; i < brojPolaznika; i++)
	{
		this->polaznici[i] = polaznici[i];
	}
}



void Kurs::pisiKursFajl()
{
	std::ofstream out("kursevi.txt", std::ios::app);
	out << this->imeKursa << " " << this->brojBodova << " " << this->predavacKursa << std::endl;
}

void Kurs::dodajPolaznika(std::string user)
{
	//Upitno jako jel treba pisati polaznici
	std::string s1 = this->imeKursa + "Polaznici.txt";
	std::ofstream fileout(s1, std::ios::app);
	fileout.seekp(0, std::ios::end);
	if (fileout.tellp() < 1) {
		fileout << 0 << std::endl;
	}
	fileout.clear();
	fileout << user << std::endl;
	fileout.close();

	std::ifstream fileout11(s1, std::ios::in);
	std::ofstream fileout12("temp1.txt", std::ios::out | std::ios::app);
	std::string line;
	int i = 0;
	int broj;
	fileout11 >> broj;
	broj++;
	while (std::getline(fileout11, line))
	{
		if (i == 0)
		{
			fileout12 << broj << std::endl;
			i++;
		}
		else
		{
			fileout12 << line << std::endl;
			i++;
		}
	}
	fileout11.close();
	fileout12.close();
	const char* c1 = s1.c_str();
	remove(c1);
	if (rename("temp1.txt", c1))
	{
		exit(0);
	}
}

void Kurs::pisiKurseve(Kurs** niz, int& duzina)
{
	std::ifstream filein("kursevi.txt", std::ios::out);
	Kurs temp;
	duzina = 0;
	while (filein >> temp.imeKursa >> temp.brojBodova >> temp.predavacKursa)
	{
		(*niz)[duzina] = temp;
		duzina++;
		std::cout << duzina << ". "; 
		temp.pisiKurs();
	}
}

void Kurs::pisiKurs()
{
	std::cout << this->imeKursa << " " << this->brojBodova << " " << this->predavacKursa << std::endl;
}

std::string Kurs::getImeKursa()
{
	return this->imeKursa;
}

void Kurs::brisiKurs(std::string imeKursa)
{
	//Brisanje iz fajla kursevi
	std::ifstream in("kursevi.txt", std::ios::in);
	std::ofstream out("temp.txt", std::ios::out | std::ios::app);
	Kurs temp;
	while (in >> temp.imeKursa >> temp.brojBodova >> temp.predavacKursa)
	{
		if (temp.imeKursa != imeKursa)
		{
			out<< temp.imeKursa << " " << temp.brojBodova << " " << temp.predavacKursa << std::endl;
		}
		else
		{
			Kurs::brisiKursKorisnicima(imeKursa, temp.predavacKursa);
		}
	}
	in.close();
	out.close();
	remove("kursevi.txt");
	if (rename("temp.txt", "kursevi.txt"))
	{
		exit(0);
	}

	//Uklanjanje kursa iz ostalih fajlova
	std::string kf = imeKursa + ".txt", line;
	std::ifstream in1(kf, std::ios::in);
	if (in1.is_open())
	{
		int brojac = 0;
		while (std::getline(in1, line))
		{
			if (brojac == 0)
			{
				brojac++;
			}
			else
			{
				Kurs::brisiKursKorisnicima(imeKursa, line);
				brojac++;
			}
		}
	}
	in1.close();
	const char* c1 = kf.c_str();
	remove(c1);
}

void Kurs::brisiKursKorisnicima(std::string imeKursa, std::string user)
{
	std::string fp = user + "Kursevi.txt", line;
	std::ifstream in(fp, std::ios::in);
	std::ofstream out("temp1.txt", std::ios::out | std::ios::app);
	int brojac = 0;
	while (std::getline(in, line))
	{
		if (brojac == 0)
		{
			int foo = atoi(line.c_str());
			foo -= 1;
			out << foo << std::endl;
			brojac++;
		}
		else
		{
			if (line != imeKursa)
			{
				out << line << std::endl;
			}
			brojac++;
		}
	}
	in.close();
	out.close();
	const char* c1 = fp.c_str();
	remove(c1);
	if (rename("temp1.txt", c1))
	{
		exit(0);
	}
}

void Kurs::modifikujKurs(std::string kurs, std::string userNameA)
{
	std::ifstream in("kursevi.txt", std::ios::in);
	std::ofstream out("tempA.txt", std::ios::out | std::ios::app);
	Kurs temp;
	std::string param;
	while (in >> temp.imeKursa >> temp.brojBodova >> temp.predavacKursa)
	{
		if (temp.imeKursa != kurs)
		{
			out << temp.imeKursa << " " << temp.brojBodova << " " << temp.predavacKursa << std::endl;
		}
		else
		{
			std::cout << kurs << std::endl;
			std::cout << "Unesite novi broj ECTS bodova: ";
			std::cin >> temp.brojBodova;
			Kurs::zamjeniPredavaca(kurs, temp);
			out << temp.imeKursa << " " << temp.brojBodova << " " << temp.predavacKursa << std::endl;
		}
	}
	in.close();
	out.close();
	remove("kursevi.txt");
	if (rename("tempA.txt", "kursevi.txt"))
	{
		exit(0);
	}
}

void Kurs::zamjeniPredavaca(std::string kurs, Kurs& temp)
{
	std::string* niz = new std::string[100];
	int duzina = 0;
	Predavac::prikaziPredavace(&niz, duzina);
	static int unos;
	do
	{
		std::cout << "Unesite redni broj predavaca koji ce preuzeti predmet: ";
		std::cin >> unos;
	} while (unos > duzina || unos < 1);
	std::string noviPredavac = niz[unos - 1];
	//VAZNO: Dodati koji kurs se modifikuje
	if (Korisnik::isUserExist(temp.predavacKursa))
	{
		Kurs::brisiKursKorisnicima(kurs, temp.predavacKursa);
	}
	temp.predavacKursa = noviPredavac;
	Predavac novi;
	novi.setUserName(noviPredavac);
	novi.dodajKursPredavacu(kurs);
	delete[] niz;
}

Kurs::~Kurs()
{
	delete[] this->polaznici;
}
