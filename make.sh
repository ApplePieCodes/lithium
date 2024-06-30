i686-elf-gcc -c src/kernel.c src/tty.c src/stdio/printf.c src/stdio/putchar.c src/stdio/puts.c src/string/memcmp.c src/string/memcpy.c src/string/memmove.c src/string/memset.c src/string/strlen.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T src/linker.ld -o lithium.bin kernel.o tty.o printf.o putchar.o puts.o memcmp.o memcpy.o memmove.o memset.o strlen.o -ffreestanding -O2 -nostdlib -lgcc

mkdir -p iso/boot/grub
cat > iso/boot/grub/grub.cfg << EOF
menuentry "Lithium Kernel" {
    multiboot /boot/lithium.bin
    boot
}
EOF

mkdir -p iso/boot
cp lithium.bin iso/boot/

grub-mkrescue -o build/lithium.iso iso

rm -rf iso
rm *.o

qemu-system-x86_64 build/lithium.iso