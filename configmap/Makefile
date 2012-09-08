include ../vars.mk

OBJS=configmap.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o configmap_test.o
LIB=libconfigmap.so
BIN=configmap_test

all: $(LIB) $(BIN)

configmap.o:
	$(CPP) $(LIBFLAGS) configmap.cpp

configmap_test.o:
	$(CPP) $(LIBFLAGS) configmap_test.cpp

configmap_test: configmap_test.o
	$(CPP) $(LDFLAGS) $(CFGMAP) -o configmap_test configmap_test.o

libconfigmap.so: $(OBJS)
	$(CPP) $(LDFLAGS) -shared -o $(LIB) $(OBJS)

tinystr.o:
	$(CPP) $(LIBFLAGS) tinystr.cpp
	
tinyxml.o:
	$(CPP) $(LIBFLAGS) tinyxml.cpp
	
tinyxmlerror.o:
	$(CPP) $(LIBFLAGS) tinyxmlerror.cpp
	
tinyxmlparser.o:
	$(CPP) $(LIBFLAGS) tinyxmlparser.cpp

clean:
	-rm -f $(OBJS) $(LIB) $(BIN) $(TMP) 
