#include <ComputeMat.h>
#include <iostream>

//using namespace BM;

int main() {

	BM::init();
	int row = 10;
	int col = 10;
	
	BM::mat O1(row, col);

	O1.fill(5.2);
	O1.sub(7.6);
	std::cout << O1;
	
	//Access Position of mat
	std::cout<<O1(3, 2)<<"\n";

	BM::mat O2(row, col);

	O2.fill(4.5);
	BM::mat O3 = O2 * 1.2;

	std::cout << O3;

}