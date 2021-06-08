#include<iostream>

using namespace std;

void show(int row) {

	for (int i = 0; i < row; i++){
		cout << i << " * " << i << " = " << i * i << endl;
	}
}


int main() {

	show(3);

	return 0;
}