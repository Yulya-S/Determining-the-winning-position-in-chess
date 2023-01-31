#pragma once

#include <vector>
#include <iostream>
using namespace std;
class error {};

class Coordinate {
public:
	int x, y;
	Coordinate() { x = 0; y = 0; };
	Coordinate(int X, int Y) : x(X), y(Y) {};
	bool operator ==(const Coordinate coordinate) { return (coordinate.x == x && coordinate.y == y); };
	Coordinate operator -=(const Coordinate coordinate) { x -= coordinate.x, y -= coordinate.y;  return *this; };
	Coordinate operator -(const Coordinate coordinate) { Coordinate coor = *this; return (coor -= coordinate); };
	bool operator !=(const Coordinate coordinate) { return (coordinate.x != x || coordinate.y != y); };
};

class YourNeighbors { //класс нужен для определения всех возможных ходов фигуры
public:
	vector<Coordinate> coordinate;
	vector<bool> white;
	vector<char> name;
	void clear() { white.clear(); coordinate.clear(); }
};

class Figures {
public:
	virtual char name() const { return '0'; }; //имя фигуры
	virtual bool White() const { return false; }; //возвращаяет цвет фигуры, true - белая, false - черная
	virtual Coordinate whereAmI() const { Coordinate cor(0, 0); return cor; }; //возращаяет координату на которой стоит фигура
	virtual int addressesSize() const { return 0; }; //возвращает кол-во адресов у фигуры
	virtual Coordinate getAddress(const int i) { Coordinate cor(0, 0); return cor; }; //возращает адрес из списка адресов по его номеру
	virtual void create(YourNeighbors neighbors, int whereAmI, bool regim = false) {}; //функция определения координаты для хода
};

class playingField {
public:
	vector<Figures*> figures;
	void readFiguresFromFile(const char* fileName); //чтение позиций шахмат из файла
	playingField& recreatingField(const playingField& field, const int numberFigure, const Coordinate whereYouWantPutIt, bool regim = false);
	//копирует поле но сдвигает выбранную фигуру на выбранную координату
	bool addressNoBusy(Coordinate coordinate, int whatFigure, bool whiteOrBlack); //определяет стоят ли около черного короля другие черные фигуры
	bool whiteAttacks(Coordinate coordinate, int whatFigure, bool whiteOrBlack); //проверяет есть ли хоть одна позиция где белые угрожают королю
	//нужна, что бы программа не определяла конец игры если все клетки вокруг короля заняты черными фигурами
	bool placeOccupied(Coordinate coordinate, int whatFigure); //проверяет не стоит ли на координате какая-либо фигура
	bool placeOccupiedPoints(Coordinate coordinate, int whatFigure);
	bool kingCanDead(); //проверяет могут ли белые убить черного короля
	bool whiteKingSave(); //проверяет что бы белый король был в безопасности
	void findFiguresWhoKillKing(vector<char>& put); //добавляет все угрожающие королю фигуры в вектор символов 
	bool endGame(bool whiteOrBlack = false); //без значения мы проверяем мат на черного короля, если прописываем true, то мат на белого короля
};

class King : public Figures{
	Coordinate posityon;
	bool white;
	vector<Coordinate> addres;
public:
	King(bool White) { white = White; };
	char name() const { return 'K'; };
	bool White() const { return white; };
	Coordinate whereAmI() const { return posityon; };
	int addressesSize() const { return addres.size(); };
	Coordinate getAddress(const int i) { return addres[i]; };
	void create(YourNeighbors neighbors, int whereAmI, bool regim = false);
};

class Queen : public Figures {
	Coordinate posityon;
	bool white;
	vector<Coordinate> addres;
public:
	Queen(bool White) : white(White) {};
	char name() const { return 'Q'; };
	bool White() const { return white; };
	Coordinate whereAmI() const { return posityon; };
	int addressesSize() const { return addres.size(); };
	Coordinate getAddress(const int i) { return addres[i]; };
	void create(YourNeighbors neighbors, int whereAmI, bool regim = false);
};


class Rook : public Figures {
	Coordinate posityon;
	bool white;
	vector<Coordinate> addres;
public:
	Rook(bool White) : white(White) {};
	char name() const { return 'R'; };
	bool White() const { return white; };
	Coordinate whereAmI() const { return posityon; };
	int addressesSize() const { return addres.size(); };
	Coordinate getAddress(const int i) { return addres[i]; };
	void create(YourNeighbors neighbors, int whereAmI, bool regim = false);
};


class Bishop : public Figures {
	Coordinate posityon;
	bool white;
	vector<Coordinate> addres;
public:
	Bishop(bool White) : white(White) {};
	char name() const { return 'B'; };
	bool White() const { return white; };
	Coordinate whereAmI() const { return posityon; };
	int addressesSize() const { return addres.size(); };
	Coordinate getAddress(const int i) { return addres[i]; };
	void create(YourNeighbors neighbors, int whereAmI, bool regim = false);
};

class Knight : public Figures {
	Coordinate posityon;
	bool white;
	vector<Coordinate> addres;
public:
	Knight(bool White) : white(White) {};
	char name() const { return 'N'; };
	bool White() const { return white; };
	Coordinate whereAmI() const { return posityon; };
	int addressesSize() const { return addres.size(); };
	Coordinate getAddress(const int i) { return addres[i]; }
	void create(YourNeighbors neighbors, int whereAmI, bool regim = false);
};

class Pount : public Figures {
	Coordinate posityon;
	bool white, queenMod = false; //queenMod - если пешка оказывается на противоположной стороне, то она начинает ходить как королева
	vector<Coordinate> addres;
public:
	Pount(bool White) : white(White) {};
	char name() const { return 'p'; };
	bool White() const { return white; };
	Coordinate whereAmI() const { return posityon; };
	int addressesSize() const { return addres.size(); };
	Coordinate getAddress(const int i) { return addres[i]; };
	void create(YourNeighbors neighbors, int whereAmI, bool regim = false);
};

void pushAddress(const int x, const int y, Coordinate myAddress, vector<Coordinate>& addres); //упрощает добавление адресов фигурам

//три функции разрешающие или запрещающие добавление адресов фигурам
bool iHaveNeighbor(YourNeighbors neighbors, const int x, const int y, const int whoAmI, bool regim);
bool iHaveNeighbor(YourNeighbors neighbors, Coordinate coordinate, const int whoAmI, bool regim);
bool iHaveNeighborIPount(YourNeighbors neighbors, const int x, const int y, const int whoAmI, bool regim);

//при создании поля из текстового файла проверяет чтобы не были допущенны ошибки
void creationErrors(YourNeighbors neighbors, vector<char> names);

//функция для нахождения победной комбинации за один ход
void matVDva(char* inFileName, char* outFileName);
bool analizNaMat(vector<char>& put, playingField fild, char name, int bukva, int number);