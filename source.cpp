#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <string>
#include <chrono>
#include <iostream>

int main() 
{
    // IMAGES! //
    sf::Texture cursorTexture;
    cursorTexture.loadFromFile("Images/cursor.png");
    cursorTexture.setSmooth(true);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("Images/bg.png");
    backgroundTexture.setSmooth(true);
    backgroundTexture.setRepeated(true);

    sf::Clock clock;

    namespace chrono = std::chrono;

    auto now = chrono::steady_clock::now().time_since_epoch();
    auto seconds = double(now.count()) / chrono::steady_clock::period::den;

    // cursor image :D (and friends)
    sf::Sprite cursor;
    cursor.setTexture(cursorTexture);

    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setPosition(-100, -100);
    background.setTextureRect(sf::IntRect(5000, 5000, 5000, 5000));
    

    // royalrte rfe.. l. musa..cw //
    sf::Music monkeys;
    monkeys.openFromFile("Audios/BGM.ogg");
    monkeys.play();
    monkeys.setLoop(true);

    double time = 0.1;

    // text :D //
    sf::Text hello;
    sf::Font progressivesoul;
    sf::Font lemonmilk;
    progressivesoul.loadFromFile("Fonts/PROGRESSIVE SOUL.ttf");
    lemonmilk.loadFromFile("Fonts/LEMONMILK.otf");
    hello.setFont(lemonmilk);
    hello.setString("SFML Test. To be rewritten");
    hello.setCharacterSize(100);

    // bad guy // 
    sf::Text badguy;
    badguy.setFont(progressivesoul);
    badguy.setString("O");

    sf::RenderWindow window(sf::VideoMode(800, 600), "Dad, i'm learning SFML!");
    sf::View view;

    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    cursor.setScale(0.2f, 0.2f);

    bool l1pressed = false;
    bool musicplaying = false;

    while (window.isOpen()) {

        hello.setRotation(0);
        hello.setColor(sf::Color(255, 255, 255));

        sf::Time sfmlTime = clock.getElapsedTime(); 

        if (hello.getGlobalBounds().intersects(cursor.getGlobalBounds())) {
            hello.setFillColor(sf::Color(102, 255, 102));
            hello.setRotation(5);
        }

        double sine = std::sin(sfmlTime.asSeconds());
        background.move(0.5f, 0.5f);
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        
        /* rip ears */
        std::cout << hello.getScale().y / 2 << " " << hello.getScale().x / 2 << std::endl;
        hello.setOrigin(hello.getLocalBounds().width / 2, hello.getLocalBounds().height / 2);


        /* cursor funnies */
        cursor.rotate(sine);
        cursor.setOrigin(75, 75);
        cursor.setPosition(400, 300);

        /* bad guy */
        
        badguy.setPosition(400, 300);

        // The current event happening on this frame ( i think )
        sf::Event event;

        // If anything happens in terms of clicking something like the close button on the window
        while(window.pollEvent(event)) {

            // Close the window if the X button is closed
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        if (event.type == sf::Event::Resized) {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
            hello.setPosition(window.getViewport(sf::View(visibleArea)).width / 2, window.getViewport(sf::View(visibleArea)).height / 2);
            
        }   


        // why dont we get input
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            l1pressed = true;
            if (cursor.getScale().x > 0.3645f) {
                cursor.scale(0.95f, 0.95f);
            }
        }


        if (l1pressed == false) {
            cursor.setScale(0.5f, 0.5f);
        }
        l1pressed = false;


        // oops
        cursor.setPosition(localPosition.x, localPosition.y);

        // oops 2
        badguy.setPosition(badguy.getPosition().x, sine * badguy.getPosition().y * 10);

        // every time a new frame is drawn the window gets cleared with a black bg (could remove this and it would make cool vapor trails, might try later)
        window.clear(sf::Color::Black);

        // draw this first
        window.draw(background);

        // draw other stuff here
        window.draw(badguy);
        window.draw(hello);

        // draw this last 
        window.draw(cursor);
        
        

        // finally, show the window to the user
        window.display();

        time = time + 0.5f;


        if (background.getPosition().x == 0 && background.getPosition().y == 0) {
            background.setPosition(-150, -150);
        }
    }

    return 0;

}