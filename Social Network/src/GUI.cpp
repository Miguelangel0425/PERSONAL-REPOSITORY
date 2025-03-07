#include "GUI.h"
#include <iostream>
#include "ThemeManager.h"
#include "SocialGraph.h"

#define MIN_USERNAME_LENGTH 3
#define MAX_USERNAME_LENGTH 20
#define MIN_PASSWORD_LENGTH 6
#define MAX_PASSWORD_LENGTH 30
#define MAX_POST_LENGTH 280

// Define constants
const sf::Color PRIMARY_COLOR = sf::Color(0, 123, 255); // Example color
const sf::Color SECONDARY_COLOR = sf::Color(108, 117, 125); // Example color
const sf::Color TEXT_COLOR = sf::Color::White; // Example color
const sf::Color INPUT_BACKGROUND = sf::Color(255, 255, 255, 200); // Example color
const sf::Color BACKGROUND_COLOR = sf::Color(30, 30, 30); // Example color
#include "InputField.h"
#include "Card.h"
#include "PostItem.h"
#include "FriendItem.h"

GUI::GUI(SocialGraph& network) 
    : socialNetwork(network),
      window(sf::VideoMode(800, 600), "Social Network App"),
      isLoggedIn(false),
      isRegistering(false),
      loginFailed(false),
      registrationFailed(false),
      isEnteringUsername(false),
      isEnteringPassword(false),
      isEnteringConfirmPassword(false),
      isEnteringPost(false),
      isEnteringFriendName(false),
      loginButton(font, "Login", 300, 350, 200, 40, PRIMARY_COLOR),
      registerButton(font, "Register", 300, 400, 200, 40, SECONDARY_COLOR),
      registerSubmitButton(font, "Create Account", 300, 420, 200, 40, PRIMARY_COLOR),
      backButton(font, "Back", 50, 520, 100, 40, SECONDARY_COLOR),
      postButton(font, "Post", 650, 520, 100, 40, PRIMARY_COLOR),
      addFriendButton(font, "Add Friend", 85, 450, 100, 30, PRIMARY_COLOR),
      logoutButton(font, "Logout", 650, 20, 100, 40, SECONDARY_COLOR) {
    
    // Try to load font
    if (!font.loadFromFile("resources/Arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        // Try system font as fallback
        if (!font.loadFromFile("resources/DejaVuSans.ttf")) {
            std::cerr << "Failed to load fallback font!" << std::endl;
        }
    }

    // Initialize UI elements
    titleText.setFont(font);
    titleText.setCharacterSize(24);
    titleText.setFillColor(TEXT_COLOR);
    
    inputText.setFont(font);
    inputText.setCharacterSize(18);
    inputText.setFillColor(TEXT_COLOR);
    
    statusText.setFont(font);
    statusText.setCharacterSize(16);
    statusText.setFillColor(sf::Color::Red);
    
    inputBox.setFillColor(INPUT_BACKGROUND);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(PRIMARY_COLOR);
    
    // Initialize buttons
    initializeButtons();
    
    // Set window frame rate limit
    window.setFramerateLimit(60);
}

void GUI::initializeButtons() {
    // Buttons are already initialized in the constructor with their positions and colors
    // This method can be used to update button positions or styles if needed
}

void GUI::clearInputStates() {
    isEnteringUsername = false;
    isEnteringPassword = false;
    isEnteringConfirmPassword = false;
    isEnteringPost = false;
    isEnteringFriendName = false;
    currentInputFriendName.clear();
}

bool GUI::isMouseOverButton(const Button& button, sf::Vector2i mousePos) {
    return button.isMouseOver(mousePos);
}

void GUI::createCardBackground(float x, float y, float width, float height) {
    cardBackground.setPosition(x, y);
    cardBackground.setSize(sf::Vector2f(width, height));
    cardBackground.setFillColor(sf::Color(50, 50, 50, 200));
    cardBackground.setOutlineThickness(1);
    cardBackground.setOutlineColor(sf::Color(100, 100, 100));
    window.draw(cardBackground);
}

void GUI::drawPostCard(const std::string& post, float& yPos) {
    PostItem postItem(font, post, currentUser, "Just now");
    postItem.setPosition(200, yPos);
    postItem.draw(window);
    yPos += 120; // Increase Y position for next card
}

void GUI::drawFriendCard(const std::string& friendName, float& yPos) {
    // Assume friends are online for this example
    bool isOnline = true; 
    FriendItem friendItem(font, friendName, isOnline);
    friendItem.setPosition(50, yPos);
    friendItem.draw(window);
    yPos += 60; // Increase Y position for next friend
}

void GUI::drawLoginScreen() {
    // Draw title
    titleText.setString("Social Network Login");
    titleText.setPosition(250, 100);
    window.draw(titleText);
    
    // Draw username input area
    inputText.setString("Username:");
    inputText.setPosition(200, 200);
    window.draw(inputText);
    
    inputBox.setSize(sf::Vector2f(300, 40));
    inputBox.setPosition(300, 200);
    window.draw(inputBox);
    
    // Draw current username input
    sf::Text userInputText;
    userInputText.setFont(font);
    userInputText.setString(currentInputUsername);
    userInputText.setPosition(310, 205);
    userInputText.setFillColor(TEXT_COLOR);
    window.draw(userInputText);
    
    // Draw password input area
    inputText.setString("Password:");
    inputText.setPosition(200, 250);
    window.draw(inputText);
    
    inputBox.setPosition(300, 250);
    window.draw(inputBox);
    
    // Draw password (as asterisks)
    sf::Text passwordText;
    passwordText.setFont(font);
    passwordText.setString(std::string(currentInputPassword.length(), '*'));
    passwordText.setPosition(310, 255);
    passwordText.setFillColor(TEXT_COLOR);
    window.draw(passwordText);
    
    // Draw buttons
    loginButton.draw(window);
    registerButton.draw(window);
    
    // Draw error message if login failed
    if (loginFailed && errorTimer.getElapsedTime().asSeconds() < 5) {
        statusText.setString("Login failed. Please check your credentials.");
        statusText.setPosition(200, 450);
        window.draw(statusText);
    }
}

void GUI::drawRegistrationScreen() {
    // Draw title
    titleText.setString("Create New Account");
    titleText.setPosition(250, 100);
    window.draw(titleText);
    
    // Draw username input area
    inputText.setString("Username:");
    inputText.setPosition(200, 200);
    window.draw(inputText);
    
    inputBox.setSize(sf::Vector2f(300, 40));
    inputBox.setPosition(300, 200);
    window.draw(inputBox);
    
    // Draw current username input
    sf::Text userInputText;
    userInputText.setFont(font);
    userInputText.setString(currentInputUsername);
    userInputText.setPosition(310, 205);
    userInputText.setFillColor(TEXT_COLOR);
    window.draw(userInputText);
    
    // Draw password input area
    inputText.setString("Password:");
    inputText.setPosition(200, 250);
    window.draw(inputText);
    
    inputBox.setPosition(300, 250);
    window.draw(inputBox);
    
    // Draw password (as asterisks)
    sf::Text passwordText;
    passwordText.setFont(font);
    passwordText.setString(std::string(currentInputPassword.length(), '*'));
    passwordText.setPosition(310, 255);
    passwordText.setFillColor(TEXT_COLOR);
    window.draw(passwordText);
    
    // Draw confirm password area
    inputText.setString("Confirm Password:");
    inputText.setPosition(150, 300);
    window.draw(inputText);
    
    inputBox.setPosition(300, 300);
    window.draw(inputBox);
    
    // Draw confirm password (as asterisks)
    sf::Text confirmPasswordText;
    confirmPasswordText.setFont(font);
    confirmPasswordText.setString(std::string(currentInputConfirmPassword.length(), '*'));
    confirmPasswordText.setPosition(310, 305);
    confirmPasswordText.setFillColor(TEXT_COLOR);
    window.draw(confirmPasswordText);
    
    // Draw buttons
    registerSubmitButton.draw(window);
    backButton.draw(window);
    
    // Draw error message if registration failed
    if (registrationFailed && errorTimer.getElapsedTime().asSeconds() < 5) {
        statusText.setString("Registration failed. " + statusText.getString());
        statusText.setPosition(200, 450);
        window.draw(statusText);
    }
}

void GUI::drawMainScreen() {
    // Draw header
    titleText.setString("Welcome, " + currentUser + "!");
    titleText.setPosition(50, 20);
    window.draw(titleText);
    
    // Draw logout button
    logoutButton.draw(window);
    
    // Draw divider
    divider.setSize(sf::Vector2f(2, 500));
    divider.setPosition(200, 70);
    divider.setFillColor(sf::Color(100, 100, 100));
    window.draw(divider);
    
    // Draw friends list section
    drawFriendsList();
    
    // Draw post creation section
    drawPostScreen();
}

void GUI::drawPostScreen() {
    // Draw post creation area
    Card postCard(font, "Create Post");
    postCard.setPosition(220, 70);
    postCard.setSize(560, 100);
    postCard.draw(window);
    
    // Draw post input box
    inputBox.setSize(sf::Vector2f(500, 60));
    inputBox.setPosition(230, 100);
    window.draw(inputBox);
    
    // Draw current post input
    sf::Text postInputText;
    postInputText.setFont(font);
    postInputText.setString(currentInputPost);
    postInputText.setPosition(240, 105);
    postInputText.setFillColor(TEXT_COLOR);
    window.draw(postInputText);
    
    // Draw post button
    postButton.draw(window);
    
    // Draw existing posts
    float yPos = 190;
    std::vector<std::string> posts = socialNetwork.getUserPosts(currentUser);
    for (const auto& post : posts) {
        drawPostCard(post, yPos);
    }
}

void GUI::drawFriendsList() {
    // Draw friends list title
    sf::Text friendsTitle;
    friendsTitle.setFont(font);
    friendsTitle.setString("Friends");
    friendsTitle.setCharacterSize(18);
    friendsTitle.setFillColor(TEXT_COLOR);
    friendsTitle.setPosition(50, 70);
    window.draw(friendsTitle);
    
    // Draw add friend section
    sf::Text addFriendTitle;
    addFriendTitle.setFont(font);
    addFriendTitle.setString("Add Friend");
    addFriendTitle.setCharacterSize(16);
    addFriendTitle.setFillColor(TEXT_COLOR);
    addFriendTitle.setPosition(50, 390);
    window.draw(addFriendTitle);
    
    // Draw friend input box
    inputBox.setSize(sf::Vector2f(150, 30));
    inputBox.setPosition(50, 415);
    window.draw(inputBox);
    
    // Draw current friend input
    sf::Text friendInputText;
    friendInputText.setFont(font);
    friendInputText.setString(currentInputFriendName);
    friendInputText.setPosition(55, 420);
    friendInputText.setCharacterSize(14);
    friendInputText.setFillColor(TEXT_COLOR);
    window.draw(friendInputText);
    
    // Draw add friend button
    addFriendButton.draw(window);
    
    // Draw friend request status if applicable
    if (friendRequestSent && errorTimer.getElapsedTime().asSeconds() < 5) {
        statusText.setPosition(50, 485);
        window.draw(statusText);
    }
    
    // Draw friends
    float yPos = 100;
    std::vector<std::string> friends = socialNetwork.getUserFriends(currentUser);
    for (const auto& friendName : friends) {
        drawFriendCard(friendName, yPos);
    }
}

void GUI::handleLoginEvents(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        if (isMouseOverButton(loginButton, mousePos)) {
            attemptLogin();
        }
        else if (isMouseOverButton(registerButton, mousePos)) {
            isRegistering = true;
            clearInputStates();
        }
        else if (mousePos.x >= 300 && mousePos.x <= 600 && mousePos.y >= 200 && mousePos.y <= 240) {
            isEnteringUsername = true;
            isEnteringPassword = false;
        }
        else if (mousePos.x >= 300 && mousePos.x <= 600 && mousePos.y >= 250 && mousePos.y <= 290) {
            isEnteringUsername = false;
            isEnteringPassword = true;
        }
        else {
            clearInputStates();
        }
    }
    else if (event.type == sf::Event::TextEntered) {
        if (isEnteringUsername) {
            if (event.text.unicode == 8 && !currentInputUsername.empty()) { // Backspace
                currentInputUsername.pop_back();
            }
            else if (event.text.unicode == 13) { // Enter
                isEnteringUsername = false;
                isEnteringPassword = true;
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                if (currentInputUsername.length() < MAX_USERNAME_LENGTH) {
                    currentInputUsername += static_cast<char>(event.text.unicode);
                }
            }
        }
        else if (isEnteringPassword) {
            if (event.text.unicode == 8 && !currentInputPassword.empty()) { // Backspace
                currentInputPassword.pop_back();
            }
            else if (event.text.unicode == 13) { // Enter
                attemptLogin();
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                if (currentInputPassword.length() < MAX_PASSWORD_LENGTH) {
                    currentInputPassword += static_cast<char>(event.text.unicode);
                }
            }
        }
    }
}

