

HEADERS		= myls.h strings.h

C_SRCS		= myls.c buildFileInfoTable.c displayFileInfo.c \
		  sizeSortDescending.c nameSortDescending.c globals.c \
		  displayOwnerName.c displayPermissions.c setDisplayMode.c

ASM_SRCS	= displayGroupName.s sizeSortAscending.s \
		  nameSortAscending.s

C_OBJS		= myls.o buildFileInfoTable.o displayFileInfo.o \
		  sizeSortDescending.o displayOwnerName.o globals.o \
		  displayPermissions.o nameSortDescending.o setDisplayMode.o

ASM_OBJS	= displayGroupName.o nameSortAscending.o \
		  sizeSortAscending.o

OBJS		= ${C_OBJS} ${ASM_OBJS}

EXE		= myls



GCC		= gcc
ASM		= $(GCC)
LINT		= lint

GCC_FLAGS	= -c -g -Wall -D__EXTENSIONS__ -std=c99
LINT_FLAGS1	= -c -err=warn
LINT_FLAGS2	= -u -err=warn
ASM_FLAGS	= -c -g
LD_FLAGS	= -g -Wall



.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Linting each C source file separately ..."
	$(LINT) $(LINT_FLAGS1) $<
	@echo ""
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

$(EXE):	$(OBJS)
	@echo "2nd phase lint on all C source files ..."
	$(LINT) $(LINT_FLAGS2) *.ln
	@echo ""
	@echo "Linking all object modules ..."
	$(GCC) -o $(EXE) $(LD_FLAGS) $(OBJS)
	@echo ""
	@echo "Done."

${C_OBJS}:      ${HEADERS}

unitTest_buildFileInfoTable: test.h myls.h strings.h buildFileInfoTable.c \
		  unitTest_buildFileInfoTable.c ref_buildFileInfoTable.o
	@echo "Compiling unitTest_buildFileInfoTable.c"
	gcc -g -o unitTest_buildFileInfoTable unitTest_buildFileInfoTable.c \
		  ref_buildFileInfoTable.o buildFileInfoTable.c
	@echo "Done."

run_unitTest_buildFileInfoTable: unitTest_buildFileInfoTable
	@echo "Running unitTest_buildFileInfoTable"
	@./unitTest_buildFileInfoTable

unitTest_setDisplayMode: test.h myls.h setDisplayMode.c \
			unitTest_setDisplayMode.c
	@echo "Compiling unitTest_setDisplayMode.c"
	gcc -g -o unitTest_setDisplayMode unitTest_setDisplayMode.c \
		  setDisplayMode.c
	@echo "Done."

unitTest_sizeSortAscending: test.h myls.h sizeSortAscending.s \
			unitTest_sizeSortAscending.c
	@echo "Compiling unitTest_sizeSortAscending.c"
	gcc -g -o unitTest_sizeSortAscending unitTest_sizeSortAscending.c \
		sizeSortAscending.s
	@echo "Done."

unitTest_sizeSortDescending: test.h myls.h sizeSortDescending.c \
			unitTest_sizeSortDescending.c
	@echo "Compiling unitTest_sizeSortDescending.c"
	gcc -g -o unitTest_sizeSortDescending unitTest_sizeSortDescending.c \
		sizeSortDescending.c
	@echo "Done."

unitTest_nameSortAscending: test.h myls.h nameSortAscending.s \
			unitTest_nameSortAscending.c
	@echo "Compiling unitTest_nameSortAscending.c"
	gcc -g -o unitTest_nameSortAscending unitTest_nameSortAscending.c \
		nameSortAscending.s
	@echo "Done."

unitTest_nameSortDescending: test.h myls.h nameSortDescending.c \
			unitTest_nameSortDescending.c
	@echo "Compiling unitTest_nameSortDescending.c"
	gcc -g -o unitTest_nameSortDescending unitTest_nameSortDescending.c \
		nameSortDescending.c
	@echo "Done."


clean:
	@echo "Cleaning up project directory ..."
	rm -f *.o a.out *.ln core $(EXE)
	@echo ""
	@echo "Clean."

new:
	make --no-print-directory clean
	make --no-print-directory

