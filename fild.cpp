#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "chess.h"
using namespace std;

void creationErrors(YourNeighbors neighbors, vector<char> names) {
	for (int i = 0; i<int(neighbors.coordinate.size()); i++) for (int j = i + 1; j<int(neighbors.coordinate.size()); j++)
		if (neighbors.coordinate[i] == neighbors.coordinate[j]) {
			cout << "Была попытка поставить фигуру на занятую клетку!" << endl;
			throw error();
		}
	int kolvoNames[2][6] = { {0,0,0,0,0,0}, {0,0,0,0,0,0} };
	char namesNumber[6] = { 'K', 'Q', 'R', 'B','N', 'p' };
	for (int i = 0; i<int(names.size()); i++) for (int j = 0; j < 6; j++)
		if (namesNumber[j] == names[i]) kolvoNames[neighbors.white[i]][j]++;
	if (kolvoNames[0][0] == 0 || kolvoNames[0][0] > 1 || kolvoNames[1][0] == 0 || kolvoNames[1][0] > 1) { cout << "Ошибка количества королей на поле!" << endl; throw error(); }
	if (kolvoNames[0][1] > 1 || kolvoNames[1][1] > 1) { cout << "Превышение количества ферзей на поле!" << endl; throw error(); }
	if (kolvoNames[0][5] > 8 || kolvoNames[1][5] > 8) { cout << "Превышение количества пешек на поле!" << endl; throw error(); }
	for (int i = 2; i < 5; i++) if (kolvoNames[0][i] > 2 || kolvoNames[1][i] > 2) { cout << "Превышение количества фигур на поле!" << endl; throw error(); }
}
void playingField::readFiguresFromFile(const char* fileName) {
	ifstream in(fileName);
	if (!in.is_open()) {
		cout << "Выбранный вами файл не может быть открыт или несуществует!" << endl;
		throw error();
	}
	string text = "none";
	char simbol[4];
	int colvo;
	bool White;
	vector<char> names;
	YourNeighbors neighbors;
	while (!in.eof()) {
		if (text != "Black:") in >> text;
		if (text == "White:") White = true;
		else White = false;
		in >> colvo;
		int i = 0;
		while (i != colvo && !in.eof()) {
			in >> text;
			if (text == "Black:") break;
			for (int j = 0; j < 3; j++)
				simbol[j] = text[j];
			if (simbol[0] == 'K') { King king(White); King* figure = new King(king); figures.push_back(figure); }
			if (simbol[0] == 'Q') { Queen queen(White); Queen* figure = new Queen(queen); figures.push_back(figure); }
			if (simbol[0] == 'R') { Rook rook(White); Rook* figure = new Rook(rook); figures.push_back(figure);}
			if (simbol[0] == 'B') { Bishop bishop(White); Bishop* figure = new Bishop(bishop); figures.push_back(figure); }
			if (simbol[0] == 'N') { Knight knight(White); Knight* figure = new Knight(knight); figures.push_back(figure); }
			if (simbol[0] == 'p') { Pount pount(White); Pount* figure = new Pount(pount); figures.push_back(figure); }
			Coordinate coordinate(simbol[1] - 'A', simbol[2] - '0' - 1);
			neighbors.name.push_back(simbol[0]);
			neighbors.coordinate.push_back(coordinate);
			neighbors.white.push_back(White);
			names.push_back(simbol[0]);
		}
	}
	creationErrors(neighbors, names);
	for (int i = 0; i<int(figures.size()); i++) figures[i]->create(neighbors, i);
}
playingField& playingField::recreatingField(const playingField& fild, const int whoAmI, const Coordinate whereYouWantPutIt, bool regim) {
	figures.clear();
	YourNeighbors neighbors;
	for (int i = 0; i < int(fild.figures.size()); i++)
		if (i != whoAmI && fild.figures[i]->whereAmI() != whereYouWantPutIt) {
			figures.push_back(fild.figures[i]);
			neighbors.coordinate.push_back(fild.figures[i]->whereAmI());
			neighbors.name.push_back(fild.figures[i]->name());
			neighbors.white.push_back(fild.figures[i]->White());
		}	
	if (fild.figures[whoAmI]->name() == 'K') { King king(fild.figures[whoAmI]->White()); King* figure = new King(king); figures.push_back(figure); }
	if (fild.figures[whoAmI]->name() == 'Q') { Queen queen(fild.figures[whoAmI]->White()); Queen* figure = new Queen(queen); figures.push_back(figure); }
	if (fild.figures[whoAmI]->name() == 'R') { Rook rook(fild.figures[whoAmI]->White()); Rook* figure = new Rook(rook); figures.push_back(figure); }
	if (fild.figures[whoAmI]->name() == 'B') { Bishop bishop(fild.figures[whoAmI]->White()); Bishop* figure = new Bishop(bishop); figures.push_back(figure); }
	if (fild.figures[whoAmI]->name() == 'N') { Knight knight(fild.figures[whoAmI]->White()); Knight* figure = new Knight(knight); figures.push_back(figure); }
	if (fild.figures[whoAmI]->name() == 'p') { Pount pount(fild.figures[whoAmI]->White()); Pount* figure = new Pount(pount); figures.push_back(figure); }
	neighbors.coordinate.push_back(whereYouWantPutIt);
	neighbors.name.push_back(fild.figures[whoAmI]->name());
	neighbors.white.push_back(fild.figures[whoAmI]->White());
	for (int i = 0; i<int(figures.size()); i++) figures[i]->create(neighbors, i);
	return *this;
}

