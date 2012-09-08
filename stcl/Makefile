include ../vars.mk

SRCS = StartrackerCmdLine.cpp
OBJS = stcl.o
BIN  = stcl

all: $(OBJS) $(BIN)
	make -C ../cdhlib
   
stcl.o: $(SRCS)
	$(CPP) $(CPPFLAGS) $(SRCS) -o $(OBJS)
  
stcl: $(OBJS)
	$(CPP) $(LDFLAGS) $(OBJS) $(CDHLIB) $(CFGMAP) -o $(BIN)
		
clean:
	-rm -f $(OBJS) $(BIN) $(TMP) 
