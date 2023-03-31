//#include "ISFGLSLGenerator.h"
#include "VVISF.hpp"
#include <iostream>
#include <typeinfo>
#include <filesystem>

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
	
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-Audio.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-AudioFFT.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-Bool.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-Color.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-Event.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-Float.fs");
	string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-Functionality.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-IMG_NORM_PIXEL.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-IMG_PIXEL.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-IMG_THIS_NORM_PIXEL.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-IMG_THIS_PIXEL.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-ImportedImage.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-Long.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-MultiPassRendering.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-PersistentBuffer.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-PersistentBufferDifferingSizes.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-Point.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-Sampler.fs");
	//string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-TempBufferDifferingSizes.fs");
	
	ISFDocRef			tmpDoc = CreateISFDocRef(tmpString);
	string			*fragSrc = new std::string();
	string			*vertSrc = new std::string();
	tmpDoc->generateShaderSource(fragSrc, vertSrc, GLVersion_4, false);
	
	cout << "***************************************************************" << endl;
	cout << *vertSrc << endl;
	cout << "***************************************************************" << endl;
	cout << *fragSrc << endl;
	cout << "***************************************************************" << endl;
	
	
	delete fragSrc;
	fragSrc = nullptr;
	delete vertSrc;
	vertSrc = nullptr;
	
	/*
	//	simulate the creation of a user-provided image object
	//void			*fakeImageData;
	//MyImage			tmpImg(fakeImageData);
	//cout << "tmpImg class is " << typeid(tmpImg).name() << endl;
	
	string			tmpString("/Users/testadmin/Documents/VDMX5/VDMX5/supplemental resources/ISF tests+tutorials/Test-Functionality.fs");
	ISFDocRef		tmpDoc = CreateISFDocRef(tmpString);
	string			*fragSrc = new std::string();
	string			*vertSrc = new std::string();
	tmpDoc->generateShaderSource(fragSrc, vertSrc, GLVersion_4, false);
	
	
	//string			baseDir = VVISF::PathByExpandingTildeInPath("/Library/Graphics/ISF");
	//std::shared_ptr<vector<string>>		files = CreateArrayOfISFsForPath(baseDir, ISFFileType_All);
	
	std::shared_ptr<vector<string>>		files = CreateArrayOfDefaultISFs();
	
	for (const auto & file : *files)	{
		cout << "\tfound file " << std::filesystem::path(file).stem() << endl;
		ISFDocRef		tmpDoc = CreateISFDocRef(file);
		std::string		fragSrc;
		std::string		vertSrc;
		tmpDoc->generateShaderSource(&fragSrc, &vertSrc, GLVersion_2, false);
		cout << "***************************************************************" << endl;
		cout << vertSrc << endl;
		cout << "***************************************************************" << endl;
		cout << fragSrc << endl;
		cout << "***************************************************************" << endl;
		break;
	}
	
	
	//cout << "******************" << endl;
	//cout << *vertSrc << endl;
	//cout << "******************" << endl;
	//cout << "******************" << endl;
	//cout << *fragSrc << endl;
	//cout << "******************" << endl;
	
	
	delete fragSrc;
	fragSrc = nullptr;
	delete vertSrc;
	vertSrc = nullptr;
	*/

	cout << "Goodbye, world!" << endl;
	
	return 0;
}