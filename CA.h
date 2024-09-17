#ifndef CA_CLASS_H
#define CA_CLASS_H
#include <SFML/Graphics.hpp>


class CellularAutomaton {
public:
    CellularAutomaton(int width, int height, int numAlive);

    void update();

    void draw(char choice);

    void run(int numAlive);

private:
    int width, height;
    std::vector<int> grid;
    sf::RenderWindow window;
    bool paused;

    int countLiveNeighbors(int x, int y);

    void initializeGrid(int numAlive);

    void clear(int numAlive);
};


#endif CA_CLASS_H