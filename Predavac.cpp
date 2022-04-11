#include "Predavac.h"

Predavac::Predavac() : Korisnik(), brojKurseva(0), nazivKursa(nullptr)
{
}

Predavac::Predavac(Korisnik other, int brojKurseva, std::string *nazivKursa) : Korisnik(other), brojKurseva(brojKurseva), nazivKursa(new std::string[brojKurseva])
{
	for (int i = 0; i < brojKurseva; i++)
	{
		this->nazivKursa[i] = nazivKursa[i];
	}
}

Predavac::Predavac(int id, std::string ime, std::string prezime, std::string userName, std::string password, int brojKurseva, std::string *nazivKursa) :
	Korisnik(id, 0, ime, prezime, userName, password), brojKurseva(brojKurseva), nazivKursa(new std::string[brojKurseva])
{
	for (int i = 0; i < brojKurseva; i++)
	{
		this->nazivKursa[i] = nazivKursa[i];
	}
}

Predavac::Predavac(const Predavac& other) : Korisnik(other.id, 0, other.ime, other.prezime, other.userName, other.password), brojKurseva(other.brojKurseva),
	nazivKursa(new std::string[other.brojKurseva])
{
	for (int i = 0; i < brojKurseva; i++)
	{
		this->nazivKursa[i] = other.nazivKursa[i];
	}
}

void Predavac::opcije()
{
	std::cout << "Izaberite jednu od sljedecih opcija:" << std::endl;
	std::cout << "1. Lista mojih kurseva" << std::endl;
	std::cout << "2. Dodavanje ucenika na kurs" << std::endl;
	std::cout << "3. Slanje poruka" << std::endl;
	std::cout << "4. Inbox" << std::endl;
	std::cout << "5. Filtriranje poruka" << std::endl;
	std::cout << "6. Odjava" << std::endl;
}

void Predavac::opcijaZahtjevi()
{
	std::cout << "Zahtjevi za kurseve: " << std::endl;
	int duzina;
	std::string* zahtjevi, * kursevi = new std::string[20];
	zahtjevi = this->prihvatanjeZahtjeva(duzina, &kursevi);
	static int unos;
	do
	{
		std::cout << "Unesite redni broj korisnika kojeg dodati na kurs: ";
		std::cin >> unos;
	} while (unos > duzina || unos < 1);
	std::string arg = zahtjevi[unos - 1];
	std::string arg1 = kursevi[unos - 1];
	this->upisUcenika(arg, arg1);
	std::cout << arg << " " << arg1;
	delete[] kursevi;
}

void Predavac::opcijaSlanjePoruke()
{
	std::string primalac;
	this->prikaziKorisnike();
	std::cout << "Unesite korisnika kojem zelite poslati poruku: ";
	std::cin >> primalac;
	this->posaljiPoruku(primalac);
}

void Predavac::opcijaCitanjePoruke()
{
	std::string posiljalac;
	this->inbox();
	std::cout << "Unesite korisnika ciju poruku zelite procitati: ";
	std::cin >> posiljalac;
	this->citajPoruku(posiljalac);
}

void Predavac::opcijaFiltriranjePoruka()
{
	std::string posiljalac;
	this->inbox();
	std::cout << "Unesite korisnika ciju zelite procitati poruku: ";
	std::cin >> posiljalac;
	this->citajPoruku(posiljalac);
	this->filtrirajPoruku(posiljalac);
}

std::string* Predavac::prihvatanjeZahtjeva(int& duzina, std::string** nizA)
{
	std::ifstream in("zahtjeviKurs.txt", std::ios::in);
	std::string userName, kurs;
	std::string* niz = new std::string[20];
	int brojac = 0;
	while (in >> kurs >> userName)
	{
		Korisnik pom;
		pom.setUserName(userName);
		if (this->odgovarajuciKurs(kurs) && !(Predavac::provjeraUpisa(userName, kurs)) && (pom.isUserNameExist()))
		{
			niz[brojac] = userName;
			(*nizA)[brojac] = kurs;
			brojac++;
			std::cout << brojac << ". " << userName << " " << kurs << std::endl;
		}
		
	}
	in.close();
	duzina = brojac;
	return niz;
}

Predavac& Predavac::nadjiPredavaca(std::string trazeni)
{
	std::ifstream info("info.txt", std::ios::out);
	int n;
	info >> n;
	info.close();
	std::ifstream filein("predavaci.txt", std::ios::out);
	Predavac* novi = new Predavac;
	for (int i = 0; i < n; i++)
	{
		filein >> novi->id >> novi->ime >> novi->prezime >> novi->userName >> novi->password;
		if (trazeni == novi->userName)
		{
			break;
		}
	}
	filein.close();
	return *novi; //potrebno osloboditi
}

