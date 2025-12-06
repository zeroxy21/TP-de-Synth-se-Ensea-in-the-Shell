# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -g # Affiche tous les warnings et ajoute les infos de debug

# Nom de l'exécutable final
TARGET = enseash

# Liste des fichiers sources
SRCS = main.c utils.c

# Transformation des .c en .o (objets)
OBJS = $(SRCS:.c=.o)

# Règle par défaut (ce qui se lance quand on tape juste "make")
all: $(TARGET)

# Édition de liens (création de l'exécutable)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilation des fichiers sources en objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Pour nettoyer les fichiers compilés (taper "make clean")
clean:
	rm -f $(OBJS) $(TARGET)