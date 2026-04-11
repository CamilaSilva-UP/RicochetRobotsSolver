#include "Robot.h"

Position Robot::getPos() const { return this->pos; }
void Robot::setPos(Position pos) { this->pos = pos; }  
void Robot::setColor(Color c) {
    this->color = c;
}

void Robot::draw(sf::RenderWindow& window, float cellSize, float offset) {
    float radius = cellSize * 0.4f; 
    sf::CircleShape shape(radius);

    if (color == Color::Red)         shape.setFillColor(sf::Color::Red);
    else if (color == Color::Green)  shape.setFillColor(sf::Color::Green);
    else if (color == Color::Blue)   shape.setFillColor(sf::Color::Blue);
    else if (color == Color::Yellow) shape.setFillColor(sf::Color::Yellow);

    float px = offset + (pos.x * cellSize) + (cellSize / 2.0f) - radius;
    float py = offset + (pos.y * cellSize) + (cellSize / 2.0f) - radius;

    shape.setOutlineThickness(3.f);
    shape.setOutlineColor(sf::Color::Black);
    shape.setPosition({px, py});
    window.draw(shape);
}