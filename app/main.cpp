//#include "ISFGLSLGenerator.h"
#include "ISFVal.hpp"
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace VVISF;




class MyImage	{
private:
	void		*imageData;
public:
	MyImage(void* inImageData=nullptr) : imageData(inImageData) {
		cout << __PRETTY_FUNCTION__ << endl;
	}
	//	copy constructor required by std::any
	MyImage(const MyImage & n)	{
		cout << __PRETTY_FUNCTION__ << endl;
	}
	~MyImage() {
		cout << __PRETTY_FUNCTION__ << endl;
	}
	
	friend std::ostream & operator<<(std::ostream & os, const MyImage & st);
	
	MyImage & operator=(const MyImage & n)	{
		if (this == &n)
			return *this;
		
		imageData = n.imageData;
		
		return *this;
	}
};




int main(int argc, const char * argv[]) {
	cout << __PRETTY_FUNCTION__ << endl;
	cout << "Hello, world!" << endl;
	
	//cout << TestEXPRTKFunction("3+3") << endl;

	//ISFVal<double>		tmpVal;
	//tmpVal = 3;
	
	//	simulate the creation of a user-provided image object
	void			*fakeImageData;
	MyImage			tmpImg(fakeImageData);
	cout << "tmpImg class is " << typeid(tmpImg).name() << endl;
	
	
	
	
	
	//ISFVal			tmpVal;
	//tmpVal.emplace<CreateISFValFloat>(4.20);
	//
	//if (const double * floatPtr = std::get_if<ISFValType_Float>(&tmpVal))
	//	cout << "variant is a float and its val is " << *floatPtr << endl;
	//else
	//	cout << "variant is not a float!" << endl;
	
	
	//tmpVal = tmpImg;
	//cout << "tmpImg's dims are " << tmpVal.width << " x " << tmpVal.height << endl;
	//cout << "MyImage's ptr is " << tmpImg.imageData << endl;

	cout << "Goodbye, world!" << endl;
	
	return 0;
}