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

release: reset build
	if not exist release mkdir release
	if exist release\libwad.a del release\libwad.a
	copy build\libwad.a release\libwad.a