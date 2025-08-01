build:
	@g++ main.cpp proc.cpp utils.cpp -o bin/ns

debug_build:
	@g++ -ggdb -g3 main.cpp proc.cpp utils.cpp -o bin/debug_ns

debug: debug_build
	@cgdb bin/debug_ns

run: build
	@./bin/ns

clean: 
	@rm ./bin/ns
	@rm ./bin/debug_ns

mem: build
	@valgrind  ./bin/ns

.PHRONY: build, run, clean, mem, debug_build, debug