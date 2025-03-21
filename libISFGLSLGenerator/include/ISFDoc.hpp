#ifndef ISFDoc_hpp
#define ISFDoc_hpp

#include <vector>
#include <mutex>
#include "VVISF_Base.hpp"
#include "ISFAttr.hpp"




namespace VVISF
{




/*!
\ingroup VVISF_BASIC
\brief Describes an "ISF file"- requires an actual file on disk which is parsed.  Capable of generating GLSL source code for the various shader types.

Constructing an instance of this class will load the files from disk into local std::string vars, parse them, and populate the instance with all the attributes(ISFAttr)/passes(ISFPassTarget) necessary to fully describe the ISF file.

Notes on use:
- ISFDoc's constructor will throw an ISFErr if the file cannot be opened, or if there's a problem parsing the JSON blob in the ISF file.
- ISFDoc can be used to examine the properties of "ISF files" on disk- create an ISFDoc instance, passing the constructor the path of the file to load, and then then you can examing the properties of the doc to get info about the ISF file.
*/
class ISFDoc	{
	private:
		std::recursive_mutex		_propLock;
		
		std::string		*_path = nullptr;	//	full path to the loaded file
		std::string		*_name = nullptr;	//	just the file name (including its extension)
		std::string		*_description = nullptr;	//	description of whatever the file does
		std::string		*_credit = nullptr;	//	credit
		std::string		*_vsn = nullptr;
		ISFFileType		_type = ISFFileType_Source;
		bool			_throwExcept = true;
		
		std::vector<std::string>	_categories;	//	array of strings of the category names this doc should be listed under
		std::vector<ISFAttrRef>		_imageImports;	//	array of ISFAttrRef instances that describe imported images. attrib's 'attribName' is the name of the sampler, attrib's 'description' is the path to the file.
		std::vector<ISFAttrRef>		_inputs;	//	array of ISFAttrRef instances for the various inputs
		std::vector<ISFAttrRef>		_imageInputs;	//	array of ISFAttrRef instances for the image inputs (the image inputs are stored in two arrays).
		std::vector<ISFAttrRef>		_audioInputs;	//	array of ISFAttrRef instances for the audio inputs (the audio inputs are stored in two arrays)
		std::vector<ISFAttrRef>		_cubeInputs;
		std::vector<ISFAttrRef>		_colorInputs;	//	array of ISFAttrRef instances that describe color inputs.  separate array because we have to declare attrs types in a specific order to ensure the variables are all aligned.
		std::vector<ISFAttrRef>		_pointInputs;	//	array of ISFAttrRef instances that describe point inputs.  separate array because we have to declare attrs types in a specific order to ensure the variables are all aligned.
		
		uint32_t		_maxUBOSize { 0 };
		//bool					bufferRequiresEval = false;	//	NO by default, set to YES during file open if any of the buffers require evaluation (faster than checking every single buffer every pass)
		//std::vector<std::string>		_renderPasses;
		std::vector<ISFPassTargetRef>	_renderPasses;
		
		std::string			*_jsonSourceString = nullptr;	//	the JSON std::string from the source *including the comments and any linebreaks before/after it*
		std::string			*_jsonString = nullptr;	//	the JSON std::string copied from the source- doesn't include any comments before/after it
		std::string			*_vertShaderSource = nullptr;	//	the raw vert shader source before being find-and-replaced
		std::string			*_fragShaderSource = nullptr;	//	the raw frag shader source before being find-and-replaced
		bool		_hasCustomVertShader = false;
		
	public:
		
		/*!
		\name Constructors
		*/
		///@{
		
		//! Constructs an ISFDoc instance from a passed file on disk.  Consider using CreateISFDocRef() instead.
		/*!
		\param inPath The path to the ISF file you want to load as an ISFDoc.
		\param inThrowExcept Whether or not the ISFDoc should throw any exceptions if it encounters errors parsing anything.
		Throws an ISFErr if there is a problem of some sort loading the ISF file from disk or parsing the JSON in the ISF file.
		*/
		ISFDoc(const std::string & inPath, const bool & inThrowExcept=true) noexcept(false);
		
