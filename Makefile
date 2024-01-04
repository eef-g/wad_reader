all: reset build tests

build: 
	mkdir build
	cd build && cmake .. -G "MinGW Makefiles"
	cd build && make

tests:
	cd build/test && wad_testing.exe

reset:
	if not exist vendor/googletest make setup
	if exist build rd /s /q build

setup:
	git submodule update --init --recursive
	mkdir build