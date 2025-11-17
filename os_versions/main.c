#if defined (DENZEL_WIN32)
    #include "hello_win.h"
#elif defined (DENZEL_LINUX)
    #include "hello_lnx.h"
#else
    #error "Unknown or unsupported OS"
#endif

int main(void) {
    hello();
    return 0;
}