void Predavac::prikaziPredavace(std::string** niz, int& duzina)
{
	std::ifstream filein("predavaci.txt", std::ios::out);
	Predavac temp;
	duzina = 0;
	while (filein >> temp.id >> temp.ime >> temp.prezime >> temp.userName >> temp.password)
	{
			(*niz)[duzina] = temp.userName;
			duzina++;
			std::cout << duzina << ". " << temp.userName << std::endl;
	}
}

void Predavac::dodajKursPredavacu(std::string kurs)
{
	std::string s1 = this->userName + "Kursevi.txt";
	std::ofstream fileout(s1, std::ios::app);
	fileout.seekp(0, std::ios::end);
	if (fileout.tellp() < 1) {
		fileout << 0 << std::endl;
	}
	fileout.clear();
	fileout << kurs << std::endl;
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

bool Predavac::odgovarajuciKurs(std::string kurs)
{
	std::string s = this->userName + "Kursevi.txt";
	std::ifstream filein(s, std::ios::in);
	int broj;
	filein >> broj;
	std::string line;
	int brojac = 0;
	while (filein >> line)
	{
		if (line == kurs)
		{
			filein.close();
			return true;
		}
	}
	filein.close();
	return false;
}

void Predavac::upisUcenika(std::string ucenik, std::string kurs)
{
	std::string s1 = ucenik + "Kursevi.txt";
	std::string s2 = kurs + ".txt";
	std::ofstream fileout1(s1, std::ios::app);
	std::ofstream fileout2(s2, std::ios::app);

	fileout1.seekp(0, std::ios::end);
	fileout2.seekp(0, std::ios::end);

	if (fileout1.tellp() < 1) {
		fileout1 << 0 << std::endl;
	}

	if (fileout2.tellp() < 1) {
		fileout2 << 0 << std::endl;
	}

	fileout1.clear();
	fileout2.clear();

	fileout1 << kurs << std::endl;
	fileout2 << ucenik << std::endl;
	fileout1.close();
	fileout2.close();

	std::ifstream fileout11(s1, std::ios::in);
	std::ofstream fileout111("temp1.txt", std::ios::out | std::ios::app);
	std::ifstream fileout21(s2, std::ios::in);
	std::ofstream fileout211("temp2.txt", std::ios::out | std::ios::app);

	std::string line;
	int i = 0, j = 0;
	int broj;
	fileout11 >> broj;
	broj++;
	while (std::getline(fileout11, line))
	{
		if (i == 0)
		{
			fileout111 << broj << std::endl;
			i++;
		}
		else
		{
			fileout111 << line << std::endl;
			i++;
		}

	}
	fileout21 >> broj;
	broj++;
	while (std::getline(fileout21, line))
	{
		if (j == 0)
		{
			fileout211 << broj << std::endl;
			j++;
		}
		else
		{
			fileout211 << line << std::endl;
			j++;
		}
	}

	fileout11.close();
	fileout21.close();
	fileout111.close();
	fileout211.close();

	const char* c1 = s1.c_str();
	remove(c1);
	if (rename("temp1.txt", c1))
	{
		exit(0);
	}

	const char* c2 = s2.c_str();
	remove(c2);
	if (rename("temp2.txt", c2))
	{
		exit(0);
	}
}

bool Predavac::provjeraUpisa(std::string ucenik, std::string kurs)
{
	std::string s = kurs + ".txt";
	std::ifstream filein(s, std::ios::out);
	int broj;
	filein >> broj;
	std::string line;
	int brojac = 0;
	while (std::getline(filein, line))
	{
		if (brojac == 0)
		{
			brojac++;
		}
		else
		{
			if (line == ucenik)
			{
				filein.close();
				return true;
			}
			brojac++;
		}

	}
	filein.close();
	return false;
}

void Predavac::posaljiPoruku(std::string user)
{
	std::string poruka1, poruka2;
	std::cout << this->userName << ": ";
	std::cin >> poruka1;
	std::getline(std::cin, poruka2);
	std::ofstream out("Poruke.txt", std::ios::app);
	out << this->userName << " " << user << " " << poruka1 << poruka2 << std::endl;
	out.close();
}

void Predavac::prikaziKorisnike()
{
	int id, tipNaloga;
	std::string ime, prezime, userName, password;
	std::ifstream in("registrovaniKorisnici.txt", std::ios::binary);
	while (in >> id >> ime >> prezime >> userName >> password >> tipNaloga)
	{
		std::cout << userName << std::endl;
	}
	in.close();
}

void Predavac::listaKurseva()
{
	std::string s = this->userName + "Kursevi.txt";
	std::ifstream filein(s, std::ios::out);
	int broj;
	filein >> broj;
	std::cout << "Ukupan broj kurseva je " << broj << std::endl;
	std::string line;
	std::cout << "Svi kursevi:" << std::endl;
	int brojac = 0;
	while (std::getline(filein, line))
	{
		if (brojac == 0)
		{
			brojac++;
		}
		else
		{
			std::cout << line << std::endl;
			brojac++;
		}

	}
	filein.close();
}

void Predavac::inbox()
{
	std::cout << "Svi Vasi razgovori:" << std::endl;
	std::ifstream filein("Poruke.txt", std::ios::out);
	std::string posiljalac, primalac, line;
	std::string niz[20];
	int i = 0;
	while (filein >> posiljalac >> primalac && std::getline(filein, line))
	{
		if (primalac == this->userName)
		{
			if (!Korisnik::pretraziNiz(niz, posiljalac, i + 1))
			{
				niz[i] = posiljalac;
				i++;
				std::cout << posiljalac << std::endl;
			}
		}
	}
}

void Predavac::citajPoruku(std::string user)
{
	std::ifstream filein("Poruke.txt", std::ios::out);
	std::string posiljalac, primalac, line;
	while (filein >> posiljalac >> primalac && std::getline(filein, line))
	{
		if (primalac == this->userName && posiljalac == user)
		{
			std::cout << posiljalac << ": " << line << std::endl;
		}
		else if (primalac == user && posiljalac == this->userName)
		{
			std::cout << posiljalac << ": " << line << std::endl;
		}
	}
}

void Predavac::filtrirajPoruku(std::string user)
{
	std::ifstream filein("Poruke.txt", std::ios::out);
	std::string posiljalac, primalac, line, filter;
	std::cout << "Unesite rijec koju zelite pretraziti u cetu: ";
	std::cin >> filter;
	while (filein >> posiljalac >> primalac && std::getline(filein, line))
	{
		if (primalac == this->userName && posiljalac == user)
		{
			if (line.find(filter) != std::string::npos)
			{
				std::cout << posiljalac << ": " << line << std::endl;
			}
		}
		else if (primalac == user && posiljalac == this->userName)
		{
			if (line.find(filter) != std::string::npos)
			{
				std::cout << posiljalac << ": " << line << std::endl;
			}
		}
	}
}

void Predavac::pisiKorisnikaFajl()
{
	std::ofstream out("predavaci.txt", std::ios::app);
	out << this->id << " " << this->ime << " " << this->prezime << " " << this->userName << " " << this->password << " " << std::endl;
}

void Predavac::modifikujPredavaca(Korisnik other)
{
	std::ifstream in("predavaci.txt", std::ios::in);
	std::ofstream out("temp.txt", std::ios::out | std::ios::app);
	Predavac temp;
	while (in >> temp.id >> temp.ime >> temp.prezime >> temp.userName >> temp.password)
	{
		if (temp.userName == other.getUserName())
		{
			temp.ime = other.getName();
			temp.prezime = other.getSurr();
			temp.password = other.getPass();
		}
		out << temp.id << " " << temp.ime << " " << temp.prezime << " " << temp.userName << " " << temp.password << std::endl;
	}
	in.close();
	out.close();
	remove("predavaci.txt");
	if (rename("temp.txt", "predavaci.txt"))
	{
		exit(0);
	}
}

void Predavac::brisiPredavaca(std::string userName)
{
	//brisanje iz fajla korisnika
	Korisnik::brisiIzGlavnogFajla(userName);

	//brisanje iz fajla predavaci.txt
	std::ifstream in("predavaci.txt", std::ios::in);
	std::ofstream out("temp.txt", std::ios::out | std::ios::app);
	Predavac temp;
	while (in >> temp.id >> temp.ime >> temp.prezime >> temp.userName >> temp.password)
	{
		if (temp.userName != userName)
		{
			out << temp.id << " " << temp.ime << " " << temp.prezime << " " << temp.userName << " " << temp.password << std::endl;
		}
	}
	in.close();
	out.close();
	remove("predavaci.txt");
	if (rename("temp.txt", "predavaci.txt"))
	{
		exit(0);
	}

	//brisanje iz fajla info.txt
	Korisnik::smanjiBrojKorisnika();

	//Zamjena predavaca na kursevima
	//Korisnik::operacijeNadKursevima(userName, Kurs::modifikujKurs);
	std::cout << "Potrebno je izvrsiti promjene kurseva na kojima je obrisani korisnik predavao" << std::endl;
	Korisnik::operacijeNadKursevima(userName, Kurs::modifikujKurs);
}

Predavac::~Predavac()
{
	delete[] this->nazivKursa;
}



