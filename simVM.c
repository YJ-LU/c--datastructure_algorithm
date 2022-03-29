#include <stdio.h>
#include <stdlib.h>


typedef struct vmTable{
	//int *pageNumArr; // page number array
    //int size;
	int data;
	float fdata;
	unsigned int addr;
	int pageFaultCount;
	int tlbMissCount;
	int disk_write;
	struct pageTable *pt;
	struct TLBtable *tt;
    struct control *ctrl;
}vmTable;


typedef struct pageTable{
	unsigned int addr1;
	int modified;
	int pt_stamptime;
	int disk_w;
}pageTable;



typedef struct TLBtable{
	unsigned int vir_addr;
	unsigned int phy_addr;
	int tt_stamptime;
}TLBtable;


typedef struct control{
	int tlb;
	int page;
}control;

 unsigned int virtual; //size of virtual memory
 int offset; // contains the bits by which address moved right
 unsigned int physic; // size of physical memory
 unsigned int tlbSize; // size of TLB
 char pageRep; // Round-robin or LRU for Page table
 char tlbRep; // Round-robin or LRU for TLB table
 int pt_size; // size of page table
 int pg_stamptime; // page table timestamp
 int tlb_stamptime; // TLB table timestamp
 int isfloat = 0;
 // . the size of the virtual memory must be larger than the size of the physical memory.
// • the size of the physical memory must be greater than zero.
// • the size of a page must be a power of two.
// • the size of the virtual memory times the size of a page must be less than or equal to 2^32.
// • the size of the TLB should be less than or equal to the size of physical memory.
// • the size of the TLB must be greater than zero.
// • the replacement algorithms are either round-robin replacement or LRU replacement. 
void *createVM(
  unsigned int sizeVM,   // size of the virtual memory in pages
  unsigned int sizePM,   // size of the physical memory in pages
  unsigned int pageSize, // size of a page in words
  unsigned int sizeTLB,  // number of translation lookaside buffer entries
  char pageReplAlg,      // page replacement alg.: 0 is Round Robin, 1 is LRU
  char tlbReplAlg        // TLB replacement alg.: 0 is Round Robin, 1 is LRU
){

	offset = 0;
	physic = 0;
	tlbSize = 0;
	pt_size = 0;
	pg_stamptime = 0;
	tlb_stamptime = 0;

	unsigned int p = pageSize;
	while( (p % 2 == 0) && (p > 1)){
    p = p/2;
    }
    if( p != 1 ){
    fprintf(stderr, "size of page not a power of 2\n");
    exit(-1);
    }

	virtual = sizeVM * pageSize; //Virtual memory = page number in VM * pagesize
    physic  = sizePM * pageSize; //Physic memory = page number in VM * pagesize

    long l = (long)(sizeVM * pageSize);
    if( l > 0x100000000){
      fprintf( stderr, "size of virtual memory greater than 2^32\n");
      exit(-1);
    }

    if( virtual <= physic ){
      fprintf( stderr, "size of virtual memory not greater than size of physic memory\n");
      exit(-1);
    } 

    if( physic <= 0 ){
      fprintf( stderr, "size of physic memory less than zero\n");
      exit(-1);
    }
  
    if(sizeTLB > sizePM)
	{
		fprintf(stderr, "size of TLB greater size of physical memory in pages\n");
		exit(-1);
	}

  if( sizeTLB <= 0){
    fprintf(stderr, "the size of the TLB less than zero\n");
    exit(-1);
   }
  
  if( (pageReplAlg != 0 )&& (pageReplAlg != 1) ){
    fprintf(stderr,"the replacement algorithms are neither round-robin replacement or LRU replacement\n");
    exit(-1);
   }

  if( (tlbReplAlg != 0) && (tlbReplAlg != 1) ){
    fprintf(stderr,"the replacement algorithms are neither round-robin replacement or LRU replacement\n");
    exit(-1);
   }
	

    pt_size = (sizeVM*pageSize)/sizePM;
	vmTable* vm_table = malloc(sizeof(vmTable)* sizeVM * pageSize);	
	pageTable* page_table = malloc(sizeof(pageTable)*pt_size);
	TLBtable* tlb_table = malloc(sizeof(TLBtable)*sizeTLB);
    control* c = malloc(sizeof(control));
	
	for (int i = 0; i < virtual; i++)
	{
		vm_table[i].data=0;
		vm_table[i].addr=i;
		vm_table[0].pageFaultCount = 0;
		vm_table[0].tlbMissCount = 0;
		vm_table[0].disk_write = 0;
		vm_table[i].fdata = 0;
	}

	physic = sizePM;
	tlbSize = sizeTLB;
	pageRep = pageReplAlg;
	tlbRep = tlbReplAlg;
	unsigned int a = pageSize;
	while(((a>>1) & 0xFFFF) > 0){
		offset++;
		a = a>>1;
	}
	
	for (int j = 0; j < pt_size; j++)
	{
		if(j<sizePM){
			page_table[j].modified = 1;
			page_table[j].addr1 = j;
			page_table[j].pt_stamptime = 0;
			page_table[j].disk_w = 0;
		}
		else{
			page_table[j].modified = 0;
			page_table[j].addr1 = 999;
			page_table[j].pt_stamptime = 0;
			page_table[j].disk_w = 0;
		}
		
	}

	for (int k = 0; k < sizeTLB; k++)
	{
		tlb_table[k].vir_addr = k;
		tlb_table[k].phy_addr = k;
		tlb_table[k].tt_stamptime = 0;
	}

	c[0].tlb = 0;
	c[0].page = 0;

	vm_table->pt = page_table;
	vm_table->tt = tlb_table;
	vm_table->ctrl = c;

	return vm_table;
}

