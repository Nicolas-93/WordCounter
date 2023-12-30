CC=gcc
BUILD_DIR=build
SRC_DIR=src
INC_DIR=include
INCLUDE=-I$(INC_DIR)
LIBS=-lm
CFLAGS=-fdiagnostics-color=always -Wall -pedantic -std=gnu17 -O2
EXEC=word_counter

SOURCES=$(wildcard $(SRC_DIR)/*.c)
HEADERS=$(wildcard $(INC_DIR)/*.h)

OBJS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
#$(info $(OBJS))

all: $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

main.o: main.c args.h wordtree.h output.h wordarray.h
wordtree.o: wordtree.c wordtree.h word.h
algo.o: algo.c algo.h wordtree.h
output.o: output.c output.h
wordarray.o: wordarray.c wordarray.h wordtree.h
word.o: word.c word.h
args.o: args.c args.h wordarray.h test.h
test.o: test.c test.h wordtree.h algo.h 

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir --parents $(BUILD_DIR)
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

format: $(SOURCES) $(HEADERS)
	clang-format -i --style=file $^
	clang-tidy --fix $^

clean:
	rm -f $(OBJS)

mrproper: clean
	rm -f $(BUILD_DIR)/$(EXEC)
	rm -f $(NOM_ZIP)

.PHONY: clean all
