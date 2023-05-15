#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <sstream>
using namespace sf;
using namespace std;
int main()
{
    // *************** Audio *****************

    Music gameMusic;
    gameMusic.openFromFile("audio/SkyFire_(Title_Screen).ogg");
    gameMusic.setVolume(10);
    gameMusic.play();
    gameMusic.setLoop(true); //loop the audio
    RenderWindow window(VideoMode(600, 600), "car game");
    float y_pos = window.getSize().y;
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("images/background.png");
    Sprite backgroundSprite(backgroundTexture);
    float window_x = window.getSize().x;
    float window_y = window.getSize().y;
    backgroundSprite.setScale(
        (float)window.getSize().x / backgroundSprite.getLocalBounds().width,
        (float)window.getSize().y * 2 / backgroundSprite.getLocalBounds().height);
    backgroundSprite.setPosition(0.0f, -(float)y_pos);
    Texture playerTexture;
    playerTexture.loadFromFile("images/car__2.png");
    Sprite playerSprite(playerTexture);
    playerSprite.setPosition(Vector2f(270.0f, 400.0f));
    playerSprite.setScale(0.7f, 0.7f);
    Texture playerTexture1;
    playerTexture1.loadFromFile("images/car__1.png");
    // Game Over Sprite -----------------------------------------------------------
    Texture gameoverTexture;
    gameoverTexture.loadFromFile("images/gameover.png");
    Sprite gameoverSprite(gameoverTexture);
    gameoverSprite.setPosition(50.0f, 150.0f);
    // Game Score -----------------------------------------------------------

    RectangleShape scoreZone(sf::Vector2f(600, 50)); // un Rectangle noir pour afficher le texte 
    //de l'heure
    scoreZone.setFillColor(Color::Transparent);
    scoreZone.setOutlineThickness(0.0f);
    scoreZone.setOutlineColor(Color::White);
    scoreZone.setPosition(0,0);
    Font font; // Police pour le texte du temps écoulé
    font.loadFromFile("font/RoughenCornerRegular.ttf"); // Un fichier TTF (True Type Font) est 
    //une police qui peut être installée sur macOS, Windows et d'autres plates-formes. Il est 
    // enregistré au format True Type Font.
      
        sf::Text timeText; // Préparation du texte du temps écoulé 
    timeText.setFont(font); // Réglage de la police du texte
    timeText.setCharacterSize(40); // Réglage de la taille du texte
    timeText.setFillColor(sf::Color::Yellow); // Réglage de la couleur du texte
    timeText.setPosition(25, 10); // Réglage de la position du texte
    // Timer 
    sf::Clock timer;
    timer.restart();
    bool gameover = false;
    std::vector <Sprite> players;
    
    while (window.isOpen())
    {   // scroll road
        y_pos = backgroundSprite.getPosition().y;
        if (y_pos >= 0)
        {
            y_pos = window.getSize().y;
            backgroundSprite.setPosition(0.0f, -(float)y_pos);
        }
        else {
            y_pos = y_pos + 0.1f;
            backgroundSprite.setPosition(0, y_pos);
        }

        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
             case Event::Closed:
                window.close();
                break;
             case Event::KeyPressed:
                 // le controle de mouvement du voiture
                switch (event.key.code)
                {
                case Keyboard::D:
                    if (playerSprite.getPosition().x < 600 - 140) {
                        playerSprite.setPosition(playerSprite.getPosition().x + 20, playerSprite.getPosition().y);
                    }
                    break;
                case Keyboard::Q:
                    if (playerSprite.getPosition().x > 30)
                        playerSprite.setPosition(playerSprite.getPosition().x - 20, playerSprite.getPosition().y);
                    break;
                case Keyboard::Z:
                    if (playerSprite.getPosition().y > 10)
                    {
                        playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y - 10);
                    }
                    break;
                case Keyboard::S:
                    if (playerSprite.getPosition().y < 600 - 190) {
                        playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y + 10);
                    }
                    break;
                }
                break;
             

            }
            
        }


        // Spawn a new car sprite every 2 second -------------------------------------------

        static Clock clock;
        if (clock.getElapsedTime().asSeconds() >= 5)
        {
            Sprite playerSprite1(playerTexture1);
            playerSprite1.setScale(0.8f, 0.8f);
            playerSprite1.setPosition(Vector2f(rand() % 500, -100.0f));
            players.push_back(playerSprite1);
            clock.restart();
            ;
        }

        // ************************ Animation ******************************



        window.clear();
        window.draw(backgroundSprite);
        window.draw(playerSprite);
        for (auto& playersprite1 : players)
        {
            playersprite1.move(0, 0.11); // move down 0.08 pixels every frame
            if (!gameover)
                window.draw(playersprite1);

            // Déclancheur du Game over : si les limites globales du sprite vaisseau spatial 
           // croisent les limites globales de n'importe quel sprite voiture 
            if (playerSprite.getGlobalBounds().intersects(playersprite1.getGlobalBounds()))
            {
                //GAME OVER
                gameover = true;
            }
        }
        if (!gameover)
        {
            // Compteur du temps écoulé -------------------------------------------------------
            int seconds = timer.getElapsedTime().asSeconds(); // récupération du nombre de 
            // secondes écoulées
            std::stringstream time;
            time << "Score: " << seconds;
            timeText.setString(time.str()); // timeText reçoit la valeur du nombre de secondes 

            window.draw(playerSprite);
        }
        else
        {
            // if (gameover)
            gameMusic.stop();
            window.clear();
            window.draw(backgroundSprite);
            window.draw(gameoverSprite);
            window.draw(scoreZone);    
        }
        window.draw(scoreZone);
        window.draw(timeText);
        window.display();
    }
    // window.draw(playerSprite1);
    




    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

