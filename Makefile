CC = g++
CFLAGS = -c -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline							\
		 -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default				\
		 -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy 				\
		 -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers 	\
		 -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing 		\
		 -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
FILENAME = a.exe
OBJDIR = Obj/

$(FILENAME): $(OBJDIR)main.o $(OBJDIR)colPrintf.o $(OBJDIR)printscan.o $(OBJDIR)sqmath.o $(OBJDIR)tests.o $(OBJDIR)argvprocessing.o $(OBJDIR)myisfinite.o
	$(CC) $(OBJDIR)main.o $(OBJDIR)colPrintf.o $(OBJDIR)printscan.o $(OBJDIR)sqmath.o $(OBJDIR)tests.o $(OBJDIR)argvprocessing.o $(OBJDIR)myisfinite.o -o $(FILENAME)

$(OBJDIR)main.o: main.cpp colors.h printscan.h sqmath.h consts.h tests.h colPrintf.h myassert.h argvprocessing.h
	$(CC) $(CFLAGS) main.cpp -o $(OBJDIR)main.o

$(OBJDIR)colPrintf.o: colPrintf.cpp colPrintf.h colors.h myassert.h
	$(CC) $(CFLAGS) colPrintf.cpp -o $(OBJDIR)colPrintf.o

$(OBJDIR)printscan.o: printscan.cpp printscan.h consts.h colPrintf.h colors.h myassert.h
	$(CC) $(CFLAGS) printscan.cpp -o $(OBJDIR)printscan.o

$(OBJDIR)sqmath.o: sqmath.cpp sqmath.h consts.h myassert.h myisfinite.h
	$(CC) $(CFLAGS) sqmath.cpp -o $(OBJDIR)sqmath.o

$(OBJDIR)tests.o: tests.cpp tests.h consts.h colPrintf.h sqmath.h colors.h myassert.h
	$(CC) $(CFLAGS) tests.cpp -o $(OBJDIR)tests.o

$(OBJDIR)argvprocessing.o: argvprocessing.cpp argvprocessing.h
	$(CC) $(CFLAGS) argvprocessing.cpp -o $(OBJDIR)argvprocessing.o

$(OBJDIR)myisfinite.o: myisfinite.cpp myisfinite.h
	$(CC) $(CFLAGS) myisfinite.cpp -o $(OBJDIR)myisfinite.o

clean:
	rm $(OBJDIR)*

