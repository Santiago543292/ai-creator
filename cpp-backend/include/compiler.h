#ifndef AI_CREATOR_COMPILER_H
#define AI_CREATOR_COMPILER_H

#include "types.h"
#include <string>
#include <vector>

namespace AICreator {

/**
 * Compiler
 * Handles compilation of AI models to native C++ binaries (.exe, .dll, .so, .dylib)
 */
class Compiler {
public:
    Compiler();
    ~Compiler() = default;

    // Compilation methods
    CompilationOutput compileModel(const ModelConfig& config, const std::string& modelPath);
    CompilationOutput compileToExecutable(const std::string& sourceFile, const std::string& outputPath);
    CompilationOutput compileToLibrary(const std::string& sourceFile, const std::string& outputPath);
    
    // Compilation configuration
    void setOptimizationLevel(int level) { optimizationLevel_ = level; } // 0-3
    void setDebugMode(bool debug) { debugMode_ = debug; }
    void addCompilerFlag(const std::string& flag) { compilerFlags_.push_back(flag); }
    
    // Code generation
    bool generateCppCode(const ModelConfig& config, std::string& generatedCode);
    bool generateCppHeader(const ModelConfig& config, std::string& headerCode);
    
    // Validation
    bool validateSourceCode(const std::string& sourceFile);
    bool checkDependencies();
    
    // Build system
    bool generateCMakeLists(const std::string& outputPath, const ModelConfig& config);
    bool buildWithCMake(const std::string& buildPath);
    
    // Platform-specific compilation
    CompilationOutput compileForWindows(const std::string& sourceFile, const std::string& outputPath);
    CompilationOutput compileForLinux(const std::string& sourceFile, const std::string& outputPath);
    CompilationOutput compileForMacOS(const std::string& sourceFile, const std::string& outputPath);

private:
    int optimizationLevel_;
    bool debugMode_;
    std::vector<std::string> compilerFlags_;
    std::string compilerPath_;
    
    // Helper methods
    std::string getCompilerCommand(TargetPlatform platform);
    std::string getCompilerFlags();
    bool executeCommand(const std::string& command, std::string& output);
    std::string getFileExtension(TargetPlatform platform, bool isLibrary);
};

} // namespace AICreator

#endif // AI_CREATOR_COMPILER_H
