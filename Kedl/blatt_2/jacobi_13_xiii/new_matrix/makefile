ODIR = obj
BDIR = bin
SDIR = src
IDIR = inc
LDIR = log
TDIR = tst

REF_FILE = $(TDIR)/matrix_out.ref
CMP_FILE = $(TDIR)/matrix_out.cmp
TST_CMD = $(BDIR)/matrix 1e-13

ARCHIVE = ./bsp_14.tar.gz

CC = g++
CXXFLAGS = -std=c++11 -Wunused
CFLGAGS = -I./$(IDIR)

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
	$(CC) $(CXXFLAGS) -c -o $@ $< $(CFLAGS) 2>&1 | tee $(LDIR)/$(notdir $<)_log.txt

$(BDIR)/matrix: $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(CXXFLAGS) -o $@ $^ $(CFLAGS)

archive:
	tar -cvzf $(ARCHIVE) ./$(IDIR) ./$(SDIR) ./$(REF_FILE) ./makefile 

testing: $(BDIR)/matrix
	[ -d $(TDIR) ] || mkdir -p $(TDIR)
	[ -f $(REF_FILE) ] || $(TST_CMD) | tee $(REF_FILE)
	$(TST_CMD) | tee $(CMP_FILE)
	meld $(REF_FILE) $(CMP_FILE)

.PHONY: clean

clean:
	rm -rf $(ODIR) \
	$(BDIR) \
	$(LDIR)
