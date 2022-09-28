#include <iostream>
#include "TestsParticule.h"

int main(int argc, char **argv) {
    std::cout << "\nStarting tests for Particule\n" << std::endl;

    std::cout << "Constructor :                 " << (TestsParticule::constructor()             ? "ok" : "fail") << std::endl;

    std::cout << "\nEnding tests for Particule\n" << std::endl;
    return EXIT_SUCCESS;
}
