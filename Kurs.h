#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Predavac.h"

class Kurs
{
private:
	std::string imeKursa;
	int brojBodova;
	std::string* polaznici;
	int brojPolaznika;
	std::string predavacKursa;
public:
	Kurs();
	Kurs(std::string imeKursa, std::string predavacKursa, std::string* polaznici = nullptr, int brojBodova = 0, int brojPolaznika=0);
	void pisiKursFajl();
	void dodajPolaznika(std::string user);
	static void pisiKurseve(Kurs** niz, int& duzina);
	void pisiKurs();
	std::string getImeKursa();
	static void brisiKurs(std::string imeKursa);
	static void brisiKursKorisnicima(std::string imeKursa, std::string user);
	static void modifikujKurs(std::string kurs, std::string userName);
	static void zamjeniPredavaca(std::string kurs, Kurs& temp);
	//static void zamjeniPredavacaPom(std::string kurs, std::string username);
	~Kurs();
};