#include "Korisnik.h"


Korisnik::Korisnik(int id, int tipNaloga, std::string ime, std::string prezime, std::string userName, std::string password) : id(id), tipNaloga(tipNaloga), ime(ime), prezime(prezime), userName(userName), password(password)
{
}

Korisnik::Korisnik(const Korisnik& other) : id(other.id), tipNaloga(other.tipNaloga), ime(other.ime), prezime(other.prezime), userName(other.userName), password(other.password)
{
}

std::string Korisnik::getName()
{
	return this->ime;
}

std::string Korisnik::getSurr()
{
	return this->prezime;
}

std::string Korisnik::getPass()
{
	return this->password;
}

int Korisnik::getType()
{
	return this->tipNaloga;
}

std::string Korisnik::getUserName()
{
	return this->userName;
}

void Korisnik::opcije()
{
	std::cout << "1. Odjava" << std::endl;
}

void Korisnik::setUserName(std::string user)
{
	this->userName = user;
}

void Korisnik::registrujKorisnika()
{
	std::cout << "Registracija" << std::endl;
	int id;

	std::ifstream fileinfo("info.txt", std::ios::in);
	fileinfo >> id;
	fileinfo.close();

	this->id = ++id;
	std::cout << "Unesite ime: " << std::endl;
	std::cin >> this->ime;
	std::cout << "Unesite prezime: " << std::endl;
	std::cin >> this->prezime;
	std::cout << "Unesite unikatno korisnicko ime: " << std::endl;
	std::cin >> this->userName;
	if (this->isUserNameExist())
	{
		throw std::exception("Birano korisnicko ime vec postoji");
	}
	std::cout << "Unesite lozinku: " << std::endl;
	std::cin >> this->password;
	do
	{
		std::cout << "Izaberite tip naloga ([0] predavac ili [1] ucenik)" << std::endl;
		std::cin >> this->tipNaloga;
	} while (this->tipNaloga < 0 || this->tipNaloga>1);

	std::ofstream fileedit("info.txt", std::ios::out);
	fileedit << id << std::endl;
	fileedit.close();
	this->pisiKorisnikaFajl();
	std::cout << "Uspjesna registracija\n";
}


void Korisnik::pisiKorisnikaFajl()
{
	Korisnik temp = *this;
	std::ofstream out("registrovaniKorisnici.txt", std::ios::app);
	out << this->id << " " << this->ime << " " << this->prezime << " " << this->userName << " " << this->password << " " << this->tipNaloga << std::endl;
	out.close();
}



void Korisnik::citajKorisnikaFajl()
{
	Korisnik prijavljen;
	std::ifstream in("registrovaniKorisnici.txt", std::ios::binary);
	while (in >> prijavljen.id >> prijavljen.ime >> prijavljen.prezime >> prijavljen.userName >> prijavljen.password >> prijavljen.tipNaloga)
	{
		prijavljen.pisiKorisnika();
	}
	in.close();
}

void Korisnik::prijavaKorisnika()
{
	int brojPokusaja = 0;
	do
	{
		std::cout << "Korisnicko ime: ";
		std::cin >> this->userName;
		std::cout << "Lozinka: ";
		std::cin >> this->password;
		brojPokusaja++;
	} while (brojPokusaja < 3 && !this->isUserValid());

	if (brojPokusaja >= 3)
	{
		throw brojPokusaja;
	}
}

Korisnik* Korisnik::fromFileToArr()
{
	int brojKorisnika;
	std::ifstream fileinfo("info.txt", std::ios::in);
	fileinfo >> brojKorisnika;
	fileinfo.close();
	Korisnik temp;
	Korisnik* arr = new Korisnik[brojKorisnika];
	std::ifstream in("registrovaniKorisnici.txt", std::ios::in);
	int i = 0;
	while (in >> temp.id >> temp.ime >> temp.prezime >> temp.userName >> temp.password >> temp.tipNaloga)
	{
		arr[i] = temp;
		i++;
	}
	in.close();
	return arr;
}

bool Korisnik::isUserValid()
{
	Korisnik* niz = Korisnik::fromFileToArr();
	
	int brojKorisnika;
	std::ifstream fileinfo("info.txt", std::ios::in);
	fileinfo >> brojKorisnika;
	fileinfo.close();
	
	for (int i = 0; i < brojKorisnika; i++)
	{
		if (this->userName == niz[i].userName && this->password == niz[i].password)
		{
			*this = niz[i];
			delete[] niz;
			return true;
		}
	}

	delete[] niz;
	return false;
}

bool Korisnik::isUserNameExist()
{
	Korisnik* niz = Korisnik::fromFileToArr();

	int brojKorisnika;
	std::ifstream fileinfo("info.txt", std::ios::in);
	fileinfo >> brojKorisnika;
	fileinfo.close();
	
	for (int i = 0; i < brojKorisnika; i++)
	{
		if (this->userName == niz[i].userName)
		{
			delete[] niz;
			return true;
		}
	}

	delete[] niz;
	return false;
}

