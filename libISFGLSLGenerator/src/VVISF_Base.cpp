#include "VVISF_Base.hpp"

//#include "GLBuffer.hpp"
//#include "GLBufferPool.hpp"
#include "ISFDoc.hpp"


namespace fs = std::filesystem;




namespace VVISF
{


using namespace std;




/*	========================================	*/
#pragma mark --------------------- ISF file management methods


std::filesystem::path GetHomeDirectory()	{
	#if MAC==1 || LINUX==1
	//cout << "mac or linux OS detected" << endl;
	static const std::filesystem::path homeDirectory(std::getenv("HOME"));
	#elif WIN==1
	cout << "windows OS detected" << endl;
	std::getenv("");
	static const std::filesystem::path homeDrive(std::getenv("HOMEDRIVE"));
	static const std::filesystem::path homePath(std::getenv("HOMEPATH"));
	static const std::filesystem::path homeDirectory = homeDrive/homePath;
	#endif
	return homeDirectory;
}
std::filesystem::path PathByExpandingTildeInPath(const std::filesystem::path & inPath)	{
	//	if the path we were passed is empty, or it does NOT start with a tilde, just return it immediately
	auto iterator_begin = inPath.begin();
	auto iterator_end = inPath.end();
	if (iterator_begin == iterator_end)
		return inPath;
	
	static const string tilde_character_string { "~" };
	auto first_component_string = iterator_begin->string();
	if (first_component_string != tilde_character_string)
		return inPath;
	
	//	...if we're here, the path we were passed definitely starts with a tilde, which needs to be replaced.
	
	static const std::filesystem::path homeDirectory = GetHomeDirectory();
	//cout << "home is: " << homeDirectory << endl;
	//	advance the beginning iterator one place, we want to skip the beginning tilde while processing...
	++iterator_begin;
	//	populate the path we'll be returning!
	std::filesystem::path returnMe { homeDirectory };
	for (auto component = iterator_begin; component != iterator_end; ++component)	{
		returnMe /= *component;
	}
	return returnMe;
}


shared_ptr<vector<string>> CreateArrayOfISFsForPath(const string & inPath, const ISFFileType & inType, const bool & inRecursive)	{
	cout << __PRETTY_FUNCTION__ << "... " << inPath << endl;
	fs::path		path { inPath };
	if (!exists(path))	{
		cout << "ERR: passed path (" << path << ") doesn't exist, " << __PRETTY_FUNCTION__ << endl;
		//return nullptr;
		return make_shared<vector<string>>();
	}
	if (!is_directory(path))	{
		cout << "ERR: passed path (" << path << ") isn't a directory, " << __PRETTY_FUNCTION__ << endl;
		//return nullptr;
		return make_shared<vector<string>>();
	}
	bool					r = inRecursive;
	//ISFFileType				func = inType;
	
	shared_ptr<vector<string>>		returnMe = make_shared<vector<string>>();
	
	//	this lambda checks the passed string (which contains a path) and adds it to 'returnMe' if its extension indicates it's a shader
	auto CheckPathForISFFile = [&](const fs::path & inPath)	{
		string		extension = inPath.extension();
		const char *	cExtension = extension.c_str();
		if (strcasecmp(cExtension, ".fs") == 0
		|| strcasecmp(cExtension, ".frag") == 0
		|| strcasecmp(cExtension, ".isf") == 0)
		{
			returnMe->push_back( inPath.string() );
		}
	};
	
	if (inRecursive)	{
		for (const auto & entry : fs::recursive_directory_iterator(inPath))	{
			CheckPathForISFFile(entry.path());
		}
	}
	else	{
		for (const auto & entry : fs::directory_iterator(inPath))	{
			CheckPathForISFFile(entry.path());
		}
	}
	
	return returnMe;
}
shared_ptr<vector<string>> CreateArrayOfDefaultISFs(const ISFFileType & inType)	{
#if defined(MAC) && MAC==1
	shared_ptr<vector<string>>		global_paths = CreateArrayOfISFsForPath("/Library/Graphics/ISF", ISFFileType_All, true);
	shared_ptr<vector<string>>		local_paths = CreateArrayOfISFsForPath(PathByExpandingTildeInPath("~/Library/Graphics/ISF"), ISFFileType_All, true);
	
	shared_ptr<vector<string>>		returnMe = make_shared<vector<string>>();
	
	returnMe->insert( returnMe->end(), std::make_move_iterator(global_paths->begin()), std::make_move_iterator(global_paths->end()) );
	global_paths->erase( global_paths->begin(), global_paths->end() );
	
	returnMe->insert( returnMe->end(), std::make_move_iterator(local_paths->begin()), std::make_move_iterator(local_paths->end()) );
	local_paths->erase( local_paths->begin(), local_paths->end() );
	
	return returnMe;
#elif defined(LINUX) && LINUX==1
#elif defined(WIN) && WIN==1
	return CreateArrayOfISFsForPath("/ProgramData/ISF", ISFFileType_All, true);
#endif
}


bool FileIsProbablyAnISF(const string & pathToFile)	{
	//return false;
	bool		returnMe = false;
	try	{
		ISFDoc		tmpDoc(pathToFile);
		returnMe = true;
	}
	catch (ISFErr)	{
	
	}
	return returnMe;
}
string ISFFileTypeString(const ISFFileType & n)	{
	switch (n)	{
	case ISFFileType_None:
		return string("Unknown");
	case ISFFileType_Source:
		return string("Source");
	case ISFFileType_Filter:
		return string("Filter");
	case ISFFileType_Transition:
		return string("Transition");
	case ISFFileType_All:
		return string("All");
	}
	return string("?");
}






}
