bin:
	@mkdir -p bin

build: bin
	@g++ main.cpp proc.cpp utils.cpp -o bin/ns

debug_build: bin
	@g++ -ggdb -g3 main.cpp proc.cpp utils.cpp -o bin/debug_ns

debug: debug_build
	@cgdb bin/debug_ns

run: build
	@./bin/ns

clean: 
	@rm -rf ./bin

mem: build
	@valgrind  ./bin/ns

.PHRONY: build, run, clean, mem, debug_build, debug