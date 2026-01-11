CXX = g++
STD = -std=c++20
CXXFLAGS = -Wall -Wextra -O3

SDL_INCLUDE_PATH = ./SDL2/include
SDL_LIB_PATH = ./SDL2/lib
SDL_DLL_SRC = .\SDL2\bin\SDL2.dll
SDL_DLL_DEST = SDL2.dll

LD_FLAGS = -lmingw32 -lSDL2main -lSDL2
SRC_DIR = ../src

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OUTPUT = GBJoy.exe

all: $(OUTPUT) copy_dll

$(OUTPUT):
	$(CXX) $(STD) $(CXXFLAGS) $(SRCS) -o $(OUTPUT) -I $(SDL_INCLUDE_PATH) -L $(SDL_LIB_PATH) $(LD_FLAGS)

copy_dll:
	@if not exist $(SDL_DLL_DEST) copy $(SDL_DLL_SRC) $(SDL_DLL_DEST)

clean:
	del $(OUTPUT) $(SDL_DLL_DEST)
