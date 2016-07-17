#include "words.h"

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;
words::words()
{
	for (int ROW = 0; ROW < 11; ROW++)
	{
		for (int COL = 0; COL < 11; COL++)
		{
			letters[ROW][COL] = ' ';
		}
	}

	positions[0] = "down";
	positions[1] = "up";
	positions[2] = "right";
	positions[3] = "left";



}





void words::askForWords()
{
	int maxLetters = 10;
	int howManyWords = 1;
	cout << " Welcome to Word Search Generator!\n You can enter upto 10 words\n And make sure each word is no more than 8 letters\n\n";
	string word;
	bool wordAcceptable = false;
	//cout << " word : ";
	//getline(cin, word);
	int ctr = 1;
	bool keepGoing = true;
	while (keepGoing){
		do{
			cout << " \n Word " << ctr << ": ";
			getline(cin, word);
			if (word.size() == 0){
				keepGoing = false;
				break;
			}
			wordAcceptable = checkIfValid(word, maxLetters);
			if (wordAcceptable) { myVec.push_back(word); }
		} while (!wordAcceptable);
		ctr++;
	}

	makeUpper(myVec);

	for (int a = 0; a < myVec.size(); a++)
	{
		generatePlace(myVec[a]);
	}
	//generatePlace(word);
}

void words::gamePlay()
{
	int rowNum1, colNum1, rowNum2, colNum2;
	int wordSize;
	cout << endl << endl;
	cout << " Enter ROW and COL of FIRST letter of the word: ";
	cin >> rowNum1 >> colNum1;
	while (rowNum1 < 0 || rowNum1 > 10 || colNum1 < 0 || colNum1 > 10)
	{
		cout << " ERROR: INVALID ENTRY " << endl;
		cout << " Enter ROW and COL of FIRST letter of the word: ";
		cin >> rowNum1 >> colNum1;
	}
	cout << "\n\n Enter ROW and COL of LAST  letter of the word: ";
	cin >> rowNum2 >> colNum2;
	while (rowNum2 < 0 || rowNum2 > 10 || colNum2 < 0 || colNum2 > 10)
	{
		cout << " ERROR: INVALID ENTRY " << endl;
		cout << " Enter ROW and COL of LAST letter of the word: ";
		cin >> rowNum1 >> colNum1;
	}
	string wordPos = "zzz";
	if (rowNum2 - rowNum1 == 0)
	{
		wordSize = abs(colNum2 - colNum1);
		if (wordSize < 0) {
			wordSize = abs(colNum2 - colNum1);
			wordPos = "left";
		}
		else{
			wordPos = "right";
		}
	}
	else if (colNum2 - colNum1 == 0)
	{
		wordSize = abs(rowNum2 - rowNum1);
		wordPos = 'c';
	}
	else {
		cerr << " ERROR ? row-col " << rowNum1 << colNum1 << rowNum2 << colNum2 << endl;
	}

	string guess;
	int ctr = 0;
	//-----------
	if (wordPos == "right")
	{

		while (colNum1 != colNum2)
		{
			guess[ctr] = letters[rowNum1][colNum1];
			ctr++;
			colNum1++;
		}
	}
	cout << " you found : " << guess << endl;

}



bool words::checkIfValid(string word, int length)
{
	if (word.length() > length)
	{
		cout << " \nERROR: You word can have maximum " << length << " letters. Try Again.\n\n";
		return false;
	}

	for (int i = 0; i < word.length(); i++)
	{
		if (isdigit(word[i]) || word[i] == ' ')
		{
			cout << " \nERROR: Illegal character '" << word[i] << "' Try Again.\n\n";
			return false;
		}
	}
	return true;
}


void words::makeUpper(vector<string>& myvec)
{
	for (int i = 0; i < myvec.size(); i++)
	{
		string tempWord = myvec[i];
		for (int j = 0; j < tempWord.size(); j++)
		{
			tempWord[j] = toupper(tempWord[j]);
		}
		myvec[i] = tempWord;
	}

}