bool playingField::addressNoBusy(Coordinate coordinate, int whatFigure, bool whiteOrBlack = false) {
	for (int i = 0; i<int(figures.size()); i++) for (int j = 0; j<int(figures[i]->addressesSize()); j++) {
		if (i != whatFigure && ((figures[i]->White()!=whiteOrBlack && figures[i]->getAddress(j) == coordinate) || (figures[i]->White() == whiteOrBlack && figures[i]->whereAmI() == coordinate))) return false;
	}
	return true;
}
bool playingField::whiteAttacks(Coordinate coordinate, int whatFigure, bool whiteOrBlack = false) {
	for (int i = 0; i<int(figures.size()); i++) for (int j = 0; j<int(figures[i]->addressesSize()); j++) {
		if (i != whatFigure && figures[i]->White()!=whiteOrBlack  && figures[i]->getAddress(j) == coordinate) return true;
	}
	return false;
}
bool playingField::placeOccupied(Coordinate coordinate, int whatFigure) {
	for (int i = 0; i<int(figures.size()); i++) for (int j = 0; j<int(figures[i]->addressesSize()); j++) {
		if (i != whatFigure && figures[i]->White() == figures[whatFigure]->White() && figures[i]->whereAmI() == coordinate) return false;
	}
	return true;
}
bool playingField::placeOccupiedPoints(Coordinate coordinate, int whatFigure) {
	for (int i = 0; i<int(figures.size()); i++) for (int j = 0; j<int(figures[i]->addressesSize()); j++) {
		if (figures[whatFigure]->name() == 'p' && (coordinate.x == figures[whatFigure]->whereAmI().x - 1 || coordinate.x == figures[whatFigure]->whereAmI().x + 1) && coordinate == figures[i]->whereAmI()) return true;
	}
	return false;
}

bool playingField::endGame(bool whiteOrBlack) {
	int king = -1;

	for (int i = 0; i<int(figures.size()); i++) if (figures[i]->White() == whiteOrBlack && figures[i]->name() == 'K') king = i;
	if (king == -1) return false;
	for (int i = 0; i<int(figures[king]->addressesSize()); i++) if (addressNoBusy(figures[king]->getAddress(i), king)) return false;
	for (int i = 0; i<int(figures[king]->addressesSize()); i++) if (whiteAttacks(figures[king]->getAddress(i), king)) return true;
	return false;
}

