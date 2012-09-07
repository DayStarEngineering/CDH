TARGET_LIBS	=  libdistributedmiladdconstantslave.so
TARGET_OBJECTS  =  DistributedMilAddConstantSlave.o
TARGET_INCLUDES =

CFLAGS   = -I$(MILDIR)/include -fPIC
CXXFLAGS = $(CFLAGS)
LDFLAGS  = -shared -L$(MILDIR)/lib -lmil -lmilim

.PHONY   = clean


%.o: %.cpp $(TARGET_INCLUDES)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(TARGET_LIBS): $(TARGET_OBJECTS)
	$(CXX) -o $(TARGET_LIBS) $(TARGET_OBJECTS) $(CXXFLAGS) $(LDFLAGS)

all: $(TARGET_LIBS)

clean:
	-rm -f $(TARGET_LIBS) $(TARGET_OBJECTS)

