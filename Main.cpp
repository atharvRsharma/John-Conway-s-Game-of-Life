#include "CA.h"

int initial_population = 6000;

int main() {
    CellularAutomaton automaton(100, 100, initial_population);
    automaton.run(initial_population);
    return 0;
}
