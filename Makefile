out: main.o Neuron.o Net.o Connection.o
	g++ main.o Neuron.o Net.o Connection.o -o out
main.o:
	g++ -c main.cpp
Neuron.o: Neuron.cpp Neuron.h
	g++ -c Neuron.cpp
Net.o: Net.cpp Net.h
	g++ -c Net.cpp
Connection: Connection.cpp Connection.h
	g++ -c Connection.cpp
clean:
	rm *.o out
