#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);


Asema::Asema()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_lauta[i][j] = nullptr;
		}
	}

	// Valkoiset nappulat
	_lauta[0][1] = vs;
	_lauta[1][1] = vs;
	_lauta[2][1] = vs;
	_lauta[3][1] = vs;
	_lauta[4][1] = vs;
	_lauta[5][1] = vs;
	_lauta[6][1] = vs;
	_lauta[7][1] = vs;

	_lauta[0][0] = vt;
	_lauta[1][0] = vr;
	_lauta[2][0] = vl;
	_lauta[3][0] = vd;
	_lauta[4][0] = vk;
	_lauta[5][0] = vl;
	_lauta[6][0] = vr;
	_lauta[7][0] = vt;

	//// Mustat nappulat
	_lauta[0][6] = ms;
	_lauta[1][6] = ms;
	_lauta[2][6] = ms;
	_lauta[3][6] = ms;
	_lauta[4][6] = ms;
	_lauta[5][6] = ms;
	_lauta[6][6] = ms;
	_lauta[7][6] = ms;

	_lauta[0][7] = mt;
	_lauta[1][7] = mr;
	_lauta[2][7] = ml;
	_lauta[3][7] = md;
	_lauta[4][7] = mk;
	_lauta[5][7] = ml;
	_lauta[6][7] = mr;
	_lauta[7][7] = mt;
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa

	// Asetetaan alkuaseman mukaisesti nappulat ruuduille
	
}


void Asema::paivitaAsema(Siirto *siirto)
{

	

	// Kaksoisaskel-lippu on oletusarvoisesti pois päältä.
	// Asetetaan myöhemmin, jos tarvii.


	//Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna()) { // Toimii hämärästi. Pitää selvittää miksi
		Nappula* vTorni = _lauta[7][1];
		Nappula* vKunkku = _lauta[4][0];
		Nappula* temp = vTorni;
		vTorni = vKunkku;
		vKunkku = temp;
	}

	// onko pitkä linna
	else if (siirto->onkoPitkälinna()) {

	}


	// Otetaan talteen se nappula, joka sijaitsee siirron LÄHTÖRUUDUSSA	
	Nappula* kakka = _lauta[siirto->getAlkuruutu().getSarake()][siirto->getAlkuruutu().getRivi()];

	// Nyt tyhjennetään edellämainittu ruutu
	_lauta[siirto->getAlkuruutu().getSarake()][siirto->getAlkuruutu().getRivi()] = NULL;

	// Pistetään ylempänä säästetty nappula siihen ruutuun, johon siirron on tarkoitus päättyä
	_lauta[siirto->getLoppuruutu().getSarake()][siirto->getLoppuruutu().getRivi()] = kakka;

	// Joka ikisen nappulan siirtämisen aikana tarkistetaan, oliko kyseessä jonkin tornin
	// siirtäminen. Jos jokin torneista siirtyy, Asema-luokka muistaa sen pelin loppuun asti.
	// Jokainen seuraavista pätkistä suoritetaan vain kyseisen tornin ENSIMMÄISELLÄ siirtokerralla.
	if (!getOnkoValkeaDTliikkunut() &&(kakka == vt) && (siirto->getAlkuruutu().getSarake() == 0)) {
		_onkoValkeaDTliikkunut = true;
		std::wcout << "Valkea kuningatteren puolen torni liikkui\n";
	}
	else if (!getOnkoMustaDTliikkunut() && (kakka == mt) && (siirto->getAlkuruutu().getSarake() == 0)) {
		_onkoMustaDTliikkunut = true;
		std::wcout << "Musta kuningatteren puolen torni liikkui\n";
	}
	else if (!getOnkoValkeaKTliikkunut() && (kakka == vt) && (siirto->getAlkuruutu().getSarake() == 7)) {
		_onkoValkeaKTliikkunut = true;
		std::wcout << "Valkea kuninkaan puolen torni liikkui\n";
	}
	else if (!getOnkoMustaKTliikkunut() && (kakka == mt) && (siirto->getAlkuruutu().getSarake() == 7)) {
		_onkoMustaKTliikkunut = true;
		std::wcout << "Musta kuninkaan puolen torni liikkui\n";
	}
	// Tarkkaillaan vielä kuninkaiden liikkumista.
	else if (!getOnkoMustaKuningasLiikkunut() && (kakka == mk) && (siirto->getAlkuruutu().getSarake() == 4)) {
		_onkoMustaKuningasLiikkunut = true;
		std::wcout << "Musta kuningas liikkui\n";
	}
	else if (!getOnkoValkeaKuningasLiikkunut() && (kakka == vk) && (siirto->getAlkuruutu().getSarake() == 4)) {
		_onkoValkeaKuningasLiikkunut = true;
		std::wcout << "Valkea kuningas liikkui\n";
	}
	// Kaikki muut siirrot


		//Ottaa siirron alkuruudussa olleen nappulan talteen 


		//Laittaa talteen otetun nappulan uuteen ruutuun


		// Tarkistetaan oliko sotilaan kaksoisaskel
		// (asetetaan kaksoisaskel-lippu)

		// Ohestalyönti on tyhjään ruutuun. Vieressä oleva (sotilas) poistetaan.

		//// Katsotaan jos nappula on sotilas ja rivi on päätyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittymän laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?

		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta lähtenyt nappula

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille väreille)

		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille väreille ja molemmille torneille)

	//päivitetään _siirtovuoro

}



