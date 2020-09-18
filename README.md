# Memory-Management-Simulator

For this project, I implemented a simulation of an operating system’s memory manager. The simulation will read files representing the process images of various processes, then replay a set of virtual address references to those processes using one of two different replacement strategies. The output will be various statistics, including the number of memory accesses, page faults, and free frames remaining in the system.

/inputs: This contains example inputs for the simulation like the processes, and the simulation input.

src/flag_parser/flag_parser.h: This contains the FlagOptions struct that contains information about the arguments the user has passed.

src/flag_parser/flag_parser.cpp: This sets the methods to set the information for the FlagOptions struct such as void print_usage() and bool parse_flags(int argc, char** argv, FlagOptions& flags). They provide information like whether verbose was requested or whether csv flag was requested. The only change made was editing print_usage() where it prints out what -c or what --csv does.

src/flag_parser/flag_parser_tests.cpp: This contains the unit tests to test the FlagOptions struct in flag_parser.h. There was no changes made. No changes were made.

src/frame/frame.h: This file contains the Frame class. No changes were made.

src/frame/frame.cpp: This file has the functions for the Frame class implemented.

src/frame/frame_tests.cpp: This file contains the unit tests to test the method for the Frame class. No changes were made.

src/page/page.h: This file contains the Page class. No changes were made to this file.

src/page/page.cpp: This file has the methods for the Page class implemented.

src/page/page_tests.cpp: This file has the unit tests to check whether the methods for the Page class work or not. No changes were made for this class.

src/page_table/page_table.h: This file has the PageTable class with struct Rows.

src/page_table/page_table.cpp: This file has the methods for the PageTable class implemented.

src/page_table/page_table_tests.cpp: This file contains the unit tests to test the methods for PageTable. No changes were made.

src/physical_address/physical_address.h: This file contains the class PhysicalAddress with an operator overload function defined for "<<" No changes were made for this file.

src/physical_address/physical_address.cpp: This file has the methods for PhysicalAddress implemented, and it implementes the operator overload function for "<<"

src/physical_address/physical_address_tests.cpp: This file contains unit tests to test the methods for PhysicalAddress and for the operator overload. No changes were made to this file.

src/process/process.h: This file contains the Process class. No changes were made to this file.

src/process/process.cpp: This file has the methods for the Process class implemented.

src/process/process_tests.cpp: This file contains the unit tests to test the methods for the Process class. No changes were made.

src/virtual_address/virtual_address.h: This file contains the VirtualAddress class with an operator overload method for "<<" No changes were made to this file.

src/virtual_address/virtual_address.cpp: This file has the methods for VirtualAddress implemented and it has the operator overload method for "<<" implemented as well.

src/virtual_address/virtual_address_tests.cpp: This file contains the unit tests for test VirtualAddress' methods. It also tests the operator overaload method as well. No changes were made to this file.

src/simulation/simulation.h: This file contains the Simulation class. The changes made was adding variables below the "private:" line for its methods. I also changed run to get a FlagOptions variable as its input. It used to have no parameters.

src/simulation/simulation.cpp: This file has the Simulation's methods implemented to run the Simulation of memory management as requested for the project.

/verify/outputs/deliverable_01: This has example outputs for an example simulation input given under inputs folder for Deliverable 1.

/verify/outputs/deliverable_02: This has example outputs for an example simulation input given under inputs folder for Deliverable 2.

author: Contains my name.

verify_output_format.sh: This verifies whether my outputs match the expected output.
