#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define NUM_PAGES 500         // This is the number of page IDs we can encounter
#define CLK_MEMORY_FRAMES 50
const int NUM_REFERENCES = 15050;               // TODO THIS NUBMER IS DIFFERENT in the input file


typedef struct PageReference {
    int page_number;
    int dirty;
} PageReference;

typedef struct MemoryFrame {
    int page_number;
    int time_of_arrival;
    bool dirty;
} MemoryFrame;

typedef struct SimulationResults {
    int page_faults;
    int write_backs;
} SimulationResults;

void read_input(PageReference page_references[]);
void next_line(FILE *filestream);
SimulationResults simulate_fifo(PageReference page_references[], int frame_count);
SimulationResults simulate_optimal(PageReference page_references[], int frame_count);
SimulationResults simulate_clock(PageReference page_references[], int num_reference_bits, int interrupt_period);


// TODO CHECK NUM REFERENCES



void read_input(PageReference page_references []) {
    /*
    Reads the input and populates the passed array with the data

    args: 
    page_references: a reference to an array to be populated with input data
    */

    next_line(stdin);  // TODO might not need this.

    for (int i = 0; i < NUM_REFERENCES; i++) {
        scanf("%d,%d", &page_references[i].page_number, &page_references[i].dirty);  // TODO make this more robust
    }
}

void next_line(FILE *filestream) {
    /*
    skips the filestream to the beginning of the next line.

    args:
    filestream: pointer to the file stream being skipped
    */

    int temp = 0;
    while (temp != '\n') {
        temp = fgetc(filestream);
    }
}

SimulationResults simulate_fifo(PageReference page_references[], int frame_count) {
    /*
    Simulates a FIFO page replacement scheme given a reference string and a specified number of memory frames
    
    args:
    page_references: the reference string
    frame_count: the number of memory frames in the simulation

    returns:
    a SimulationResults structure which is a duple containing:
        the number of page faults occuring in the simulation
        the number of write backs occuring in the simulation    
    */


    int page_faults = 0;
    int write_backs = 0;
    SimulationResults return_values;

    MemoryFrame memory_frames[frame_count];

    // initialize memory frames
    for (int i = 0; i < frame_count; i++) {
        memory_frames[i].page_number = -1;
        memory_frames[i].time_of_arrival = INT_MAX;
        memory_frames[i].dirty = 0;
    }


    // simulate references
    for (int time_step = 0; time_step < NUM_REFERENCES; time_step++) {

        int called_page = page_references[time_step].page_number;
        bool dirty_reference = page_references[time_step].dirty;

        int oldest_page_index = -1;                 // this is the index of the memory frame with the oldest page
        int oldest_page_arrival_time = INT_MAX;
        bool need_replacement = true;

        // iterate over memory frames to check if page is in memory
        for (int i = 0; i < frame_count && need_replacement; i++) {

            // if empty memory frame found
            if (memory_frames[i].page_number == -1) {

                need_replacement = false;
                page_faults++;

                // populate frame with page
                memory_frames[i].page_number = called_page;
                memory_frames[i].dirty = dirty_reference;
                memory_frames[i].time_of_arrival = time_step;

                // set oldest page if there is no known one
                if (oldest_page_index == -1) {
                    oldest_page_index = i;
                    oldest_page_arrival_time = time_step;
                }
            }

            // if the page is in memory
            else if (memory_frames[i].page_number == called_page) {

                need_replacement = false;
                memory_frames[i].dirty |= dirty_reference;  // set dirty bit to true if necessary
            }

            // not the page we're looking for but oldest found page, update tracking variables
            else if (oldest_page_arrival_time > memory_frames[i].time_of_arrival) {
                oldest_page_index = i;
                oldest_page_arrival_time = memory_frames[i].time_of_arrival;  
            }
        }

        // perform page replacement if necessary
        if (need_replacement) {

            page_faults++;
            if (memory_frames[oldest_page_index].dirty) write_backs++;

            memory_frames[oldest_page_index].page_number = called_page;
            memory_frames[oldest_page_index].dirty = dirty_reference;
            memory_frames[oldest_page_index].time_of_arrival = time_step;
        }
    }


    // return results
    return_values.page_faults = page_faults;
    return_values.write_backs = write_backs;

    return return_values;
}


SimulationResults simulate_optimal(PageReference page_references[], int frame_count) {

    int page_faults = 0;
    int write_backs = 0;
    SimulationResults return_values;


    // simulations here

    // return results
    return_values.page_faults = page_faults;
    return_values.write_backs = write_backs;

    return return_values;

}

