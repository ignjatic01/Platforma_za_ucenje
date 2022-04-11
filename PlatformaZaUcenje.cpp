#include "Korisnik.h"
#include "Kurs.h"
#include "Predavac.h"
#include "Ucenik.h"
#include "Administrator.h"

int main()
{
	std::cout << "Dobar dan i dobro dosli!" << std::endl;
	int param1;
	static Korisnik trenutni;
login:
	system("CLS");
	do {
		std::cout << "Izaberite opciju [0] za prijavu na platformu ili [1] za registraciju" << std::endl;
		std::cin >> param1;
	} while (param1 < 0 || param1>1);
	if (param1)
	{
		try 
		{
			
			trenutni.registrujKorisnika();
			if (trenutni.getType() == 1)
			{
				std::string index;
				std::cout << "Unesi index: ";
				std::cin >> index;
				Ucenik novi(trenutni, index, 0, nullptr, 0, nullptr);
				novi.pisiUcenikaFajl();
			}
			else if (trenutni.getType() == 0)
			{
				std::string imeKursa;
				std::string predavac = trenutni.getUserName();
				int brojBodova;
				std::cout << "Unesi ime kursa: ";
				std::cin >> imeKursa;
				std::cout << "Unesi broj bodova: ";
				std::cin >> brojBodova;
				Kurs noviKurs(imeKursa, predavac, nullptr, brojBodova, 0);
				noviKurs.pisiKursFajl();
				std::string niz[1] = { noviKurs.getImeKursa() };
				Predavac noviPredavac(trenutni, 1, niz);
				noviPredavac.pisiKorisnikaFajl();
				noviPredavac.dodajKursPredavacu(imeKursa);
			}
			/*else if (trenutni.getType() == 2)
			{
				Administrator noviAdministrator(trenutni);
				noviAdministrator.pisiAdminaFajl();
			}*/
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			exit(0);
		}
		statusPrijave = true;
	}
	else
	{
		try {
			trenutni.prijavaKorisnika();
		}
		catch (int)
		{
			std::cout << "Prekoracili ste dozvoljeni broj pokusaja";
			exit(0);
		}
		statusPrijave = true;
	}
	//Korisnik::citajKorisnikaFajl();
	system("CLS");
	std::string ime = trenutni.getName();
	std::cout << "Dobro dosao "<<ime<<std::endl;
	int type = trenutni.getType();
	switch (type)
	{
		case 0:
		{
pocP:		system("CLS");
			std::string other = trenutni.getUserName();
			Predavac predavac = Predavac::nadjiPredavaca(other);
			predavac.opcije();
			int a;
			std::cin >> a;
			switch (a)
			{
				case 1:
				{
					predavac.listaKurseva();
					break;
				}
				case 2:
				{
					predavac.opcijaZahtjevi();
					break;
				}
				case 3:
				{
					predavac.opcijaSlanjePoruke();
					break;
				}
				case 4:
				{
					predavac.opcijaCitanjePoruke();
					break;
				}
				case 5:
				{
					predavac.opcijaFiltriranjePoruka();
					break;
				}
				case 6:
				{
					goto login;
					break;
				}
				default:
					break;
			}
			std::cout << "Zelite li jos neku opciju y/n? ";
			char c;
			std::cin >> c;
			if (c == 'y')
				goto pocP;
			break;
		}
		case 1:
		{
pocU:		system("CLS");
			std::string other = trenutni.getUserName();
			Ucenik ucenik = Ucenik::nadjiUcenika(other);
			ucenik.opcije();
			int a;
			std::cin >> a;
			switch (a)
			{
				case 1:
				{
					ucenik.lista(0);
					break;
				}
				case 2:
				{
					ucenik.lista(1);
					break;
				}
				case 3:
				{
					ucenik.opcijaZahtjevPrijateljstvo();
					break;
				}
				case 4:
				{
					std::string arg;
					ucenik.opcijePrihvatanjePrijateljstva(arg);
					try
					{
						ucenik.novoPrijateljstvo(arg);
					}
					catch (std::exception& e)
					{
						std::cerr << e.what() << std::endl;
						return -1;
					}
					break;
				}
				case 5:
				{
					ucenik.lista(0);
					std::string primalac;
					std::cout << "Unesite korisnika kojem zelite poslati poruku: "; 
					std::cin >> primalac;
					try
					{
						if(!ucenik.postojanjePrijatelja(primalac))
							throw std::exception("Birani korisnik Vam nije prijatelj");
						ucenik.posaljiPoruku(primalac);
					}
					catch (std::exception& e)
					{
						std::cerr << e.what() << std::endl;
						exit(0);
					}
					break;
				}
				case 6:
				{
					ucenik.opcijeCitanjePoruke();
					break;
				}
				case 7:
				{
					ucenik.opcijeZahtjviKurs();
					break;
				}
				case 8:
				{
					ucenik.opcijePorukePredavacu();
					break;
				}
				case 9:
				{
					ucenik.opcijeFiltriranjePoruka();
					break;
				}
				case 10:
				{
					goto login;
					break;
				}
				default:
					break;
			}
			//delete &ucenik;
			std::cout << "Zelite li jos neku opciju y/n? ";
			char c;
			std::cin >> c;
			if (c == 'y')
				goto pocU;
			break;
		}
		case 2:
		{
pocA:		system("CLS");
			Administrator admin(trenutni);
			admin.opcije();
			int a;
			std::cin >> a;
			switch (a)
			{
				case 1:
				{
					Korisnik arg;
					admin.opcijeNadNalozima(arg);
					int b;
					std::cin >> b;
					switch (b)
					{
						case 1:
						{
							int tipNaloga = arg.getType();
							if (tipNaloga == 1)
							{
								try
								{
									Ucenik::brisiUcenika(arg.getUserName());
								}
								catch (std::exception& e)
								{
									std::cerr << e.what() << std::endl;
								}
							}
							else if (tipNaloga == 0)
							{
								Predavac::brisiPredavaca(arg.getUserName());
							}
							break;
						}
						case 2:
						{
							Korisnik pomocni;
							trenutni.modifikujKorisnika(arg.getUserName(), pomocni);
							if (pomocni.getType())
							{
								Ucenik::modifikujKorisnika(pomocni);
							}
							else
							{
								Predavac::modifikujPredavaca(pomocni);
							}
							break;
						}
					default:
						break;
					}
					break;
				}
				case 2:
				{
					trenutni.registrujKorisnika();
					if (trenutni.getType() == 1)
					{
						std::string index;
						std::cout << "Unesi index: ";
						std::cin >> index;
						Ucenik novi(trenutni, index, 0, nullptr, 0, nullptr);
						novi.pisiUcenikaFajl();
					}
					else if (trenutni.getType() == 0)
					{
						std::string imeKursa;
						std::string predavac = trenutni.getUserName();
						int brojBodova;
						std::cout << "Unesi ime kursa: ";
						std::cin >> imeKursa;
						std::cout << "Unesi broj bodova: ";
						std::cin >> brojBodova;
						Kurs noviKurs(imeKursa, predavac, nullptr, brojBodova, 0);
						noviKurs.pisiKursFajl();
						std::string niz[1] = { noviKurs.getImeKursa() };
						Predavac noviPredavac(trenutni, 1, niz);
						noviPredavac.pisiKorisnikaFajl();
						noviPredavac.dodajKursPredavacu(imeKursa);
					}
					break;
				}
				case 3:
				{
					Kurs arg;
					admin.opcijeNadKursevima(arg);
					int b;
					std::cin >> b;
					switch (b)
					{
						case 1:
						{
							Kurs::brisiKurs(arg.getImeKursa());
							break;
						}
						case 2:
						{
							std::string pom;
							Kurs::modifikujKurs(arg.getImeKursa(), pom);
							break;
						}
						default:
							break;
					}
					break;
				}
				case 4:
				{
					std::string naziv, predavac, * niz = new std::string[20];
					int broj, duzina = 0;
					std::cout << "Unesite ime kursa" << std::endl;
					std::cin >> naziv;
					std::cout << "Unesite broj ECTS bodova" << std::endl;
					std::cin >> broj;
					std::cout << "odaberite jednog od registrovanih predavaca:" << std::endl;
					Predavac::prikaziPredavace(&niz, duzina);
					static int unos;
					do
					{
						std::cout << "Unesite redni broj korisnika kojeg zelite mijenjati: ";
						std::cin >> unos;
					} while (unos > duzina || unos < 1);
					std::string noviPredavac = niz[unos - 1];
					Kurs noviKurs(naziv, noviPredavac, nullptr, broj, 0);
					noviKurs.pisiKursFajl();
					Predavac *predavacKursa = new Predavac;
					*predavacKursa = Predavac::nadjiPredavaca(noviPredavac);
					(*predavacKursa).pisiKorisnika();
					(*predavacKursa).dodajKursPredavacu(naziv);
					delete[] niz;
					delete predavacKursa;
					break;
				}
				case 5:
				{
					Kurs arg1, arg2;
					admin.opcijePoredjenjaKurseva(arg1, arg2);
					int a;
					std::cin >> a;
					switch (a)
					{
						case 1:
						{
							admin.ispisiUniju(arg1.getImeKursa(), arg2.getImeKursa());
							break;
						}
						case 2:
						{
							admin.ispisiPresjek(arg1.getImeKursa(), arg2.getImeKursa());
							break;
						}
						case 3:
						{
							admin.ispisiRazliku(arg1.getImeKursa(), arg2.getImeKursa());
							break;
						}
						default:
							break;
					}
					break;
				}
				case 6:
				{
					admin.matricaPoznanstva();
					break;
				}
				case 7:
				{
					goto login;
					break;
				}
			}

			std::cout << "Zelite li jos neku opciju y/n? ";
			char c;
			std::cin >> c;
			if (c == 'y')
				goto pocA;
			break;
			break;
		}
		default:
			break;
	}
}
