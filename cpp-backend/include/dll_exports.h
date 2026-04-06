#ifndef AI_CREATOR_DLL_EXPORTS_H
#define AI_CREATOR_DLL_EXPORTS_H

#ifdef _WIN32
    #ifdef BUILDING_DLL
        #define DLL_EXPORT __declspec(dllexport)
    #else
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#else
    #define DLL_EXPORT
#endif

#endif // AI_CREATOR_DLL_EXPORTS_H
