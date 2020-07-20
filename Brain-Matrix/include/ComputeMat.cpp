#include "ComputeMat.h"
#include "Core.h"

namespace BM {
	//GLOBAL SCOPED VARIABLES
	//get all platforms (drivers)
	std::vector<cl::Platform> allPlatforms;

	//get all devices
	std::vector<cl::Device> allDevices;

	//Store the default Platform / Device data
	cl::Platform defaultPlatform;
	cl::Device defaultDevice;
	
	//-------------------------------------------

	// Matrix obj's constructor (not default)


	mat::mat(int x, int y) {
		this->x = x;
		this->y = y;
		int total = x * y;
		data = (float*)malloc(total * sizeof(float));
	}

	//--------------------------------------------------------------

	// Fills matrix with a float value

	void mat::fill(const float& val) {
		cl::Context context({ defaultDevice });
		int total = x * y;
		cl::Buffer buffer(context, CL_MEM_READ_WRITE, sizeof(float) * total);
		cl::CommandQueue queue(context, defaultDevice);
		queue.enqueueFillBuffer(buffer, val, 0, sizeof(float) * total);
		queue.enqueueReadBuffer(buffer, CL_FALSE, 0, sizeof(float) * total, data);
		cl::finish();
	}

	//--------------------------------------------------------------

	// Addition operation changes the matrix through which it is called

	mat& mat::add(const mat& right) {
		cl::Context context({ defaultDevice });

		// kernel calculates for each element C=A+B
		std::string kernel_code =
			"   __kernel void addMat(__global float* A, __global float* B){       "
			"       A[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];       "
			"   }                                                                       ";

		cl::Program::Sources sources(1, std::make_pair(kernel_code.c_str(),kernel_code.length()+1));

		cl::Program program(context, sources);
		program.build("-cl-std=CL1.2");

		int total = x * y;
		cl::Buffer bufferA(context, CL_MEM_READ_WRITE, sizeof(float) * total);
		cl::Buffer bufferB(context, CL_MEM_READ_WRITE, sizeof(float) * total);

		cl::CommandQueue queue(context, defaultDevice);

		queue.enqueueWriteBuffer(bufferA, CL_TRUE, 0, sizeof(float) * total, data);
		queue.enqueueWriteBuffer(bufferB, CL_TRUE, 0, sizeof(float) * total, right.data);
			 
		cl::Kernel kernel_add(program, "addMat");
		kernel_add.setArg(0, bufferA);
		kernel_add.setArg(1, bufferB);

		queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(total), cl::NullRange);
		queue.finish();

		queue.enqueueReadBuffer(bufferA, CL_TRUE, 0, sizeof(float) * total, data);

