# Required Dependencies:
# * gnu make		(sudo apt-get install make)
# * nasm		(sudo apt-get install nasm)
# * gcc cross-compiler	(see http://wiki.osdev.org/GCC_Cross-Compiler)
# * grub-mkrescue	(sudo apt-get install xorriso)

# Additional Reccomended Software:
# * qemu		(sudo apt-get install qemu)



# executables
export ASM=nasm
export CC=i686-elf-gcc
export LINK=i686-elf-gcc
export QEMU=qemu-system-i386

# flags
export ASFLAGS=-felf32
export CFLAGS=-nostdlib -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdinc -fno-builtin -I./include -masm=intel -c
export LDFLAGS=-ffreestanding -O3 -nostdlib -lgcc

# object files
OBJS=			\
kernel/start.o		\
kernel/main.o		\

all:
	make build
	make vm
	make clean

build:
	# iso
	mkdir -p iso/boot/grub
	cp grub.cfg iso/boot/grub/grub.cfg
	
	# kernel
	$(MAKE) -C kernel build
	
	# library
	# $(MAKE) -C library build
	
	# kernel.bin
	$(CC) $(LDFLAGS) -T kernel/link.ld -o iso/boot/kernel.bin $(OBJS)
	
	# CarbonOS.iso
	grub-mkrescue -o CarbonOS.iso iso

vm:
	$(QEMU) -cdrom CarbonOS.iso

clean:
	rm -rf iso
	rm -f CarbonOS.iso
	$(MAKE) -C kernel clean