int Asema::getSiirtovuoro() 
{
	return _siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro) 
{
	_siirtovuoro = vuoro;
	
}


bool Asema::getOnkoValkeaKuningasLiikkunut() 
{

	if (_onkoValkeaKuningasLiikkunut) {
		return _onkoValkeaKuningasLiikkunut;
	}
	else {
		return false;
	}
}


bool Asema::getOnkoMustaKuningasLiikkunut() 
{
	return _onkoMustaKuningasLiikkunut;
}


bool Asema::getOnkoValkeaDTliikkunut() 
{
	if (_onkoValkeaDTliikkunut) {
		return _onkoValkeaDTliikkunut;
	}
	else {
		return false;
	}
}


bool Asema::getOnkoValkeaKTliikkunut() 
{
	return _onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaDTliikkunut() 
{
	return _onkoMustaDTliikkunut;
}


bool Asema::getOnkoMustaKTliikkunut() 
{
	return _onkoMustaKTliikkunut;
}


/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
Lähetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyvä että kunigas g1 tai b1/c1
Loppupelissä vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla estämässä vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitkiä linjoja daami, torni ja lähetti
*/
double Asema::evaluoi() 
{
	return 0;

	//kertoimet asetettu sen takia että niiden avulla asioiden painoarvoa voidaan säätää helposti yhdestä paikasta
	
	//1. Nappuloiden arvo
	
	//2. Kuningas turvassa
	
	//3. Arvosta keskustaa
	
	// 4. Arvosta linjoja
	
}


double Asema::laskeNappuloidenArvo(int vari) 
{
	return 0;
	
}


bool Asema::onkoAvausTaiKeskipeli(int vari) 
{
	return 0;
	// Jos upseereita 3 tai vähemmän on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami jäljellä
	
	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
	

}


double Asema::nappuloitaKeskella(int vari) 
{
	return 0;

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa
	
	//valkeille ydinkeskusta

	
	
	//valkeille laitakeskusta
	


	//mustille ydinkeskusta
	
	//mustille laitakeskusta
	
}


double Asema::linjat(int vari) 
{
	return 0;
	
	//valkoiset
	
	//mustat
	
}


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lisäsin parametrina aseman)
//int maxi(int depth, asema a) 
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

//int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.
	
	// Rekursion kantatapaus 1: peli on loppu
	
	// Rekursion kantatapaus 2: katkaisusyvyydessä
	
	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	
	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{

	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari) 
{ 
	
}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) {
	
}
