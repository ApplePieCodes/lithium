KERNEL := kernel.elf

GCC = x86_64-elf-gcc
LD = x86_64-elf-ld

ARCH=x86_64

CFLAGS += 				 \
	-std=c99             \
	-ffreestanding       \
	-fno-stack-protector \
	-fno-stack-check     \
	-fno-lto             \
	-fno-pie             \
	-fno-pic             \
	-m64                 \
	-march=x86-64        \
	-mabi=sysv           \
	-mno-80387           \
	-mno-mmx             \
	-mno-sse             \
	-mno-sse2            \
	-mno-red-zone        \
	-mcmodel=kernel      \
	-MMD                 \
	-I.			 		 \
	-I src/include/ 	 \

LDFLAGS +=         			\
	-nostdlib               \
	-static                 \
	-m elf_x86_64           \
	-z max-page-size=0x1000 \
	-T linker.ld            \

NASMFLAGS = \
	-f elf64

ifeq ($(ARCH), x86_64)
	CFLAGS += -DARCH_x86_64=1
endif

CFILES = $(shell find src -type f -name '*.c')
ASMFILES = $(shell find src -type f -name '*.asm')
OBJ = $(CFILES:.c=.o) $(ASMFILES:.asm=.o)

all: $(KERNEL)

limine.h:
	curl -f https://raw.githubusercontent.com/limine-bootloader/limine/trunk/limine.h -o $@ || (echo "Failed to download limine.h"; exit 1)
	

$(KERNEL): $(OBJ) linker.ld
	$(LD) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c limine.h
	$(GCC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	nasm $(NASMFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(KERNEL) $(shell find src -type f -name '*.d')