#include <stdio.h>
#include <stdbool.h>
void wyswietl(int mapa[9][9]) {
	int wers, kolumna;
	for (wers = 0; wers <= 8; wers++) {
		printf("  ");
		for (kolumna = 0; kolumna <= 8; kolumna++) {
			printf("%d", mapa[wers][kolumna]);
			if ((kolumna + 1) % 3 == 0) {
				printf(" ");
			}
			if ((kolumna + 1) % 9 == 0) {
				printf("\n");
			}
		}
		if ((wers + 1) % 3 == 0) {
			printf("\n");
		}
	}
	printf("===============\n===============\n");
}

bool sprzecznosc_w_wierszu(int mapa[9][9], int wers, int kolumna) {
	int sprawdzana_cyfra = mapa[wers][kolumna];
	if (sprawdzana_cyfra == 0) return false;
	for (int i = 0; i <= 8; i++) {
		if (kolumna != i) {
			if (sprawdzana_cyfra == mapa[wers][i]) return true;
		}
	}
	return false;
}
bool sprzecznosc_w_kolumnie(int mapa[9][9], int wers, int kolumna) {
	int sprawdzana_cyfra = mapa[wers][kolumna];
	if (sprawdzana_cyfra == 0) return false;
	for (int j = 0; j <= 8; j++) { 
		if (wers != j) {
			if (sprawdzana_cyfra == mapa[j][kolumna]) return true;
		}
	}
	return false;
}
bool sprzecznosc_w_bloku(int mapa[9][9], int wers, int kolumna) {
	int sprawdzana_cyfra = mapa[wers][kolumna];
	if (sprawdzana_cyfra == 0) return false;

	int blokxy[2]; //ocenia który kwadrat gdyby podzieliæ mape na bloki 3x3
	if (wers <= 2) blokxy[1] = 0;
	else if (wers <= 5) blokxy[1] = 1;
	else blokxy[1] = 2;
	if (kolumna <= 2) blokxy[0] = 0;
	else if (kolumna <= 5) blokxy[0] = 1;
	else blokxy[0] = 2;

	for (int w = 0; w <= 2; w++) { // sprawdzenie czy w bloku nie powtarza siê sprawdzana cyfra
		for (int k = 0; k <= 2; k ++) {
			if (((3 * blokxy[0]) + k) != kolumna && ((3 * blokxy[1]) + w) != wers) {
				if (sprawdzana_cyfra == mapa[(3 * blokxy[1]) + w][(3 * blokxy[0]) + k]) {
					return true;
				}
			}
		}
	}
	return false;
}
bool sprzecznosc(int mapa[9][9], int wers, int kolumna) {
	if (sprzecznosc_w_bloku(mapa, wers, kolumna) || sprzecznosc_w_kolumnie(mapa, wers, kolumna) || sprzecznosc_w_wierszu(mapa, wers, kolumna)) return true;
	else return false;
}

void sprzecznosc_gdziekolwiek(int mapa[9][9]) {
	for (int wers = 0; wers <= 8; wers++) {
		for (int kolumna = 0; kolumna <= 8; kolumna++) {
			if (sprzecznosc(mapa, wers, kolumna)) {
				printf("ZNALEZIONO SPRZECZNOSC, PROGRAM NIE DZIALA\n");
				printf("b³¹d w: %d, %d\n", wers, kolumna);
				return 1;
			}
		}
	}
}



int main() {
	int mapa[9][9] = { //nie polecam wpisywaæ losowych kombinacji ma³ej iloœci cyfr, istnieje dok³adnie 6,670,903,752,021,072,936,960 rozwi¹zañ sudoku bez podanej ¿adnej cyfry, gdyby podaæ tylko parê cyfr rowi¹zañ nadal bêd¹ miliardy.
						0, 0, 0,	0, 5, 6,	0, 9, 0,
						0, 5, 0,	4, 0, 0,	0, 0, 0,
						0, 6, 0,	3, 8, 0,	0, 4, 5,

						0, 0, 6,	0, 0, 0,	0, 0, 0,
						0, 0, 0,	0, 0, 0,	0, 2, 0,
						3, 0, 0,	0, 0, 0,	8, 0, 0,

						0, 0, 0,	0, 4, 0,	0, 3, 0,
						8, 0, 0,	7, 0, 3,	0, 0, 6,
						0, 0, 7,	8, 0, 5,	0, 0, 0
	};
	int czy_mozna_zmienic[9][9];
	for (int w = 0; w <= 8; w++) { // sprawdzenie czy pole jest ustalone z góry, czy do ustalenia
		for (int k = 0; k <= 8; k++) {
			if (mapa[w][k] != 0) czy_mozna_zmienic[w][k] = 0;
			else czy_mozna_zmienic[w][k] = 1;
		}
	}
	//	// tutaj siedzi ca³a logika 
	int znalezionych_rozwiazan = 0;
	int blad_w_poprzedniej = 0;
	int prob = 0;
	for (int w = 0; w <= 8; w++) {
		for (int k = 0; k <= 8; k++) {
			if (czy_mozna_zmienic[w][k] == 1) {
				for (int cyfra = 1; cyfra <= 9; cyfra++) {				
					if (blad_w_poprzedniej == 1) {

						cyfra = mapa[w][k] + 1;
						blad_w_poprzedniej = 0;
					}

					mapa[w][k] = cyfra;
					//printf("ilosc cyfr przetestowanych %d\n", prob);
					prob++;
					if (!sprzecznosc(mapa, w, k)) {
						break;
					}
					else if (cyfra == 9) {
						blad_w_poprzedniej = 1;
						mapa[w][k] = 0;
					}
				}
			}
			if(blad_w_poprzedniej == 1) {
				przepraszam: //tutaj program szuka poprzedniej cyfry któr¹ mo¿na zmieniæ
				if (false) {
					patoprogramowanie:
					k = 9;
					w = 8;
				}
				if (k == 0) {
					if (w == 0) {
						printf("Znaleziono wszystkie rozwiazania");
						return 0;
					}
					w--;
					k = 8;
				}
				else {
					k--;
				}
				if (czy_mozna_zmienic[w][k] == 0) {
					goto przepraszam;
				}
				if (mapa[w][k] == 9) {
					mapa[w][k] = 0;
					goto przepraszam;
				}
				k--;

			}
		}
	}
	//	//
	
		znalezionych_rozwiazan++;
		printf("rozwiazanie %d:\n", znalezionych_rozwiazan);
		wyswietl(mapa);
		sprzecznosc_gdziekolwiek(mapa);
		blad_w_poprzedniej = 1;
		goto patoprogramowanie; //nie chcia³o mi siê tego tak formatowaæ by nie musieæ u¿ywaæ goto


	return 0;

}

