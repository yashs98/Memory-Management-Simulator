/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */


#include "simulation/simulation.h"

using namespace std;


void Simulation::run(FlagOptions &flagOptions) {
    // TODO: implement me


    for(int k = 0; k<NUM_FRAMES; k++) {
        Frame f;
        free_frames.push_back(f);
    }

  
    
    ifstream input(flagOptions.filename);

    int amountProcesses = 0;
    virtual_time = 0;
    
    string processFiles;

    counter = 0;
    counter_frames = 0;

    
    maxFrames = flagOptions.max_frames;

    this->flagOptions = flagOptions;
    
    size_t numPages = 0;
    string bytes;
    input>>amountProcesses;
    char byte;

    free_frames.reserve(maxFrames);

    for(int i = 0; i<amountProcesses; i++) {
        input>>pid;
        input>>processFiles;

        
        ifstream getProcess(processFiles);

        if(getProcess.good()) {
            Process* process = Process::read_from_input(getProcess);
            
            processes.emplace(pid, process);
            validSimulation = true;
        }

        else {
            
            validSimulation = false;
             
        }
        
    }

    int counter = 0;
    if(validSimulation) {
        while(!input.eof()) {
        
            input>>pid;
            input>>bytes;

            if(input.eof()) {
                break;
            }

            else {

                virtual_time++;

                VirtualAddress virtualAddress = VirtualAddress::from_string(pid, bytes);

                addresses.push_back(virtualAddress);

                
                counter++;
                

                processes.at(pid)->memory_accesses++;
                
                processes_with_rss.emplace(pid, 0);
                
                if(processes_with_va.find(pid) != processes_with_va.end()) {
                    processes_with_va.at(pid).push_back(virtualAddress);
                }

                else {
                    vector<VirtualAddress> temp_va;
                    temp_va.push_back(virtualAddress);
                    processes_with_va.emplace(pid, temp_va);
                }

                

                byte = perform_memory_access(virtualAddress);

                
            }
            

        }



    }

    for(auto y: processes) {
        total_pages += y.second->pages.size();
    }
    print_summary();
    
}


