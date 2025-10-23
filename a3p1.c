#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct PageReference {
    int page_number;
    bool dirty;
} PageReference;



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


void simulate_fifo(PageReference page_references[], int frame_count) {

    int page_faults = 0;
    int write_backs = 0;

    // per frame window: need time of arrival (recorded via queue?), dirty bit, and page number

    for (int i = 0; i < NUM_REFERENCES; i++) {
        
    }

}


void simulate_optimal(PageReference page_references[], int frame_count) {
    
}

void simulate_clock(PageReference page_references[], int reference_bits, int interrupt_period) {

}


int main(int argc, char *argv[]) {

    PageReference page_references[NUM_REFERENCES];

    read_input(page_references);

    if (strcmp(argv[1], "FIFO") == 0) {
        for (int frame_count = 1; frame_count <= 100; frame_count++) {
            simulate_fifo(page_references, frame_count);
        }
    }
    
    if (strcmp(argv[1], "OPT") == 0) {
        for (int frame_count = 1; frame_count <= 100; frame_count++) {
            simulate_optimal(page_references, frame_count);
        }
    }

    if (strcmp(argv[1], "CLK") == 0) {
        // vary reference bits, fixing interrupt period = 10
        for (int reference_bits = 1; reference_bits <= 32; reference_bits++) {
            simulate_clock(page_references, reference_bits, 10);
        }

        // vary interrupt period, fixing reference bits = 8
        for (int interrupt_period = 1; interrupt_period <= 100; interrupt_period++) {
            simulate_clock(page_references, 8, interrupt_period);
        }
    }


    return 0;
}