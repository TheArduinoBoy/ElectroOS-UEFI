#include "kernel.h"

extern "C" int _start(BootInfo* bootinfo){
    UtilClasses utils = initlize(bootinfo);
    Print print = utils.print;
    PageFrameAllocator pageFrameAloc = utils.pageFrameAlloc;

    print.print("RAM: ");
    print.print(intToString(((pageFrameAloc.GetFreeRAM() / 1024) / 1024 + (pageFrameAloc.GetUsedRAM() / 1024) / 1024 + (pageFrameAloc.GetReservedRAM() / 1024) / 1024)));
    print.println("MB");
    print.print("Free RAM: ");
    print.print(intToString((pageFrameAloc.GetFreeRAM() / 1024) / 1024));
    print.println("MB");
    print.print("Reserved RAM: ");
    print.print(intToString((pageFrameAloc.GetReservedRAM() / 1024) / 1024));
    print.println("MB");

    PageMapIndex pageIndexer(0x1000 * 52 + 0x50000 * 7);
    print.print(uintToString(pageIndexer.getP()));
    print.print(" - ");
    print.print(uintToString(pageIndexer.getPT()));
    print.print(" - ");
    print.print(uintToString(pageIndexer.getPD()));
    print.print(" - ");
    print.println(uintToString(pageIndexer.getPDP()));

    while(1);
    return 0;
}