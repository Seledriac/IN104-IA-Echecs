CC = gcc
CCWIN = x86_64-w64-mingw32-gcc
ifdef DEBUG
	CFLAGS = -Wall -Wextra
else
	CFLAGS = -Ofast
endif
SRC = src
OBJ_LINUX = obj/linux
OBJ_WINDOWS = obj/windows
BIN = bin
SRCS = $(wildcard $(SRC)/*.c)
OBJS_LINUX = $(patsubst $(SRC)/%.c, $(OBJ_LINUX)/%.o, $(SRCS))
OBJS_WINDOWS = $(patsubst $(SRC)/%.c, $(OBJ_WINDOWS)/%.o, $(SRCS))

TARGET_LINUX = $(BIN)/nom1_nom2_linux # à éditer
TARGET_WINDOWS = $(BIN)/nom1_nom2_windows.exe # à éditer

.PHONY: all linux windows clean

all: linux windows

linux: $(TARGET_LINUX)

windows: $(TARGET_WINDOWS)

$(TARGET_LINUX): $(OBJS_LINUX)
	$(CC) $^ -o $@

$(TARGET_WINDOWS): $(OBJS_WINDOWS)
	$(CCWIN) $^ -o $@

$(OBJ_LINUX)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_WINDOWS)/%.o: $(SRC)/%.c
	$(CCWIN) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_LINUX)/* $(OBJ_WINDOWS)/* $(BIN)/*