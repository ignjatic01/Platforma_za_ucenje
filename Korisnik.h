#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Korisnik
{
protected:
	int id;
	int tipNaloga;
	std::string ime;
	std::string prezime;
	std::string userName;
	std::string password;
public:
	Korisnik(int id = 0, int tipNaloga=0, std::string ime = "Default", std::string prezime = "Default", std::string userName = "err", std::string password = "err");
	Korisnik(const Korisnik& other);
	std::string getName();
	std::string getSurr();
	std::string getPass();
	int getType();
	std::string getUserName();
	virtual void opcije();
	void setUserName(std::string user);
	void registrujKorisnika();
	void pisiKorisnikaFajl();
	static void citajKorisnikaFajl();
	void prijavaKorisnika();
	static Korisnik* fromFileToArr();
	bool isUserValid();
	bool isUserNameExist();
	virtual void posaljiPoruku(std::string user);
	virtual void citajPoruku(std::string user);
	static bool isUserExist(std::string user);
	virtual void pisiKorisnika();
	void pisiSveKorisnike(Korisnik** niz, int& duzina);
	static bool pretraziNiz(std::string niz[], std::string kljuc, int duzina);
	void modifikujKorisnika(std::string user, Korisnik& pomocni);
	static void brisiIzGlavnogFajla(std::string username);
	static void smanjiBrojKorisnika();
	static void operacijeNadKursevima(std::string username, void(*f)(std::string kurs, std::string userName));
	~Korisnik();
};

static bool statusPrijave = false;