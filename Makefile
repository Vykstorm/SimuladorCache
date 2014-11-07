

CC=gcc
CFLAGS=-O3 -Wall 
LDFLAGS=
SOURCES=Util.c Leer.c Cache.c SimuladorCache.c 
OBJECTS=$(SOURCES:.c=.o)
EXEC=SimuladorCache
TESTS=TestLeerConfiguracion TestLeerDirecciones 

all: build


build: $(EXEC)

tests: $(TESTS)

clean: 
	rm -f *.o
	rm -f $(EXEC)
	rm -f $(TESTS)

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Compilación de los tests
TestLeerConfiguracion: TestLeerConfiguracion.o Leer.o Util.o
	$(CC)  $(LDFLAGS) $^ -o $@

TestLeerDirecciones: TestLeerDirecciones.o Leer.o Util.o 
	$(CC) $(LDFLAGS) $^ -o $@ 

# Regla para compilar código fuente .c
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@ 