void GUI::handleRegistrationEvents(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        if (isMouseOverButton(registerSubmitButton, mousePos)) {
            attemptRegister();
        }
        else if (isMouseOverButton(backButton, mousePos)) {
            isRegistering = false;
            clearInputStates();
        }
        else if (mousePos.x >= 300 && mousePos.x <= 600 && mousePos.y >= 200 && mousePos.y <= 240) {
            isEnteringUsername = true;
            isEnteringPassword = false;
            isEnteringConfirmPassword = false;
        }
        else if (mousePos.x >= 300 && mousePos.x <= 600 && mousePos.y >= 250 && mousePos.y <= 290) {
            isEnteringUsername = false;
            isEnteringPassword = true;
            isEnteringConfirmPassword = false;
        }
        else if (mousePos.x >= 300 && mousePos.x <= 600 && mousePos.y >= 300 && mousePos.y <= 340) {
            isEnteringUsername = false;
            isEnteringPassword = false;
            isEnteringConfirmPassword = true;
        }
        else {
            clearInputStates();
        }
    }
    else if (event.type == sf::Event::TextEntered) {
        if (isEnteringUsername) {
            if (event.text.unicode == 8 && !currentInputUsername.empty()) { // Backspace
                currentInputUsername.pop_back();
            }
            else if (event.text.unicode == 13) { // Enter
                isEnteringUsername = false;
                isEnteringPassword = true;
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                if (currentInputUsername.length() < MAX_USERNAME_LENGTH) {
                    currentInputUsername += static_cast<char>(event.text.unicode);
                }
            }
        }
        else if (isEnteringPassword) {
            if (event.text.unicode == 8 && !currentInputPassword.empty()) { // Backspace
                currentInputPassword.pop_back();
            }
            else if (event.text.unicode == 13) { // Enter
                isEnteringPassword = false;
                isEnteringConfirmPassword = true;
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                if (currentInputPassword.length() < MAX_PASSWORD_LENGTH) {
                    currentInputPassword += static_cast<char>(event.text.unicode);
                }
            }
        }
        else if (isEnteringConfirmPassword) {
            if (event.text.unicode == 8 && !currentInputConfirmPassword.empty()) { // Backspace
                currentInputConfirmPassword.pop_back();
            }
            else if (event.text.unicode == 13) { // Enter
                attemptRegister();
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                if (currentInputConfirmPassword.length() < MAX_PASSWORD_LENGTH) {
                    currentInputConfirmPassword += static_cast<char>(event.text.unicode);
                }
            }
        }
    }
}

