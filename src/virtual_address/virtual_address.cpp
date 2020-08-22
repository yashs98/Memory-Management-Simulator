/**
 * This file contains implementations for methods in the VirtualAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "virtual_address/virtual_address.h"


using namespace std;


VirtualAddress VirtualAddress::from_string(int process_id, string address) {
  // TODO: implement me

  string pageBits;
  string offsetBits;
  
  
  for(int i = 0; i<PAGE_BITS; i++) {
    pageBits += address[i];

  }

  for(int j = PAGE_BITS; j<PAGE_BITS + OFFSET_BITS; j++) {
    offsetBits += address[j];
  }

  stringstream ss(pageBits);
  stringstream ss2(offsetBits);



  bitset<PAGE_BITS> pageBitsConverted;
  bitset<OFFSET_BITS> offsetBitsConverted;

  ss >> pageBitsConverted;
  ss2 >> offsetBitsConverted;

  int pageBitsToInt = pageBitsConverted.to_ulong();

  int offsetBitsToInt = offsetBitsConverted.to_ulong();


  return VirtualAddress(process_id, pageBitsToInt, offsetBitsToInt);
}


string VirtualAddress::to_string() const {
  // TODO: implement me

  string pageNumberBits = bitset<PAGE_BITS>(page).to_string();

  string offsetBits = bitset<OFFSET_BITS>(offset).to_string();

  string virtualAddressBits = pageNumberBits + offsetBits;

  return virtualAddressBits;
}


ostream& operator <<(ostream& out, const VirtualAddress& address) {
  // TODO: implement me

  out<<"PID "<<address.process_id<<" @ "<<address.to_string()<<" [page: "<<address.page<<"; offset: "<<address.offset<<"]";

  return out;
}
