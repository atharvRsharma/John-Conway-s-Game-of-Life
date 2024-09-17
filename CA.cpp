#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <numeric>
#include "CA.h"


CellularAutomaton::CellularAutomaton(int width, int height, int numAlive) : width(width), height(height), grid(width* height), window(sf::VideoMode(width * 10, height * 10), "conway ca"), paused(false) {
    std::srand(std::time(nullptr));
    initializeGrid(numAlive);
}

void CellularAutomaton::update() {
    if (paused) {
        return;
    }

    std::vector<int> newGrid = grid;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            int liveNeighbors = countLiveNeighbors(x, y);

            if (grid[index] == 1) {
                newGrid[index] = (liveNeighbors == 2 || liveNeighbors == 3) ? 1 : 0;
            }
            else {
                newGrid[index] = (liveNeighbors == 3) ? 1 : 0;
            }
        }
    }
    grid = newGrid;
}

void CellularAutomaton::draw(char choice) {
    {
        window.clear();
        sf::RectangleShape cellShape(sf::Vector2f(7, 7));
        

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                sf::Color col(rand() % 256, rand() % 256, rand() % 256);
                cellShape.setPosition(x * 10, y * 10);
                if (grid[y * width + x] == 1) {
                    if (choice == 'b') {
                        cellShape.setFillColor(sf::Color::Blue);
                    }
                    if (choice == 'r') {
                        cellShape.setFillColor(sf::Color::Red);
                    }
                    if (choice == 'x') {
                        cellShape.setFillColor(col);
                    }
                    if (choice == 'g') {
                        cellShape.setFillColor(sf::Color::Green);
                    }
                    if (choice == 'c') {
                        cellShape.setFillColor(sf::Color::Cyan);
                    }
                    if (choice == 'm') {
                        cellShape.setFillColor(sf::Color::Magenta);
                    }
                    if (choice == 'y') {
                        cellShape.setFillColor(sf::Color::Yellow);
                    }
                    if(choice == NULL) {
                        cellShape.setFillColor(sf::Color::White);
                    }
                }                                   
                else {
                    cellShape.setFillColor(sf::Color::Black);
                }
                window.draw(cellShape);
            }
        }
        window.display();
    }
}

void CellularAutomaton::run(int numAlive) {
    while (window.isOpen()) {
        sf::Event event;
        char choice = NULL;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S) {
                    clear(numAlive);
                }
                else if (event.key.code == sf::Keyboard::P) {
                    paused = !paused;
                }
                if (event.key.code == sf::Keyboard::R) {
                    choice = 'r';
                }
                if (event.key.code == sf::Keyboard::G) {
                    choice = 'g';
                }
                if (event.key.code == sf::Keyboard::B) {
                    choice = 'b';
                }
                if (event.key.code == sf::Keyboard::M) {
                    choice = 'm';
                }
                if (event.key.code == sf::Keyboard::W) {
                    choice = 'w';
                }
                if (event.key.code == sf::Keyboard::C) {
                    choice = 'c';
                }
                if (event.key.code == sf::Keyboard::Y) {
                    choice = 'y';
                }
                if (event.key.code == sf::Keyboard::X) {
                    choice = 'x';
                }
            }

        }

        update();
        draw(choice);
        sf::sleep(sf::milliseconds(30)); //update rate
    }
}

int CellularAutomaton::countLiveNeighbors(int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                count += grid[ny * width + nx];
            }
        }
    }
    return count;
}

void CellularAutomaton::initializeGrid(int numAlive) {
    std::fill(grid.begin(), grid.end(), 0);

    std::vector<int> indices(width * height);
    std::iota(indices.begin(), indices.end(), 0);

    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(std::rand()));

    for (int i = 0; i < numAlive && i < indices.size(); ++i) {
        grid[indices[i]] = 1;
    }
}

void CellularAutomaton::clear(int numAlive) {
    initializeGrid(numAlive);
}