#include "VVISF_StringUtils.hpp"

//#include "VVISF_Base.hpp"
#include "ISFVal.hpp"

#include "exprtk.hpp"




namespace VVISF
{


using namespace std;


/*	========================================	*/
#pragma mark --------------------- string manipulation functions




//vector<string> PathComponents(const string & n) {
//	//cout << __PRETTY_FUNCTION__ << endl;
//	
//	vector<string>		returnMe(0);
//	//	count the # of the path delineators in the string, reserve space in the vector we're returning
//#if defined(VVGL_SDK_WIN)
//	size_t				delimCount = count(n.begin(), n.end(), '\\') + 1;
//#else
//	size_t				delimCount = count(n.begin(), n.end(), '/') + 1;
//#endif
//	returnMe.reserve(delimCount);
//	//	get the ptr to the string data
//	char				*inString = const_cast<char*>(n.data());
//	//	tokenize the string data, creating strings in the vector we'll be returning
//#if defined(VVGL_SDK_WIN)
//	const char			*delimPtr = "\\";
//#else
//	const char			*delimPtr = "/";
//#endif
//	char				*token = strtok(inString, delimPtr);
//	while (token != nullptr)	{
//		//cout << "\ttoken: " << token << endl;
//		returnMe.push_back(string(token));
//		token = strtok(NULL, delimPtr);
//	}
//	return returnMe;
//}
//string LastPathComponent(const string & n)	{
//#if defined(VVGL_SDK_WIN)
//	size_t		lastSlashIndex = n.find_last_of('\\');
//#else
//	size_t		lastSlashIndex = n.find_last_of('/');
//#endif
//	if (lastSlashIndex == string::npos)
//		return n;
//	else if (lastSlashIndex == (n.length()-1))
//		return n;
//	return n.substr(lastSlashIndex+1);
//}
//string StringByDeletingLastPathComponent(const string & n)	{
//#if defined(VVGL_SDK_WIN)
//	size_t		lastSlashIndex = n.find_last_of('\\');
//#else
//	size_t		lastSlashIndex = n.find_last_of('/');
//#endif
//	if (lastSlashIndex == string::npos)
//		return n;
//	else if (lastSlashIndex == 0)
//		return n;
//	return n.substr(0, lastSlashIndex);
//}
std::filesystem::path PathByDeletingLastPathComponent(const std::filesystem::path & inPath)	{
	//cout << __PRETTY_FUNCTION__ << ", " << inPath << endl;
	auto iterator_begin = inPath.begin();
	auto iterator_end = inPath.end();
	//	if there aren't any path components (if it's an empty path), just bail and return the path we were passed
	if (iterator_begin == iterator_end)
		return inPath;
	//	we want to iterate across everything EXCEPT the last path component, so adjust the iterator- and then check to make sure we'll still be returning something
	--iterator_end;
	if (iterator_begin == iterator_end)
		return std::filesystem::path { };
	//	assemble the path we're going to return
	std::filesystem::path outPath { };
	for (auto component = inPath.begin(); component != iterator_end; ++component)	{
		outPath /= *component;
	}
	return outPath;
}
//string PathFileExtension(const string & n)	{
//	size_t			extensionIndex = n.find_last_of(".");
//	if (extensionIndex == string::npos || extensionIndex == 0)
//		return n;
//	else if (extensionIndex == (n.length()-1))
//		return n;
//	return n.substr(extensionIndex+1);
//}
//string StringByDeletingExtension(const string & n)	{
//	size_t			extensionIndex = n.find_last_of(".");
//	if (extensionIndex == string::npos)
//		return n;
//	return n.substr(0, extensionIndex);
//}
//string StringByDeletingLastAndAddingFirstSlash(const string & n)	{
//	if (n.size()<1)
//		return string("");
//	
//	int			tmpLen = int(n.size());
//#if defined(VVGL_SDK_WIN)
//	bool		hasFirst = (n[0] == '\\') ? true : false;
//	bool		hasLast = (n[tmpLen - 1] == '\\') ? true : false;
//#else
//	bool		hasFirst = (n[0]=='/') ? true : false;
//	bool		hasLast = (n[tmpLen-1]=='/') ? true : false;
//#endif
//	string		returnMe = n;
//	if (hasLast)	{
//		if (tmpLen > 1) {
//			returnMe.pop_back();
//		}
//	}
//	if (!hasFirst)	{
//#if defined(VVGL_SDK_WIN)
//		returnMe.insert(0, 1, '\\');
//#else
//		returnMe.insert(0, 1, '/');
//#endif
//	}
//	return returnMe;
//}
//string StringByDeletingLastSlash(const string & n)	{
//	if (n.size()<1)
//		return string("");
//	
//	//bool		hasFirst = (n[0]=='/') ? true : false;
//	int			tmpLen = int(n.size());
//#if defined(VVGL_SDK_WIN)
//	bool		hasLast = (n[tmpLen - 1] == '\\') ? true : false;
//#else
//	bool		hasLast = (n[tmpLen-1]=='/') ? true : false;
//#endif
//	string		returnMe = n;
//	if (hasLast)	{
//		if (tmpLen > 1) {
//			returnMe.pop_back();
//		}
//	}
//	//if (!hasFirst)
//	//	returnMe.insert(0, 1, '/');
//	return returnMe;
//}
//bool CaseInsensitiveCompare(const string & a, const string & b) {
//	size_t		sz = a.size();
//	if (b.size() != sz)
//		return false;
//	for (unsigned int i = 0; i < sz; ++i)	{
//		if (tolower(a[i]) != tolower(b[i])) {
//			return false;
//		}
//	}
//	return true;
//}
string FmtString(const char * fmt, ...) {
	va_list			args;
	va_start(args, fmt);
	int				tmpLen = vsnprintf(nullptr, 0, fmt, args) + 1;
	va_end(args);
	
	if (tmpLen < 1)
		return string("");
	
	va_start(args, fmt);
	char			*buf = (char*)malloc(tmpLen*sizeof(char));
	memset(buf, 0, tmpLen);
	vsnprintf(buf, tmpLen, fmt, args);
	va_end(args);
	string			returnMe = string(buf);
	free(buf);
	return returnMe;
}
int NumLines(const string & n)	{
	int			returnMe = 0;
	for (const char & c : n)	{
		switch (c)	{
		case '\r':
		case '\n':
			++returnMe;
			break;
		default:
			break;
		}
	}
	return returnMe;
}




ISFVal ParseStringAsBool(const string & n)	{
	string			testStrings[4] = { string("yes"), string("true"), string("no"), string("false") };
	for (int testStrIdx=0; testStrIdx<4; ++testStrIdx)	{
		if (testStrings[testStrIdx].size() == n.size())	{
			bool		match = true;
			auto		itA = testStrings[testStrIdx].begin();
			auto		itB = n.begin();
			for (itA=testStrings[testStrIdx].begin(), itB=n.begin(); itA!=testStrings[testStrIdx].end(); ++itA, ++itB)	{
				if (tolower(*itA) != (*itB))	{
					match = false;
					break;
				}
			}
			if (match)	{
				if (testStrIdx < 2)
					return CreateISFValBool(true);
				else
					return CreateISFValBool(false);
			}
		}
	}
	return CreateISFValNull();
}

ISFVal ISFValByEvaluatingString(const string & n, const map<string, double> & inSymbols)	{
	exprtk::expression<double>		expr;
	exprtk::symbol_table<double>	table;
	exprtk::parser<double>			parser;
	
	size_t			inSymbolsCount = inSymbols.size();
	//double			tmpVars[inSymbolsCount];
	double			*tmpVars = (double*)malloc(sizeof(double)*inSymbolsCount);
	
	if (inSymbolsCount > 0)	{
		//vector<double>		tmpVars;
		//tmpVars->reserve(inSymbolsCount);
		int				i=0;
		for (auto const & it : inSymbols)	{
			//double		tmpDouble = it.second;
			//table.add_variable(it.first.c_str(), tmpDouble);
			tmpVars[i] = it.second;
			table.add_variable(it.first.c_str(), tmpVars[i]);
			++i;
		}
		expr.register_symbol_table(table);
	}
	free(tmpVars);
	tmpVars = nullptr;
	
	parser.compile(n, expr);
	
	return CreateISFValFloat(expr.value());
}

Range LexFunctionCall(const string & inBaseStr, const Range & inFuncNameRange, vector<string> & outVarArray)	{
	//cout << __PRETTY_FUNCTION__ << endl;
	
	if (inFuncNameRange.len==0 || inFuncNameRange.max()>inBaseStr.size())
		return Range(0,0);
	//if (inFuncLen==0 || ((inFuncLen+inFuncLen)>inBaseStr.size()))
	//	return Range(0,0);
	size_t		searchStartIndex = inFuncNameRange.max();
	size_t		lexIndex = searchStartIndex;
	size_t		openGroupingCount = 0;
	Range	substringRange(0,0);
	substringRange.loc = searchStartIndex + 1;
	do	{
		switch (inBaseStr[lexIndex])	{
		case '(':
		case '{':
			++openGroupingCount;
			break;
		case ')':
		case '}':
			--openGroupingCount;
			if (openGroupingCount == 0)	{
				substringRange.len = lexIndex - substringRange.loc;
				string		groupString = inBaseStr.substr(substringRange.loc, substringRange.len);
				groupString = TrimWhitespace(groupString);
				outVarArray.push_back(groupString);
			}
			break;
		case ',':
			if (openGroupingCount == 1)	{
				substringRange.len = lexIndex - substringRange.loc;
				string		groupString = inBaseStr.substr(substringRange.loc, substringRange.len);
				groupString = TrimWhitespace(groupString);
				outVarArray.push_back(groupString);
				substringRange.loc = lexIndex + 1;
			}
			break;
		}
		++lexIndex;
	} while (openGroupingCount > 0);
	Range	rangeToReplace = Range(inFuncNameRange.loc, lexIndex-inFuncNameRange.loc);
	return rangeToReplace;
}
string TrimWhitespace(const string & inBaseStr)	{
	Range		wholeRange(0, inBaseStr.size());
	//cout << "\t" << __PRETTY_FUNCTION__ << "- FINISHED\n";
	//return inBaseStr.substr(wholeRange.loc, wholeRange.len);
	
	Range		trimmedRange = wholeRange;
	size_t			tmpPos = inBaseStr.find_last_not_of(" \t\r\n");
	if (tmpPos != string::npos)
		trimmedRange.len = tmpPos+1;
	tmpPos = inBaseStr.find_first_not_of(" \t\r\n");
	if (tmpPos != string::npos)
		trimmedRange.loc = tmpPos;
	trimmedRange.len -= trimmedRange.loc;
	if (wholeRange == trimmedRange)
		return inBaseStr;
	return inBaseStr.substr(trimmedRange.loc, trimmedRange.len);
	
}
void FindAndReplaceInPlace(string & inSearch, string & inReplace, string & inBase)	{
	size_t		pos = 0;
	while ((pos=inBase.find(inSearch, pos)) != string::npos)	{
		inBase.replace(pos, inSearch.length(), inReplace);
		pos += inReplace.length();
	}
}
void FindAndReplaceInPlace(const char * inSearch, const char * inReplace, string & inBase)	{
	string		is(inSearch);
	string		ir(inReplace);
	FindAndReplaceInPlace(is, ir, inBase);
}


string FullPath(const string & inRelativePath)	{
#if _WIN32
	char		*outPath = _fullpath(NULL, inRelativePath.c_str(), 0);
	return std::string(outPath);
#else
	char		*outPath = realpath(inRelativePath.c_str(), NULL);
	return std::string(outPath);
#endif
}


}

