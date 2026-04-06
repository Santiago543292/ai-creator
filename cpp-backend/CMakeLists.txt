cmake_minimum_required(VERSION 3.15)
project(AICreator VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# ============================================
# Main Executable - Minimal Version
# ============================================

add_executable(ai_creator WIN32
    src/main.cpp
)

# Windows-specific settings
if(WIN32)
    # Windows API libraries
    target_link_libraries(ai_creator PUBLIC
        user32
        gdi32
        shell32
        ole32
        oleaut32
        uuid
        comctl32
        ws2_32
    )
    
    # Compiler flags for optimization
    add_compile_options(/W4 /O2 /EHsc)
    
    # Set Windows subsystem (no console window)
    set_target_properties(ai_creator PROPERTIES WIN32_EXECUTABLE ON)
    
elseif(APPLE)
    add_compile_options(-Wall -O2)
    set_target_properties(ai_creator PROPERTIES SUFFIX ".app")
else()
    add_compile_options(-Wall -O2)
    target_link_libraries(ai_creator PUBLIC pthread)
endif()

# ============================================
# DLL Libraries - Specialized Components
# ============================================

# 1. Model Manager DLL
add_library(model_manager SHARED 
    src/model_manager.cpp
)
set_target_properties(model_manager PROPERTIES
    PREFIX ""
    SUFFIX ".dll"
)
if(WIN32)
    target_link_libraries(model_manager PRIVATE user32)
endif()

# 2. Data Loader DLL
add_library(data_loader SHARED
    src/data_loader.cpp
)
set_target_properties(data_loader PROPERTIES
    PREFIX ""
    SUFFIX ".dll"
)
if(WIN32)
    target_link_libraries(data_loader PRIVATE user32)
endif()

# 3. Compiler DLL
add_library(compiler SHARED
    src/compiler.cpp
)
set_target_properties(compiler PROPERTIES
    PREFIX ""
    SUFFIX ".dll"
)
if(WIN32)
    target_link_libraries(compiler PRIVATE user32)
endif()

# 4. Neural Network DLL
add_library(neural_network SHARED
    src/neural_network.cpp
)
set_target_properties(neural_network PROPERTIES
    PREFIX ""
    SUFFIX ".dll"
)
if(WIN32)
    target_link_libraries(neural_network PRIVATE user32)
endif()

# 5. Decision Tree DLL
add_library(decision_tree SHARED
    src/decision_tree.cpp
)
set_target_properties(decision_tree PROPERTIES
    PREFIX ""
    SUFFIX ".dll"
)
if(WIN32)
    target_link_libraries(decision_tree PRIVATE user32)
endif()

# ============================================
# Installation
# ============================================

install(TARGETS ai_creator model_manager data_loader compiler neural_network decision_tree
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
