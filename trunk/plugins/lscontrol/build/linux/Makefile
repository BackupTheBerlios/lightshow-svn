CXX = g++-3.4
PROGRAM = lscontrol_plugin.so
# wx-config --libs
WX_LIBS = $(shell /usr/lib/wx/config/gtk2-unicode-debug-2.6 --libs)
# wx-config --cxxflags
WX_CXXFLAGS = -I../../include $(shell /usr/lib/wx/config/gtk2-unicode-debug-2.6 --cxxflags)

OBJECTS := $(patsubst ../../%.cpp,%.o,$(wildcard ../../*.cpp))

# implementation

.SUFFIXES:      .o .cpp

%.o : ../../%.cpp
	$(CXX) $(WX_CXXFLAGS) -c  -o $@ $<

all:	$(PROGRAM)

$(PROGRAM):$(OBJECTS)
	$(CXX) $(WX_LIBS) -shared -fPIC -o $(PROGRAM) $(OBJECTS)
