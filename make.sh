i686-elf-gcc -c src/kernel.c src/drivers/vga.c src/utils/wait.c src/drivers/idt.c src/drivers/keyboard.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
nasm -f elf32 src/drivers/idt_load.asm -o idt_load.o
i686-elf-gcc -T src/linker.ld -o lithium.bin kernel.o vga.o wait.o idt.o keyboard.o idt_load.o -ffreestanding -O2 -nostdlib -lgcc

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