/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"

using namespace std;

string PhysicalAddress::to_string() const {
    // TODO: implement me

    string frameBits = bitset<FRAME_BITS>(frame).to_string();

    string offsetBits = bitset<OFFSET_BITS>(offset).to_string();

    string physicalAddressBits = frameBits + offsetBits;


    return physicalAddressBits;
}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
    // TODO: implement me

    out << address.to_string()<< " [frame: "<<address.frame<<"; offset: "<<address.offset<<"]";

    return out;
}
