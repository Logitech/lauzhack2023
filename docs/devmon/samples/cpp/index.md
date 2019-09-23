# Logitech Input Device Monitor - C++ code sample

Code sample is located in `devmon/samples/cpp/src/devmon_test.cpp`.

It is a collection (suite) of test cases which demonstrate how the API works.

API for building the test suite is [Google Test](https://github.com/google/googletest).

## Pre-requisites

Download and install [CMake](https://cmake.org/download/).

### Windows

You should have Visual Studio (minimum version 2017)

### Mac OS

You should have Xcode

## Build

1. Ensure the GIT submodules in this repository have been retrieved:

From root folder, within a terminal, run:

```
git submodule update --init --recursive
```

2. cd to `devmon\samples\cpp` and create a `build` directory and cd to this directory

3. In your terminal, run:

    - on Windows:
    
    ```
    cmake -G "Visual Studio 15 2017 Win64" ..
    ```

    - on Mac OS:

    ```
    cmake -G Xcode ..
    ```

4. Open your IDE and look for generated solution in `build` folder.

You should be able to build `logi-devmon-test`.

## Run

To run (without debugging) code sample, open a terminal in `devmon/samples/cpp/build/Debug` folder:

    - on Windows :

    ```
    logi-devmon-test.exe --gtest_filter=<test case selector>
    ```

    - on Mac OS:

    ```
    ./logi-devmon-test --gtest_filter=<test case selector>
    ```

Where `test case selector` matches a test case in `devmon_test.cpp`.

For example `--gtest_filter=devmon_test.spy_device` will run code in `TEST_F(devmon_test, spy_device)`.

## Debug

- on Windows:
    
Open `devmon-test.sln`, build it and select test case from Test Explorer.

You can then run or debug it, and also add breakpoints.

- on Mac OS:

Open XCode and select `devmon-test` target.

You will need to add launch arguments.
