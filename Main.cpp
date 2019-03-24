//the purpose of this program encoding in utf-8
//the menu gives a choice between:
//1)encoding an integer (symbol's unicode number) in utf-8 OR
//2)converting a pre-selected 386intel.txt file to utf-8
//the 386intel.txt is encoded using asc-II table 473 (for symbols 128-255)
//this program looks at the position(ints) of the symbols in 473 and switches them
//to their unicode positions (unicode ints).
//Then it encodes those numbers in utf-8 and writes that code as a char 1 byte at a time (2 hex digis = 8 bites)
//into a new file, completing the conversion
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>
#include <fstream>

using namespace std;

void hex_to_bin(vector <int>& v, string& s) {   // "konvertuoja" kiekviena hex symboli is vect i stringo dali ir sudeda i viena stringa
	for (int i = v.size() - 1; i >= 0; i--) {
		string curr = " ";
		switch (v[i]) {
		case 0:
			curr = "0000";
			s = s + curr;
			break;
		case 1:
			curr = "0001";
			s = s + curr;
			break;
		case 2:
			curr = "0010";
			s = s + curr;
			break;
		case 3:
			curr = "0011";
			s = s + curr;
			break;
		case 4:
			curr = "0100";
			s = s + curr;
			break;
		case 5:
			curr = "0101";
			s = s + curr;
			break;
		case 6:
			curr = "0110";
			s = s + curr;
			break;
		case 7:
			curr = "0111";
			s = s + curr;
			break;
		case 8:
			curr = "1000";
			s = s + curr;
			break;
		case 9:
			curr = "1001";
			s = s + curr;
			break;
		case 10:
			curr = "1010";
			s = s + curr;
			break;
		case 11:
			curr = "1011";
			s = s + curr;
			break;
		case 12:
			curr = "1100";
			s = s + curr;
			break;
		case 13:
			curr = "1101";
			s = s + curr;
			break;
		case 14:
			curr = "1110";
			s = s + curr;
			break;
		case 15:
			curr = "1111";
			s = s + curr;
			break;
		default:
			break;
		}

	}
}


void fillv(int x, vector <int>& v) {                   //isskaido dec skaiciu i hex skaitmenys ir uzraso i vektoriu
	for (int i = 0; i <100; i++) {                     //loopas pasibaigs tik tada kai nebus ka dalint is 16(x==0)
		v.push_back(x % 16);
		x = x / 16;
		if (x == 0) break;
	}
}

void fill_UNIFILE(int UNIFILE[128][2]) {              // uzpildo masyva UNIFILE  
	ifstream reader("473_to_Unicode.txt");

	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 2; j++) {
			reader >> UNIFILE[i][j];
		}
	}
	reader.close();
}




void string_to_int(string& s, string& finales, vector <int>& baigs) {   //konvertuoja utf-8 binary i hexa. 4bitai-1skaitmuo i vektoriu
	string curr;                                                        // rez charus pushbackina i stringa finales (1 uzduotys)
	char rez;                                                           // ivek intus pushbackina i vekt baigs (nauduoja 
	int ivek;
	for (int i = 0; i < s.size(); i += 4) {              //s stringe irasyta vienaa is byteX UTF-8 binary
		for (int j = i; j < i + 4; j++) {
			curr.push_back(s[j]);
		}
		if (curr == "0000") {
			rez = '0';
			ivek = 0;
		}                 //tiesiog konvertuoju i paprasta inta ir ji isvesiu kaip << hex << int
		else if (curr == "0001") {
			rez = '1';
			ivek = 1;
		}
		else if (curr == "0010") {
			rez = '2';
			ivek = 2;
		}
		else if (curr == "0011") {
			rez = '3';
			ivek = 3;
		}
		else if (curr == "0100") {
			rez = '4';
			ivek = 4;
		}
		else if (curr == "0101") {
			rez = '5';
			ivek = 5;
		}
		else if (curr == "0110") {
			rez = '6';
			ivek = 6;
		}
		else if (curr == "0111") {
			rez = '7';
			ivek = 7;
		}
		else if (curr == "1000") {
			rez = '8';
			ivek = 8;
		}
		else if (curr == "1001") {
			rez = '9';
			ivek = 9;
		}
		else if (curr == "1010") {
			rez = 'a';
			ivek = 10;
		}
		else if (curr == "1011") {
			rez = 'b';
			ivek = 11;
		}
		else if (curr == "1100") {
			rez = 'c';
			ivek = 12;
		}
		else if (curr == "1101") {
			rez = 'd';
			ivek = 13;
		}
		else if (curr == "1110") {
			rez = 'e';
			ivek = 14;
		}
		else if (curr == "1111") {
			rez = 'f';
			ivek = 15;
		}
		finales.push_back(rez);
		baigs.push_back(ivek);
		curr.clear();
	}
}



