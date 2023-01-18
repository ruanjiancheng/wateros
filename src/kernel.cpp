#include "types.h"
#include "gdt.h"
#include "printk.h"



typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}



extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
    console_clear();

    printk("hello waterkernel");

    GlobalDescriptorTable gdt;

    while(1);
}
