/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"

using namespace std;


size_t PageTable::get_present_page_count() const {
    // TODO: implement me

    size_t numPresent = 0;

    for(auto x: rows) {
        if(x.present) {
            numPresent++;
        }
    }

    

    return numPresent;
}


size_t PageTable::get_oldest_page() const {
    // TODO: implement me

    size_t loaded = -1;

    size_t index = -1;

    
    for(int i = 0; i<rows.size(); i++) {
       
        if(rows.at(i).loaded_at < loaded && rows.at(i).present) {
           
            loaded = rows.at(i).loaded_at;
            index = i;
        }
    }


    return index;
}


size_t PageTable::get_least_recently_used_page() const {
    // TODO: implement me

    size_t used = 9999;
    size_t index = -1;

    for(int i = 0; i<rows.size(); i++) {
        if(rows.at(i).last_accessed_at < used && rows.at(i).present) {
            used = rows.at(i).last_accessed_at;
            index = i;
        }
    }


    return index;
}
