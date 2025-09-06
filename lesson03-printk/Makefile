CROSS ?= aarch64-linux-gnu
QEMU_BASE_DIR ?= /home/thomas/workspace/qemu-8.2.1/install/bin/
CFLAGS = -g -Wall -nostdlib -nostdinc -O0 -Iinclude
ASMFLAGS = -g -Iinclude -O0

all: clean kernel.img

%.o: %.c
	${CROSS}-gcc $(CFLAGS) -c $< -o $@

%.o: %.S
	${CROSS}-gcc $(ASMFLAGS) -c $< -o $@

C_FILES = $(wildcard *.c)
ASM_FILES = $(wildcard *.S)
OBJ_FILES = $(ASM_FILES:%.S=%.o)
OBJ_FILES += $(C_FILES:%.c=%.o)

kernel.elf: $(OBJ_FILES)
	${CROSS}-ld  $(OBJ_FILES) -T link.ld -Map kernel.map -o kernel.elf

kernel.img: kernel.elf
	${CROSS}-objcopy -O binary kernel.elf kernel.img
	${CROSS}-objdump -D kernel.elf > kernel.dump

clean:
	rm kernel.elf kernel.img kernel.map kernel.dump *.o >/dev/null 2>/dev/null || true

run: kernel.img
	${QEMU_BASE_DIR}qemu-system-aarch64 -M virt -cpu cortex-a72 \
		-device loader,file=kernel.img,addr=0x40100000,cpu-num=0 \
		-nographic

debug: kernel.img
	${QEMU_BASE_DIR}qemu-system-aarch64 -M virt -cpu cortex-a72 \
		-device loader,file=kernel.img,addr=0x40100000,cpu-num=0 \
		-nographic -S -s