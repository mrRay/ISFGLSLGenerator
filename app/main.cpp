//#include "ISFGLSLGenerator.h"
#include "VVISF.hpp"
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace VVISF;



/*
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
*/



int main(int argc, const char * argv[]) {
	cout << __PRETTY_FUNCTION__ << endl;
	//cout << "Hello, world!" << endl;
	
	//	simulate the creation of a user-provided image object
	//void			*fakeImageData;
	//MyImage			tmpImg(fakeImageData);
	//cout << "tmpImg class is " << typeid(tmpImg).name() << endl;
	
	string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-Functionality.fs");
	ISFDocRef		tmpDoc = CreateISFDocRef(tmpString);
	string			*fragSrc = new std::string();
	string			*vertSrc = new std::string();
	tmpDoc->generateShaderSource(fragSrc, vertSrc, GLVersion_4, false);
	
	/*
	cout << "******************" << endl;
	cout << *vertSrc << endl;
	cout << "******************" << endl;
	cout << "******************" << endl;
	cout << *fragSrc << endl;
	cout << "******************" << endl;
	*/
	
	delete fragSrc;
	fragSrc = nullptr;
	delete vertSrc;
	vertSrc = nullptr;
	
	cout << "Goodbye, world!" << endl;
	
	return 0;
}