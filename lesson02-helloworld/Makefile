CROSS ?= aarch64-linux-gnu
QEMU_BASE_DIR ?= /home/thomas/workspace/qemu-8.2.1/install/bin/
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles

all: clean kernel.img

start.o: start.S
	${CROSS}-gcc $(CFLAGS) -c start.S -o start.o

kernel.o: kernel.c
	${CROSS}-gcc $(CFLAGS) -c kernel.c -o kernel.o

kernel.img: start.o kernel.o
	${CROSS}-ld -nostdlib -nostartfiles start.o kernel.o -T link.ld -o kernel.elf
	${CROSS}-objcopy -O binary kernel.elf kernel.img

clean:
	rm kernel.elf kernel.img *.o >/dev/null 2>/dev/null || true

run:
	${QEMU_BASE_DIR}qemu-system-aarch64 -M virt -cpu cortex-a57 \
		-kernel kernel.img \
		-nographic