void words::generatePlace(string word)
{

	srand(time(NULL));
	bool allGood = false;
	while (!allGood)
	{
		int row = rand() % 12;
		int col = rand() % 12;
		int checkRow = row;
		int checkCol = col;
		if (letters[row][col] != ' ')   // if there is already a char at that spot, go to beginning of loop
		{
			continue;
		}
		else          // otherwise generate position and place word
		{
			int pos = rand() % 4;
			string position;// = positions[pos];
			position = "right";
			bool enoughSpace = true;
			if (position == "down")
			{

				for (int i = 0; i < word.length(); i++)
				{
					if (letters[checkRow][checkCol] != ' ' || word.length() + row > COLS)
					{
						enoughSpace = false;
						break;
					}
					else{
						checkRow++;
					}
				}
				if (enoughSpace){
					for (int i = 0; i < word.length(); i++)
					{
						letters[row][col] = word[i];
						row += 1;
					}
					allGood = true;
				}
			} // ~ if down
			//***********************************************************************************************************
			else if (position == "up")
			{
				for (int i = 0; i < word.length(); i++)
				{
					if (letters[checkRow][checkCol] != ' ' || 0 + row < word.length())
					{
						enoughSpace = false;
						break;
					}
					else{
						checkRow--;
					}
				}
				if (enoughSpace){

					for (int i = 0; i < word.length(); i++)
					{
						letters[row][col] = word[i];
						row -= 1;
					}
					allGood = true;
				}
			} // ~ elseif up
			//***********************************************************************************************************
			else if (position == "right")
			{

				for (int i = 0; i < word.length(); i++)
				{
					if (letters[checkRow][checkCol] != ' ' || word.length() + col > ROWS)
					{
						enoughSpace = false;
						break;
					}
					else{
						checkCol++;
					}
				}
				if (enoughSpace){
					for (int i = 0; i < word.length(); i++)
					{
						letters[row][col] = word[i];
						col += 1;
					}
					allGood = true;
				}
			} // ~ elseif right
			//***********************************************************************************************************
			else if (position == "left")
			{
				for (int i = 0; i < word.length(); i++)
				{
					if (letters[checkRow][checkCol] != ' ' || 0 + col < word.length())
					{
						enoughSpace = false;
						break;
					}
					else{
						checkCol--;
					}
				}
				if (enoughSpace){

					for (int i = 0; i < word.length(); i++)
					{
						letters[row][col] = word[i];
						col -= 1;
					}
					allGood = true;
				}
			} // ~ elseif left
			//***********************************************************************************************************
			else{
				cerr << " ERROR ? " << position << " " << "row " << row << " col " << col << endl;
			}

		} // ~ big else (if first spot is not empty
	} // ~ while allGood

} //~ exit generatePlace()

void words::randomFill()
{
	string abcd = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	for (int ROW = 0; ROW < 11; ROW++)
	{
		for (int COL = 0; COL < 11; COL++)
		{
			if (letters[ROW][COL] == ' ')
			{
				int pickLetter = rand() % 26;
				letters[ROW][COL] = abcd[pickLetter];
			}
		}
	}


}






void words::board(){

	system("cls");
	cout << endl;
	randomFill(); // fill blank spaces with random letters
	cout << " \n Welcome to Word Search Generator!\n\n\n";
	cout << " Words to look for: \n\n\n\n     ";
	for (int k = 0; k < myVec.size(); k++)
	{
		cout << " " << myVec[k] << "    ";
	}
	cout << "\n\n\n\n\n";


	//	cout << "                                         ";
	cout << "       0   1   2   3   4   5   6   7   8   9   10\n";
	cout << "     _____________________________________________" << endl;
	cout << "    |                                             |" << endl;
	for (int ROW = 0; ROW < 11; ROW++)
	{
		if (ROW != 10) { cout << "  " << ROW << " |"; }
		else { cout << " " << ROW << " |"; }

		for (int COL = 0; COL < 11; COL++)
		{
			cout << "  " << letters[ROW][COL] << " ";
		}
		if (ROW != 10) { cout << " |" << endl << "    |                                             |" << endl; }
		else { cout << " |" << endl << "    |                                             |" << endl; }
	}

	cout << "    |_____________________________________________|" << endl << endl;

}