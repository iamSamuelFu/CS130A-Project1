all: compile run

run: main
	./main
clean:
	rm main
compile:
	g++ -std=c++11 -o main *.cpp 
