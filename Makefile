OS := $(shell uname)

all: reset build tests

build: 
	mkdir build
ifeq ($(OS), Linux)
	cd build && cmake .. -G "Unix Makefiles"
	cd build && make CXXFLAGS=-g
else
	cd build & cmake .. -G "MinGW Makefiles"
	cd build && make CXXFLAGS=-g
endif

tests:
ifeq ($(OS), Linux) 
	cd build/test && ./wad_testing
else
	cd build/test && wad_testing.exe
endif

reset:
ifeq ($(OS), Linux) 
	if [ ! -d "vendor/googletest" ]; then make setup; fi
	if [ -d "build" ]; then rm -rf build; fi
else
	if not exist vendor/googletest make setup
	if exist build rd /s /q build
endif

setup:
	git submodule update --init --recursive
	mkdir build

release: reset build
ifeq ($(OS), Linux) 
	if [ ! -d "release" ]; then mkdir release; fi
	if [ -d "release/libwad.a"]; then rm release/libwad.a; fi
	cp build/libwad.a release/libwad.a
else
	if not exist release mkdir release
	if exist release\libwad.a del release\libwad.a
	copy build\libwad.a release\libwad.a
endif

debug:
ifeq ($(OS), Linux)
	cd build/test && gdb ./wad_testing
else
	cd build/test && gdb wad_testing.exe
endif
