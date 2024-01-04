# WAD Reader
 A library written in C++ that allows you to read and parse a .WAD file

## About
This is a project that can either be used as a standalone library, or can be used to error-check and look at the data inside of a .WAD file. **At the moment, this WAD Reader can only correctly parse DOOM1 and DOOM2 style WAD files. It cannot parse any ZDOOM WAD files.**

## Building The Project
 This project uses CMake as the primary method of compiling. However, there is an included Makefile in the root of the project that will run all of the setup commands for you. 

 ### __To build the project with the Makefile__
```sh
    make
```

### To run the examples executable
```sh
    cd build
    ./examples.exe
``` 

### To copy the library to your project
```sh
    cd build
    cp libwad.a <TARGET DIRECTORY>/libwad.a
```

### __To build the project with CMake on your own__
1. ```sh
    mkdir build
    cd build
    cmake ..
   ```
2. Afterwards, the steps are reliant on what CMake kit you use, but when making this project the GCC compiler was what was tested.


### __NOTE:__ 
The executable will be created and stored in the build directory of the project unless you change it.

## License
This project is licensed under the terms of the MIT license. See the [LICENSE](LICENSE) file for the full text.