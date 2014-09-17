all : Statistic.test Statistic_demo
	@true

Statistic.test: Statistic_test
	@echo -n "Testing class Statistic ... " && ./Statistic_test

Statistic_test: Statistic_test.cpp Statistic.h IExtrema.h IAverage.h IValue.h RingBuffer.h
	g++ -std=c++0x Statistic_test.cpp -o $@
Statistic_demo: Statistic_demo.cpp Statistic.h IExtrema.h IAverage.h IValue.h RingBuffer.h
	g++ -std=c++0x Statistic_demo.cpp -o $@

clean:
	rm -f a.out core *.o $(ALL:.test=_test)