char Simulation::perform_memory_access(const VirtualAddress& address) {
    // TODO: implement me
    char byte;
    
    if(flagOptions.verbose) {
        cout<<address<<endl;
    }

    if(!processes.at(address.process_id)->is_valid_page(address.page)) {
        cout<<"SEGFAULT - INVALID PAGE"<<endl;
        exit(EXIT_FAILURE);
    }
    
    processes.at(address.process_id)->page_table.rows.at(address.page).last_accessed_at = virtual_time;
    if(!processes.at(address.process_id)->page_table.rows.at(address.page).present) {
        
        if(flagOptions.verbose) {
            cout<<"\t-> PAGE FAULT"<<endl;
        }
        
        processes.at(address.process_id)->page_faults++;
        processes.at(address.process_id)->page_table.rows.at(address.page).loaded_at = virtual_time;
       
        if((processes.at(address.process_id)->page_table.get_present_page_count() < flagOptions.max_frames) && (counter_frames < NUM_FRAMES)) { 

            free_frames.at(counter_frames).set_page(processes.at(address.process_id), address.page);
            processes.at(address.process_id)->page_table.rows.at(address.page).frame = counter_frames;
            PhysicalAddress pa(processes.at(address.process_id)->page_table.rows.at(address.page).frame, address.offset);
            
            if(free_frames.at(counter_frames).contents->is_valid_offset(pa.offset)) {
                byte = free_frames.at(counter_frames).contents->get_byte_at_offset(pa.offset);
               
            }

            else {
                 if(flagOptions.verbose) {
                    PhysicalAddress pa2(processes.at(address.process_id)->page_table.rows.at(address.page).frame, address.offset);
                    cout<<"\t-> physical address "<< pa2<<endl; 
                }
                cout<<"SEGFAULT - INVALID OFFSET"<<endl;
                exit(EXIT_FAILURE);
            }
            
            processes.at(address.process_id)->page_table.rows.at(address.page).present = true;

            counter_frames++;
        }

        else {            
            
            handle_page_fault(processes.at(address.process_id), address.page);

            int indexFrame = processes.at(address.process_id)->page_table.rows.at(address.page).frame;

            if(free_frames.at(indexFrame).contents->is_valid_offset(address.offset)) {
                byte = free_frames.at(indexFrame).contents->get_byte_at_offset(address.offset);

            }

            else {
                 if(flagOptions.verbose) {
                    PhysicalAddress pa2(processes.at(address.process_id)->page_table.rows.at(address.page).frame, address.offset);
                    cout<<"\t-> physical address "<< pa2<<endl; 
                }
                cout<<"SEGFAULT - INVALID OFFSET"<<endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    else {
        
        if(flagOptions.verbose) {
            cout<<"\t-> IN MEMORY"<<endl;
        }

        PhysicalAddress pa(processes.at(address.process_id)->page_table.rows.at(address.page).frame, address.offset);

        if(free_frames.at(pa.frame).contents->is_valid_offset(pa.offset)) {

            byte = free_frames.at(pa.frame).contents->get_byte_at_offset(pa.offset);

        }

    }


    if(flagOptions.verbose) {
        PhysicalAddress pa2(processes.at(address.process_id)->page_table.rows.at(address.page).frame, address.offset);
        cout<<"\t-> physical address "<< pa2<<endl; 
    }


    if(flagOptions.verbose) {

        cout<<"\t-> RSS: "<< processes.at(address.process_id)->get_rss()<<endl;
        cout<<endl;
    }
    

    return byte;
}


void Simulation::handle_page_fault(Process* process, size_t page) {
    // TODO: implement me


    if(flagOptions.strategy == ReplacementStrategy::FIFO) {

        int index =  process->page_table.get_oldest_page();
        process->page_table.rows.at(index).present = false;
        process->page_table.rows.at(page).frame = process->page_table.rows.at(index).frame;
        free_frames.at(process->page_table.rows.at(page).frame).set_page(process, page);
        process->page_table.rows.at(page).present = true;

    }

    else {

        int index2 = process->page_table.get_least_recently_used_page();
        process->page_table.rows.at(index2).present = false;
        process->page_table.rows.at(page).frame = process->page_table.rows.at(index2).frame;
        free_frames.at(process->page_table.rows.at(page).frame).set_page(process, page);
        process->page_table.rows.at(page).present = true;

    }

    
    
}

void Simulation::print_summary() {

    for(auto process: processes) {
       page_faults += process.second->page_faults;
    }

    if(validSimulation) {
        if (!flagOptions.csv) {
            

            
            boost::format process_fmt(
                "Process %3d:  "
                "ACCESSES: %-6lu "
                "FAULTS: %-6lu "
                "FAULT RATE: %-8.2f "
                "RSS: %-6lu\n");

            for (auto entry : processes) {
                cout << process_fmt
                    % entry.first
                    % entry.second->memory_accesses
                    % entry.second->page_faults
                    % entry.second->get_fault_percent()
                    % entry.second->get_rss();
            }

            // Print statistics.
            boost::format summary_fmt(
                "\n%-25s %12lu\n"
                "%-25s %12lu\n"
                "%-25s %12lu\n");

            cout << summary_fmt
                % "Total memory accesses:"
                % addresses.size()
                % "Total page faults:"
                % page_faults
                % "Free frames remaining:"
                % (free_frames.size() - counter_frames);
        }

        if (flagOptions.csv) {
            
            boost::format process_fmt(
                "%d,"
                "%lu,"
                "%lu,"
                "%.2f,"
                "%lu\n");

            for (auto entry : processes) {
                cout << process_fmt
                    % entry.first
                    % entry.second->memory_accesses
                    % entry.second->page_faults
                    % entry.second->get_fault_percent()
                    % entry.second->get_rss();
            }

            // Print statistics.
            boost::format summary_fmt(
                "%lu,,,,\n"
                "%lu,,,,\n"
                "%lu,,,,\n");

            cout << summary_fmt
                % addresses.size()
                % page_faults
                % (free_frames.size() - counter_frames);
        }
    }

    else {
        print_usage();
    }
}
