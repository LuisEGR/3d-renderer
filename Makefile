drawPokemon: drawPokemon.cpp
	g++ -std=c++11 drawPokemon.cpp -o drawPokemon -Wall -pthread

run: drawPokemon
	./drawPokemon
clean:
	rm -f a.out

