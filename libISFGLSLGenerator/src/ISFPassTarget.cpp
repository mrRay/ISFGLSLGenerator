#include "ISFPassTarget.hpp"
//#include "ISFScene.hpp"
#include "ISFDoc.hpp"




namespace VVISF
{


using namespace std;
using namespace exprtk;



//	this function modifies the passed vars, so you shoud probably make sure the owning doc is locked before running it
void ExpressionUpdater(string ** exprString, expression<double> ** expr, const map<string,double*> & inSubDict, double * outVal);
//	this is the global copier shared amongst all pass targets as a backup.
//static GLTexToTexCopierRef _isfPassTargetCopier = nullptr;




/*	========================================	*/
#pragma mark *************** ISFPassTarget class ***************

/*	========================================	*/
#pragma mark --------------------- factory/creation

ISFPassTargetRef ISFPassTarget::Create(const string & inName, const ISFDoc * inParentDoc)	{
	return make_shared<ISFPassTarget>(inName, inParentDoc);
}
void ISFPassTarget::cleanup()	{
	//_isfPassTargetCopier = nullptr;
}

/*	========================================	*/
#pragma mark --------------------- constructor/destructor

ISFPassTarget::ISFPassTarget(const string & inName, const ISFDoc * inParentDoc)	{
	//cout << __PRETTY_FUNCTION__ << "->" << this << endl;
	_name = string(inName);
	_parentDoc = (ISFDoc *)inParentDoc;
	//_cachedUnis[0] = make_shared<GLCachedUni>(_name);
	//_cachedUnis[1] = make_shared<GLCachedUni>(std::format("_{}_imgRect",_name));
	//_cachedUnis[2] = make_shared<GLCachedUni>(std::format("_{}_imgSize",_name));
	//_cachedUnis[3] = make_shared<GLCachedUni>(std::format("_{}_flip",_name));
}
ISFPassTarget::~ISFPassTarget()	{
	//cout << __PRETTY_FUNCTION__ << "->" << this << endl;
	
	lock_guard<mutex>		lock(_targetLock);
	if (_targetWidthString != nullptr)	{
		delete _targetWidthString;
		_targetWidthString = nullptr;
	}
	if (_targetWidthExpression != nullptr)	{
		delete _targetWidthExpression;
		_targetWidthExpression = nullptr;
	}
	if (_targetHeightString != nullptr)	{
		delete _targetHeightString;
		_targetHeightString = nullptr;
	}
	if (_targetHeightExpression != nullptr)	{
		delete _targetHeightExpression;
		_targetHeightExpression = nullptr;
	}
}

/*	========================================	*/
#pragma mark --------------------- getters/setters

void ISFPassTarget::setTargetSize(const int & inWidth, const int & inHeight, const bool & inResize, const bool & inCreateNewBuffer)	{
	//using namespace VVISF;
	using namespace std;
	
	_targetWidth = inWidth;
	_targetHeight = inHeight;
	
	//	if the buffer's currently nil
	if (_image == nullptr)	{
		if (inCreateNewBuffer)	{
			_image = make_shared<ISFImage>(inWidth, inHeight);
		}
	}
	//	else there's a buffer...
	else	{
		//	if the buffer size is wrong...
		if (inWidth != _image->width || inHeight != _image->height)	{
			//	if i'm supposed to resize, do so
			if (inResize)	{
				ISFImageRef		newBuffer = make_shared<ISFImage>(inWidth, inHeight);
				_image = newBuffer;
			}
			//	else i'm not supposed to resize
			else	{
				//	if i'm supposed to create a new buffer
				if (inCreateNewBuffer)	{
					_image = make_shared<ISFImage>(inWidth, inHeight);
				}
				//	else i'm not supposed to create a new buffer
				else	{
					_image = nullptr;
				}
			}
		}
		//	else the buffer size is fine- do nothing...
		
	}
}
void ISFPassTarget::setTargetWidthString(const string & n)	{
	//cout << __PRETTY_FUNCTION__ << endl;
	
	lock_guard<mutex>		lock(_targetLock);
	
	if (_targetWidthString != nullptr)	{
		delete _targetWidthString;
		_targetWidthString = nullptr;
	}
	if (_targetWidthExpression != nullptr)	{
		delete _targetWidthExpression;
		_targetWidthExpression = nullptr;
	}
	
	if (n.length() < 1)
		return;
	
	_targetWidthString = new string(n);
	//	leave the expression nil- it'll be instantiated (and compiled) when we evaluate (we need to provide a symbol table with variables)
}
const string ISFPassTarget::targetWidthString()	{
	lock_guard<mutex>		lock(_targetLock);
	return (_targetWidthString==nullptr) ? string("") : string(*_targetWidthString);
}
void ISFPassTarget::setTargetHeightString(const string & n)	{
	//cout << __PRETTY_FUNCTION__ << endl;
	
	lock_guard<mutex>		lock(_targetLock);
	
	if (_targetHeightString != nullptr)	{
		delete _targetHeightString;
		_targetHeightString = nullptr;
	}
	if (_targetHeightExpression != nullptr)	{
		delete _targetHeightExpression;
		_targetHeightExpression = nullptr;
	}
	
	if (n.length() < 1)
		return;
	
	_targetHeightString = new string(n);
	//	leave the expression nil- it'll be instantiated (and compiled) when we evaluate (we need to provide a symbol table with variables)
}
const string ISFPassTarget::targetHeightString()	{
	lock_guard<mutex>		lock(_targetLock);
	return (_targetHeightString==nullptr) ? string("") : string(*_targetHeightString);
}
void ISFPassTarget::setFloatFlag(const bool & n)	{
	using namespace std;
	
	bool		changed = (_floatFlag==n) ? false : true;
	if (!changed)
		return;
	_floatFlag = n;
	if (_image != nullptr)	{
		ISFImageRef		newBuffer = make_shared<ISFImage>(_targetWidth, _targetHeight);
		if (newBuffer != nullptr)	{
			_image = newBuffer;
		}
	}
}
void ISFPassTarget::setPersistentFlag(const bool & n)	{
	_persistentFlag = n;
}

/*	========================================	*/
#pragma mark --------------------- methods

void ISFPassTarget::clearBuffer()	{
	_image = nullptr;
}
void ISFPassTarget::evalTargetSize(const int & inWidth, const int & inHeight, std::map<std::string, double*> & inSymbols, const bool & inResize, const bool & inCreateNewBuffer)
{
	using namespace exprtk;
	
	//cout << __FUNCTION__ << endl;
	//cout << "\tbefore, target size was " << _targetWidth << " x " << _targetHeight << endl;
	double			newWidth = 1.0;
	double			newHeight = 1.0;
	{
		lock_guard<mutex>		lock(_targetLock);
		
		//	update my local size vars
		_widthExpressionVar = inWidth;
		_heightExpressionVar = inHeight;
		//	update the passed dict with the address of my local size vars
		inSymbols.erase(string("WIDTH"));
		inSymbols.insert(make_pair(string("WIDTH"), &_widthExpressionVar));
		inSymbols.erase(string("HEIGHT"));
		inSymbols.insert(make_pair(string("HEIGHT"), &_heightExpressionVar));
		
		//	evaluate the width/height expressions, outputting to a new size struct
		if (_targetWidthString == nullptr)
			newWidth = *(inSymbols[string("WIDTH")]);
		else	{
			//cout << "\tevaluating width string " << *_targetWidthString << endl;
			ExpressionUpdater(&_targetWidthString, &_targetWidthExpression, inSymbols, &newWidth);
		}
	
		if (_targetHeightString == nullptr)
			newHeight = *(inSymbols[string("HEIGHT")]);
		else	{
			//cout << "\tevaluating height string " << *_targetHeightString << endl;
			ExpressionUpdater(&_targetHeightString, &_targetHeightExpression, inSymbols, &newHeight);
		}
	}
	if (std::isnan(newWidth))
		newWidth = 1.;
	if (std::isnan(newHeight))
		newHeight = 1.;
	
	//	set the target size based on the new size i just calculated
	//cout << "\tsetting target size to " << newSize.width << " x " << newSize.height << endl;
	setTargetSize(newWidth, newHeight, inResize, inCreateNewBuffer);
	
	//cout << "\t" << __FUNCTION__ << "- FINISHED" << endl;
}




void ExpressionUpdater(string ** exprString, expression<double> ** expr, const map<string,double*> & inSubDict, double * outVal)	{
	//cout << __PRETTY_FUNCTION__ << endl;
	
	//	if there's an expression
	if (*expr != nullptr)	{
		//cout << "\t\tthere's already an expression- updating values...\n";
		bool		deleteFlag = false;
		symbol_table<double> &		exprTable = (*expr)->get_symbol_table();
		
		//	run through the substitution dict
		for (auto const & it : inSubDict)	{
			//	if this key isn't in the symbol table, bail and flag for deletion
			if (!exprTable.is_variable(it.first))	{
				deleteFlag = true;
				break;
			}
			
			//	else the key is in the symbol table- update the value
			//else	{
			//	double &		tmpVar = exprTable.get_variable(it.first)->ref();
			//	tmpVar = it.second;
			//	//cout << "\t\t\tupdated " << it.first << " to " << tmpVar << endl;
			//}
			
		}
		
		//exprTable.clear();
		//for (auto const & it : inSubDict)	{
		//	exprTable.add_variable(it.first, const_cast<double&>(it.second));
		//}
		
		//	if i'm flagged for deletion- delete the expression
		if (deleteFlag)	{
			delete *expr;
			*expr = nullptr;
		}
	}
	//	if there's an expression string but no expression
	if (*exprString != nullptr && *expr == nullptr)	{
		//cout << "\t\tmaking an expression...\n";
		//	make a new expression, set it up with a symbol table, and compile it
		*expr = new expression<double>;
		symbol_table<double>		tmpTable;
		parser<double>				tmpParser;
		for (auto const & it : inSubDict)	{
			//tmpTable.add_variable(it.first, const_cast<double&>(it.second));
			tmpTable.add_variable(it.first, const_cast<double&>(*(it.second)));
			//double			tmpDouble = it.second;
			//tmpTable.add_variable(it.first, tmpDouble);
		}
		(*(*expr)).register_symbol_table(tmpTable);
		tmpParser.compile(**exprString, **expr);
	}
	//	if there's an expression, evaluate it and dump it to the output value
	if (*expr != nullptr)	{
		*outVal = (*(*expr)).value();
		
		//delete *expr;
		//*expr = nullptr;
	}
	
}



}
