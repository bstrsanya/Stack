all: built run
built:
	g++ -Iinclude src/*.cpp -o main
run:
	.\main