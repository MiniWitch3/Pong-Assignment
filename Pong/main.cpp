
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

#include <cmath>
#include <string>

//Canvas settings
int Height = 480;
int Width = 640;
std::string windowTitle{"Pong Pong"};

//make the paddles' sizes and locations
float fifty = 50;
float LPSize_X = 25;
float LPSize_Y = 75;
float LPPos_X = 5;
float LPPos_Y = (Height/2) - (LPSize_Y/2);
float RPSize_X = 25;
float RPSize_Y = 75;
float RPPos_X = 605;
float RPPos_Y = (Height/2) - (RPSize_Y/2);

//making the Pong Ball
float ballX = 320;
float ballY = 240;
float ballRadius = 10;
float Bspeed = 0.2;
float ballDirX = 1;
float ballDirY = 1;

//Scoreboard
int playerscore = 0;
int opponentscore = 0;

int main(){
    
    //create the game window
    sf::RenderWindow window(sf::VideoMode(Width, Height), windowTitle);
    
    //set the icon
    sf::Image icon;
    if(!icon.loadFromFile(resourcePath() + "icon.png")){
        return EXIT_FAILURE;
    }
    
    //load music
    sf::Music melody;
    if(!melody.openFromFile(resourcePath() + "Nice_song.ogg")){
        return EXIT_FAILURE;
    }
    
    //Play Music
    melody.play();
    
    //create shapes and texts
    sf::Font font;
    sf::Text pScoreText, oScoreText;
    sf::RectangleShape bgLeftBox, bgRightBox, centerbox, LP, RP;
    sf::CircleShape pongBall;
    
    //setting up the left and right backgrounds
    bgLeftBox.setSize(sf::Vector2f(Width/2, Height));
    bgLeftBox.setPosition(sf::Vector2f(0, 0));
    bgLeftBox.setFillColor(sf::Color::Blue);
    bgRightBox.setSize(sf::Vector2f(Width/2, Height));
    bgRightBox.setPosition(sf::Vector2f(Width/2, 0));
    bgRightBox.setFillColor(sf::Color::Red);
    
    //import font and create score text
    std::string resourcePath(void);
    font.loadFromFile(resourcePath() + "boxfont.ttf");
    pScoreText.setFont(font);
    oScoreText.setFont(font);
    pScoreText.setCharacterSize(60);
    oScoreText.setCharacterSize(60);
    pScoreText.setColor(sf::Color::Red);
    oScoreText.setColor(sf::Color::Blue);
    pScoreText.setPosition(sf::Vector2f(Width/4, 0));
    oScoreText.setPosition(sf::Vector2f(3 * Width/4, 0));
    pScoreText.setString("0");
    oScoreText.setString("0");
    
    //set up the left and right paddles
    LP.setSize(sf::Vector2f(LPSize_X, LPSize_Y));
    LP.setPosition(sf::Vector2f(LPPos_X, LPPos_Y));
    LP.setFillColor(sf::Color::Red);
    RP.setSize(sf::Vector2f(RPSize_X, RPSize_Y));
    RP.setPosition(sf::Vector2f(RPPos_X, RPPos_Y));
    RP.setFillColor(sf::Color::Blue);
    
    //create center part
    centerbox.setSize(sf::Vector2f(fifty, fifty));
    centerbox.setPosition(320, 240);
    centerbox.setFillColor(sf::Color::Yellow);
    
    //Create the ball
    pongBall.setRadius(ballRadius);
    pongBall.setPosition(ballX, ballY);
    pongBall.setFillColor(sf::Color::Green);
    
    //game loop
    while (window.isOpen()){
        
        //moving the ball across the screen
        ballX += Bspeed * ballDirX;
        ballY += Bspeed * ballDirY;
        pongBall.setPosition(ballX, ballY);
        
        //bounce off walls
        if(pongBall.getPosition().y >Height){
            ballDirY = -fabs(ballDirY);
        }else if(pongBall.getPosition().y < 0){
            ballDirY = fabs(ballDirY);
        }
        
        //ball collides with left paddle
        if(pongBall.getPosition().x < LP.getSize().x + LP.getPosition().x &&
           pongBall.getPosition().x > LP.getPosition().x &&
           pongBall.getPosition().y < LP.getSize().y + LP.getPosition().y &&
           pongBall.getPosition().y > LP.getPosition().y)
        {
            ballDirX = fabs(ballDirX);
            
            //ball misses left paddle
        }else if(pongBall.getPosition().x < 0){
            ballX = Width/2;
            ballY = Height/2;
            pongBall.setPosition(ballX, ballY);
            ballDirX = fabs(ballDirX);
            ++opponentscore;
            std::string oTextScore = std::to_string(opponentscore);
            oScoreText.setString(oTextScore);
            
            if(opponentscore == 11){
                
                //the Opponent Wins, Player loses
                oScoreText.setColor(sf::Color::Yellow);
                oScoreText.setCharacterSize(20);
                oScoreText.setPosition(sf::Vector2f(0, Height/2));
                oScoreText.setString("Blue Wins!  Thanks for playing!");
                window.clear();
                window.close();
            }
        }
        
        //ball collides with right paddle
        if(pongBall.getPosition().x < RP.getPosition().x + RP.getSize().x &&
           pongBall.getPosition().x > RP.getPosition().x &&
           pongBall.getPosition().y < RP.getPosition().y + RP.getSize().y &&
           pongBall.getPosition().y > RP.getPosition().y)
        {
            ballDirX = -fabs(ballDirX);
            
            //ball misses right paddle
        }else if(pongBall.getPosition().x > Width){
            ballX = Width/2;
            ballY = Height/2;
            pongBall.setPosition(ballX, ballY);
            ballDirX = -fabs(ballDirX);
            ++playerscore;
            std::string pTextScore = std::to_string(playerscore);
            pScoreText.setString(pTextScore);
            
            if(playerscore == 11){
                
                //the Player Wins, Opponent Loses
                pScoreText.setColor(sf::Color::Yellow);
                pScoreText.setCharacterSize(20);
                pScoreText.setPosition(sf::Vector2f(0, Height/2));
                pScoreText.setString("Red Win!  Thanks for playing!");
                window.clear();
                window.close();
            }
        }
        
        //ball collides with top of block in the center
        if(pongBall.getPosition().y == 190 && pongBall.getPosition().x > 270 && pongBall.getPosition().x < 370){
            if(ballDirX > 0){
                pongBall.setPosition(ballX, 470);
            }else if(ballDirX < 0){
                pongBall.setPosition(ballX, 170);
            }
        //ball collides with bottom of block in center
        }else if(pongBall.getPosition().y == 290 && pongBall.getPosition().x > 270 && pongBall.getPosition().x < 370){
            if(ballDirX > 0){
                pongBall.setPosition(ballX, 470);
            }else if(ballDirX < 0){
                pongBall.setPosition(ballX, 170);
            }
        //ball collides with left of block in center
        }else if(pongBall.getPosition().x == 270 && pongBall.getPosition().y > 190 && pongBall.getPosition().y < 290){
            if(ballDirX > 0){
                pongBall.setPosition(ballX, 470);
            }else if(ballDirX < 0){
                pongBall.setPosition(ballX, 170);
            }
        //ball collides with right of block in center
        }else if(pongBall.getPosition().x == 370 && pongBall.getPosition().y > 190 && pongBall.getPosition().y < 290){
            if(ballDirX > 0){
                pongBall.setPosition(ballX, 470);
            }else if(ballDirX < 0){
                pongBall.setPosition(ballX, 170);
            }
        }
        
        //Game Events
        sf::Event event;
        while(window.pollEvent(event)){
            
            //close window
            if(event.type == sf::Event::Closed){
                
                //clear screen
                window.clear(sf::Color::White);
                window.close();
            }
            
            //Move the Left Paddle
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                
                LP.move(sf::Vector2f(0, -12));
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                
                LP.move(sf::Vector2f(0, 12));
            }
            
            //Move the Right Paddle
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
                
                RP.move(sf::Vector2f(0, -12));
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
                
                RP.move(sf::Vector2f(0, 12));
            }
        }
        
        //draws the sprites
        window.draw(bgLeftBox);
        window.draw(bgRightBox);
        window.draw(pScoreText);
        window.draw(oScoreText);
        window.draw(LP);
        window.draw(RP);
        window.draw(pongBall);
        
        //updating the window regularly
        window.display();
        
    }
    
}
