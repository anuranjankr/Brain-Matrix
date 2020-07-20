#include <ComputeMat.h>
#include <iostream>

//using namespace BM;

int main() {
	BM::Init();
	int row = 10;
	int col = 20;
	
	BM::mat O1(row, col);
	O1.fill(3);
	
	BM::mat O2(row, col);
	O2.fill(5);
	
	//Access Position of mat
	std::cout<<O1(3, 2)<<"\n";
	
	std::cout << O1 + O2;
}