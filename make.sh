i686-elf-gcc -c src/kernel.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c stdlib/memcmp.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c stdlib/memcpy.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c stdlib/memmove.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c stdlib/memset.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c stdlib/strlen.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T src/linker.ld -o lithium.bin kernel.o memcmp.o memcpy.o memmove.o memset.o strlen.o -ffreestanding -O2 -nostdlib -lgcc

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