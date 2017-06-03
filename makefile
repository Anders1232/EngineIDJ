#-------------------------------------------------------------
#Assume-se uma distribuição Linux como sistema operacional padrão
#-------------------------------------------------------------

COMPILER = g++
#comando para remover pastas
RMDIR = rm -rf
#comando para remover arquivos
RM = rm -f
CD = cd
#comando para executar o make
MAKE = make

#Flags para geração automática de dependências
DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_PATH)/$.d
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
#Se o gcc não reconhecer a flag -fdiagnostics-color basta retirar ela
#FLAGS= -std=c++11 -Wall -pedantic -Wextra -fmax-errors=5 -Wno-unused-parameter -fdiagnostics-color
FLAGS = -std=c++11 -Wall -pedantic -Wextra -fmax-errors=5 -Wno-unused-parameter
DFLAGS = -g -O0

GAME_PATH= Game
ENGINE_PATH= Engine

GAME_INC_PATH = -I$(GAME_PATH)/include
GAME_SRC_PATH = $(GAME_PATH)/src
GAME_BIN_PATH = $(GAME_PATH)/bin
GAME_DEP_PATH = $(GAME_PATH)/dep
ENGINE_INC_PATH = -I$(ENGINE_PATH)/include
ENGINE_SRC_PATH = $(ENGINE_PATH)/src
ENGINE_BIN_PATH = $(ENGINE_PATH)/bin
ENGINE_DEP_PATH = $(ENGINE_PATH)/dep

#Uma lista de arquivos por extensão:
GAME_CPP_FILES= $(wildcard $(GAME_SRC_PATH)/*.cpp)
GAME_OBJ_FILES= $(addprefix $(GAME_BIN_PATH)/,$(notdir $(GAME_CPP_FILES:.cpp=.o)))
GAME_DEP_FILES = $(wildcard $(GAME_DEP_PATH)/*.d)
ENGINE_CPP_FILES= $(wildcard $(ENGINE_SRC_PATH)/*.cpp)
ENGINE_OBJ_FILES= $(addprefix $(ENGINE_BIN_PATH)/,$(notdir $(ENGINE_CPP_FILES:.cpp=.o)))
ENGINE_DEP_FILES = $(wildcard $(ENGINE_DEP_PATH)/*.d)

#Nome do executável
EXEC = JOGO

#-------------------------------------------------------------
#Caso o sistema seja windows
#-------------------------------------------------------------
ifeq ($(OS),Windows_NT)
#comando para remover um diretório recursivamente
RMDIR= rd /s /q
#comando para deletar um único arquivo
RM = del
#comando para fazer o make
MAKE = mingw32-make

#path da SDL
SDL_PATH = C:/Tools/msys64/mingw64
INC_PATH += -I$(SDL_PATH)/include/SDL2
FLAGS += -mwindows
DFLAGS +=  -mconsole
LIBS := -lmingw32 -lSDL2main $(LIBS)

#Nome do executável
EXEC := $(EXEC).exe

else
UNAME_S := $(shell uname -s)

#-------------------------------------------------------------
#Caso o sistema seja Mac
#-------------------------------------------------------------

ifeq ($(UNAME_S), Darwin)

LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

endif
endif

all: $(EXEC)

$(EXEC): $(ENGINE_OBJ_FILES) $(GAME_OBJ_FILES)
	$(COMPILER) -o $@ $^ $(LIBS) $(FLAGS)


.PHONY: $(ENGINE_BIN_PATH)/%.o
$(ENGINE_BIN_PATH)/%.o: $(ENGINE_SRC_PATH)/%.cpp
	$(CD) $(ENGINE_PATH) && $(MAKE) $(DEBUG_OU_RELEASE) objects

.PHONY: $(GAME_BIN_PATH)/%.o
$(GAME_BIN_PATH)/%.o: $(GAME_SRC_PATH)/%.cpp
	$(CD) $(GAME_PATH) && $(MAKE) $(DEBUG_OU_RELEASE) objects


clean:
	$(CD) $(ENGINE_PATH) && $(MAKE) clean
	$(CD) $(GAME_PATH) && $(MAKE) clean
	$(RM) $(EXEC)

.PHONY: debug clean release again
#regra pra debug
print-% : ; @echo $* = $($*)

debug: DEBUG_OU_RELEASE = fdebug
debug: FLAGS += $(DFLAGS)
debug: all

release: DEBUG_OU_RELEASE = frelease
release: FLAGS += -O3 -mtune=native
release: all

again: clean
again: all

doc: dclean
	doxygen Doxyfile

dclean:
	$(RMDIR) docs
	$(RM) doxygen_sqlite3.db

help:
	@echo.
	@echo Available targets:
	@echo - release:  Builds the release version (default target)
	@echo - debug:    Builds the debug version
	@echo - doc:      Clean and generate Doxygen documentation
	@echo - dclean:   Clean Doxygen documentation
	@echo - profile:  Builds a version to use with gprof (not implemented)
	@echo - coverage: Builds a version to use with gcov (not implemented)
	@echo - help:     Shows this help
	@echo.

