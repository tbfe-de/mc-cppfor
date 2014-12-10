ALL= Value.test Average.test Average-SOHO.test Extrema-SOHO.test Extrema.test

all : $(ALL)
	@true

Value.test: Value_test
	@echo -n "Testing class Value ... " && ./Value_test
Average.test: Average_test
	@echo -n "Testing class Average ... " && ./Average_test
Average-SOHO.test: Average-SOHO_test
	@echo -n "Testing class Average (history only)... " && ./Average-SOHO_test
Extrema.test: Extrema_test
	@echo -n "Testing class Extrema ... " && ./Extrema_test
Extrema-SOHO.test: Extrema-SOHO_test
	@echo -n "Testing class Extrema (history only)... " && ./Extrema-SOHO_test

Value_test: Value_test.cpp Value.h
	g++ -std=c++0x Value_test.cpp -o $@
Average_test: Average_test.cpp Average.h Value.h
	g++ -std=c++0x Average_test.cpp -o $@
Average-SOHO_test: Average_test.cpp Average.h Value.h
	g++ -std=c++0x -DSTATISTIC_OF_HISTORY_ONLY Average_test.cpp -o $@
Extrema_test: Extrema_test.cpp Extrema.h Average.h Value.h
	g++ -std=c++0x Extrema_test.cpp -o $@
Extrema-SOHO_test: Extrema_test.cpp Extrema.h Average.h Value.h
	g++ -std=c++0x -DSTATISTIC_OF_HISTORY_ONLY Extrema_test.cpp -o $@

clean:
	rm -f a.out core *.o $(ALL:.test=_test)
