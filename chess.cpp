#include <iostream>
#include <vector>
#include "chess.h"
using namespace std;

void pushAddress(const int x, const int y, Coordinate myAddress, vector<Coordinate>& addres) {
	Coordinate coordinate(myAddress.x + x, myAddress.y + y);
	addres.push_back(coordinate);
}
bool iHaveNeighbor(YourNeighbors neighbors, const int x, const int y, const int whoAmI, bool regim) {
	Coordinate coordinate(neighbors.coordinate[whoAmI].x + x, neighbors.coordinate[whoAmI].y + y);
	for (int i = 0; i < int(neighbors.coordinate.size()); i++)
		if (i != whoAmI && (neighbors.name[i] != 'K' || (neighbors.white[i] == neighbors.white[whoAmI] && !regim)) && coordinate == neighbors.coordinate[i]) return false;
	return true;
}
bool iHaveNeighbor(YourNeighbors neighbors, Coordinate coordinate, const int whoAmI, bool regim) {
	for (int i = 0; i < int(neighbors.coordinate.size()); i++)
		if (i != whoAmI && (neighbors.name[i] != 'K' || (neighbors.white[i] == neighbors.white[whoAmI] && !regim)) && coordinate == neighbors.coordinate[i]) return false;
	return true;
}
bool iHaveNeighborIPount(YourNeighbors neighbors, const int x, const int y, const int whoAmI, bool regim) {
	Coordinate coordinate(neighbors.coordinate[whoAmI].x + x, neighbors.coordinate[whoAmI].y + y);
	for (int i = 0; i < int(neighbors.coordinate.size()); i++)
		if (i != whoAmI && (!regim || (neighbors.white[i] != neighbors.white[whoAmI] && coordinate == neighbors.coordinate[i]))) return true;
	return false;
}
bool iHaveNeighborIPountIGoTop(YourNeighbors neighbors, const int x, const int y, const int whoAmI, bool regim) {
	Coordinate coordinate(neighbors.coordinate[whoAmI].x + x, neighbors.coordinate[whoAmI].y + y);
	for (int i = 0; i < int(neighbors.coordinate.size()); i++)
		if (i != whoAmI && coordinate == neighbors.coordinate[i]) return false;
	return true;
}


