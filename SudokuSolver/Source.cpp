#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;

const vector<int> FULL_SET = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


vector<vector<int>> v = {
	{ 0,7,0,2,0,6,0,5,0 },
	{ 5,0,0,0,0,0,0,0,3 },
	{ 0,4,0,0,0,0,0,9,0 },
	{ 0,0,2,0,1,0,8,0,0 },
	{ 0,1,0,0,0,0,0,2,0 },
	{ 0,0,6,0,4,0,5,0,0 },
	{ 0,9,0,0,0,0,0,7,0 },
	{ 2,0,0,0,0,0,0,0,9 },
	{ 0,5,0,4,0,7,0,1,0 } };

bool search(const int num, const vector<int> *vec) {
	bool inside = false;
	for (vector<int>::const_iterator iter = vec->begin(); iter != vec->end(); iter++) {
		if (*iter == num) {
			inside = true;
			break;
		}
	}
	return inside;
}

void both(vector<int> *first, const vector<int> *other) {
	vector<int>::iterator iter = first->begin();
	while (iter != first->end()) {
		if (!search(*iter, other))
			iter = first->erase(iter);
		else
			iter++;
	}
}

void invert(vector<int> *vec) {
	vector<int> copy = FULL_SET;
	vector<int>::iterator iter = copy.begin();
	while (iter != copy.end()) {
		if (search(*iter, vec))
			iter = copy.erase(iter);
		else
			iter++;
	}
	*vec = copy;
}



