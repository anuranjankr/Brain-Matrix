#include "Core.h"
#include "ComputeMat.h"
#include <iostream>
#include <vector>

namespace BM {

	// Matrix obj's constructor (not default)

	mat::mat(int x, int y) {
		val = new float* [x];
		this->x = x;
		this->y = y;
		// Also be created using kernels
		for (int i = 0; i < x; i++) {
			val[i] = new float[y];
		}
	}

	/* This function is called at the beginning to initialise the heterogenous computing units available / connected to 
		the system . 
		The API used here is openCL 2.0 . And can change in future according to the needs and platform available. */

	void Init() {
		std::vector<cl::Platform> all_platforms;
		cl::Platform::get(&all_platforms);
		if (all_platforms.size() == 0) {
			std::cout << " No platforms found. Check OpenCL installation!\n";
			exit(1);
		}
		cl::Platform default_platform = all_platforms[0];
		std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";
	}
}