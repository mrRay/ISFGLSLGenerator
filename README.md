# ISFGLSLGenerator

ISFGLSLGenerator is a cross-platform c++ lib that provides a programmatic interface for browsing and examining ISF files as well as generating GLSL shader source code for them that can be used for rendering.  This lib doesn't do any actual rendering- it just parses ISF files and generates shader code.

### Dependencies

* ISFGLSLGenerator uses nlohmann's JSON for Modern C++, a header-only library for JSON parsing and output.  The source code for this is included in ./libISFGLSLGenerator/include/nlohmann_json.
* ISFGLSLGenerator uses exprtk, a header-only library for high-performance evaluation of strings as values.  The source code for this is included in ./libISFGLSLGenerator/include/exprtk.

### ISF Shaders

The [ISF Files](https://github.com/Vidvox/ISF-Files) repository contains over 200 different opensource video generators and effects written in ISF that can be used with these libraries.

### Building and Using ISFGLSLGenerator

ISFGLSLGenerator is intended to be built and used as a shared library.  Precompiled binaries are not distributed because the expectation is that the binaries you compile of ISFGLSLGenerator are going to be specific to your use-case (you'll likely be compiling them against a specific SDK/operating system, and even within the same OS/SDK binaries may not be compatible from compiler to compiler).

### Documentation

This project is documented using both Doxygen and traditional inline comments.

### Licensing

This lib is BSD licensed and its dependencies are MIT licensed, you can do whatever you want with it and feel good about yourself!  If you have any ideas for improvements (or you find any bugs or problems), please open an issue and let me know.

### Say hi!

I love seeing what other people do with ISF- don't be a stranger, send an email with your project details to isf [at] vidvox [dot] net!
