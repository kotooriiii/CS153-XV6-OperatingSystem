#include "param.h"
#include "types.h"
#include "defs.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

struct {
    struct spinlock lock;
    struct shm_page {
        uint id;
        char *frame;
        int refcnt;
    } shm_pages[64];
} shm_table;

void shminit() {
    int i;
    initlock(&(shm_table.lock), "SHM lock");
    acquire(&(shm_table.lock));
    for (i = 0; i < 64; i++) {
        shm_table.shm_pages[i].id = 0;
        shm_table.shm_pages[i].frame = 0;
        shm_table.shm_pages[i].refcnt = 0;
    }
    release(&(shm_table.lock));
}

int shm_open(int id, char **pointer) {

    int i;
    acquire(&(shm_table.lock)); //acquire lock
    //Case 1:
    //Iterate 64 pages and check whether segment id  exists
    for (i = 0; i < 64; i++) {
        //Found, it exists! ID MATCH
        if (shm_table.shm_pages[i].id == id) {
            //Increase ref. count
            mappages(myproc()->pgdir, (char *) PGROUNDUP(myproc()->sz), PGSIZE, V2P(shm_table.shm_pages[i].frame),
                     PTE_W | PTE_U);
            shm_table.shm_pages[i].refcnt++;
            *pointer = (char *) PGROUNDUP(myproc()->sz); // return ptr
            myproc()->sz += PGSIZE; //Update process sz too add PG size due to virtual address space being increased
            release(&(shm_table.lock));
            return 0; //Break out of loop
        }
    }
    //Case 2: Shared Memory does not exist
    for (i = 0; i < 64; i++) {
        if (shm_table.shm_pages[i].id == 0) {
            shm_table.shm_pages[i].id = id;
            shm_table.shm_pages[i].frame = kalloc();
            shm_table.shm_pages[i].refcnt = 1;
            memset(shm_table.shm_pages[i].frame, 0, PGSIZE);
            mappages(myproc()->pgdir, (char *) PGROUNDUP(myproc()->sz), PGSIZE, V2P(shm_table.shm_pages[i].frame),
                     PTE_W | PTE_U);
            *pointer = (char *) PGROUNDUP(myproc()->sz); // return the ptr
            myproc()->sz += PGSIZE; //Update process sz too add PG size due to virtual address space being increased
            release(&(shm_table.lock));
            return 0; //This does nothing
        }
    }
    release(&(shm_table.lock));
    return 0;
}


int shm_close(int id) {

    int i;
    initlock(&(shm_table.lock), "SHM lock"); //reinitialize lock
    acquire(&(shm_table.lock));
    for (i = 0; i < 64; i++) {
        if (shm_table.shm_pages[i].id == id) { //We found page id that matches the one we closing
            shm_table.shm_pages[i].refcnt--; //Decrease ref count
            if (shm_table.shm_pages[i].refcnt == 0) { //If ref count is 0, clear table
                shm_table.shm_pages[i].id = 0;
                shm_table.shm_pages[i].frame = 0;
                shm_table.shm_pages[i].refcnt = 0;
            }
        }
    }


    release(&(shm_table.lock));
    return 0; //added to remove compiler warning -- you should decide what to return
}
