PROGS=\
	BAD-local_demo\
	local_demo\
	choice_demo1\
	choice_demo2\
	choice_demo3\
	choice_demo4\
	choice_demo5\
	choice_demo6

all: $(PROGS)
	@echo "updated: $(PROGS)"

ITRACE_DEP=ITrace.h ITrace.cpp
CHOICE_DEP=Window.h MenuItem.h
WRAPPER_DEP=WindowRes.h MenuItemRes.h

BAD-local_demo: BAD-local_demo.cpp $(ITRACE_DEP)
	g++ -std=c++0x -DVERSION=1 BAD-local_demo.cpp ITrace.cpp -o $@
local_demo: BAD-local_demo.cpp $(ITRACE_DEP)
	g++ -std=c++0x -DVERSION=1 local_demo.cpp ITrace.cpp -o $@
choice_demo1: choice_demo.cpp Choice1.h $(CHOICE_DEP) $(ITRACE_DEP)
	g++ -std=c++0x -DVERSION=1 choice_demo.cpp ITrace.cpp -o $@
choice_demo2: choice_demo.cpp Choice2.h $(CHOICE_DEP) $(ITRACE_DEP)
	g++ -std=c++0x -DVERSION=2 choice_demo.cpp ITrace.cpp -o $@
choice_demo3: choice_demo.cpp Choice3.h $(CHOICE_DEP) $(ITRACE_DEP)
	g++ -std=c++0x -DVERSION=3 choice_demo.cpp ITrace.cpp -o $@
choice_demo4: choice_demo.cpp Choice4.h $(WRAPPER_DEP) $(CHOICE_DEP) $(ITRACE_DEP)
	g++ -std=c++0x -DVERSION=4 choice_demo.cpp ITrace.cpp -o $@
choice_demo5: choice_demo.cpp Choice5.h $(CHOICE_DEP) $(ITRACE_DEP)
	g++ -std=c++0x -DVERSION=5 choice_demo.cpp ITrace.cpp -o $@
choice_demo6: choice_demo.cpp Choice6.h $(CHOICE_DEP) $(ITRACE_DEP)
	g++ -std=c++0x -DVERSION=6 choice_demo.cpp ITrace.cpp -o $@

clean:
	rm -f a.out core *.o $(PROGS)
