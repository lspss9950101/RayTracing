release:
	mkdir -p release
	cd release; cmake -DCMAKE_BUILD_TYPE=Release ..; make

build:
	mkdir -p build
	cd build; cmake -DCMAKE_BUILD_TYPE=Debug..; make

clean:
	rm -rf build release
	rm main

.PHONY: build
.PHONY: release