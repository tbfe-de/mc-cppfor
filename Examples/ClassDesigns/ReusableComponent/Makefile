ALL= RingBuffer.test

all: $(ALL)

RingBuffer.test: RingBuffer_test
	@echo -n "Testing the RingBuffer ... " && ./RingBuffer_test

RingBuffer_test: RingBuffer_test.cpp RingBuffer.h
	g++ RingBuffer_test.cpp -o $@

clean:
	rm -f a.out core *.o $(ALL:.test=_test)
