CXX = g++
PROGRAM = yourproject
# wx-config --libs
WX_LIBS = $(shell /usr/lib/wx/config/gtk2-unicode-debug-2.6 --libs)
# wx-config --cxxflags
WX_CXXFLAGS = -I../../include $(shell /usr/lib/wx/config/gtk2-unicode-debug-2.6 --cxxflags)

OBJECTS := $(patsubst ../../src/%.cpp,%.o,$(wildcard ../../src/*.cpp))

# implementation

.SUFFIXES:      .o .cpp

%.o : ../../src/%.cpp
	$(CXX) $(WX_CXXFLAGS) -c  -o $@ $<

all:	$(PROGRAM)

$(PROGRAM):$(OBJECTS)
	$(CXX) $(WX_LIBS) -o $(PROGRAM) $(OBJECTS)
