TARGET	= mdighook

CFLAGS   = -I$(MILDIR)/include -g
CXXFLAGS = $(CFLAGS)
LDFLAGS  = -L$(MILDIR)/lib -lmil
.PHONY   = clean

all: $(TARGET)

clean:
	-rm -f $(TARGET) $(TARGET).o

$(TARGET) : $(TARGET).o
