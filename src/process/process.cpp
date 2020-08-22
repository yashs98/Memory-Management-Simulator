/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"

using namespace std;


Process* Process::read_from_input(std::istream& in) {
    // TODO: implement me

    vector<Page*> p;

    char imageChar;
    int numBytes = 0;
    int counter = 0;
    vector<char> bytes;

    vector<Page*> tempPages;


    while(!in.eof()) {

        Page* page = Page::read_from_input(in);

        if(page != nullptr) {
           
            tempPages.push_back(page);
            numBytes += page->size();

        }

        else {
            break;
        }
        
    }

    PageTable pt(tempPages.size());

    Process* newProcess = new Process(numBytes, tempPages);

    

    

    return newProcess;
}


size_t Process::size() const {
    // TODO: implement me
    
    return num_bytes;
}


bool Process::is_valid_page(size_t index) const {
    // TODO: implement me

    for(int i = 0; i<pages.size(); i++) {
        if(i == index) {
            return true;
        }
    }

    return false;
}


size_t Process::get_rss() const {
    // TODO: implement me

    int counter = 0;

    for(int i = 0; i<pages.size(); i++) {
        if(page_table.rows.at(i).present) {
            counter++;
        }
    }

    return counter++;
}


double Process::get_fault_percent() const {
    // TODO: implement me
    double rate = 0.0;
    
    if(memory_accesses > 0) {
        rate = (double) ((page_faults/(double) memory_accesses) * 100.0);
    }
    
    return rate;
}
