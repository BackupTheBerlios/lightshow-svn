CXX = $(shell /usr/bin/wx-config --cxx)
PROGRAM = keyboard_plugin
VERSION = 0.8
# wx-config --libs
WX_LIBS = $(shell /usr/bin/wx-config --libs) -lwxtiffd-2.6 -lwxjpegd-2.6 -lwxpngd-2.6 -lwxexpatd-2.6
# wx-config --cxxflags
WX_CXXFLAGS = -I../../include $(shell /usr/bin/wx-config --cxxflags) -fPIC

OBJECTS := $(patsubst ../../%.cpp,%.o,$(wildcard ../../*.cpp))

# implementation

.SUFFIXES:      .o .cpp

%.o : ../../%.cpp
	$(CXX) $(WX_CXXFLAGS) -c  -o $@ $<

all:	$(PROGRAM) $(PROGRAM).bundle

$(PROGRAM):$(OBJECTS)
	$(CXX) -bundle -o $(PROGRAM) $(WX_LIBS) $(OBJECTS)
	
$(PROGRAM).bundle: $(PROGRAM) 
	mkdir -p $(PROGRAM).bundle    
	mkdir -p $(PROGRAM).bundle/Contents
	mkdir -p $(PROGRAM).bundle/Contents/MacOS
	mkdir -p $(PROGRAM).bundle/Contents/Resources
		
	sed -e "s/EXECUTABLE/$(PROGRAM)/" \
	-e "s/VERSION/$(VERSION)/" \
	Info.plist.in > $(PROGRAM).bundle/Contents/Info.plist
	
	echo -n 'BNDL????' > $(PROGRAM).bundle/Contents/PkgInfo
	cp $(PROGRAM) $(PROGRAM).bundle/Contents/MacOS/$(PROGRAM)

clean:	
	rm *.o
	rm -r $(PROGRAM).bundle