void cp437_to_uni(int UNIFILE[128][2], int& x) {           //  keicia x reiksme is cp437 i unicode
	for (int i = 0; i < 128; i++) {
		if (x == UNIFILE[i][0]) {
			x = UNIFILE[i][1];
			break;
		}


	}
}

string bin_to_utf8(string& s, int& x) {
	string byte1 = "00000000";               // inicializuoju kaip sablonus
	string byte2 = "1100000010000000";
	string byte3 = "111000001000000010000000";
	string byte4 = "11110000100000001000000010000000";
	int ats = 0;                            //// suzinoti kuri byteX grazint

	if (x <= 127) {
		if (s.size() == 4) {
			byte1 = "0000" + s;
		}
		else if (s.size() == 8) {
			byte1 = s;
		}
		ats = 1;
	}
	else if (x > 0x7f && x <= 0x7ff) {          // nuo 127 iki 2047
		if (s.size() == 8) {                   // jei bin skaiciu sudaro 8 digits
			for (int i = 7, j = 15; i > 1; i--, j--) {            // is 1 byte didzio irasome i 2 byte didi, i- original digit vieta, j- kur irasome i unocode byte
				byte2[j] = s[i];
			}
			for (int i = 1, j = 7; i >= 0; i--, j--) {									// s skaiciuje liko tik 2 skaitmenis, jas irasysime i nauja baita
				byte2[j] = s[i];
			}
		}
		else if (s.size() == 12) {                // int iki 2047 telpa i 12 bitu
			for (int i = 11, j = 15; i > 5; i--, j--) {                  // 6 skaitmenis
				byte2[j] = s[i];
			}
			for (int i = 5, j = 7; i > 0; i--, j--) {                    //5 skaitmenis
				byte2[j] = s[i];
			}
		}
		ats = 2;
	}
	else if (x > 0x7ff && x <= 0xffff) {   // nuo 2048 iki 65535
		if (s.size() == 12) {
			for (int i = 11, j = 23; i > 5; i--, j--) {             //6 i right
				byte3[j] = s[i];
			}
			for (int i = 5, j = 15; i >= 0; i--, j--) {              //6 i mid
				byte3[j] = s[i];
			}
		}
		else if (s.size() == 16) {
			for (int i = 15, j = 23; i > 9; i--, j--) {            // 6 skaitmenys i right
				byte3[j] = s[i];
			}
			for (int i = 9, j = 15; i > 3; i--, j--) {            // 6 skaitmenys i mid byte
				byte3[j] = s[i];
			}
			for (int i = 3, j = 7; i >= 0; i--, j--) {            //4 i left, paskutinis 
				byte3[j] = s[i];
			}
		}
		ats = 3;
	}
	else if (x > 0x10000 && x <= 0x10ffff) {
		if (s.size() == 20) {
			for (int i = 19, j = 31; i > 13; i--, j--) {
				byte4[j] = s[i];
			}
			for (int i = 13, j = 23; i > 7; i--, j--) {
				byte4[j] = s[i];
			}
			for (int i = 7, j = 15; i > 1; i--, j--) {
				byte4[j] = s[i];
			}
			for (int i = 1, j = 7; i >= 0; i--, j--) {
				byte4[j] = s[i];
			}
		}

		else if (s.size() == 24) {
			for (int i = 23, j = 31; i > 17; i--, j--) {
				byte4[j] = s[i];
			}
			for (int i = 17, j = 23; i > 11; i--, j--) {
				byte4[j] = s[i];
			}
			for (int i = 11, j = 15; i > 5; i--, j--) {
				byte4[j] = s[i];
			}
			for (int i = 5, j = 7; i > 2; i--, j--) {            //irasom 3 paskutinius
				byte4[j] = s[i];
			}
		}
		ats = 4;
	}

	if (ats == 1) return byte1;
	else if (ats == 2) return byte2;
	else if (ats == 3) return byte3;
	else if (ats == 4) return byte4;                   //reikia padaryt skaiciams virs 65535
}







