#include "PageTableManager.h"

PageTableManager::PageTableManager(PageTable* PML4Address, UtilClasses classes) {
    this->PML4Address = PML4Address;
    this->utilclass = &classes;
}

void PageTableManager::mapMemory(void* vmem, void* pmem) {
    UtilClasses utils = *utilclass;
    PageFrameAllocator pageFrameAloc = utils.pageFrameAlloc;

    PageMapIndex indexer((uint64_t) vmem);
    PageDirEntry PDE = PML4Address->entries[indexer.getPDP()];
    PageTable* PDP;
    if(!PDE.Present) { 
        PDP = (PageTable*) pageFrameAloc.RequestPage();
        memset(PDP, 0, 0x1000);
        PDE.Address = (uint64_t) PDP >> 12;
        PDE.Present = true;
        PDE.RW = true;
        PML4Address->entries[indexer.getPDP()] = PDE;
    } else PDP = (PageTable*) ((uint64_t) PDE.Address << 12);

    PDE = PDP->entries[indexer.getPD()];
    PageTable* PD;
    if(!PDE.Present) { 
        PD = (PageTable*) pageFrameAloc.RequestPage();
        memset(PD, 0, 0x1000);
        PDE.Address = (uint64_t) PD >> 12;
        PDE.Present = true;
        PDE.RW = true;
        PML4Address->entries[indexer.getPD()] = PDE;
    } else PDP = (PageTable*) ((uint64_t) PDE.Address << 12);
}