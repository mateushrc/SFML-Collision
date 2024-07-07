#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main() {
    //Atributos Gerais
    int screenHeight, screenWidth;
    screenWidth = 1280;
    screenHeight = 720;
    RenderWindow window(VideoMode(screenWidth, screenHeight), "SFML Collision Test", Style::Default);
    float sizeP1 = 70.f;
    float sizeP2 = 70.f;
    
    //Player 1 
    RectangleShape p1(Vector2f(sizeP1, sizeP1));
    p1.setPosition(screenWidth/3 , screenHeight/2);
    p1.setFillColor(Color::Blue);
    p1.setOrigin(sizeP1/2, sizeP1/2);

    //Player 2
    RectangleShape p2(Vector2f(sizeP2, sizeP2));
    p2.setPosition(screenWidth /2, screenHeight /2);
    p2.setFillColor(Color::Red);
    p2.setOrigin(sizeP2/2, sizeP2/2);

    //Fonte
    Font font;
    font.loadFromFile("Resource/Fonts/minecraft.ttf");

    //Infos de controles
    Text p1Txt;
    p1Txt.setFont(font);
    p1Txt.setString("Player 1\nW = Up\nS = Down\nA = Left\nD = Right");
    p1Txt.setCharacterSize(24);
    p1Txt.setFillColor(Color::Blue);
    p1Txt.setPosition(screenWidth/screenWidth, screenHeight/screenHeight);

    //Infos de controles
    Text p2Txt;
    p2Txt.setFont(font);
    p2Txt.setString("Player 2\nArrowUp = Up\nArrowDown = Down\nArrowLeft = Left\nArrowRight = Right");
    p2Txt.setCharacterSize(24);
    p2Txt.setFillColor(Color::Red);
    p2Txt.setOrigin(240, 0);
    p2Txt.setPosition(screenWidth, screenHeight / screenHeight);

    while (window.isOpen()) {
        Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == Event::Closed) {
                window.close();
            }
        }

        //Pegando as posições
        Vector2f oldP1Pos = p1.getPosition();
        Vector2f oldP2Pos = p2.getPosition();

        // Player 1 controles
        bool moved = false;
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            p1.move(-1.f, 0.f);
            moved = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            p1.move(1.f, 0.f);
            moved = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            p1.move(0.f, -1.f);
            moved = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            p1.move(0.f, 1.f);
            moved = true;
        }

        // Verificar colisão entre p1 e p2 após movimento
        if (p1.getGlobalBounds().intersects(p2.getGlobalBounds())) {
            if (moved) {
                p1.setPosition(oldP1Pos); // Reverte a posição
            }
        }

        // Player 2 controles
        moved = false;
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            p2.move(-1.f, 0.f);
            moved = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            p2.move(1.f, 0.f);
            moved = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            p2.move(0.f, -1.f);
            moved = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            p2.move(0.f, 1.f);
            moved = true;
        }

        // Verificar colisão entre p2 e p1 após movimento
        if (p2.getGlobalBounds().intersects(p1.getGlobalBounds())) {
            if (moved) {
                p2.setPosition(oldP2Pos); // Reverte a posição
            }
        }

        window.clear(Color::Black);

        // Draw
        window.draw(p1);
        window.draw(p2);
        window.draw(p1Txt);
        window.draw(p2Txt);

        // Atualiza a janela
        window.display();
    }

    return 0;
}