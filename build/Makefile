COMPILER = g++
OUTPUT = windows/game.exe
FLAGS = -w -std=c++17
INCLUDE = -L ../lib -I ../include -lraylib -lopengl32 -lgdi32 -lwinmm

default:
ifeq ($(OS),LINUX)
	$(eval OUTPUT=linux/game)
	$(eval INCLUDE=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11)
endif
	$(COMPILER) ../main.cpp -o $(OUTPUT) $(FLAGS) $(INCLUDE)
	cd linux/ && touch save && echo "999999" > save
	cd windows/ && touch save && echo "999999" > save