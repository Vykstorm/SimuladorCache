

CC=gcc
CFLAGS=-O3 -Wall 
LDFLAGS=
SOURCES=Util.c Leer.c Cache.c SimuladorCache.c 
OBJECTS=$(SOURCES:.c=.o)
EXEC=SimuladorCache


all: build


build: $(EXEC)

tests: $(TESTS)

clean: 
	rm -f *.o
	rm -f $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@


# Regla para compilar código fuente .c
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@ 