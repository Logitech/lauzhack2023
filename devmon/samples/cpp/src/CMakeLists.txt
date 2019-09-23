file(GLOB SOURCES *.h *.cpp)

add_executable(logi-devmon-test ${SOURCES})

target_link_libraries(logi-devmon-test
    PRIVATE gtest
    PRIVATE gmock
)

if(APPLE)

    find_library(COREFOUNDATION CoreFoundation "/")
    target_link_libraries(logi-devmon-test PRIVATE ${COREFOUNDATION})

    set_property(TARGET
        logi-devmon-test PROPERTY
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
    )

endif()
