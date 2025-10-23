#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct PageReference {
    int page_number;
    bool dirty;
} PageReference;

typedef struct SimulationResults {
    int page_faults;
    int write_backs;
} SimulationResults;

void read_input(PageReference page_references []);
void next_line(FILE *filestream);


const int NUM_REFERENCES = 15000;   // TODO THIS NUBMER IS DIFFERENT in the input file
const int NUM_PAGES = 500;          // number of pages in the input file

// TODO CHECK NUM REFERENCES



void read_input(PageReference page_references []) {
    /*
    Reads the input and populates the passed array with the data

    args: 
    page_references: a reference to an array to be populated with input data
    */

    next_line(stdin);  // TODO might not need this.

    for (int i = 0; i < NUM_REFERENCES; i++) {
        scanf("%d,%d", page_references[i].page_number, page_references[i].dirty);  // TODO make this more robust
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

    int page_faults = 0;
    int write_backs = 0;
    SimulationResults return_values;

    // per frame window: need time of arrival (recorded via queue?), dirty bit, and page number

    for (int i = 0; i < NUM_REFERENCES; i++) {
        
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

    int reference_bits[NUM_PAGES] = {0};
    int page_faults = 0;
    int write_backs = 0;
    SimulationResults return_values;


    // simulation here

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