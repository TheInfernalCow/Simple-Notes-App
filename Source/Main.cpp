#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Config.hpp"

sf::String wrapText(sf::String string, sf::Font font, int maxWidth, int fontSize) {
  
    int currWidth = 0;
    int wordWidth = 0;
    std::size_t wordPos(0);

    for (int i = 0; i < string.getSize(); i++) {

        auto glyph = font.getGlyph(string[i], fontSize, false);

        wordWidth += glyph.advance;

        if (string[i] == ' ') {
            if ((currWidth + wordWidth) > maxWidth) {
                string[wordPos] = '\n';
                currWidth = wordWidth;
            } else {
                currWidth += wordWidth;
            }
            wordWidth = 0;

            wordPos = std::size_t(i);
        } else if (string[i] == '\n') {
            currWidth = 0;
            wordWidth = 0;
            
            wordPos = std::size_t(i);
        }

    }

    return string;

}

int main() {

    Config config("config", "text"); 
    
    //Load configuration files and define variables
    int width = std::stoi(config["width"]);
    int height = std::stoi(config["height"]);
    int padding = std::stoi(config["padding"]);
    int fontSize = std::stoi(config["font_size"]);
    int xOffset = std::stoi(config["x_offset"]);
    int yOffset = std::stoi(config["y_offset"]);
    std::string fontName = config["font"];
    sf::Color background(std::stoi(config["background_r"]), std::stoi(config["background_g"]), std::stoi(config["background_b"]), std::stoi(config["background_a"]));
    sf::Time sleeptime = sf::milliseconds(std::stoi(config["update_interval"]));
    sf::String string(config.getText());

    sf::RenderWindow window(sf::VideoMode(width, height), "notes-app");
    window.setPosition(sf::Vector2i(xOffset, yOffset));

    sf::Font font;
    if (!font.loadFromFile(fontName)) {
        std::cout << "[ERROR]: Specified font cannot be found!" << std::endl;
    }

    sf::Text text;

    string = wrapText(string, font, width - (2 * padding), fontSize);

    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(fontSize);
    text.setPosition(padding, padding);

    while (window.isOpen()) {
    
        sf::Event e;
        while (window.pollEvent(e)) {
        
            if (e.type == sf::Event::Closed)
                window.close();

            else if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Escape)
                    system("./restart.sh");
            }

        }

        window.clear(background);

        window.draw(text);

        window.display();
        sf::sleep(sleeptime);
    }

    return 0;

}
