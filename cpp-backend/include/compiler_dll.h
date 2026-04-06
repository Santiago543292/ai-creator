#ifndef AI_CREATOR_COMPILER_DLL_H
#define AI_CREATOR_COMPILER_DLL_H

#include "dll_exports.h"
#include "types.h"

namespace AICreator {

/**
 * Compiler DLL Interface
 * Exported functions for model compilation to native binaries
 */

extern "C" {
    // Compile model to executable and DLL
    DLL_EXPORT CompilationOutput CompileModel(const ModelConfig* config, const char* modelPath);
    
    // Compile to executable only
    DLL_EXPORT CompilationOutput CompileToExecutable(const char* sourceFile, const char* outputPath);
    
    // Compile to library only
    DLL_EXPORT CompilationOutput CompileToLibrary(const char* sourceFile, const char* outputPath);
    
    // Set optimization level (0-3)
    DLL_EXPORT void SetOptimizationLevel(int level);
    
    // Set debug mode
    DLL_EXPORT void SetDebugMode(bool debug);
    
    // Add compiler flag
    DLL_EXPORT void AddCompilerFlag(const char* flag);
    
    // Generate C++ code
    DLL_EXPORT bool GenerateCppCode(const ModelConfig* config, char* output, int maxSize);
    
    // Generate C++ header
    DLL_EXPORT bool GenerateCppHeader(const ModelConfig* config, char* output, int maxSize);
    
    // Validate source code
    DLL_EXPORT bool ValidateSourceCode(const char* sourceFile);
    
    // Check dependencies
    DLL_EXPORT bool CheckDependencies();
    
    // Generate CMakeLists.txt
    DLL_EXPORT bool GenerateCMakeLists(const char* outputPath, const ModelConfig* config);
    
    // Build with CMake
    DLL_EXPORT bool BuildWithCMake(const char* buildPath);
    
    // Compile for Windows
    DLL_EXPORT CompilationOutput CompileForWindows(const char* sourceFile, const char* outputPath);
    
    // Compile for Linux
    DLL_EXPORT CompilationOutput CompileForLinux(const char* sourceFile, const char* outputPath);
    
    // Compile for macOS
    DLL_EXPORT CompilationOutput CompileForMacOS(const char* sourceFile, const char* outputPath);
}

} // namespace AICreator

#endif // AI_CREATOR_COMPILER_DLL_H
