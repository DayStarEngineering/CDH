include ../vars.mk

OBJS=MILTest.o MILWrapper.o MILObjects.o grey2bin.o
LIBS=libmilwrapper.so libmilobjs.so libgrey2bin.so
BIN=MILTest MILWrapperTest

all: $(OBJS) $(LIBS) $(BIN)

MILWrapper.o: MILWrapper.cpp
	$(CPP) $(LIBFLAGS) $(MILINC) MILWrapper.cpp -o MILWrapper.o
	
libmilwrapper.so: MILWrapper.o
	$(CPP) $(LDFLAGS) $(MILLIB) $(STLIB) -shared MILWrapper.o -o libmilwrapper.so

MILObjects.o: MILObjects.cpp
	$(CPP) $(LIBFLAGS) $(MILINC) MILObjects.cpp -o MILObjects.o
	
libmilobjs.so: MILObjects.o
	$(CPP) $(LDFLAGS) $(MILLIB) -shared MILObjects.o -o libmilobjs.so

grey2bin.o: grey2bin.cpp
	$(CPP) $(LIBFLAGS) $(MILINC) grey2bin.cpp -o grey2bin.o
	
libgrey2bin.so: grey2bin.o
	$(CPP) $(LDFLAGS) $(MILLIB) -shared grey2bin.o -o libgrey2bin.so	

MILTest.o: MILTestScript.cpp 
	$(CPP) $(CPPFLAGS) $(MILINC) MILTestScript.cpp -o MILTest.o
	
MILTest: MILTest.o
	$(CPP) -o MILTest MILTest.o $(LDFLAGS) $(MILLIB)
	
MILWrapperTest: MILWrapperTest.cpp
	$(CPP) -Wall $(MILINC) $(MILLIB) $(STLIB) $(CDHLIB) $(CFGMAP) ../cdhlib/Logger.cpp MILWrapperTest.cpp MILWrapper.cpp MILObjects.cpp -pthread -o MILWrapperTest
	
clean:
	-rm -f $(OBJS) $(LIBS) $(BIN) $(TMP) 
