/**
 * This file contains the definition of the Simulation class.
 *
 * You're free to modify this class however you see fit. Add new methods to help
 * keep your code modular.
 */

#pragma once
#include "process/process.h"
#include "virtual_address/virtual_address.h"
#include "physical_address/physical_address.h"
#include <map>
#include <vector>
#include <list>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cassert>
#include <boost/format.hpp>
#include "flag_parser/flag_parser.h"
#include <string>
#include "frame/frame.h"
using namespace std;


/**
    * Class responsible for running the memory simulation.
*/

class Simulation {
    // PUBLIC CONSTANTS
    public:

    /**
        * The maximum number of frames in the simulated system (512).
    */
    static const size_t NUM_FRAMES = 1 << 9;

    // PUBLIC API METHODS
    public:

    /**
        * Runs the simulation.
    */
    void run(FlagOptions &flagOptions);

    // PRIVATE METHODS
    private:

    /**
        * Performs a memory access for the given virtual address, translating it to
        * a physical address and loading the page into memory if needed. Returns the
        * byte at the given address.
    */
    char perform_memory_access(const VirtualAddress& address);

    /**
        * Handles a page fault, attempting to load the given page for the given
        * process into memory.
    */
    void handle_page_fault(Process* process, size_t page);

    /** 2pm-4pm Tuesday O
        * Print the summary statistics in the required format.
    */
    void print_summary();

    // INSTANCE VARIABLES
    private:

    map<int, Process*> processes;
    vector<VirtualAddress> addresses;
    vector<PhysicalAddress> pa;
    
   
    vector<Frame> free_frames;
    
    int maxFrames;
    int page_faults;

    FlagOptions flagOptions;

    bool validSimulation;

    map<int, vector<VirtualAddress>> processes_with_va;

    map<int, vector<PhysicalAddress>> processes_with_pa;

    map<int, Frame> full_frames;

    int total_pages;

    int num_frames;

    map<int, vector<Frame*>> processes_with_frames;

   
    int pid;

    int virtual_time;
    int counter_frames;

    int amountFreeFrames;

    vector<bool> isInMemory;

    map<int, int> processes_with_rss;

    int counter;

    map<int, vector<int>> fault_records;



   

};