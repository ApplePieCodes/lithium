mkdir -p iso_root

if [ ! -d "limine" ]; then
	git clone https://github.com/limine-bootloader/limine.git --branch=v8.x-binary --depth=1
fi
cd limine
make limine
cd ..
rm -rf iso_root
mkdir -p iso_root/boot
cp -v kernel.elf bg.png iso_root/boot
mkdir -p iso_root/boot/limine
touch iso_root/boot/limine/limine.conf
echo "timeout: 3
" \
" wallpaper: boot():/boot/bg.png
" \
"/lithium
" \
"    protocol: limine
" \
"    path: boot():/boot/kernel.elf
" > iso_root/boot/limine/limine.conf
mkdir -p iso_root/EFI/BOOT
cp -v limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/boot/limine/
cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/
cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/
xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin \
	-no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
	-apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin \
	-efi-boot-part --efi-boot-image --protective-msdos-label \
	iso_root -o lithium.iso
./limine/limine bios-install lithium.iso