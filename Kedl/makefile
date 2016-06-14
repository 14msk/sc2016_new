#Makefile fuer: ../sc2016/blatt_2/jacobi_13_xiii/matrix

ODIR = obj
BDIR = bin
SDIR = src
IDIR = inc
LDIR = log
TDIR = tst
HTML_DIR = html

REF_FILE = $(TDIR)/matrix_out.ref
CMP_FILE = $(TDIR)/matrix_out.cmp
TST_CMD = $(BDIR)/matrix 1e-13
TST_CMD_GPROF = $(BDIR)/matrix_gprof 1e-13
GPROF_LOG = $(LDIR)/matrix_gprof_out.txt
VALGRIND_CMD = valgrind -v --leak-check=yes $(TST_CMD)
GPROF_CMD = gprof

ARCHIVE = ./bsp_14.tar.gz

CC = g++
CXXFLAGS = -std=c++11 -Wunused -Wall -g
CXXFLAGS_GPROF = -std=c++11 -Wall -g -pg -O1

_DEPS = matrix.hpp \
	myexceptions.h \
	myvector.h

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = matrix.o \
	main.o \
	myvector.o \
	myexceptions.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	@mkdir -p $(@D)
	[ -d $(LDIR) ] || mkdir -p $(LDIR)
	$(CC) $(CXXFLAGS) -c -o $@ < 2>&1 | tee $(LDIR)/$(notdir $<)_log.txt

$(BDIR)/matrix: $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(CXXFLAGS) -o $@ $^ 

archive:
	tar -cvzf $(ARCHIVE) ./$(IDIR) ./$(SDIR) ./$(REF_FILE) ./makefile 

valgrind: $(BDIR)/matrix
	$(VALGRIND_CMD) 2>&1 | tee $(LDIR)/matrix_valgrind.txt

testing: $(BDIR)/matrix
	[ -d $(TDIR) ] || mkdir -p $(TDIR)
	[ -f $(REF_FILE) ] || $(TST_CMD) | tee $(REF_FILE)
	$(TST_CMD) | tee $(CMP_FILE)
	meld $(REF_FILE) $(CMP_FILE)

git_push: 
	git push

git_pull: 
	git pull

.PHONY: clean \
	gprof \
	doxygen

doxygen:
	doxygen doxygen/Doxyfile

gprof: $(SDIR)/*.cpp $(DEPS)
	[ -d $(LDIR) ] || mkdir -p $(LDIR)
	[ -d $(BDIR) ] || mkdir -p $(BDIR)
	$(CC) $(CXXFLAGS_GPROF) -o $(BDIR)/matrix_$@ $^ 
	$(TST_CMD_GPROF) && mv gmon.out $(GPROF_LOG)
	gprof $(BDIR)/matrix_$@ $(GPROF_LOG) > $(LDIR)/matrix_gprof_analysis.txt

clean:
	rm -rf $(ODIR) \
	$(BDIR) \
	$(HTML_DIR) \
        $(ARCHIVE) \
        $(CMP_FILE) \
	./doxygen/*.log \
	$(LDIR)
