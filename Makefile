
# Répertoires
CC = g++
CFLAGS = 
NOM_EXEC = Jeux
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = include
OBJ_FILES = $(OBJ_DIR)/main.o $(OBJ_DIR)/Plateau.o $(OBJ_DIR)/Case.o $(OBJ_DIR)/Pion.o $(OBJ_DIR)/fonctions.o $(OBJ_DIR)/Position.o $(OBJ_DIR)/Joueur.o $(OBJ_DIR)/PlateauP4.o $(OBJ_DIR)/PlateauO.o $(OBJ_DIR)/CaseO.o $(OBJ_DIR)/PlateauFoM.o $(OBJ_DIR)/CaseFoM.o $(OBJ_DIR)/PionFoM.o $(OBJ_DIR)/Echequier.o $(OBJ_DIR)/Piece.o $(OBJ_DIR)/CaseE.o 
LIBS =

all : $(NOM_EXEC)

$(NOM_EXEC): $(OBJ_FILES)
	$(CC) -o $(NOM_EXEC) $(OBJ_FILES) $(LIBS)

obj/main.o : main.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
	
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	$(CC) -c $< -o $@ $(CFLAGS)
	
clear : clean
	rm Jeux
	
clean : 
	rm obj/*.o