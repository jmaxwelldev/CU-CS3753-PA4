/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains an lru pageit
 *      implmentation.
 */

#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

//returns integer value of process whose page to evict, updates *leastUsedPage
int lru_page_to_evict(Pentry q[MAXPROCESSES], int timestamps[MAXPROCESSES][MAXPROCPAGES], int proctmp, int pagetmp, int *leastUsedPage){
    leastResentPage = -1;
    leastResentProcess = -1;
    leastResentTick = INT_MAX;
    for (int process = 0; process < MAXPROCESSES; process++)
    {
        for (int page = 0; page < MAXPROCPAGES; page++)
        {
            if (timestamps[process][page]<leastResentTick && q[process].pages[page])
            {
                leastResentTick = timestamps[process][page];
                leastResentProcess = process;
                leastResentPage = page;
            }
        }
    }
    *leastUsedPage = leastResentPage;
    return leastResentProcess;
}

void pageit(Pentry q[MAXPROCESSES]) { 
    
    /* This file contains the stub for an LRU pager */
    /* You may need to add/remove/modify any part of this file */

    /* Static vars */
    static int initialized = 0;
    static int tick = 1; // artificial time
    static int timestamps[MAXPROCESSES][MAXPROCPAGES];

    /* Local vars */
    int proctmp;
    int pagetmp;

    /* initialize static vars on first run */
    if(!initialized){
	for(proctmp=0; proctmp < MAXPROCESSES; proctmp++){
	    for(pagetmp=0; pagetmp < MAXPROCPAGES; pagetmp++){
		timestamps[proctmp][pagetmp] = 0; 
	    }
	}
	initialized = 1;
    }

    //update times
    for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++)
    {
        pagetmp = q[proctmp].pc/PAGESIZE;
        timestamps[proctmp][pagetmp] = tick;
    }
    

    //main control flow, loops through process'
    for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++){
        //check if its dead if its dead kill
        if (!q[proctmp].alive)
        {
            for (pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++)
            {
                pageout(proctmp,pagetmp);
            }
            continue;
        }
    

        
        pagetmp = q[proctmp]/PAGESIZE;

        //check if its swapped in, if it is then success
        if (q[proctmp].pages[pagetmp])
        {
            continue;
        }

        //If here not swapped in, try swapping in:
        if (pagein(proctmp, pagetmp))
        {
            continue
        }

        //If here swap failed send LRU algorithm
        int leastUsedPage;
        int leastUsedProcess = lru_page_to_evict(q,timestamps,proctmp,pagetmp, leastUsedPage);
        printf("%d\n", leastUsedPage);

    }


    /* TODO: Implement LRU Paging */
    fprintf(stderr, "pager-lru not yet implemented. Exiting...\n");
    exit(EXIT_FAILURE);

    /* advance time for next pageit iteration */
    tick++;
    }
} 
