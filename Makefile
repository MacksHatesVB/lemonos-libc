BUILD_DIR := build

CC := gcc
ASM := nasm
ASMFLAGS := -f elf32
# sse3 support being considered...
CCFLAGS := -O3 -fno-stack-protector -static -fpie --static-pie -msse -msse2 -mno-avx -mhard-float -m32 -fno-builtin -fno-builtin-function -fomit-frame-pointer -funsigned-char -falign-functions=16 -ffreestanding -nostdlib -nostartfiles -funsigned-char -Iinclude
LD := ld
LDFLAGS := -m elf_i386 --no-dynamic-linker -pic -pie -Tlink.ld
MAKE := make
AR := ar

ASM_SOURCES=$(wildcard src/*.asm)
SOURCES=$(wildcard src/*.c)
ASM_OBJECTS=$(patsubst src/%.asm,$(BUILD_DIR)/%.o,$(ASM_SOURCES))
OBJECTS=$(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

OUTPUT := libc.a

# chmod 554 $(OUTPUT)
OUTPUT_PERMS := 664

TEST_PROGRAM := main.c
TEST_OUTPUT := main

default: mkdir build

mkdir:
	mkdir -p ${BUILD_DIR}

$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CCFLAGS) $^ -c -o $@

$(BUILD_DIR)/%.o: src/%.asm
	$(ASM) $(ASMFLAGS) $^ -o $@

build: $(OBJECTS) $(ASM_OBJECTS)
	$(AR) cr $(OUTPUT) $^
	chmod $(OUTPUT_PERMS) $(OUTPUT)
	$(CC) $(CCFLAGS) $(TEST_PROGRAM) -c -o $(TEST_OUTPUT).o
	$(LD) $(LDFLAGS) $(TEST_OUTPUT).o $(OUTPUT) -o $(TEST_OUTPUT)

clean:
	rm -rf ${BUILD_DIR} ${OUTPUT} $(TEST_OUTPUT).o $(TEST_OUTPUT)
