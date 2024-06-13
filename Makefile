TARGET := png2ico
TARGET_VERSION := $(shell cat version.txt)

BUILD_DIR := ./build
SRC_DIR := ./src

SRCS := $(shell find $(SRC_DIR) -name '*.c')

OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

INC_FLAGS := -I$(SRC_DIR)

CC = gcc
CFLAGS = --std=c99 -Os -Wall -Wextra -Wfloat-equal -Wundef -Wshadow \
	-Wpointer-arith -Wcast-align -Wstrict-prototypes -Wswitch-default \
	-Wunreachable-code -DPNG2ICO_VERSION='"$(TARGET_VERSION)"'

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