// readInt
//
int readInt(void *handle, unsigned int address){
	
	vmTable *vm_table = (vmTable*) handle;
    pageTable* page_table = vm_table->pt;
    TLBtable* tlb_table = vm_table->tt;
    control* c = vm_table->ctrl;

	
	unsigned int pgnum = address>>offset;
	for (int i = 0; i < tlbSize; i++)
	{
		unsigned int vaddr= tlb_table[i].vir_addr;
		if(vaddr== pgnum){
		
			if(tlbRep){
				tlb_stamptime++;
				tlb_table[i].tt_stamptime = tlb_stamptime;
				int t = 0;
				int first = 0;
				while(t<(tlbSize-1)){
					if(tlb_table[t+1].tt_stamptime > tlb_table[t].tt_stamptime){
						t++;
						continue;
					}
					else if(tlb_table[t+1].tt_stamptime > tlb_table[first].tt_stamptime){
						t++;
						continue;
					}
					else if(tlb_table[t+1].tt_stamptime == tlb_table[first].tt_stamptime){
						t++;
						continue; 
					}
					else
						first = t+1;

					t++;
				}
				c[0].tlb = first;
			}
			
			vm_table->pt = page_table;
			vm_table->tt = tlb_table;
			vm_table->ctrl = c;


            return vm_table[address].data;
		}
	}
	++vm_table[0].tlbMissCount;    // TLB Miss
	int pos = c[0].tlb;
	tlb_table[pos].vir_addr = pgnum;
	
	if(page_table[pgnum].modified == 1){
		
		tlb_table[pos].phy_addr = page_table[pgnum].addr1;


		if(tlbRep){
			tlb_stamptime++;
			tlb_table[pos].tt_stamptime = tlb_stamptime;
			int t = 0;
			int first = 0;
			while(t<(tlbSize-1)){
				if(tlb_table[t+1].tt_stamptime > tlb_table[t].tt_stamptime){
					t++;
					continue;
				}
				else if(tlb_table[t+1].tt_stamptime > tlb_table[first].tt_stamptime){
					t++;
					continue;
				}
				else if(tlb_table[t+1].tt_stamptime == tlb_table[first].tt_stamptime){
					t++;
					continue; 
				}
				else
					first = t+1;

				t++;
			}
			c[0].tlb = first;
		}

		else{
			if(pos<(tlbSize-1)){
              c[0].tlb = pos+1;
			} 
			else{
              c[0].tlb = 0;
			} 
		}


		if(pageRep){
			pg_stamptime++;
			page_table[pgnum].pt_stamptime = pg_stamptime;
			int t = 0;
			while(page_table[t].modified == 0){
				t++;
			}
			int cnt = 0;
			int first = t;
			t = 0;
			while(cnt<(physic-1)){
				while(page_table[t].modified == 0){
					t++;
				}
				int g = t;
				t++;
				while(page_table[t].modified == 0){
					t++;
				}
				int h = t;
				if(page_table[h].pt_stamptime > page_table[g].pt_stamptime){
					cnt++;
					if(page_table[g].pt_stamptime < page_table[first].pt_stamptime)
						first = g;
					else if(page_table[g].pt_stamptime == page_table[first].pt_stamptime){
						if(page_table[g].addr1 < page_table[first].addr1){
							first = g;
						} 
					}
					continue;
				}
				else if(page_table[h].pt_stamptime > page_table[first].pt_stamptime){
					cnt++;
					first = g;
					continue;
				}
				else if(page_table[h].pt_stamptime == page_table[first].pt_stamptime){
					cnt++;
					if(page_table[h].addr1 < page_table[first].addr1){
						first = h;
						} 
					continue; 
				}
				else
					first = h;

				cnt++;
			}
			c[0].page = page_table[first].addr1;
		}
		
		
		vm_table->pt = page_table;
		vm_table->tt = tlb_table;
		vm_table->ctrl = c;

		return vm_table[address].data;
	}

	vm_table[0].pageFaultCount++; // Page Fault
	if(page_table[pgnum].modified == 0){
		if(page_table[pgnum].disk_w == 1){
			vm_table[0].disk_write++;
		} 
	}
	page_table[pgnum].modified = 1;
	int pos1 = c[0].page;
	
	tlb_table[pos].phy_addr = pos1;
	int i = 0;
	unsigned int v = page_table[i].addr1;
	while(v != pos1){
		i++;
		v = page_table[i].addr1;
	}
	
	page_table[i].modified = 0;
	page_table[i].addr1 = 999;
	if(pageRep) page_table[i].pt_stamptime = 0;
	page_table[pgnum].addr1 = pos1;


	if(pageRep){
		pg_stamptime++;
		page_table[pgnum].pt_stamptime = pg_stamptime;
		int t = 0;
		while(page_table[t].modified == 0){
			t++;
		}
		int cnt = 0;
		int first = t;
		t = 0;
		while(cnt<(physic-1)){
			while(page_table[t].modified == 0){
				t++;
			}
			int g = t;
			t++;
			while(page_table[t].modified == 0){
				t++;
			}
			int h = t;
			if(page_table[h].pt_stamptime > page_table[g].pt_stamptime){
				cnt++;
				if(page_table[g].pt_stamptime < page_table[first].pt_stamptime)
					first = g;
				else if(page_table[g].pt_stamptime == page_table[first].pt_stamptime){
					if(page_table[g].addr1 < page_table[first].addr1){
						first = g;
						} 
				}
				continue;
			}
			else if(page_table[h].pt_stamptime > page_table[first].pt_stamptime){
				cnt++;
				first = g;
				continue;
			}
			else if(page_table[h].pt_stamptime == page_table[first].pt_stamptime){
				cnt++;
				if(page_table[h].addr1 < page_table[first].addr1){
					first = h;
				} 
				continue; 
			}
			else{
				first = h;
			}

			cnt++;
		}
		c[0].page = page_table[first].addr1;
	}

	else{
		if(pos1<(physic-1)){
			c[0].page = pos1+1;
		} 
		else{
           c[0].page = 0;
		} 
	}
	

	if(tlbRep){
		tlb_stamptime++;
		tlb_table[pos].tt_stamptime = tlb_stamptime;
		int t = 0;
		int first = 0;
		while(t<(tlbSize-1)){
			if(tlb_table[t+1].tt_stamptime > tlb_table[t].tt_stamptime){
				t++;
				continue;
			}
			else if(tlb_table[t+1].tt_stamptime > tlb_table[first].tt_stamptime){
				t++;
				continue;
			}
			else if(tlb_table[t+1].tt_stamptime == tlb_table[first].tt_stamptime){
				t++;
				continue; 
			}
			else
				first = t+1;

			t++;
		}
		c[0].tlb = first;
	}

	else{
		if(pos<(tlbSize-1)){
			c[0].tlb = pos+1;
		} 
		else c[0].tlb = 0;
	}

	vm_table->pt = page_table;
	vm_table->tt = tlb_table;
	vm_table->ctrl = c;

	return vm_table[address].data;
}


