#pragma once 
#include <SFML/Graphics.hpp>
#include "SocialGraph.h"

using namespace std;

struct ValidationResult {
    bool isValid;
    std::string message;
    ValidationResult(bool valid, const std::string& msg) : isValid(valid), message(msg) {}
};

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
    void initializeButtons();
    bool isMouseOverButton(const sf::RectangleShape& button, sf::Vector2i mousePos);
    void clearInputStates();
    const sf::Color BACKGROUND_COLOR = sf::Color(37, 37, 37);
    const sf::Color PRIMARY_COLOR = sf::Color(70, 130, 180);
    const sf::Color SECONDARY_COLOR = sf::Color(95, 158, 160);
    const sf::Color TEXT_COLOR = sf::Color(240, 240, 240);
    const sf::Color INPUT_BACKGROUND = sf::Color(45, 45, 45);
    const sf::Color BUTTON_HOVER_COLOR = sf::Color(100, 149, 237);
    
    // Elementos visuales adicionales
    sf::RectangleShape cardBackground;
    sf::RectangleShape divider;
    std::vector<sf::RectangleShape> postCards;
    std::vector<sf::RectangleShape> friendCards;
    
    // Métodos auxiliares para estilos
    void styleButton(sf::RectangleShape& button, sf::Text& text, const std::string& buttonText);
    void createCardBackground(float x, float y, float width, float height);
    void drawPostCard(const std::string& post, float& yPos);
    void drawFriendCard(const std::string& friendName, float& yPos);

    //mensajes de eventos
    void handleLoginEvents(sf::Event &event);
    void handleRegistrationEvents(sf::Event &event);
    void handleMainScreenEvents(sf::Event &event);
    void attemptLogin();
    void attemptRegister();

    const size_t MIN_USERNAME_LENGTH = 4;
    const size_t MAX_USERNAME_LENGTH = 20;
    const size_t MIN_PASSWORD_LENGTH = 8;
    const size_t MAX_PASSWORD_LENGTH = 30;
    const size_t MAX_POST_LENGTH = 280;
    
    
    // Funciones de validación
    ValidationResult validateUsername(const std::string& username);
    ValidationResult validatePassword(const std::string& password);
    ValidationResult validatePost(const std::string& post);
    bool containsInvalidChars(const std::string& str);



public:
    GUI(SocialGraph& network);
    void run();
};