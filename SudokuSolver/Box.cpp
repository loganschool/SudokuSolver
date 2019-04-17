#include <vector>
#include "tools.h"

#include <iostream>

using std::cout; using std::endl;

class Box {
public:
	Box(int n, int r, int c)
		: num(n), row(r), col(c)
	{
		possible = FULL_SET;
		if (num)
			solve = true;
	}
	//BASICALLY both() SO CHANGE THAT LATER
	//Also, if only one possibility left, set it to the solution.
	void updatePossible(const vector<int> *other) {
		if (!num) {
			vector<int>::iterator iter = possible.begin();
			while (iter != possible.end()) {
				if (!search(*iter, other))
					iter = possible.erase(iter);
				else
					iter++;
			}
		}
	}
	int getNum() {
		return num;
	}
	int getRow() {
		return row;
	}
	int getCol() {
		return col;
	}
	void printPossible() {
		for (vector<int>::iterator iter = possible.begin();
			iter != possible.end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;
	}
	vector<int> getPossible() {
		return possible;
	}
	bool solved() {
		return solve;
	}
private:
	int num;
	int row, col;
	vector<int> possible = FULL_SET;
	bool solve = false;
};