void GUI::handleMainScreenEvents(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        if (isMouseOverButton(logoutButton, mousePos)) {
            isLoggedIn = false;
            currentUser = "";
            clearInputStates();
        }
        else if (isMouseOverButton(postButton, mousePos)) {
            if (!currentInputPost.empty()) {
                ValidationResult postValidation = validatePost(currentInputPost);
                if (postValidation.isValid()) {
                    socialNetwork.addPost(currentUser, currentInputPost);
                    currentInputPost.clear();
                }
                else {
                    statusText.setString(postValidation.getErrorMessage());
                    errorTimer.restart();
                }
            }
        }
        else if (isMouseOverButton(addFriendButton, mousePos)) {
            attemptAddFriend();
        }
        else if (mousePos.x >= 230 && mousePos.x <= 730 && mousePos.y >= 100 && mousePos.y <= 160) {
            isEnteringPost = true;
            isEnteringFriendName = false;
        }
        else if (mousePos.x >= 50 && mousePos.x <= 200 && mousePos.y >= 415 && mousePos.y <= 445) {
            isEnteringPost = false;
            isEnteringFriendName = true;
        }
        else {
            isEnteringPost = false;
            isEnteringFriendName = false;
        }
    }
    else if (event.type == sf::Event::TextEntered) {
        if (isEnteringPost) {
            if (event.text.unicode == 8 && !currentInputPost.empty()) { // Backspace
                currentInputPost.pop_back();
            }
            else if (event.text.unicode == 13) { // Enter
                if (!currentInputPost.empty()) {
                    ValidationResult postValidation = validatePost(currentInputPost);
                    if (postValidation.isValid()) {
                        socialNetwork.addPost(currentUser, currentInputPost);
                        currentInputPost.clear();
                    }
                    else {
                        statusText.setString(postValidation.getErrorMessage());
                        errorTimer.restart();
                    }
                }
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                if (currentInputPost.length() < MAX_POST_LENGTH) {
                    currentInputPost += static_cast<char>(event.text.unicode);
                }
            }
        }
        else if (isEnteringFriendName) {
            if (event.text.unicode == 8 && !currentInputFriendName.empty()) { // Backspace
                currentInputFriendName.pop_back();
            }
            else if (event.text.unicode == 13) { // Enter
                attemptAddFriend();
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                if (currentInputFriendName.length() < MAX_USERNAME_LENGTH) {
                    currentInputFriendName += static_cast<char>(event.text.unicode);
                }
            }
        }
    }
}

