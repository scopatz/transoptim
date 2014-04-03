
cyclus_root = /home/r/cyc/install
cycpp = /home/r/cyc/cyclus/cli/cycpp.py
libname = libRecipeExtractor.so
fname = recipe_extractor

##### dependency info #####
includes += -I$(cyclus_root)/include/cyclus
includes += $(shell pkg-config --cflags sqlite3)
includes += $(shell pkg-config --cflags cbc)
includes += $(shell pkg-config --cflags libxml-2.0)
includes += $(shell pkg-config --cflags libxml++-2.6)

libs += -L$(cyclus_root)/lib -lcycluscore

##### variable setup #####
source += $(wildcard *.cc)
source_unique = $(sort $(source))
objs = $(source_unique:%.cc=%.o)

##### primary targets #####
$(libname): $(objs)
	$(CXX) -shared -fpic -rdynamic $(CXXFLAGS) $(CPPFLAGS) $(libs) $(objs) -o $@

$(fname).o : $(fname).gen.cpp $(fname).gen.hpp
	$(CXX) -c -fpic $(CXXFLAGS) $(CPPFLAGS) $(includes) $< -o $@

$(fname).gen.cpp: $(fname).cc
	$(cycpp) --cpp-path=$(CXX) --pass3-use-orig $(includes) $< -o $@ 
	sed -i 's/$(fname).h/$(fname).gen.hpp/' $@
	$(CXX) -MM $(CXXFLAGS) $(includes) $< > $*.d

$(fname).gen.hpp: $(fname).h
	$(cycpp) --cpp-path=$(CXX) --pass3-use-orig $(includes) $< -o $@ 

clean:
	rm -f *.o *.d
	rm -f $(libname)
	rm -f $(fname).gen.hpp
	rm -f $(fname).gen.cpp

##### pattern rules to build all object files from source #####
# pull in dependency info for *existing* .o files
-include $(objs:%.o=%.d)

%.o : %.cc %.h
	$(CXX) -c -fpic $(CXXFLAGS) $(CPPFLAGS) $(includes) $< -o $@
	$(CXX) -MM $(CXXFLAGS) $(includes) $< > $*.d

# disable makes built-in implicit rules
.SUFFIXES: