CC=gcc
CFLAGS=-std=c99 -Wall

VERDE=\033[38;2;57;249;128m
NORMAL=\033[0m

DIROBJETOS=.objs
DIRS=$(DIROBJETOS) bin

OBJETOS=$(DIROBJETOS)/main.o $(DIROBJETOS)/planificador.o $(DIROBJETOS)/lista.o $(DIROBJETOS)/colacp.o

all: planificador

objetos:
	@mkdir -p $(DIRS)
	@echo -e "$(VERDE)[20%] Creando objeto lista.o $(NORMAL)"
	@$(CC) $(CFLAGS) -c -o $(DIROBJETOS)/lista.o lista/lista.c

	@echo -e "$(VERDE)[40%] Creando objeto colacp.o $(NORMAL)"
	@$(CC) $(CFLAGS) -c -o $(DIROBJETOS)/colacp.o colacp/colacp.c

	@echo -e "$(VERDE)[60%] Creando objeto planificado.o $(NORMAL)"
	@$(CC) $(CFLAGS) -c -o $(DIROBJETOS)/planificador.o planificador/planificador.c

	@echo -e "$(VERDE)[80%] Creando objeto main.o $(NORMAL)"
	@$(CC) $(CFLAGS) -c -o $(DIROBJETOS)/main.o main.c

planificador: objetos
	@echo -e "$(VERDE)[100%] Creando ejecutable planificador $(NORMAL)"
	@$(CC) $(CFLAGS) -o bin/$@ $(OBJETOS)

documentacion:
	@echo -e "$(VERDE)Generando Documentacion... $(NORMAL)"
	@doxygen Doxyfile > /dev/null