void Korisnik::posaljiPoruku(std::string user)
{
}

void Korisnik::citajPoruku(std::string user)
{
}

bool Korisnik::isUserExist(std::string user)
{
	Korisnik* niz = Korisnik::fromFileToArr();

	int brojKorisnika;
	std::ifstream fileinfo("info.txt", std::ios::in);
	fileinfo >> brojKorisnika;
	fileinfo.close();

	for (int i = 0; i < brojKorisnika; i++)
	{
		if (user == niz[i].userName)
		{
			delete[] niz;
			return true;
		}
	}

	delete[] niz;
	return false;
}


void Korisnik::pisiKorisnika()
{
	std::cout << this->id << " " << this->ime << " " << this->prezime << " " << this->userName << " " << this->password << " " << this->tipNaloga << std::endl;
}

void Korisnik::pisiSveKorisnike(Korisnik** niz, int& duzina)
{
	std::ifstream filein("registrovaniKorisnici.txt", std::ios::out);
	Korisnik temp;
	duzina = 0;
	while (filein >> temp.id >> temp.ime >> temp.prezime >> temp.userName >> temp.password >> temp.tipNaloga)
	{
		if (temp.tipNaloga != 2)
		{
			(*niz)[duzina] = temp;
			duzina++;
			//temp.pisiKorisnika();
			std::cout << duzina << ". " << temp.id << " " << temp.ime << " " << temp.prezime << " " << temp.userName << " " << temp.password << " " << temp.tipNaloga << std::endl;

		}
	}
}

bool Korisnik::pretraziNiz(std::string niz[], std::string kljuc, int duzina)
{
	for (int i = 0; i < duzina; i++)
	{
		if (niz[i] == kljuc)
		{
			return true;
		}

	}
	return false;
}

void Korisnik::modifikujKorisnika(std::string user, Korisnik& pomocni)
{
	std::ifstream in("registrovaniKorisnici.txt", std::ios::in);
	std::ofstream out("temp.txt", std::ios::out | std::ios::app);
	Korisnik temp;
	while (in >> temp.id >> temp.ime >> temp.prezime >> temp.userName >> temp.password >> temp.tipNaloga)
	{
		if (user == temp.userName)
		{
			std::cout << "Unesite novo ime: ";
			std::cin >> temp.ime;
			std::cout << "Unesite novo prezime: ";
			std::cin >> temp.prezime;
			std::cout << "Unesite novu lozinku: ";
			std::cin >> temp.password;
			pomocni = temp;
		}
		out << temp.id << " " << temp.ime << " " << temp.prezime << " " << temp.userName << " " << temp.password << " " << temp.tipNaloga << std::endl;
	}
	in.close();
	out.close();
	remove("registrovaniKorisnici.txt");
	if (rename("temp.txt", "registrovaniKorisnici.txt"))
	{
		exit(0);
	}
}

void Korisnik::brisiIzGlavnogFajla(std::string userName)
{
	std::ifstream in1("registrovaniKorisnici.txt", std::ios::in);
	std::ofstream out1("temp.txt", std::ios::out | std::ios::app);
	Korisnik temp1;
	while (in1 >> temp1.id >> temp1.ime >> temp1.prezime >> temp1.userName >> temp1.password >> temp1.tipNaloga)
	{
		if (temp1.userName != userName)
		{
			out1 << temp1.id << " " << temp1.ime << " " << temp1.prezime << " " << temp1.userName << " " << temp1.password << " " << temp1.tipNaloga << std::endl;
		}
	}
	in1.close();
	out1.close();
	remove("registrovaniKorisnici.txt");
	if (rename("temp.txt", "registrovaniKorisnici.txt"))
	{
		exit(0);
	}
}

void Korisnik::smanjiBrojKorisnika()
{
	std::ifstream info("info.txt", std::ios::in);
	std::ofstream outinfo("temp.txt", std::ios::out | std::ios::app);
	int param;
	info >> param;
	param--;
	outinfo << param;
	info.close();
	outinfo.close();
	remove("info.txt");
	if (rename("temp.txt", "info.txt"))
	{
		exit(0);
	}
}

void Korisnik::operacijeNadKursevima(std::string username, void(*f)(std::string kurs, std::string userName))
{
	std::string fk = username + "Kursevi.txt", line;
	std::cout << fk;
	std::ifstream in3(fk, std::ios::in);
	std::ofstream out3("temp.txt", std::ios::out | std::ios::app);
	if (in3.is_open())
	{
		int brojac = 0;
		while (std::getline(in3, line))
		{
			//std::cout << brojac;
			if (brojac == 0)
			{
				brojac++;
			}
			else
			{
				(*f)(line, username);
				brojac++;
			}
		}
	}
	in3.close();
	out3.close();
	const char* c2 = fk.c_str();
	remove(c2);
}


Korisnik::~Korisnik()
{
}