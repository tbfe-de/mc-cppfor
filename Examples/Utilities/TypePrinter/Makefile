ALL_TARGETS=\
	tp-final

all: $(ALL_TARGETS)
	@echo "targets up-to-date."

DEFINE_TESTS=\
	-DALL_BASIC_TYPES\
	-DSOME_CV_QUALIFICATIONS\
	-DSOME_DECORATIONS

tp-final: tp-final.cpp
	g++ $(DEFINE_TESTS) -std=c++0x tp-final.cpp -o $@

clean:
	rm -f a.out core *.o tp-final
