SRC= src
OBJ = obj


SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))


.PHONY: clean all debug

all: $(OBJECTS)
	echo "Generando ejecutable..."
	gcc $^ -o lab


$(OBJ)/%.o: $(SRC)/%.c
	@echo "Generando archivos object de $@ ...."
	gcc -I$(SRC) $(OPTIONS) -c $< -o $@ 

debug: OPTIONS := -DDEBUG
debug: all

clean:
	-rm -rfv $(OBJ)/*.O	