		cl::finish();
		return *this;
	}

	//--------------------------------------------------------------

	// Subtraction operation changes the matrix through which it is called

	mat& mat::sub(const mat& right) {
		cl::Context context({ defaultDevice });

		// kernel calculates for each element C=A+B
		std::string kernel_code =
			"   __kernel void subMat(__global float* A, __global float* B){       "
			"       A[get_global_id(0)]=A[get_global_id(0)]-B[get_global_id(0)];           "
			"   }                                                                               ";

		cl::Program::Sources sources(1, std::make_pair(kernel_code.c_str(), kernel_code.length() + 1));

		cl::Program program(context, sources);
		program.build("-cl-std=CL1.2");

		int total = x * y;

		cl::Buffer bufferA(context, CL_MEM_READ_WRITE, sizeof(float) * total);
		cl::Buffer bufferB(context, CL_MEM_READ_WRITE, sizeof(float) * total);

		cl::CommandQueue queue(context, defaultDevice);

		queue.enqueueWriteBuffer(bufferA, CL_TRUE, 0, sizeof(float) * total, data);
		queue.enqueueWriteBuffer(bufferB, CL_TRUE, 0, sizeof(float) * total, right.data);

		cl::Kernel kernel_add(program, "subMat");
		kernel_add.setArg(0, bufferA);
		kernel_add.setArg(1, bufferB);

		queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(total), cl::NullRange);
		queue.finish();

		queue.enqueueReadBuffer(bufferA, CL_TRUE, 0, sizeof(float) * total, data);

		cl::finish();
		return *this;
	}

	//--------------------------------------------------------------

	// Addition operation using '+' sign and creates a new matrix to pass

	mat& mat::operator+(const mat& right) {

		mat *temp = new mat(x,y);

		cl::Context context({ defaultDevice });

		// kernel calculates for each element C=A+B
		std::string kernel_code =
			"   __kernel void addMat(__global float* A, __global float* B){       "
			"       A[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];       "
			"   }                                                                       ";

		cl::Program::Sources sources(1, std::make_pair(kernel_code.c_str(), kernel_code.length() + 1));

		cl::Program program(context, sources);
		program.build("-cl-std=CL1.2");

		int total = x * y;

		cl::Buffer bufferA(context, CL_MEM_READ_WRITE, sizeof(float) * total);
		cl::Buffer bufferB(context, CL_MEM_READ_WRITE, sizeof(float) * total);

		cl::CommandQueue queue(context, defaultDevice);

		queue.enqueueWriteBuffer(bufferA, CL_TRUE, 0, sizeof(float) * total, data);
		queue.enqueueWriteBuffer(bufferB, CL_TRUE, 0, sizeof(float) * total, right.data);

		cl::Kernel kernel_add(program, "addMat");
		kernel_add.setArg(0, bufferA);
		kernel_add.setArg(1, bufferB);

		queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(total), cl::NullRange);
		queue.finish();

		queue.enqueueReadBuffer(bufferA, CL_TRUE, 0, sizeof(float) * total, temp->data);

		cl::finish();
		return *temp;
	}

	//--------------------------------------------------------------

	// Subtraction operation using '-' sign and creates a new matrix to pass

	mat& mat::operator-(const mat& right) {

		mat* temp = new mat(x, y);

		cl::Context context({ defaultDevice });

		// kernel calculates for each element C=A+B
		std::string kernel_code =
			"   __kernel void subMat(__global float* A, __global float* B){       "
			"       A[get_global_id(0)]=A[get_global_id(0)]-B[get_global_id(0)];                 "
			"   }                                                                               ";

		cl::Program::Sources sources(1, std::make_pair(kernel_code.c_str(), kernel_code.length() + 1));

		cl::Program program(context, sources);
		program.build("-cl-std=CL1.2");

		int total = x * y;

		cl::Buffer bufferA(context, CL_MEM_READ_WRITE, sizeof(float) * total);
		cl::Buffer bufferB(context, CL_MEM_READ_WRITE, sizeof(float) * total);

		cl::CommandQueue queue(context, defaultDevice);

		queue.enqueueWriteBuffer(bufferA, CL_TRUE, 0, sizeof(float) * total, data);
		queue.enqueueWriteBuffer(bufferB, CL_TRUE, 0, sizeof(float) * total, right.data);

		cl::Kernel kernel_add(program, "subMat");
		kernel_add.setArg(0, bufferA);
		kernel_add.setArg(1, bufferB);

		queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(total), cl::NullRange);
		queue.finish();

		queue.enqueueReadBuffer(bufferA, CL_TRUE, 0, sizeof(float) * total, temp->data);
		cl::finish();
		return *temp;
	}

	//--------------------------------------------------------------

	// To extract data from the matrix for further calculations
	float& mat::operator() (int rows,int cols) {
		return data[rows * y + cols];
	}
	 
	//---------------------------------------------------------------
	

	// Overloading -----(cout<<)----- function to output the matrix

	std::ostream& operator<< (std::ostream& stream, const mat& obj) {
		stream << "[\n";
		for (int i = 0; i < obj.x; i++) {
			stream << " ";
			for (int j = 0; j < obj.y; j++) {
				stream << obj.data[i*obj.y + j]<< " " ;
			}
			stream << "\n";
		}
		stream << " ]";
		return stream;
	}

	//-----------------------------------------------------------------


	/* This function is called at the beginning to initialise the heterogenous computing units available / connected to 
		the system . 
		The API used here is openCL 2.0 . And can change in future according to the needs and platform available. */

	void Init() {

		cl::Platform::get(&allPlatforms);
		if (allPlatforms.size() == 0) {
			std::cout << " No platforms found. Check OpenCL installation!\n";
			exit(1);
		}
		defaultPlatform = allPlatforms[0];
		//std::cout << "Using platform: " << defaultPlatform.getInfo<CL_PLATFORM_NAME>() << "\n";

		//get default device of the default platform
		defaultPlatform.getDevices(CL_DEVICE_TYPE_ALL, &allDevices);
		if (allDevices.size() == 0) {
			std::cout << " No devices found. Check OpenCL installation!\n";
			exit(1);
		}
		defaultDevice = allDevices[0];
		//std::cout << "Using device: " << defaultDevice.getInfo<CL_DEVICE_NAME>() << "\n";

	}

	//------------------------------------------------------------------------------------------------------------------
}