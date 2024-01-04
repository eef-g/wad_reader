all: reset build tests

build: 
	mkdir build
	cd build && cmake .. -G "MinGW Makefiles"
	cd build && make

tests:
	cd build/test && wad_testing.exe

reset:
	if exist build rd /s /q build