		//! Constructs an ISFDoc instance from shader strings.  Consider using CreateISFDocRef() instead.
		/*
		\param inFSContents A std::string containing the fragment shader portion of the ISF file.  The JSON blob that defines the ISF file must be contained in here.
		\param inVSContents A std::string containing the vertex shader portion of the ISF file.  If you don't have a vertex shader to pass, VVISF defines a static std::string "ISFVertPassthru_GL2", which should work as a "passthru" vertex shader for most purposes.
		\param inImportsDir A std::string containing the path to the directory that will contain any related media files (used for IMPORT/etc).
		\param inThrowExcept Whether or not the ISFDoc should throw any exceptions if it encounters errors parsing anything.
		Throws an ISFErr if there is a problem of some sort parsing the JSON blob from the frag shader std::string.
		*/
		ISFDoc(const std::string & inFSContents, const std::string & inVSContents, const std::string & importsDir, const bool & inThrowExcept=true);
		
		///@}
		
		
		~ISFDoc();
		
		
		/*!
		\name ISF file properties
		*/
		///@{
		
		//!	Returns the path of the ISF file for the receiver.  This is probably the path to the frag shader.
		std::string path() const { return (_path==nullptr) ? std::string("") : std::string(*_path); }
		//!	Returns the name of the receiver's ISF file (the file name, minus the extension).
		std::string name() const { return (_name==nullptr) ? std::string("") : std::string(*_name); }
		//!	Returns the receiver's "description" std::string, as defined in its JSON blob ("DESCRIPTION").
		std::string description() const { return (_description==nullptr) ? std::string("") : std::string(*_description); }
		//!	Returns the receiver's "credit" std::string, as defined in its JSON blob ("CREDIT").
		std::string credit() const { return (_credit==nullptr) ? std::string("") : std::string(*_credit); }
		//!	Returns the receiver's "vsn" std::string, as defined in its JSON blob ("VSN")
		std::string vsn() const { return (_vsn==nullptr) ? std::string("") : std::string(*_vsn); }
		//!	Returns the receiver's file type.
		ISFFileType type() const { return _type; }
		//! Returns the max size of the buffer necessary to pass all of the attribute and pass data to the shader.  calculated when the doc's created.
		uint32_t getMaxUBOSize() const { return _maxUBOSize; }
		//!	Returns a std::vector containing strings listing the receiver's categories.
		std::vector<std::string> & categories() { return _categories; }
		//!	Returns a bool indicating whether or not the ISF's vertex shader was generated using a user-provided vertex shader.
		bool hasCustomVertShader() const { return _hasCustomVertShader; }
		
		///@}
		
		
		/*!
		\name ISF attribute/INPUT getters
		*/
		///@{
		
		//!	Returns a std::vector of ISFAttrRef instances describing all of the receiver's inputs.
		std::vector<ISFAttrRef> & inputs() { return _inputs; }
		//!	Returns a std::vector of ISFAttrRef instances describing only the receiver's image inputs.
		std::vector<ISFAttrRef> & imageInputs() { return _imageInputs; }
		//!	Returns a std::vector of ISFAttrRef instances describing only the receiver's audio inputs.
		std::vector<ISFAttrRef> & audioInputs() { return _audioInputs; }
		//!	Returns a std::vector of ISFAttrRef instances describing only the receiver's audioFFT inputs.
		std::vector<ISFAttrRef> & imageImports() { return _imageImports; }
		//!	Returns a std::vector of ISFAttrRef instances describing only the receiver's inputs that match the passed type.
		std::vector<ISFAttrRef> inputsOfType(const ISFValType & inInputType);
		//!	Returns the ISFAttrRef for the input with the passed name
		ISFAttrRef input(const std::string & inAttrName);
		
		///@}
		
		
		/*!
		\name ISF render pass getters
		*/
		///@{
		
		//!	Returns a std::vector of std::std::string instances describing the names of the render passes, in order.  If the names were not specified properly in the JSON blob, this array will be incomplete or inaccurate and rendering won't work!
		std::vector<ISFPassTargetRef> & renderPasses() { return _renderPasses; }
		//!	Returns the ISFPassTarget that matches the passed key.  Returns null if no pass could be found.
		const ISFPassTargetRef passTargetForKey(const std::string & n);
		//!	Returns the ISFPassTarget that matches the passed key.  Returns null if no pass could be found or if the pass found wasn't flagged as requiring a persistent buffer.
		const ISFPassTargetRef persistentPassTargetForKey(const std::string & n);
		//!	Returns the ISFPassTarget that matches the passed key.  Returns null if no pass could be found or if the pass found was flagged as requiring a persistent buffer.
		const ISFPassTargetRef tempPassTargetForKey(const std::string & n);
		
