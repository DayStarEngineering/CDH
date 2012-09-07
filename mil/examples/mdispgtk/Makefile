TARGET= mdispgtk
CXX=g++
TARGET_SOURCES= mainframe.cpp mdispgtk.cpp mdispgtkview.cpp childframe.cpp roidlg.cpp mdispgtkmarshal.cpp
TARGET_OBJECTS=mainframe.o mdispgtk.o mdispgtkview.o childframe.o roidlg.o mdispgtkmarshal.o
TARGET_INCLUDES = mainframe.h mdispgtk.h mdispgtkview.h mdispgtkmarshal.h childframe.h roidlg.h 

GTK2_LIBS:=`pkg-config gtk+-2.0 gthread-2.0 --libs`
GTK2_CFLAGS:=`pkg-config gtk+-2.0 gthread-2.0 --cflags`

CPPFLAGS   = -g -Wall -I. -I$(MILDIR)/include $(GTK2_CFLAGS)
LDFLAGS  = -g -export-dynamic -L$(MILDIR)/lib -lmil $(GTK2_LIBS) -L/usr/X11R6/lib 

.PHONY   = clean

%.o: %.cpp $(TARGET_INCLUDES)
	$(CXX) -c -o $@ $< $(CPPFLAGS)

$(TARGET): $(TARGET_OBJECTS)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(LDFLAGS)

all: $(TARGET)

clean:
	-rm -f $(TARGET) $(TARGET_OBJECTS)

