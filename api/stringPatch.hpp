#pragma once
#include <Geode/Geode.hpp>

#ifdef GEODE_IS_WINDOWS
    #ifdef GDLAPI_EXPORTING
        #define GDLAPI_DLL __declspec(dllexport)
    #else
        #define GDLAPI_DLL __declspec(dllimport)
    #endif
#else
    #define GDLAPI_DLL __attribute__((visibility("default")))
#endif

namespace gdl {
#if defined(GEODE_IS_WINDOWS64)
    /// @brief Patch a normal C string
    /// @param absAddr The ABSOLUTE address of the `lea` instruction
    /// @param str A string. Note that it must have static lifetime!
    /// @return Whether the patch was successful
    [[nodiscard]] GDLAPI_DLL bool patchCString(uintptr_t srcAddr, const char* str);

    // All addresses are absolute!
    [[nodiscard]] GDLAPI_DLL bool patchStdString(const char* str, uintptr_t allocSizeInsn, uintptr_t sizeInsn, uintptr_t capacityInsn, std::vector<uintptr_t> assignInsns);
    
    // same as patchStdString but all addresses are relative to gd base (it will be added to all addresses)
    [[nodiscard]] GDLAPI_DLL bool patchStdStringRel(const char* str, uintptr_t allocSizeInsn, uintptr_t sizeInsn, uintptr_t capacityInsn, std::vector<uintptr_t> assignInsns);

    struct PatchBlock {
        uintptr_t start;
        unsigned int len;
    };

    // all addrs are absolute
    [[nodiscard]] bool patchStdString2(const char* str, const std::vector<PatchBlock>& blocks, uintptr_t bufAssignInsn);
#elif defined(GEODE_IS_ANDROID32)
    [[nodiscard]] GDLAPI_DLL bool patchString(const uintptr_t srcAddr, const char* str);
#endif
} // namespace gdl