#ifndef WORDS_H
#define WORDS_H

#include <vector>
#include <string>


#define ROWS 12
#define COLS 12
using namespace  std;
class words
{
public:
	words();
	void board();
	void askForWords();
	
	vector<string>myVec;
	bool checkIfValid(string word, int length);
	void generatePlace(string word);
	void makeUpper(vector<string>& myvec);
	void randomFill();
	void gamePlay();

private:
	char letters[ROWS][COLS];
	//char random[ROWS][COLS];
	string positions[6];
	
};

#endif