class SudokuBoard {
private:
	vector<vector<Box>> board;
public:
	/*
	Sudoku(){
	for (int x = 0; x < 9; x++) {
	vector<int> row;
	for (int y = 0; y < 9; y++) {
	int a;
	cin >> a;
	row.push_back(a);
	}
	board.push_back(row);
	}
	}
	*/
	SudokuBoard(vector<vector<int>> b)
	{
		vector<vector<Box>> temp;
		vector<vector<int>>::iterator iter = b.begin();
		int x = 0, y = 0;
		while (iter != b.end()) {
			vector<Box> tempRow;
			vector<int> row = *iter;
			vector<int>::iterator iter2 = row.begin();

			while (iter2 != row.end()) {
				Box box(*iter2, x, y);
				tempRow.push_back(box);
				iter2++;
				y++;
			}
			temp.push_back(tempRow);
			iter++;
			x++;
			y = 0;
		}
		board = temp;

	}
	void print() {
		string div = "+-------+-------+-------+";
		cout << div << endl;
		vector<vector<Box>>::iterator iter = board.begin();
		for (int x = 0; x < 3; x++) {
			printf("| %i %i %i | %i %i %i | %i %i %i |\n",
				iter->at(0).getNum(), iter->at(1).getNum(), iter->at(2).getNum(),
				iter->at(3).getNum(), iter->at(4).getNum(), iter->at(5).getNum(),
				iter->at(6).getNum(), iter->at(7).getNum(), iter->at(8).getNum());
			iter++;
		}
		cout << div << endl;
		for (int x = 0; x < 3; x++) {
			printf("| %i %i %i | %i %i %i | %i %i %i |\n",
				iter->at(0).getNum(), iter->at(1).getNum(), iter->at(2).getNum(),
				iter->at(3).getNum(), iter->at(4).getNum(), iter->at(5).getNum(),
				iter->at(6).getNum(), iter->at(7).getNum(), iter->at(8).getNum());
			iter++;
		}
		cout << div << endl;
		for (int x = 0; x < 3; x++) {
			printf("| %i %i %i | %i %i %i | %i %i %i |\n",
				iter->at(0).getNum(), iter->at(1).getNum(), iter->at(2).getNum(),
				iter->at(3).getNum(), iter->at(4).getNum(), iter->at(5).getNum(),
				iter->at(6).getNum(), iter->at(7).getNum(), iter->at(8).getNum());
			iter++;
		}
		cout << div << endl;
	}
	vector<int> horizontalPossible(int row) {
		vector<int> notPossible;
		vector<Box> r = board.at(row);
		vector<Box>::iterator iter = r.begin();
		while (iter != r.end()) {
			if (iter->getNum())
				notPossible.push_back(iter->getNum());
			iter++;
		}
		invert(&notPossible);
		return notPossible;
	}
	vector<int> verticalPossible(int col) {
		vector<int> notPossible;
		vector<vector<Box>>::iterator iter = board.begin();
		while (iter != board.end()) {
			vector<Box> row = *iter;
			Box x = row.at(col);
			if (x.getNum())
				notPossible.push_back(x.getNum());
			iter++;
		}
		invert(&notPossible);
		return notPossible;
	}
	vector<int> sectionPossible(int sec) {
		vector<int> notPossible;
		for (int i = sec / 3; i < (sec / 3 + 3); i++) {
			vector<Box> row = board.at(i);
			for (int j = sec % 3 * 3; j < (sec % 3 * 3 + 3); j++) {
				Box col = row.at(j);
				if (col.getNum()) {
					notPossible.push_back(col.getNum());
				}
			}
		}
		invert(&notPossible);
		return notPossible;
	}
	void horizontalUpdate(int row, vector<int> possible) {
		/*
		vector<Box> r = board.at(row);
		vector<Box>::iterator iter = r.begin();
		while (iter != r.end()){
		iter->updatePossible(&possible);
		iter++;
		}
		*/
		for (int x = 0; x < 9; x++)
			board.at(row).at(x).updatePossible(&possible);
	}
	void verticalUpdate(int col, vector<int> possible) {
		/*
		vector<vector<Box>>::iterator iter = board.begin();
		while (iter != board.end()){
		vector<Box> row = *iter;
		Box *x = &row.at(col);
		x->updatePossible(&possible);
		iter++;
		}
		*/
		for (int x = 0; x < 9; x++)
			board.at(x).at(col).updatePossible(&possible);
	}
	void sectionUpdate(int sec, vector<int> possible) {
		/*
		for (int i = sec / 3; i < (sec / 3 + 3); i++){
		vector<Box> row = board.at(i);
		for (int j = sec % 3 * 3; j < (sec % 3 * 3 + 3); j++){
		Box *col = &row.at(j);
		col->updatePossible(&possible);
		}
		}
		*/
		for (int i = sec / 3; i < (sec / 3 + 3); i++)
			for (int j = sec % 3 * 3; j < (sec % 3 * 3 + 3); j++)
				board.at(i).at(j).updatePossible(&possible);
	}
	void possUpdate() {
		vector<int> temp;
		for (int x = 0; x < 9; x++) {
			temp = horizontalPossible(x);
			horizontalUpdate(x, temp);
			temp = verticalPossible(x);
			verticalUpdate(x, temp);
			temp = sectionPossible(x);
			sectionUpdate(x, temp);
		}
	}
	vector<vector<Box>> retBoard() {
		return board;
	}

};

void printVectorInt(vector<int> vec) {
	vector<int>::iterator iter = vec.begin();
	while (iter != vec.end()) {
		cout << *iter << " ";
		iter++;
	}
	cout << endl;
}

int main() {
	Box b(0, 0, 0);
	b.printPossible();
	vector<int> p = { 1, 2, 3, 4, 5 };
	b.updatePossible(&p);
	b.printPossible();
	p = { 4, 5, 6 };
	b.updatePossible(&p);
	b.printPossible();


	SudokuBoard s(v);
	s.print();
	s.possUpdate();
	printVectorInt(s.retBoard().at(5).at(1).getPossible());
	printVectorInt(s.retBoard().at(5).at(8).getPossible());

	/*
	vector<int>::iterator iter = h.begin();
	while (iter != h.end()) {
	cout << *iter << " ";
	iter++;
	}
	cout << endl;
	*/
	/*
	for (int i = 0; i < 9; i++) {
	cout << i << " " << i / 3 * 3 << " " << i % 3 * 3 << endl;
	}
	*/
	return 0;
}