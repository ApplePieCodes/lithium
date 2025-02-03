import os
import subprocess
import shutil

def run_command(command):
    """Run a shell command and print its output."""
    print(f"Running command: {command}")
    subprocess.run(command, shell=True, check=True)

def build_iso():
    # Cloning Limine bootloader
    print("Cloning Limine bootloader...")
    if not os.path.isdir("limine"):
        run_command("git clone https://github.com/limine-bootloader/limine.git --branch=v8.x-binary --depth=1")
    
    # Building Limine
    print("Building Limine...")
    run_command("cd limine && make limine")
    
    # Cleaning up previous iso_root
    print("Cleaning up previous iso_root...")
    if os.path.exists("iso_root"):
        shutil.rmtree("iso_root")
    
    # Creating directory structure
    print("Creating directory structure...")
    os.makedirs("iso_root/boot", exist_ok=True)
    shutil.copy("kernel.elf", "iso_root/boot")
    shutil.copy("bg.png", "iso_root/boot")
    
    # Creating limine.conf
    os.makedirs("iso_root/boot/limine", exist_ok=True)
    with open("iso_root/boot/limine/limine.conf", "w") as f:
        f.write("timeout: 3\n")
        f.write("/lithium\n")
        f.write("    protocol: limine\n")
        f.write("    path: boot():/boot/kernel.elf\n")
    
    # Copying Limine binaries
    print("Copying Limine binaries...")
    os.makedirs("iso_root/EFI/BOOT", exist_ok=True)
    shutil.copy("limine/limine-bios.sys", "iso_root/boot/limine/")
    shutil.copy("limine/limine-bios-cd.bin", "iso_root/boot/limine/")
    shutil.copy("limine/limine-uefi-cd.bin", "iso_root/boot/limine/")
    shutil.copy("limine/BOOTX64.EFI", "iso_root/EFI/BOOT/")
    shutil.copy("limine/BOOTIA32.EFI", "iso_root/EFI/BOOT/")
    
    # Creating ISO
    print("Creating ISO...")
    run_command('xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin '
                '-no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus '
                '-apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin '
                '-efi-boot-part --efi-boot-image --protective-msdos-label '
                'iso_root -o lithium.iso')
    
    # Installing BIOS bootloader
    print("Installing BIOS bootloader...")
    run_command("./limine/limine bios-install lithium.iso")

if __name__ == "__main__":
    build_iso()
