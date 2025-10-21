#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct PageReference {
    int page_number;
    bool dirty;
} PageReference;

void read_input(PageReference page_references []);
void next_line(FILE *filestream);


const int NUM_REFERENCES = 15000; // TODO THIS NUBMER IS DIFFERENT

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


void simulate_fifo(PageReference page_references[]) {

    FILE *output_file = fopen("fifo_output.csv", "r");

    for (int i = 0; i < NUM_REFERENCES; i++) {
        
    }


    fclose(output_file);
}

void simulate_optimal(PageReference page_references[]) {

}



int main() {

    PageReference page_references[NUM_REFERENCES];

    read_input(page_references);

    return 0;
}