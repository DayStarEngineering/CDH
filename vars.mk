# Linker and include flags
CDHLIB = -L../cdhlib -llogger -ldw -ldp -lpi -lcmd -lsw -lmsgqw -lssi -lgl -lgv -ltimer #-lbi
CFGMAP = -L../configmap -lconfigmap
IMGLIB = -L../imglib -lmilwrapper -lmilobjs -lgrey2bin
STLIB  = -L../stlib -lcentroid -lstdata
MILLIB = -L../mil/lib -lmil -limf -lsvml -lintlc -lmilim
MILINC = -I../mil/include

# Filesystem Directories:
FS = ./filesystem
INSBIN = $(FS)/home/bin
INSSCR = $(FS)/home/scripts
INSLIB = $(FS)/lib
INSCNF = $(FS)/home/conf
INSETC = $(FS)/etc

# Compile Flags:
CPP = /usr/bin/g++-4.4
CPPFLAGS = -O2 -mtune=core2 -march=core2 -m64 -pipe -c -Wall -Wextra
LIBFLAGS = -O2 -mtune=core2 -march=core2 -m64 -pipe -c -Wall -Wextra -fPIC
LDFLAGS = -mtune=core2 -march=core2 -m64 -pipe -Wall -Wextra -lpthread -pthread

# Clean Flags:
TMP = *~

