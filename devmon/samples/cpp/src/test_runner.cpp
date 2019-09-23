#include <gmock/gmock.h>

#if defined(__APPLE__)
    #import <CoreFoundation/CoreFoundation.h>

    #include <thread>
    using std::thread;
#endif

using testing::InitGoogleMock;

int main(int argc, char* argv[])
{
    // Init Google Test + Google Mock
    // (also parses command-line arguments)
    InitGoogleMock(&argc, argv);

    int ret_code = -1;

#if defined(__APPLE__)
    thread test_thread([&ret_code]()
    {
        ret_code = RUN_ALL_TESTS();

        CFRunLoopStop(CFRunLoopGetMain());
    });

    CFRunLoopRun();

    test_thread.join();
#else
    ret_code = RUN_ALL_TESTS();
#endif

    return ret_code;
}