void GUI::attemptAddFriend() {
    if (currentInputFriendName.empty()) {
        friendRequestSent = true;
        statusText.setString("Friend name cannot be empty.");
        errorTimer.restart();
        return;
    }
    
    if (currentInputFriendName == currentUser) {
        friendRequestSent = true;
        statusText.setString("You cannot add yourself as a friend.");
        errorTimer.restart();
        return;
    }
    
    if (!socialNetwork.userExists(currentInputFriendName)) {
        friendRequestSent = true;
        statusText.setString("User does not exist.");
        errorTimer.restart();
        return;
    }
    
    if (socialNetwork.areFriends(currentUser, currentInputFriendName)) {
        friendRequestSent = true;
        statusText.setString("Already friends with this user.");
        errorTimer.restart();
        return;
    }
    
    if (socialNetwork.addFriend(currentUser, currentInputFriendName)) {
        friendRequestSent = true;
        statusText.setString("Friend added successfully!");
        statusText.setFillColor(sf::Color::Green);
        errorTimer.restart();
        currentInputFriendName.clear();
    } else {
        friendRequestSent = true;
        statusText.setString("Failed to add friend.");
        statusText.setFillColor(sf::Color::Red);
        errorTimer.restart();
    }
}

void GUI::attemptLogin() {
    ValidationResult usernameValidation = validateUsername(currentInputUsername);
    ValidationResult passwordValidation = validatePassword(currentInputPassword);
    
    if (!usernameValidation.isValid() || !passwordValidation.isValid()) {
        loginFailed = true;
        statusText.setString(usernameValidation.isValid() ? passwordValidation.getErrorMessage() : usernameValidation.getErrorMessage());
        errorTimer.restart();
        return;
    }
    
    if (socialNetwork.verifyPassword(currentInputUsername, currentInputPassword)) {
        isLoggedIn = true;
        currentUser = currentInputUsername;
        loginFailed = false;
        clearInputStates();
    } else {
        loginFailed = true;
        statusText.setString("Invalid username or password.");
        errorTimer.restart();
    }
}

