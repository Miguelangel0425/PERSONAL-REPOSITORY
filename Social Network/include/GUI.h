#include "Button.h"
#include "ValidationResult.h" // Include the header file where ValidationResult is defined
#include "SocialGraph.h"
#include <SFML/Graphics.hpp>
class GUI {
    public:
        bool areFriends(const std::string& user1, const std::string& user2);
        bool addFriend(const std::string& user, const std::string& friendName);
        GUI(SocialGraph& network);
        void run();
        void drawLoginScreen();
        void drawRegistrationScreen();
        void drawMainScreen();
        void drawPostScreen();
        void drawFriendsList();
        void handleLoginEvents(sf::Event &event);
        void handleRegistrationEvents(sf::Event &event);
        void handleMainScreenEvents(sf::Event &event);
        void attemptAddFriend();
        void attemptLogin();
        void attemptRegister();
        ValidationResult validateUsername(const std::string& username);
        ValidationResult validatePassword(const std::string& password);
        ValidationResult validatePost(const std::string& post);
        bool containsInvalidChars(const std::string& str);
    private:
        SocialGraph& socialNetwork;
        sf::RenderWindow window;
        sf::Font font;
        sf::Text titleText;
        sf::Text inputText;
        sf::Text statusText;
        sf::RectangleShape inputBox;
        sf::RectangleShape cardBackground;
        sf::RectangleShape divider;
        Button loginButton;
        Button registerButton;
        Button registerSubmitButton;
        Button backButton;
        Button postButton;
        Button addFriendButton;
        Button logoutButton;
        bool isLoggedIn;
        bool isRegistering;
        bool loginFailed;
        bool registrationFailed;
        bool isEnteringUsername;
        bool isEnteringPassword;
        bool isEnteringConfirmPassword;
        bool isEnteringPost;
        bool isEnteringFriendName;
        std::string currentUser;
        std::string currentInputUsername;
        std::string currentInputPassword;
        std::string currentInputConfirmPassword;
        std::string currentInputPost;
        std::string currentInputFriendName;
        sf::Clock errorTimer;
        bool friendRequestSent;
        void initializeButtons();
        void clearInputStates();
        bool isMouseOverButton(const Button& button, sf::Vector2i mousePos);
        void createCardBackground(float x, float y, float width, float height);
        void drawPostCard(const std::string& post, float& yPos);
        void drawFriendCard(const std::string& friendName, float& yPos);
    };