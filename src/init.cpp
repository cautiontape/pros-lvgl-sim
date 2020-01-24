#include "main.hpp"
std::unique_ptr<ncrapi::UserDisplay> userDisplay = nullptr;
void init()
{
#if defined(_WIN32)
    std::cout << "win32" << std::endl;
#elif defined(_WIN64)
    std::cout << "win64" << std::endl;
#elif defined(_linux)
    std::cout << "linux" << std::endl;
#else
    std::cout << "unkonw system" << std::endl;
#endif
#if defined(__GNUC__)
    std::cout << "gcc" << std::endl;
#elif defined(__clang__)
    std::cout << "clang" << std::endl;
#elif defined(_MSC_VER)
    std::cout << "msvc" << std::endl;
#elif defined(__arm__)
    std::cout << "arm-none-eabi" << std::endl;
#else
    std::cout << "unkonw compiler" << std::endl;
#endif
    userDisplay = std::make_unique<ncrapi::UserDisplay>();
}