float readFloat(void *handle, unsigned int address){
	isfloat = 1;
	vmTable *vm_table = (vmTable*) handle;
	readInt(vm_table,address);
	float m = vm_table[address].fdata;
	isfloat = 0;
	return m;
}


void writeInt(void *handle, unsigned int address, int value){

	vmTable * vm_table = (vmTable*) handle;
	unsigned int pgnum = address >> offset;
	readInt(vm_table,address);
	if(vm_table->pt[pgnum].modified == 0){
		if(vm_table->pt[pgnum].disk_w == 1){
			vm_table[0].disk_write++;
		} 
	}
	vm_table->pt[pgnum].modified = 1;
	vm_table[address].data = value;


	
}


void writeFloat(void *handle, unsigned int address, float value){
	isfloat = 1;
	vmTable *vm_table = (vmTable*) handle;
	writeInt(vm_table,address,value);
	vm_table[address].fdata = value;
	isfloat = 0;
}


void printStatistics(void *handle)
{
	vmTable *vm_table = (vmTable*) handle;
	printf("Number of page faults: %d\n", vm_table[0].pageFaultCount);
	printf("Number of TLB misses: %d\n", vm_table[0].tlbMissCount);
	printf("Number of disk writes: %d\n", vm_table[0].disk_write);

}

void cleanupVM(void *handle)
{
	vmTable *vm_table = (vmTable*) handle;

	free(vm_table->pt);
	free(vm_table->tt);
	free(vm_table->ctrl);
	free(vm_table);
	
}