GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386


CC = gcc
LD = ld
ASM = as


CPP_SOURCES = $(shell find . -name "*.cpp")
CPP_OBJECTS = $(patsubst %.cpp, %.o, $(CPP_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))


%.o: %.cpp
	$(CC) $(GCCPARAMS) -c -o $@ $<

%.o: %.s
	$(AS) $(ASPARAMS) -o $@ $<

wateros.bin: scripts/linker.ld $(CPP_OBJECTS) $(S_OBJECTS)
	$(LD) $(LDPARAMS) -T $< -o $@ $(CPP_OBJECTS) $(S_OBJECTS)

wateros.iso: wateros.bin
	@mkdir iso
	@mkdir iso/boot
	@mkdir iso/boot/grub
	@cp wateros.bin iso/boot/wateros.bin
	@echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	@echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	@echo ''                                  >> iso/boot/grub/grub.cfg
	@echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	@echo '  multiboot /boot/wateros.bin'     >> iso/boot/grub/grub.cfg
	@echo '  boot'                            >> iso/boot/grub/grub.cfg
	@echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=wateros.iso iso
	@rm -rf iso

disk: 
	@echo "make hard disk"
	qemu-img create waterDisk.img 5G

run: disk wateros.iso
	@echo "qemu run"
	qemu-system-x86_64 -boot d -cdrom wateros.iso -m 512 -hda waterDisk.img

debug: disk wateros.iso
	@echo "qemu debug"
	qemu-system-x86_64 -boot d -cdrom wateros.iso -s -m 512 -hda waterDisk.img &
	sleep 1
	cgdb -x scripts/gdbinit


clean: 
	-@rm -rf iso *.o *.bin *.iso *.img
	-@rm -rf $(CPP_OBJECTS) $(S_OBJECTS)


.PHONY: wateros.bin wateros.iso build clean disk all debug