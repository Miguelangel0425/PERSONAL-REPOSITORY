#pragma once 
#include <SFML/Graphics.hpp>
#include "SocialGraph.h"

using namespace std;

class GUI{
    private:
    sf::RenderWindow window;
    SocialGraph& socialNetwork;

    //estado del GUI
    bool isLoggedIn;
    bool isRegistering;
    string currentUser;
    bool loginFailed;
    bool registrationFailed;
    sf::Clock errorTimer;

    //Recursos graficos
    sf::Font font;
    sf::Text titleText;
    sf::Text inputText;
    sf::Text statusText;
    sf::RectangleShape inputBox;

    //eleemntos de la interfaz
    void drawLoginScreen();
    void drawRegistrationScreen();
    void drawMainScreen();
    void drawPostScreen();
    void drawFriendsList();

    bool isEnteringUsername;
    bool isEnteringPassword;
    bool isEnteringConfirmPassword;
    bool isEnteringPost;
    std::string currentInputUsername;
    std::string currentInputPassword;
    std::string currentInputConfirmPassword;
    std::string currentInputPost;
    
    // Botones
    sf::RectangleShape loginButton;
    sf::RectangleShape registerButton;
    sf::RectangleShape registerSubmitButton;
    sf::RectangleShape backButton;
    sf::RectangleShape postButton;
    sf::RectangleShape logoutButton;
    sf::Text loginButtonText;
    sf::Text registerButtonText;
    sf::Text registerSubmitButtonText;
    sf::Text backButtonText;
    sf::Text postButtonText;
    sf::Text logoutButtonText;
    
    // Métodos auxiliares
    void initializeButtons();
    bool isMouseOverButton(const sf::RectangleShape& button, sf::Vector2i mousePos);
    void clearInputStates();

    //mensajes de eventos
    void handleLoginEvents(sf::Event &event);
    void handleRegistrationEvents(sf::Event &event);
    void handleMainScreenEvents(sf::Event &event);
    void attemptLogin();
    void attemptRegister();

public:
    GUI(SocialGraph& network);
    void run();
};