#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

vector<vector<int> > Board(int w, int h, int mines);
vector<vector<int> > cornerBoard(int w, int h, vector<vector<int> >& board);
vector<vector<int> > edgesBoard(int w, int h, vector<vector<int> >& board);
vector<vector<int> > fullBoard(int w, int h, vector<vector<int> >& board);
int numIndex(vector<vector<int> >& board, int y, int x);
bool checkNumBoard(vector<vector<int> >& board, int y, int x);
void revealBlanks(vector<vector<int> >& dummyBoard, int y, int x);
bool checkWin(vector<vector<int> >& flagBoard, int& flagTracker);
int getLeft(int flagTracker);
int getRight(int flagTracker);
int getLeft3(int flagTracker);
int getRight3(int flagTracker);
int getL1(int flagTracker);