		///@}
		
		
		/*!
		\name ISF file source code getters
		*/
		///@{
		
		//! Returns the JSON std::string from the source *including the comments and any linebreaks before/after it*
		std::string * jsonSourceString() const { return _jsonSourceString; }
		//!	Returns the JSON std::string copied from the source- doesn't include any comments before/after it
		std::string * jsonString() const { return _jsonString; }
		//!	Returns the raw vert shader source before being find-and-replaced
		std::string * vertShaderSource() const { return _vertShaderSource; }
		//!	Returns the raw frag shader source before being find-and-replaced
		std::string * fragShaderSource() const { return _fragShaderSource; }
		//!	Populates the passed var with the JSON std::string from the source *including the comments and any linebreaks before/after it*
		void jsonSourceString(std::string & outStr);
		
		///@}
		
		//	returns a std::string describing the type of the expected texture samplers ("R" for Rect, "C" for Cube).  save this, if it changes in a later pass the shader source must be generated again.
		std::string generateTextureTypeString();
		
		/*!
		\brief Returns a true if successful.  Generates GLSL source code, populating the provided vars with strings that are usable for frag/vert shaders
		\param outFragSrc A non-null pre-allocated std::std::string variable which will be populated with the fragment shader source code generated for this ISF file.
		\param outVertSrc A non-null pre-allocated std::std::string variable which will be populated with the vertex shader source code generated for this ISF file.
		\param inGLVers The version of OpenGL that the generated source code must be compatible with.
		\param inVarsAsUBO Defaults to false.  If true, variable declarations for non-image INPUTS will be assembled in a uniform block.  This option was added because a downstream utility requires it.
		*/
		bool generateShaderSource(std::string * outFragSrc, std::string * outVertSrc, const GLVersion & inGLVers, const bool & inVarsAsUBO=false, size_t * outUBOSize=nullptr);
		//	this method must be called before rendering (passes/etc may have expressions that require the render dims to be evaluated)
		void evalBufferDimensionsWithRenderSize(const int & inWidth, const int & inHeight);
		
		friend std::ostream & operator<<(std::ostream & os, const ISFDoc & n);
		
	protected:
		//	used so we can have two constructors without duplicating code
		void _initWithRawFragShaderString(const std::string & inRawFile);
		//	returns a true if successful.  populates a std::string with variable declarations for a frag shader
		bool _assembleShaderSource_VarDeclarations(std::string * outVSString, std::string * outFSString, const GLVersion & inGLVers, const bool & inVarsAsUBO=false, size_t * outUBOSize=nullptr);
		//	returns a true if successful.  populates a map with std::string/value pairs that will be used to evaluate variable names in strings
		bool _assembleSubstitutionMap(std::map<std::string,double*> * outMap);
};




//! Constructs an ISFDoc instance from a passed file on disk.
/*!
\relatedalso ISFDoc
\param inPath The path to the ISF file you want to load as an ISFDoc.
\param inThrowExcept Whether or not the ISFDoc should throw any exceptions if it encounters errors parsing anything.
Throws an ISFErr if there is a problem of some sort loading the ISF file from disk or parsing the JSON in the ISF file.
*/
inline ISFDocRef CreateISFDocRef(const std::string & inPath, const bool & inThrowExcept=true) noexcept(false) { return std::make_shared<ISFDoc>(inPath,inThrowExcept); }

//! Constructs an ISFDoc instance from shader strings.
/*!
\relatedalso ISFDoc
\param inFSContents A std::string containing the fragment shader portion of the ISF file.  The JSON blob that defines the ISF file must be contained in here.
\param inVSContents A std::string containing the vertex shader portion of the ISF file.  If you don't have a vertex shader to pass, VVISF defines a static std::string "ISFVertPassthru_GL2", which should work as a "passthru" vertex shader for most purposes.
\param inThrowExcept Whether or not the ISFDoc should throw any exceptions if it encounters errors parsing anything.
Throws an ISFErr if there is a problem of some sort parsing the JSON blob from the frag shader std::string.
*/
inline ISFDocRef CreateISFDocRefWith(const std::string & inFSContents, const std::string & inImportsDir=std::string("/"), const std::string & inVSContents=std::string(ISFVertPassthru_GL2), const bool & inThrowExcept=true) { return std::make_shared<ISFDoc>(inFSContents,inVSContents,inImportsDir,inThrowExcept); }



}




#endif /* ISFDoc_hpp */