void GUI::attemptRegister() {
    ValidationResult usernameValidation = validateUsername(currentInputUsername);
    ValidationResult passwordValidation = validatePassword(currentInputPassword);
    
    if (!usernameValidation.isValid() || !passwordValidation.isValid()) {
        registrationFailed = true;
        statusText.setString(usernameValidation.isValid() ? passwordValidation.getErrorMessage() : usernameValidation.getErrorMessage());
        errorTimer.restart();
        return;
    }
    
    if (currentInputPassword != currentInputConfirmPassword) {
        registrationFailed = true;
        statusText.setString("Passwords don't match.");
        errorTimer.restart();
        return;
    }
    
    if (socialNetwork.userExists(currentInputUsername)) {
        registrationFailed = true;
        statusText.setString("Username already exists.");
        errorTimer.restart();
    } else {
        if (socialNetwork.addUser(currentInputUsername, currentInputPassword)) {
            isRegistering = false;
            clearInputStates();
            registrationFailed = false;
        } else {
            registrationFailed = true;
            statusText.setString("Failed to create account.");
            errorTimer.restart();
        }
    }
}

ValidationResult GUI::validateUsername(const std::string& username) {
    if (username.empty()) {
        return ValidationResult(false, "Username cannot be empty.");
    }
    
    if (username.length() < MIN_USERNAME_LENGTH) {
        return ValidationResult(false, "Username must be at least " + std::to_string(MIN_USERNAME_LENGTH) + " characters.");
    }
    
    if (username.length() > MAX_USERNAME_LENGTH) {
        return ValidationResult(false, "Username cannot exceed " + std::to_string(MAX_USERNAME_LENGTH) + " characters.");
    }
    
    if (containsInvalidChars(username)) {
        return ValidationResult(false, "Username contains invalid characters.");
    }
    
    return ValidationResult(true, "");
}

