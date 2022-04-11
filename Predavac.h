#pragma once
#include <string>
#include "Korisnik.h"
#include "Kurs.h"

class Predavac : public Korisnik
{
private:
	int brojKurseva;
	std::string *nazivKursa;
public:
	Predavac();
	Predavac(Korisnik other, int brojKurseva, std::string* nazivKursa);
	Predavac(int id, std::string ime, std::string prezime, std::string userName, std::string password, int brojKurseva, std::string* nazivKursa);
	Predavac(const Predavac& other);
	virtual void opcije() override;
	void opcijaZahtjevi();
	void opcijaSlanjePoruke();
	void opcijaCitanjePoruke();
	void opcijaFiltriranjePoruka();
	std::string* prihvatanjeZahtjeva(int &duzina, std::string** niz);
	static Predavac& nadjiPredavaca(std::string trazeni);
	static void prikaziPredavace(std::string** niz, int& duzina);
	void dodajKursPredavacu(std::string kurs);
	bool odgovarajuciKurs(std::string kurs);
	void upisUcenika(std::string ucenik, std::string kurs);
	static bool provjeraUpisa(std::string ucenik, std::string kurs);
	virtual void posaljiPoruku(std::string user) override;
	void prikaziKorisnike();
	void listaKurseva();
	void inbox();
	virtual void citajPoruku(std::string user) override;
	void filtrirajPoruku(std::string user);
	void pisiKorisnikaFajl();
	static void modifikujPredavaca(Korisnik other);
	static void brisiPredavaca(std::string userName);
	~Predavac();
};