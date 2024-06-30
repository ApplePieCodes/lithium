i686-elf-gcc -c src/kernel.c src/stdlib/tty.c src/stdlib/stdio/printf.c src/stdlib/stdio/putchar.c src/stdlib/stdio/puts.c src/stdlib/string/memcmp.c src/stdlib/string/memcpy.c src/stdlib/string/memmove.c src/stdlib/string/memset.c src/stdlib/string/strlen.c src/gdt.c src/memutils.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wno-error=implicit-function-declaration
i686-elf-gcc -T src/linker.ld -o lithium.bin kernel.o tty.o printf.o putchar.o puts.o memcmp.o memcpy.o memmove.o memset.o strlen.o gdt.o memutils.o -ffreestanding -O2 -nostdlib -lgcc

mkdir -p iso/boot/grub
cat > iso/boot/grub/grub.cfg << EOF
menuentry "Lithium Kernel" {
    multiboot2 /boot/lithium.bin
    boot
}
EOF

mkdir -p iso/boot
cp lithium.bin iso/boot/

grub-mkrescue -o build/lithium.iso iso

rm -rf iso
rm *.o

qemu-system-x86_64 build/lithium.iso