SimulationResults simulate_clock(PageReference page_references[], int num_reference_bits, int interrupt_period) {
    /*
    Simulates a clock page replacement scheme with 50 memory frames given a reference string and 
    a specified number of reference bits and interrupt period
    
    args:
    page_references: the reference string
    frame_count: the number of memory frames in the simulation

    returns:
    a SimulationResults structure which is a duple containing:
        the number of page faults occuring in the simulation
        the number of write backs occuring in the simulation    
    */

    int reference_bits[CLK_MEMORY_FRAMES] = {0};
    int page_faults = 0;
    int write_backs = 0;
    SimulationResults return_values;

    MemoryFrame memory_frames[CLK_MEMORY_FRAMES];

    // initialize memory frames
    for (int i = 0; i < CLK_MEMORY_FRAMES; i++) {
        memory_frames[i].page_number = -1;
        memory_frames[i].time_of_arrival = INT_MAX;
        memory_frames[i].dirty = 0;
    }


    // simulate references
    for (int time_step = 0; time_step < NUM_REFERENCES; time_step++) {

        int called_page = page_references[time_step].page_number;
        bool dirty_reference = page_references[time_step].dirty;

        int oldest_page_index = -1;                 // this is the index of the memory frame with the oldest page
        int oldest_page_arrival_time = INT_MAX;
        int oldest_page_refence_bits = 0;
        bool need_replacement = true;

        // reset refence bits on interrupt period
        if (time_step % interrupt_period == 0) {
            for (int i = 0; i < CLK_MEMORY_FRAMES; i++) {
                reference_bits[i] >>= 1;
            }
        }


        // iterate over memory frames to check if page is in memory
        for (int i = 0; i < CLK_MEMORY_FRAMES && need_replacement; i++) {

            // if empty memory frame found
            if (memory_frames[i].page_number == -1) {

                need_replacement = false;
                page_faults++;

                // populate frame with page
                memory_frames[i].page_number = called_page;
                memory_frames[i].dirty = dirty_reference;
                memory_frames[i].time_of_arrival = time_step;

                // sets the (num_reference_bits)-th bit of the called page to 1
                reference_bits[i] = (1 << (num_reference_bits - 1));  

                // set oldest page if there is no known one
                if (oldest_page_index == -1) {
                    oldest_page_index = i;
                    oldest_page_arrival_time = time_step;
                }
            }

            // if the page is in memory
            else if (memory_frames[i].page_number == called_page) {

                need_replacement = false;
                memory_frames[i].dirty |= dirty_reference;  // set dirty bit to true if necessary
        
                // sets the (num_reference_bits)-th bit of the called page to 1
                reference_bits[i] |= (1 << (num_reference_bits - 1));  
            }

            // not the page we're looking for but oldest found page, update tracking variables
            else if (oldest_page_refence_bits > reference_bits[i] || ( oldest_page_refence_bits == reference_bits[i] && oldest_page_arrival_time > memory_frames[i].time_of_arrival) ) {
                oldest_page_refence_bits = reference_bits[i];
                oldest_page_index = i;
                oldest_page_arrival_time = memory_frames[i].time_of_arrival;  
            }
        }

        // perform page replacement if necessary
        if (need_replacement) {

            page_faults++;
            if (memory_frames[oldest_page_index].dirty) write_backs++;

            memory_frames[oldest_page_index].page_number = called_page;
            memory_frames[oldest_page_index].dirty = dirty_reference;
            memory_frames[oldest_page_index].time_of_arrival = time_step;

            reference_bits[oldest_page_index] = (1 << (num_reference_bits - 1));
        }
    }


    // return results
    return_values.page_faults = page_faults;
    return_values.write_backs = write_backs;

    return return_values;
}


int main(int argc, char *argv[]) {

    PageReference page_references[NUM_REFERENCES];
    SimulationResults sim_results;

    read_input(page_references);




    // FIFO simulation
    if (strcmp(argv[1], "FIFO") == 0) {

        // print output header
        printf("FIFO\n");
        printf("+-----------+-----------------+-----------------+\n");
        printf("+  Frames   +   Page Faults   +   Write-Backs   +\n");
        printf("+-----------+-----------------+-----------------+\n");

        for (int frame_count = 1; frame_count <= 100; frame_count++) {
            sim_results = simulate_fifo(page_references, frame_count);
            printf("+%10d +%16d +%16d +\n", frame_count, sim_results.page_faults, sim_results.write_backs);
            printf("+-----------+-----------------+-----------------+\n");
        }
    }
    
    // Optimal simulation
    if (strcmp(argv[1], "OPT") == 0) {

        // print output header
        printf("OPT\n");
        printf("+-----------+-----------------+-----------------+\n");
        printf("+  Frames   +   Page Faults   +   Write-Backs   +\n");
        printf("+-----------+-----------------+-----------------+\n");
        
        for (int frame_count = 1; frame_count <= 100; frame_count++) {
            sim_results = simulate_optimal(page_references, frame_count);
            printf("+%10d +%16d +%16d +\n", frame_count, sim_results.page_faults, sim_results.write_backs);
            printf("+-----------+-----------------+-----------------+\n");
        }
    }

    // Clock simulation
    if (strcmp(argv[1], "CLK") == 0) {

        // print output header
        printf("CLK, m = 10\n");
        printf("+-----+-----------------+-----------------+\n");
        printf("+  n  +   Page Faults   +   Write-Backs   +\n");
        printf("+-----+-----------------+-----------------+\n");
        
        // vary reference bits, fixing interrupt period = 10
        for (int n_reference_bits = 1; n_reference_bits <= 32; n_reference_bits++) {
            sim_results = simulate_clock(page_references, n_reference_bits, 10);
            printf("+%4d +%16d +%16d +", n_reference_bits, sim_results.page_faults, sim_results.write_backs);
            printf("+-----+-----------------+-----------------+\n");
        }


        // print output header
        printf("\n\nCLK, m = 10\n");
        printf("+-----+-----------------+-----------------+\n");
        printf("+  m  +   Page Faults   +   Write-Backs   +\n");
        printf("+-----+-----------------+-----------------+\n");

        // vary interrupt period, fixing reference bits = 8
        for (int m_interrupt_period = 1; m_interrupt_period <= 100; m_interrupt_period++) {
            sim_results = simulate_clock(page_references, 8, m_interrupt_period);
            printf("+%4d +%16d +%16d +\n", m_interrupt_period, sim_results.page_faults, sim_results.write_backs);
            printf("+-----+-----------------+-----------------+\n");
        }
    }

    return 0;
}