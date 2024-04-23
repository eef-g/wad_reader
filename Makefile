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
	if [ -d "build" ]; then rm -rf build; fi
else
	if exist build rd /s /q build
endif

setup:
	git submodule update --init --recursive

release: build
ifeq ($(OS), Linux) 
	if [ ! -d "release" ]; then mkdir release && mkdir release/Linux; fi
	if [ -d "release/Linux/libwad.a" ]; then rm release/Linux/libwad.a; fi
	cp build/libwad.a release/Linux/libwad.a
else
	if not exist release mkdir release
	if not exist release\Windows mkdir release\Windows
	if exist release\Windows\libwad.a del release\Windows\libwad.a
	copy build\libwad.a release\Windows\libwad.a
endif

debug:
ifeq ($(OS), Linux)
	cd build/test && gdb ./wad_testing
else
	cd build/test && gdb wad_testing.exe
endif

build-gh: 
	mkdir build
ifeq ($(OS), Linux)
	cd build && cmake .. -G "Unix Makefiles"
	cd build && make
else
	cd ${GITHUB_WORKSPACE}\build & cmake .. -G "MinGW Makefiles"
	cd ${GITHUB_WORKSPACE}\build && make
endif

release-gh: build-gh
ifeq ($(OS), Linux) 
	if [ ! -d "release" ]; then mkdir release && mkdir release/Linux; fi
	if [ -d "release/Linux/libwad.a" ]; then rm release/Linux/libwad.a; fi
	cp build/libwad.a release/Linux/libwad.a
else
	if not exist release mkdir release
	if not exist release\Windows mkdir release\Windows
	if exist release\Windows\libwad.a del release\Windows\libwad.a
	copy build\libwad.a release\Windows\libwad.a
endif
