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

class YourNeighbors { //����� ����� ��� ����������� ���� ��������� ����� ������
public:
	vector<Coordinate> coordinate;
	vector<bool> white;
	vector<char> name;
	void clear() { white.clear(); coordinate.clear(); }
};

class Figures {
public:
	virtual char name() const { return '0'; }; //��� ������
	virtual bool White() const { return false; }; //����������� ���� ������, true - �����, false - ������
	virtual Coordinate whereAmI() const { Coordinate cor(0, 0); return cor; }; //���������� ���������� �� ������� ����� ������
	virtual int addressesSize() const { return 0; }; //���������� ���-�� ������� � ������
	virtual Coordinate getAddress(const int i) { Coordinate cor(0, 0); return cor; }; //��������� ����� �� ������ ������� �� ��� ������
	virtual void create(YourNeighbors neighbors, int whereAmI, bool regim = false) {}; //������� ����������� ���������� ��� ����
};

class playingField {
public:
	vector<Figures*> figures;
	void readFiguresFromFile(const char* fileName); //������ ������� ������ �� �����
	playingField& recreatingField(const playingField& field, const int numberFigure, const Coordinate whereYouWantPutIt, bool regim = false);
	//�������� ���� �� �������� ��������� ������ �� ��������� ����������
	bool addressNoBusy(Coordinate coordinate, int whatFigure, bool whiteOrBlack); //���������� ����� �� ����� ������� ������ ������ ������ ������
	bool whiteAttacks(Coordinate coordinate, int whatFigure, bool whiteOrBlack); //��������� ���� �� ���� ���� ������� ��� ����� �������� ������
	//�����, ��� �� ��������� �� ���������� ����� ���� ���� ��� ������ ������ ������ ������ ������� ��������
	bool placeOccupied(Coordinate coordinate, int whatFigure); //��������� �� ����� �� �� ���������� �����-���� ������
	bool placeOccupiedPoints(Coordinate coordinate, int whatFigure);
	bool kingCanDead(); //��������� ����� �� ����� ����� ������� ������
	bool whiteKingSave(); //��������� ��� �� ����� ������ ��� � ������������
	void findFiguresWhoKillKing(vector<char>& put); //��������� ��� ���������� ������ ������ � ������ �������� 
	bool endGame(bool whiteOrBlack = false); //��� �������� �� ��������� ��� �� ������� ������, ���� ����������� true, �� ��� �� ������ ������
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
	bool white, queenMod = false; //queenMod - ���� ����� ����������� �� ��������������� �������, �� ��� �������� ������ ��� ��������
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

void pushAddress(const int x, const int y, Coordinate myAddress, vector<Coordinate>& addres); //�������� ���������� ������� �������

//��� ������� ����������� ��� ����������� ���������� ������� �������
bool iHaveNeighbor(YourNeighbors neighbors, const int x, const int y, const int whoAmI, bool regim);
bool iHaveNeighbor(YourNeighbors neighbors, Coordinate coordinate, const int whoAmI, bool regim);
bool iHaveNeighborIPount(YourNeighbors neighbors, const int x, const int y, const int whoAmI, bool regim);

//��� �������� ���� �� ���������� ����� ��������� ����� �� ���� ��������� ������
void creationErrors(YourNeighbors neighbors, vector<char> names);

//������� ��� ���������� �������� ���������� �� ���� ���
void matVDva(char* inFileName, char* outFileName);
bool analizNaMat(vector<char>& put, playingField fild, char name, int bukva, int number);