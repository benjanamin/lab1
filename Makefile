SRC= src
OBJ = obj


SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))



all: $(OBJECTS)
	echo "Generando ejecutable..."
	gcc $^ -o salida


$(OBJ)/%.o: $(SRC)/%.c
	@echo "Generando archivos object de $@ ...."
	gcc -I$(SRC) -c $< -o $@ 
