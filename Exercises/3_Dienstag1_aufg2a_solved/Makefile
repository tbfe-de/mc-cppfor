aufg2a: aufg2a.cpp Value.o
	g++ -std=c++0x aufg2a.cpp Value.o -o $@
	@./$@
Value.o: Value.h RingBuffer.h Value.cpp
	g++ -c -std=c++0x Value.cpp
