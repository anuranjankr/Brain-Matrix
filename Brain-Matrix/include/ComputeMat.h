#pragma once

namespace BM {
	class mat
	{
	private:
		float** val;
		int x, y;
	public:
		mat(int x, int y);
	};

	void Init();
}
