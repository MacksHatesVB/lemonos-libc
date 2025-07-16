BUILD_DIR := build

CC := gcc
ASM := nasm
ASMFLAGS := -f elf32
SSEFLAGS := -msse -mno-avx
SSE2FLAGS := -msse -msse2 -mno-avx
SSE4FLAGS := -msse -msse2 -msse4 -mno-avx
AVXFLAGS := -msse -msse2 -msse4 -mavx
FPUFLAGS := -mno-sse -mno-avx
CCFLAGS := -m32 -Ofast -fno-stack-protector -D __LEMONOS__ -static -fpie --static-pie -mhard-float -fomit-frame-pointer -funsigned-char -falign-functions=16 -ffreestanding -nostdlib -nostartfiles -funsigned-char -Iinclude
LD := ld
LDFLAGS := -m elf_i386 --no-dynamic-linker -pic -pie -Tlink.ld
MAKE := make
AR := ar

ASM_SOURCES=$(wildcard src/*.asm)
SOURCES=$(wildcard src/*.c)
ASM_OBJECTS=$(patsubst src/%.asm,$(BUILD_DIR)/%.o,$(ASM_SOURCES))
OBJECTS=$(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

SSE_ASM_OBJECTS=$(patsubst src/%.asm,$(BUILD_DIR)_sse/%.o,$(ASM_SOURCES))
SSE_OBJECTS=$(patsubst src/%.c,$(BUILD_DIR)_sse/%.o,$(SOURCES))
SSE2_ASM_OBJECTS=$(patsubst src/%.asm,$(BUILD_DIR)_sse2/%.o,$(ASM_SOURCES))
SSE2_OBJECTS=$(patsubst src/%.c,$(BUILD_DIR)_sse2/%.o,$(SOURCES))
SSE4_ASM_OBJECTS=$(patsubst src/%.asm,$(BUILD_DIR)_sse4/%.o,$(ASM_SOURCES))
SSE4_OBJECTS=$(patsubst src/%.c,$(BUILD_DIR)_sse4/%.o,$(SOURCES))
AVX_ASM_OBJECTS=$(patsubst src/%.asm,$(BUILD_DIR)_avx/%.o,$(ASM_SOURCES))
AVX_OBJECTS=$(patsubst src/%.c,$(BUILD_DIR)_avx/%.o,$(SOURCES))

OUTPUT := libc.a
SSE_OUTPUT := sse_libc.a
SSE2_OUTPUT := sse2_libc.a
SSE4_OUTPUT := sse4_libc.a
AVX_OUTPUT := avx_libc.a

# chmod 554 $(OUTPUT)
OUTPUT_PERMS := 664

TEST_PROGRAM := main.c
TEST_OUTPUT := main

default: mkdir build build_sse build_sse2 build_sse4 build_avx test

mkdir:
	mkdir -p ${BUILD_DIR} ${BUILD_DIR}_sse ${BUILD_DIR}_sse2 ${BUILD_DIR}_sse4 ${BUILD_DIR}_avx

$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(FPUFLAGS) $(CCFLAGS) $^ -c -o $@
$(BUILD_DIR)/%.o: src/%.asm
	$(ASM) $(ASMFLAGS) $^ -o $@

$(BUILD_DIR)_sse/%.o: src/%.c
	$(CC) $(SSEFLAGS) $(CCFLAGS) $^ -c -o $@
$(BUILD_DIR)_sse/%.o: src/%.asm
	$(ASM) $(ASMFLAGS) $^ -o $@

$(BUILD_DIR)_sse2/%.o: src/%.c
	$(CC) $(SSE2FLAGS) $(CCFLAGS) $^ -c -o $@
$(BUILD_DIR)_sse2/%.o: src/%.asm
	$(ASM) $(ASMFLAGS) $^ -o $@

$(BUILD_DIR)_sse4/%.o: src/%.c
	$(CC) $(SSE4FLAGS) $(CCFLAGS) $^ -c -o $@
$(BUILD_DIR)_sse4/%.o: src/%.asm
	$(ASM) $(ASMFLAGS) $^ -o $@

$(BUILD_DIR)_avx/%.o: src/%.c
	$(CC) $(AVXFLAGS) $(CCFLAGS) $^ -c -o $@
$(BUILD_DIR)_avx/%.o: src/%.asm
	$(ASM) $(ASMFLAGS) $^ -o $@


build: $(OBJECTS) $(ASM_OBJECTS)
	$(AR) cr $(OUTPUT) $^
	chmod $(OUTPUT_PERMS) $(OUTPUT)

build_sse: $(SSE_OBJECTS) $(SSE_ASM_OBJECTS)
	$(AR) cr $(SSE_OUTPUT) $^
	chmod $(OUTPUT_PERMS) $(SSE_OUTPUT)

build_sse2: $(SSE2_OBJECTS) $(SSE2_ASM_OBJECTS)
	$(AR) cr $(SSE2_OUTPUT) $^
	chmod $(OUTPUT_PERMS) $(SSE2_OUTPUT)

build_sse4: $(SSE4_OBJECTS) $(SSE4_ASM_OBJECTS)
	$(AR) cr $(SSE4_OUTPUT) $^
	chmod $(OUTPUT_PERMS) $(SSE4_OUTPUT)

build_avx: $(AVX_OBJECTS) $(AVX_ASM_OBJECTS)
	$(AR) cr $(AVX_OUTPUT) $^
	chmod $(OUTPUT_PERMS) $(AVX_OUTPUT)

test: $(OUTPUT)
	$(CC) $(CCFLAGS) $(TEST_PROGRAM) -c -o $(TEST_OUTPUT).o
	$(LD) $(LDFLAGS) $(TEST_OUTPUT).o $(OUTPUT) -o $(TEST_OUTPUT)

clean:
	rm -rf ${BUILD_DIR} ${BUILD_DIR}_sse ${BUILD_DIR}_sse2 ${BUILD_DIR}_sse4 ${BUILD_DIR}_avx
	rm -rf ${OUTPUT} ${SSE_OUTPUT} ${SSE2_OUTPUT} ${SSE4_OUTPUT} ${AVX_OUTPUT} $(TEST_OUTPUT).o $(TEST_OUTPUT)
