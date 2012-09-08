TARGET	= mdispwindowgtk
GTK_LIBS   := `pkg-config gtk+-2.0 --libs`  
GTK_CFLAGS := `pkg-config gtk+-2.0 --cflags`

CPPFLAGS   = -Wall -g -I$(MILDIR)/include $(GTK_CFLAGS) 
LDFLAGS  = -L$(MILDIR)/lib -lmil $(G_LIBS) $(GTK_LIBS)
.PHONY   = clean

all: $(TARGET)

clean:
	-rm -f $(TARGET) $(TARGET).o

$(TARGET) : $(TARGET).o
