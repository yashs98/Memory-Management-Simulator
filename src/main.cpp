/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
 */

#include <cstdlib>
#include "simulation/simulation.h"
#include "flag_parser/flag_parser.h"

using namespace std;

/**
* The main entry point to the simulation.
*/

int main(int argc, char** argv) {
    // TODO: implement me

   Simulation* simulation = new Simulation();

   FlagOptions flagOptions;

   if(parse_flags(argc, argv, flagOptions)){

        simulation->run(flagOptions);
    }

    else {
        print_usage();
    }


    

    

    return EXIT_SUCCESS;
}
