include ../vars.mk

SRCS = DataParserCmdLine.cpp ASCI2BinaryPortWriter.cpp FrameGrabberCmdLine.cpp
OBJS = dpcl.o asci2bin.o fgcl.o
BIN  = dpcl asci2bin fgcl

all: $(OBJS) $(BIN)
	make -C ../cdhlib
	make -C ../imglib
	make -C ../stlib
	make -C ../configmap
   
dpcl.o: DataParserCmdLine.cpp
	$(CPP) $(CPPFLAGS) DataParserCmdLine.cpp -o dpcl.o

asci2bin.o: ASCI2BinaryPortWriter.cpp
	$(CPP) $(CPPFLAGS) ASCI2BinaryPortWriter.cpp -o asci2bin.o
  
fgcl.o: FrameGrabberCmdLine.cpp
	$(CPP) $(CPPFLAGS) $(MILINC) FrameGrabberCmdLine.cpp -o fgcl.o
	
dpcl: dpcl.o
	$(CPP) $(LDFLAGS) dpcl.o $(CDHLIB) $(CFGMAP) -o dpcl

#asci2bin: asci2bin.o
#	$(CPP) $(LDFLAGS) asci2bin.o $(CDHLIB) $(CFGMAP) -o asci2bin

asci2bin: ASCI2BinaryPortWriter.cpp ../cdhlib/PortInterface.cpp
	$(CPP) -O2 -mtune=core2 -march=core2 -m64 -pipe -Wall ASCI2BinaryPortWriter.cpp ../cdhlib/PortInterface.cpp ../cdhlib/GlobalLock.cpp -pthread -o asci2bin

fgcl: fgcl.o
	$(CPP) $(LDFLAGS) fgcl.o $(CDHLIB) $(CFGMAP) $(IMGLIB) $(MILLIB) $(STLIB) -o fgcl
	
clean:
	-rm -f $(OBJS) $(BIN) $(TMP) 