ValidationResult GUI::validatePassword(const std::string& password) {
    if (password.empty()) {
        return ValidationResult(false, "Password cannot be empty.");
    }
    
    if (password.length() < MIN_PASSWORD_LENGTH) {
        return ValidationResult(false, "Password must be at least " + std::to_string(MIN_PASSWORD_LENGTH) + " characters.");
    }
    
    if (password.length() > MAX_PASSWORD_LENGTH) {
        return ValidationResult(false, "Password cannot exceed " + std::to_string(MAX_PASSWORD_LENGTH) + " characters.");
    }
    
    return ValidationResult(true, "");
}

ValidationResult GUI::validatePost(const std::string& post) {
    if (post.empty()) {
        return ValidationResult(false, "Post cannot be empty.");
    }
    
    if (post.length() > MAX_POST_LENGTH) {
        return ValidationResult(false, "Post cannot exceed " + std::to_string(MAX_POST_LENGTH) + " characters.");
    }
    
    return ValidationResult(true, "");
}

bool GUI::containsInvalidChars(const std::string& str) {
    for (char c : str) {
        if (!isalnum(c) && c != '_' && c != '-') {
            return true;
        }
    }
    return false;
}

void GUI::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Handle events based on current screen
            if (!isLoggedIn) {
                if (isRegistering) {
                    handleRegistrationEvents(event);
                } else {
                    handleLoginEvents(event);
                }
            } else {
                handleMainScreenEvents(event);
            }
        }
        
        // Clear the window
        window.clear(BACKGROUND_COLOR);
        
        // Draw the current screen
        if (!isLoggedIn) {
            if (isRegistering) {
                drawRegistrationScreen();
            } else {
                drawLoginScreen();
            }
        } else {
            drawMainScreen();
        }
        
        // Update the window
        window.display();
    }
}