void playingField::findFiguresWhoKillKing(vector<char>& put) {
	int king = -1;
	for (int i = 0; i<int(figures.size()); i++) if (!figures[i]->White() && figures[i]->name() == 'K') { king = i; break; }
	if (king != -1)
		for (int i = 0; i<int(figures.size()); i++) for (int j = 0; j<int(figures[i]->addressesSize()); j++)
			if (i != king && figures[i]->White() && figures[king]->whereAmI() == figures[i]->getAddress(j)) {
				put.push_back(figures[i]->name());
				put.push_back(figures[i]->getAddress(j).x + 'A');
				put.push_back(figures[i]->getAddress(j).y + 1 + '0');
				put.push_back(';'); put.push_back(' ');
			}
}
bool playingField::kingCanDead() {
	int king = -1;
	for (int i = 0; i<int(figures.size()); i++) if (!figures[i]->White() && figures[i]->name() == 'K') { king = i; break; }
	if (king == -1) return false;
	for (int i = 0; i<int(figures.size()); i++) for (int j = 0; j<int(figures[i]->addressesSize()); j++)
		if (i != king && figures[i]->White() && figures[king]->whereAmI() == figures[i]->getAddress(j))
			return true;
	return false;
}
bool playingField::whiteKingSave() {
	int king = -1;
	for (int i = 0; i<int(figures.size()); i++) if (figures[i]->White() && figures[i]->name() == 'K') { king = i; break; }
	if (king == -1) return false;
	for (int i = 0; i<int(figures.size()); i++) for (int j = 0; j<int(figures[i]->addressesSize()); j++)
		if (i != king && !figures[i]->White() && figures[king]->whereAmI() == figures[i]->getAddress(j))
			return false;
	return true;
}
void matVDva(char* inFileName, char* outFileName) {

	ofstream out(outFileName);
	vector<char> put;
	playingField fild, fild1, fild2;
	bool onceHod = false;

	cout << "Программа работает..." << endl;

	fild.readFiguresFromFile(inFileName);

	if (fild.kingCanDead() || fild.endGame()) {
		cout << "Ошибка данных! король уже находится в матовой позиции." << endl;
		throw error();
	}

	for (int i = 0; i<int(fild.figures.size()); i++) if (fild.figures[i]->White()) for (int j = 0; j< int(fild.figures[i]->addressesSize()); j++)
		if (fild.placeOccupied(fild.figures[i]->getAddress(j), i) && (fild.figures[i]->name()!='p' || (fild.placeOccupiedPoints(fild.figures[i]->getAddress(j), i) || fild.figures[i]->getAddress(j).x == fild.figures[i]->whereAmI().x)) ) {
			
			bool onceChance = false;
			put.clear();
			put.push_back(fild.figures[i]->name());
			put.push_back(fild.figures[i]->getAddress(j).x + 'A');
			put.push_back(fild.figures[i]->getAddress(j).y + 1 + '0');
			put.push_back(':');
		
			fild1.recreatingField(fild, i, fild.figures[i]->getAddress(j), true);
			for (int i1 = 0; i1<int(fild1.figures.size()); i1++) if (!fild1.figures[i1]->White()) for (int j1 = 0; j1< int(fild1.figures[i1]->addressesSize()); j1++)
				if (fild1.placeOccupied(fild1.figures[i1]->getAddress(j1), i1) && (fild1.figures[i1]->name() != 'p' || (fild1.placeOccupiedPoints(fild1.figures[i1]->getAddress(j1), i1) || fild1.figures[i1]->getAddress(j1).x == fild1.figures[i1]->whereAmI().x))) {
			
					fild2.recreatingField(fild1, i1, fild1.figures[i1]->getAddress(j1), true);
			
					if (analizNaMat(put, fild2, fild1.figures[i1]->name(), fild1.figures[i1]->getAddress(j1).x, fild1.figures[i1]->getAddress(j1).y)) {
						onceChance = true;
					}
				}
			if (onceChance) {
				put.push_back('\n');
				for (int u = 0; u< int(put.size()); u++) cout << put[u];
				cout << endl;
				for (int u = 0; u< int(put.size()); u++) out << put[u];
				out << "\n";
				onceHod = true;
			}
			else { cout << "."; }
		}
	cout << "Конец работы программы." << endl;

	out.close();

}

bool analizNaMat(vector<char>& puts, playingField fild, char name, int bukva, int number) {
	playingField fil2, fil3;
	vector<char> put;
	bool onesChance = false;

	for (int i = 0; i<int(fild.figures.size()); i++) if (fild.figures[i]->White()) for (int j = 0; j< int(fild.figures[i]->addressesSize()); j++)
		if (fild.placeOccupied(fild.figures[i]->getAddress(j), i) && (fild.figures[i]->name() != 'p' || (fild.placeOccupiedPoints(fild.figures[i]->getAddress(j), i) || fild.figures[i]->getAddress(j).x == fild.figures[i]->whereAmI().x))) {
			int option = true;

			fil2.recreatingField(fild, i, fild.figures[i]->getAddress(j), true); //сдвигаем одну из фигур на одну из её возможных координат

			if ((fil2.kingCanDead() || fil2.endGame()) && !fil2.endGame(true) && fil2.whiteKingSave()) {
				for (int i1 = 0; i1<int(fil2.figures.size()); i1++) if (!fil2.figures[i1]->White()) for (int j1 = 0; j1< int(fil2.figures[i1]->addressesSize()); j1++)
					if (fil2.placeOccupied(fil2.figures[i1]->getAddress(j1), i1) && (fil2.figures[i1]->name() != 'p' || (fil2.placeOccupiedPoints(fil2.figures[i1]->getAddress(j1), i1) || fil2.figures[i1]->getAddress(j1).x == fil2.figures[i1]->whereAmI().x))) {

						fil3.recreatingField(fil2, i1, fil2.figures[i1]->getAddress(j1)); //регестрируем ещё один ход для определения угрожающей королю фигуры

						if (!fil3.kingCanDead()) { option = false;  break; }

						fil3.findFiguresWhoKillKing(put);
					}
				if (option) { //если король точно может быть убит выдаём полученный вектор символов в файл
					put.clear();
					put.push_back(fild.figures[i]->name());
					put.push_back(fild.figures[i]->getAddress(j).x + 'A');
					put.push_back(fild.figures[i]->getAddress(j).y + 1 + '0');
					put.push_back(' ');

					puts.push_back('\n');
					puts.push_back(name);
					puts.push_back(bukva + 'A');
					puts.push_back(number + 1 + '0');
					puts.push_back(':');

					for (int u = 0; u< int(put.size()); u++) puts.push_back(put[u]);
					onesChance = true;
				}
			}
		}
	return onesChance;
}
