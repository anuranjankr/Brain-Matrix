#pragma once
#include <iostream>

namespace BM {

	class mat
	{
	private:
		float* data;
		int x, y;
	public:
		mat(int x, int y);
		void fill(const float& val);

		//Operations on different matrix
		mat& add(const mat& right);
		mat& sub(const mat& right);

		//Operator overloading for add and subtract using + , -
		mat& operator+(const mat& right);
		mat& operator-(const mat& right);

		//Overloaded the () functionality to change or operate on data at certain position
		float& operator() (int row,int cols);

		// Overloaded the cout functionality
		friend std::ostream& operator<< (std::ostream& stream, const mat& obj);
	};

	void Init();

}