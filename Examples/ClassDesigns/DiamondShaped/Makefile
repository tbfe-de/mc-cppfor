ALL= Average.test Extrema.test Statistic.test

all : $(ALL)
	@true

Value.test: Value_test
	@echo -n "Testing class Value ... " && ./Value_test
Average.test: Average_test
	@echo -n "Testing class Average ... " && ./Average_test
Extrema.test: Extrema_test
	@echo -n "Testing class Extrema ... " && ./Extrema_test
Statistic.test: Statistic_test
	@echo -n "Testing class Statistic ... " && ./Statistic_test

Value_test: Value_test.cpp Value.h
	g++ -std=c++0x Value_test.cpp -o $@
Average_test: Average_test.cpp Average.h Value.h
	g++ -std=c++0x Average_test.cpp -o $@
Extrema_test: Extrema_test.cpp Extrema.h Value.h
	g++ -std=c++0x Extrema_test.cpp -o $@
Statistic_test: Statistic_test.cpp Statistic.h Extrema.h Average.h Value.h
	g++ -std=c++0x Statistic_test.cpp -o $@

clean:
	rm -f a.out core *.o $(ALL:.test=_test)
