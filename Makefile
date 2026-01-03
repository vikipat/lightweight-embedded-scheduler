# Project: Lightweight Embedded Scheduler
# Author: Vivek Patel

CC      := gcc
TARGET  := scheduler_demo

SRC_DIR := src
BUILD_DIR := build

SRCS := $(SRC_DIR)/main.c \
        $(SRC_DIR)/scheduler.c

CFLAGS_COMMON := -Wall -Wextra -std=c11

CFLAGS_DEBUG  := $(CFLAGS_COMMON) -g
CFLAGS_RELEASE := $(CFLAGS_COMMON) -O2

.PHONY: all debug release clean

all: debug

debug:
	$(CC) $(CFLAGS_DEBUG) $(SRCS) -o $(BUILD_DIR)/debug/$(TARGET)

release:
	$(CC) $(CFLAGS_RELEASE) $(SRCS) -o $(BUILD_DIR)/release/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)/debug/* $(BUILD_DIR)/release/*
