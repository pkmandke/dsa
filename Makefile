CC=g++
CPPFLAGS=-std=c++11 -O3

ODIR=./obj

INCL=commons/common.h
COMN=commons/common.cpp

sorting: $(INCL) $(COMN) sorting/sorts.cpp
	$(CC) $(CPPFLAGS) -o $(ODIR)/sorts $(COMN) sorting/sorts.cpp

btrees: $(INCL) $(COMN) btrees/btrees.h btrees/methods.cpp btrees/test.cpp
	$(CC) $(CPPFLAGS) -o $(ODIR)/btrees $(COMN) btrees/methods.cpp btrees/test.cpp

.PHONY: clean sorting btrees

clean:
	rm -f obj/*