void King::create(YourNeighbors neighbors, int whereAmI, bool regim) {
	posityon = neighbors.coordinate[whereAmI];
	addres.clear();
	for (int i = -1; i < 2; i++) for (int j = -1; j < 2; j++)
		if ((j != 0 || i != 0) && (posityon.x + i >= 0 && posityon.x + i < 8 && posityon.y + j >= 0 && posityon.y + j < 8))
			pushAddress(i, j, posityon, addres);
}
void Queen::create(YourNeighbors neighbors, int whereAmI, bool regim) {
	posityon = neighbors.coordinate[whereAmI];
	addres.clear();
	bool zanetost = true;
	for (int i = 1; i < 8; i++)
		if (posityon.x + i >= 0 && posityon.x + i < 8) { zanetost = iHaveNeighbor(neighbors, i, 0, whereAmI, regim); pushAddress(i, 0, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.x - i >= 0 && posityon.x - i < 8) { zanetost = iHaveNeighbor(neighbors, -i, 0, whereAmI, regim); pushAddress(-i, 0, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.x - i >= 0 && posityon.x - i < 8 && posityon.y + i >= 0 && posityon.y + i < 8) { zanetost = iHaveNeighbor(neighbors, -i, i, whereAmI, regim); pushAddress(-i, i, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.x - i >= 0 && posityon.x - i < 8 && posityon.y - i >= 0 && posityon.y - i < 8) { zanetost = iHaveNeighbor(neighbors, -i, -i, whereAmI, regim); pushAddress(-i, -i, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.x + i >= 0 && posityon.x + i < 8 && posityon.y - i >= 0 && posityon.y - i < 8) { zanetost = iHaveNeighbor(neighbors, i, -i, whereAmI, regim); pushAddress(i, -i, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.x + i >= 0 && posityon.x + i < 8 && posityon.y + i >= 0 && posityon.y + i < 8) { zanetost = iHaveNeighbor(neighbors, i, i, whereAmI, regim); pushAddress(i, i, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.y + i >= 0 && posityon.y + i < 8) { zanetost = iHaveNeighbor(neighbors, 0, i, whereAmI, regim); pushAddress(0, i, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.y - i >= 0 && posityon.y - i < 8) { zanetost = iHaveNeighbor(neighbors, 0, -i, whereAmI, regim); pushAddress(0, -i, posityon, addres); if (!zanetost) break; }
}
void Rook::create(YourNeighbors neighbors, int whereAmI, bool regim) {
	posityon = neighbors.coordinate[whereAmI];
	addres.clear();
	bool zanetost = true;
	for (int i = 1; i < 8; i++)
		if (posityon.x + i >= 0 && posityon.x + i < 8) { zanetost = iHaveNeighbor(neighbors, i, 0, whereAmI, regim); pushAddress(i, 0, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.x - i >= 0 && posityon.x - i < 8) { zanetost = iHaveNeighbor(neighbors, -i, 0, whereAmI, regim); pushAddress(-i, 0, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.y + i >= 0 && posityon.y + i < 8) { zanetost = iHaveNeighbor(neighbors, 0, i, whereAmI, regim); pushAddress(0, i, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.y - i >= 0 && posityon.y - i < 8) { zanetost = iHaveNeighbor(neighbors, 0, -i, whereAmI, regim); pushAddress(0, -i, posityon, addres); if (!zanetost) break; }
}
void Bishop::create(YourNeighbors neighbors, int whereAmI, bool regim) {
	posityon = neighbors.coordinate[whereAmI];
	addres.clear();
	bool zanetost = true;
	for (int i = 1; i < 8; i++)
		if (posityon.x + i >= 0 && posityon.x + i < 8 && posityon.y + i >= 0 && posityon.y + i < 8) { zanetost = iHaveNeighbor(neighbors, i, i, whereAmI, regim); pushAddress(i, i, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.x - i >= 0 && posityon.x - i < 8 && posityon.y + i >= 0 && posityon.y + i < 8) { zanetost = iHaveNeighbor(neighbors, -i, i, whereAmI, regim); pushAddress(-i, i, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.x - i >= 0 && posityon.x - i < 8 && posityon.y - i >= 0 && posityon.y - i < 8) { zanetost = iHaveNeighbor(neighbors, -i, -i, whereAmI, regim); pushAddress(-i, -i, posityon, addres); if (!zanetost) break; }
	zanetost = true; for (int i = 1; i < 8; i++)
		if (posityon.x + i >= 0 && posityon.x + i < 8 && posityon.y - i >= 0 && posityon.y - i < 8) { zanetost = iHaveNeighbor(neighbors, i, -i, whereAmI, regim); pushAddress(i, -i, posityon, addres); if (!zanetost) break; }
}
void Knight::create(YourNeighbors neighbors, int whereAmI, bool regim) {
	posityon = neighbors.coordinate[whereAmI];
	addres.clear();
	if (posityon.x + 1 >= 0 && posityon.x + 1 < 8 && posityon.y + 2 >= 0 && posityon.y + 2 < 8) pushAddress(1, 2, posityon, addres);
	if (posityon.x - 1 >= 0 && posityon.x - 1 < 8 && posityon.y + 2 >= 0 && posityon.y + 2 < 8) pushAddress(-1, 2, posityon, addres);
	if (posityon.x - 1 >= 0 && posityon.x - 1 < 8 && posityon.y - 2 >= 0 && posityon.y - 2 < 8) pushAddress(-1, -2, posityon, addres);
	if (posityon.x + 1 >= 0 && posityon.x + 1 < 8 && posityon.y - 2 >= 0 && posityon.y - 2 < 8) pushAddress(1, -2, posityon, addres);
	if (posityon.x + 2 >= 0 && posityon.x + 2 < 8 && posityon.y + 1 >= 0 && posityon.y + 1 < 8) pushAddress(2, 1, posityon, addres);
	if (posityon.x - 2 >= 0 && posityon.x - 2 < 8 && posityon.y + 1 >= 0 && posityon.y + 1 < 8) pushAddress(-2, 1, posityon, addres);
	if (posityon.x - 2 >= 0 && posityon.x - 2 < 8 && posityon.y - 1 >= 0 && posityon.y - 1 < 8) pushAddress(-2, -1, posityon, addres);
	if (posityon.x + 2 >= 0 && posityon.x + 2 < 8 && posityon.y - 1 >= 0 && posityon.y - 1 < 8) pushAddress(2, -1, posityon, addres);
}
void Pount::create(YourNeighbors neighbors, int whereAmI, bool regim) {
	posityon = neighbors.coordinate[whereAmI];
	addres.clear();
	if ((posityon.y == 0 && !white) || (posityon.y == 7 && white)) {
		queenMod = true;
		bool zanetost = true;
		for (int i = 1; i < 8; i++)
			if (posityon.x + i >= 0 && posityon.x + i < 8) { zanetost = iHaveNeighbor(neighbors, i, 0, whereAmI, regim); pushAddress(i, 0, posityon, addres); if (!zanetost) break; }
		zanetost = true; for (int i = 1; i < 8; i++)
			if (posityon.x - i >= 0 && posityon.x - i < 8) { zanetost = iHaveNeighbor(neighbors, -i, 0, whereAmI, regim); pushAddress(-i, 0, posityon, addres); if (!zanetost) break; }
		zanetost = true; for (int i = 1; i < 8; i++)
			if (posityon.x - i >= 0 && posityon.x - i < 8 && posityon.y + i >= 0 && posityon.y + i < 8) { zanetost = iHaveNeighbor(neighbors, -i, i, whereAmI, regim); pushAddress(-i, i, posityon, addres); if (!zanetost) break; }
		zanetost = true; for (int i = 1; i < 8; i++)
			if (posityon.x - i >= 0 && posityon.x - i < 8 && posityon.y - i >= 0 && posityon.y - i < 8) { zanetost = iHaveNeighbor(neighbors, -i, -i, whereAmI, regim); pushAddress(-i, -i, posityon, addres); if (!zanetost) break; }
		zanetost = true; for (int i = 1; i < 8; i++)
			if (posityon.x + i >= 0 && posityon.x + i < 8 && posityon.y - i >= 0 && posityon.y - i < 8) { zanetost = iHaveNeighbor(neighbors, i, -i, whereAmI, regim); pushAddress(i, -i, posityon, addres); if (!zanetost) break; }
		zanetost = true; for (int i = 1; i < 8; i++)
			if (posityon.x + i >= 0 && posityon.x + i < 8 && posityon.y + i >= 0 && posityon.y + i < 8) { zanetost = iHaveNeighbor(neighbors, i, i, whereAmI, regim); pushAddress(i, i, posityon, addres); if (!zanetost) break; }
		zanetost = true; for (int i = 1; i < 8; i++)
			if (posityon.y + i >= 0 && posityon.y + i < 8) { zanetost = iHaveNeighbor(neighbors, 0, i, whereAmI, regim); pushAddress(0, i, posityon, addres); if (!zanetost) break; }
		zanetost = true; for (int i = 1; i < 8; i++)
			if (posityon.y - i >= 0 && posityon.y - i < 8) { zanetost = iHaveNeighbor(neighbors, 0, -i, whereAmI, regim); pushAddress(0, -i, posityon, addres); if (!zanetost) break; }
		if (posityon.x + 1 >= 0 && posityon.x + 1 < 8 && posityon.y + 2 >= 0 && posityon.y + 2 < 8) pushAddress(1, 2, posityon, addres);
		if (posityon.x - 1 >= 0 && posityon.x - 1 < 8 && posityon.y + 2 >= 0 && posityon.y + 2 < 8) pushAddress(-1, 2, posityon, addres);
		if (posityon.x - 1 >= 0 && posityon.x - 1 < 8 && posityon.y - 2 >= 0 && posityon.y - 2 < 8) pushAddress(-1, -2, posityon, addres);
		if (posityon.x + 1 >= 0 && posityon.x + 1 < 8 && posityon.y - 2 >= 0 && posityon.y - 2 < 8) pushAddress(1, -2, posityon, addres);
		if (posityon.x + 2 >= 0 && posityon.x + 2 < 8 && posityon.y + 1 >= 0 && posityon.y + 1 < 8) pushAddress(2, 1, posityon, addres);
		if (posityon.x - 2 >= 0 && posityon.x - 2 < 8 && posityon.y + 1 >= 0 && posityon.y + 1 < 8) pushAddress(-2, 1, posityon, addres);
		if (posityon.x - 2 >= 0 && posityon.x - 2 < 8 && posityon.y - 1 >= 0 && posityon.y - 1 < 8) pushAddress(-2, -1, posityon, addres);
		if (posityon.x + 2 >= 0 && posityon.x + 2 < 8 && posityon.y - 1 >= 0 && posityon.y - 1 < 8) pushAddress(2, -1, posityon, addres);
	}
	else {
		if (white) {
			if (posityon.y==1 && iHaveNeighborIPountIGoTop(neighbors, 0, 1, whereAmI, regim) && iHaveNeighborIPountIGoTop(neighbors, 0, 2, whereAmI, regim)) pushAddress(0, 2, posityon, addres);
			for (int i = -1; i < 2; i++)
				if (i!=0 && posityon.x + i >= 0 && posityon.x + i < 8 && iHaveNeighborIPount(neighbors, i, 1, whereAmI, regim))
					pushAddress(i, 1, posityon, addres);
			if (iHaveNeighborIPountIGoTop(neighbors, 0, 1, whereAmI, regim)) pushAddress(0, 1, posityon, addres);
		}
		else {
			if (posityon.y == 6 && iHaveNeighborIPountIGoTop(neighbors, 0, -1, whereAmI, regim) && iHaveNeighborIPountIGoTop(neighbors, 0, -2, whereAmI, regim)) pushAddress(0, -2, posityon, addres);
			for (int i = -1; i < 2; i++)
				if (i != 0 && posityon.x + i >= 0 && posityon.x + i < 8 && iHaveNeighborIPount(neighbors, i, -1, whereAmI, regim))
					pushAddress(i, -1, posityon, addres);
			if (iHaveNeighborIPountIGoTop(neighbors, 0, -1, whereAmI, regim)) pushAddress(0, -1, posityon, addres);
		}
	}
}
