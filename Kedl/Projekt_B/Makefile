# Makefile zu Proj_B
# Scientific Computing, SoSe 2016
# Simon Pieber, Pia Kedl
# Mesh improvement and manipulation

PROGRAM = main.exe

SRC_FILES = main.cpp MyMatrix.cpp MyMatrixCRS.cpp MyVector.cpp mesh.cpp
#SRC_FILES = $(wildcard *.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

COMPILER = g++
CFLAGS = -std=c++11 -Wall -pedantic -Weffc++ -Wextra \
-Wno-sign-compare -Wswitch-default -Wfloat-equal -Wundef \
-Wredundant-decls -Winit-self -Wshadow -Wparentheses \
-Wshadow -Wunreachable-code -Wuninitialized

# Erstes Target (Standard)

$(PROGRAM): $(OBJ_FILES)
	@echo "Erzeuge $(PROGRAM)"
	@g++ $(OBJ_FILES) -o $(PROGRAM)

.cpp.o:
	@echo "Compiliere: $<"
	@$(COMPILER) -c $(CFLAGS) $< 2> logs/$(<:.cpp=).log
   
.h.cpp:
	@echo "Neuerungen bei $<"
	@touch $(SRC_FILES)

clean:
	@rm -fv *.o *.log *.exe x*.dat
	@rm -fvr bin obj
	@rm -fr doxy_html && echo "Dokumentation entfernt."

run: $(PROGRAM)
	@echo " "
	@echo "Starte $(PROGRAM) $(INPUT) ..."
	@echo " "
	@./$(PROGRAM) $(INPUT)

	
rebuild:
	@make clean
	@make -j8

rrun:
	@make clean
	@make run
	
doc:
	@doxygen Doxyfile

tar:
	@make clean > /dev/null
	@tar -cf proj_b.tar *
	@mkdir proj_b
	@tar -xf proj_b.tar -C proj_b
	@tar -cf proj_b.tar proj_b
	@rm -rf proj_b
	@echo "Projekt verpackt in proj_b.tar"
	@ls -lh proj_b.tar
	