int main() {
	int UNIFILE[128][2];            // cia eis visi cp 437 lenteles intai ir ju unikodo alternatyva (vienoje eiluteje)
	int menu;                       // pasirinkimas ivest ranka ar skaityt 386
	int x;                          // cin arba i ji irasynesim po chara is temp
	unsigned char temp;
	unsigned char temp2;             // po 1 eis visi bytes is 386
	vector <int> v;                 // i vec uzrasomas po 1 skaitmeni hex skaicius konvertuojamas is dec
	vector <int> baigs;
	string finales;                   // cia bus galutinis atsakymas utf-8 intais, jis isvedamas
	string s;                      // i sita stringa bus irasytas bin skaicius (dec->hex->bin)
	string utf8bin;                  // laikys rezultata is bin_to_utf reiksme binary forma
	ofstream writer("Converted 386intel.txt");

	cout << "Menu: " << '\n' << "1)Enter a symbols unicode position(int)" << '\n' << "2) Read symbols from 386intel.txt" << '\n';

	cin >> menu;
	if (menu == 1) {                         //isrynkta ivesti ranka
		while (true) {
			cout << "Enter an integer \n";
			cin >> x;
			fillv(x, v);                    // dec->hex
			hex_to_bin(v, s);               // hex->bin
			utf8bin = bin_to_utf8(s, x);      // gauna utf-8 reiksme binary formatu
			string_to_int(utf8bin, finales, baigs);     // baigs yra naudojamas atlikti 2 uzduoties dali
			cout << "UTF-8 code is ";
			cout << finales << '\n';                                     

			cout << '\n';
			baigs.clear();
			v.clear();                                              // "refreshinu" reiksmes
			s.clear();
			finales.clear();
			utf8bin.clear();
			cout << '\n';

		}
	}

	else if (menu == 2) {

		cout << "Reading simbols from 386intel.txt, please wait. . ." << '\n';
		fill_UNIFILE(UNIFILE);               //pildomas masyvas UNIFILE is 128-255 lenteles
		ifstream reader2("386intel.txt");

		while (temp = reader2.get(), reader2.good()) {     //iraso i unsigned temp chara po VIENA byte is 386intel
			x = temp;
			if (x>127) {                      // jei charo reiksme int virs 127...
				cp437_to_uni(UNIFILE, x);        // into x reiksme pakeicia pagal lentele
				fillv(x, v);                      // i v uzrasomas po 1 skaitmeni hex skaicius konvertuojamas is dec x
				hex_to_bin(v, s);                // convertuoja hex vectoriu i bin stringa

				utf8bin = bin_to_utf8(s, x);      // gauna utf-8 reiksme binary formatu
				string_to_int(utf8bin, finales, baigs);         // po funkcijos vfinal elementai bus skaiciai nuo 0 iki 15, representuojanti utf-8
				
																
				for (int i = 0; i < baigs.size(); i += 2) {            // ima hex skaicius is baigs, poromis konvertuoja (1 pora 1 byte)
					writer << (char)(baigs[i] * 16 + baigs[i + 1]);    // ir viska iraso i faila paprastais int skaiciais
				}
															
				baigs.clear();
				v.clear();                                              // "refreshinu" reiksmes
				s.clear();
				finales.clear();
				utf8bin.clear();
			}
			else {
				writer << temp;
			}




		}
	}

	else cout << "No such option!\n";
	writer.close();
}


