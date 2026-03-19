#include "Board.h"
#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>

int main() {
    Board board(5, 5);
    board.addWall(0, 0, false, true, false, true);
    board.addWall(2, 2, true, false, false, false);

    sf::RenderWindow window(sf::VideoMode(400, 400), "Ricochet Robots!");

    while (window.isOpen()) {
        sf::Event event;
        // Verifica todos os eventos (ex: rato, teclado, clicar no X da janela)
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 3. Limpar a janela do frame anterior com uma cor de fundo (Branco)
        window.clear(sf::Color::White);

        // 4. Desenhar o nosso tabuleiro passando a janela
        board.drawBoard(window);

        // 5. Atualizar o ecrã para mostrar os desenhos
        window.display();
    }

    return 0;
}