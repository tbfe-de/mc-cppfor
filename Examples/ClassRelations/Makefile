PROGS=\
	general_association\
	general_association-NOFR\
	directed_association\
	composition-PAM\
	composition-PAPB\
	composition-PVRP\
	composition-PVUP\
	aggregation

all: $(PROGS)
	@echo DONE

general_association: general_association.cpp
	g++ -S -std=c++0x $< -o /dev/null
general_association-NOFR: general_association.cpp
	g++ -S -std=c++0x -DNO_FRIEND_RELATIONSHIP $< -o /dev/null
directed_association: directed_association.cpp
	g++ -S -std=c++0x $< -o /dev/null
composition-PAM: composition.cpp
	g++ -DPART_AS_MEMBER -S -std=c++0x $< -o /dev/null
composition-PAPB: composition.cpp
	g++ -DPART_AS_PRIVATE_BASE -S -std=c++0x $< -o /dev/null
composition-PVRP: composition.cpp
	g++ -DPART_VIA_RAW_POINTER -S -std=c++0x $< -o /dev/null
composition-PVUP: composition.cpp
	g++ -DPART_VIA_UNIQUE_PTR -S -std=c++0x $< -o /dev/null
aggregation: aggregation.cpp
	g++ -std=c++0x aggregation.cpp -o $@

clean:
	rm -f a.out core aggregation
