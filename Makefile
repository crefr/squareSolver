FILENAME = a.exe
OBJDIR = Obj/
SRCDIR = sources/
HEADDIR = headers/

CC = g++
CFLAGS = -c -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline							\
		 -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default				\
		 -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy 				\
		 -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers 	\
		 -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing 		\
		 -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE				\
		 -I./$(HEADDIR)

$(FILENAME): $(OBJDIR)main.o $(OBJDIR)colPrintf.o $(OBJDIR)printscan.o $(OBJDIR)sqmath.o $(OBJDIR)tests.o $(OBJDIR)argvprocessing.o $(OBJDIR)myisfinite.o
	$(CC) $(OBJDIR)main.o $(OBJDIR)colPrintf.o $(OBJDIR)printscan.o $(OBJDIR)sqmath.o $(OBJDIR)tests.o $(OBJDIR)argvprocessing.o $(OBJDIR)myisfinite.o -o $(FILENAME)

$(OBJDIR)main.o: $(SRCDIR)main.cpp $(HEADDIR)colors.h $(HEADDIR)printscan.h $(HEADDIR)sqmath.h $(HEADDIR)consts.h $(HEADDIR)tests.h $(HEADDIR)colPrintf.h $(HEADDIR)myassert.h $(HEADDIR)argvprocessing.h
	$(CC) $(CFLAGS) $(SRCDIR)main.cpp -o $(OBJDIR)main.o

$(OBJDIR)colPrintf.o: $(SRCDIR)colPrintf.cpp $(HEADDIR)colPrintf.h $(HEADDIR)colors.h $(HEADDIR)myassert.h
	$(CC) $(CFLAGS) $(SRCDIR)colPrintf.cpp -o $(OBJDIR)colPrintf.o

$(OBJDIR)printscan.o: $(SRCDIR)printscan.cpp $(HEADDIR)printscan.h $(HEADDIR)consts.h $(HEADDIR)colPrintf.h $(HEADDIR)colors.h $(HEADDIR)myassert.h
	$(CC) $(CFLAGS) $(SRCDIR)printscan.cpp -o $(OBJDIR)printscan.o

$(OBJDIR)sqmath.o: $(SRCDIR)sqmath.cpp $(HEADDIR)sqmath.h $(HEADDIR)consts.h $(HEADDIR)myassert.h $(HEADDIR)colors.h $(HEADDIR)myisfinite.h $(HEADDIR)colPrintf.h
	$(CC) $(CFLAGS) $(SRCDIR)sqmath.cpp -o $(OBJDIR)sqmath.o

$(OBJDIR)tests.o: $(SRCDIR)tests.cpp $(HEADDIR)tests.h $(HEADDIR)consts.h $(HEADDIR)colPrintf.h $(HEADDIR)sqmath.h $(HEADDIR)colors.h $(HEADDIR)myassert.h
	$(CC) $(CFLAGS) $(SRCDIR)tests.cpp -o $(OBJDIR)tests.o

$(OBJDIR)argvprocessing.o: $(SRCDIR)argvprocessing.cpp $(HEADDIR)argvprocessing.h $(HEADDIR)myassert.h $(HEADDIR)colPrintf.h $(HEADDIR)consts.h $(HEADDIR)colors.h
	$(CC) $(CFLAGS) $(SRCDIR)argvprocessing.cpp -o $(OBJDIR)argvprocessing.o

$(OBJDIR)myisfinite.o: $(SRCDIR)myisfinite.cpp $(HEADDIR)myisfinite.h
	$(CC) $(CFLAGS) $(SRCDIR)myisfinite.cpp -o $(OBJDIR)myisfinite.o

clean:
	rm $(OBJDIR)*

