/**
 * This file contains implementations for methods in the Page class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page/page.h"

using namespace std;


// Ensure PAGE_SIZE is initialized.
const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
    // TODO: implement me
    char bit;

    vector<char> b;

    int counter = 0;
    
   

    while(!in.eof()) {
        
        bit = in.get();

        if(bit == -1) {
            break;
        }

        if(counter < PAGE_SIZE) {
            //in>>bit;
            b.push_back(bit);
            counter++;
        }

        else {
            in.putback(bit);
            break;
        }
        
    }

   

    if(b.size()== 0) {
        return nullptr;
    }
   

    else {
        Page* page = new Page(b);
        
        return page;
    }

}


size_t Page::size() const {
    // TODO: implement me
    
    size_t pageSize = Page::bytes.size();
  
    return pageSize;

    
}


bool Page::is_valid_offset(size_t offset) const {  
    // TODO: implement me

    
    if(offset < bytes.size()) {
        return true;
    }
    return false;
}


char Page::get_byte_at_offset(size_t offset) {
    // TODO: implement me

    return bytes.at(offset);
}

