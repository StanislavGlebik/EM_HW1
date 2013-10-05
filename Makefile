STXXL_ROOT      ?= $(HOME)/EM/stxxl-1.3.1
STXXL_CONFIG    ?= stxxl.mk

include $(STXXL_ROOT)/$(STXXL_CONFIG)

CXX              = $(STXXL_CXX)
CPPFLAGS        += $(STXXL_CPPFLAGS)
LDLIBS          += $(STXXL_LDLIBS)

CPPFLAGS        += -O3 -Wall -g 

my.bin: main.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) main.o -o $@ $(LDLIBS)

clean: 
	rm main.o my.bin
