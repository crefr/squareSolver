CC = g++
CFLAGS = -c -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
FILENAME = a.exe
OBJDIR = Obj/

$(FILENAME): Obj/main.o Obj/colPrintf.o Obj/printscan.o Obj/sqmath.o Obj/tests.o
	$(CC) $(OBJDIR)main.o $(OBJDIR)colPrintf.o $(OBJDIR)printscan.o $(OBJDIR)sqmath.o $(OBJDIR)tests.o -o $(FILENAME)

Obj/main.o: main.cpp colors.h printscan.h sqmath.h consts.h tests.h colPrintf.h
	$(CC) $(CFLAGS) main.cpp -o $(OBJDIR)main.o

Obj/colPrintf.o: colPrintf.cpp colPrintf.h colors.h
	$(CC) $(CFLAGS) colPrintf.cpp -o $(OBJDIR)colPrintf.o

Obj/printscan.o: printscan.cpp printscan.h consts.h colPrintf.h colors.h
	$(CC) $(CFLAGS) printscan.cpp -o $(OBJDIR)printscan.o

Obj/sqmath.o: sqmath.cpp sqmath.h consts.h
	$(CC) $(CFLAGS) sqmath.cpp -o $(OBJDIR)sqmath.o

Obj/tests.o: tests.cpp tests.h consts.h colPrintf.h sqmath.h colors.h
	$(CC) $(CFLAGS) tests.cpp -o $(OBJDIR)tests.o

clean:
	rm $(OBJDIR)*

