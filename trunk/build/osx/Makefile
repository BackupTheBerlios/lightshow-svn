CXX = $(shell /usr/bin/wx-config --cxx)
PROGRAM = lightshow
VERSION = 0.8
# wx-config --libs
WX_LIBS = $(shell /usr/bin/wx-config --libs)
# wx-config --cxxflags
WX_CXXFLAGS = -I../../include $(shell /usr/bin/wx-config --cxxflags)

OBJECTS := $(patsubst ../../src/%.cpp,%.o,$(wildcard ../../src/*.cpp))

# implementation

.SUFFIXES:      .o .cpp

%.o : ../../src/%.cpp
	$(CXX) $(WX_CXXFLAGS) -c  -o $@ $<

all:	$(PROGRAM) $(PROGRAM).app

$(PROGRAM):$(OBJECTS)
	$(CXX) $(WX_LIBS) -o $(PROGRAM) $(OBJECTS)

$(PROGRAM).app: $(PROGRAM) 
	mkdir -p $(PROGRAM).app    
	mkdir -p $(PROGRAM).app/Contents
	mkdir -p $(PROGRAM).app/Contents/MacOS
	mkdir -p $(PROGRAM).app/Contents/Resources
	
	
	sed -e "s/EXECUTABLE/$(PROGRAM)/" \
	-e "s/VERSION/$(VERSION)/" \
	Info.plist.in > $(PROGRAM).app/Contents/Info.plist
	
	echo -n 'APPL????' > $(PROGRAM).app/Contents/PkgInfo
	mv $(PROGRAM) $(PROGRAM).app/Contents/MacOS/$(PROGRAM)
	cp $(PROGRAM).icns $(PROGRAM).app/Contents/Resources/

clean:	
	rm *.o
	rm -r $(PROGRAM).app
