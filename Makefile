.PHONY: build

clean:
	rm build/*

build: clean
	g++ -g -fpermissive -o ./build/server ./src/main.cpp ./src/server.cpp
