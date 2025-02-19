#include "GUI.h"
#include <iostream>

#include "GUI.h"
#include <iostream>

GUI::GUI(SocialGraph& network)
    : window(sf::VideoMode(800,600), "Red Social"),
    socialNetwork(network),
    isLoggedIn(false),
    isRegistering(false),
    loginFailed(false),
    registrationFailed(false),
    isEnteringUsername(false),
    isEnteringPassword(false),
    isEnteringConfirmPassword(false),
    isEnteringPost(false) {  // Fixed initialization order to match declaration order
        if(!font.loadFromFile("arial.ttf")){
            std::cerr << "Error al cargar la fuente" << std::endl;
        }

        titleText.setFont(font);
        titleText.setCharacterSize(24);
        titleText.setFillColor(sf::Color::White);

        inputBox.setSize(sf::Vector2f(200, 30));
        inputBox.setFillColor(sf::Color::White);
        inputBox.setOutlineColor(sf::Color::Black);

        inputText.setFont(font);
        inputText.setCharacterSize(20);
        inputText.setFillColor(sf::Color::Black);
        
        statusText.setFont(font);
        statusText.setCharacterSize(16);
        statusText.setFillColor(sf::Color::Red);
        statusText.setPosition(300, 350);
        
        initializeButtons();
}

void GUI::initializeButtons() {
        // Configurar botón de login
        loginButton.setSize(sf::Vector2f(200, 30));
        loginButton.setPosition(300, 300);
        loginButton.setFillColor(sf::Color(50, 150, 250));
        loginButtonText.setFont(font);
        loginButtonText.setString("Iniciar Sesion");
        loginButtonText.setCharacterSize(16);
        loginButtonText.setFillColor(sf::Color::White);
        // Centrar el texto en el botón
        sf::FloatRect textBounds = loginButtonText.getLocalBounds();
        loginButtonText.setPosition(
            300 + (200 - textBounds.width) / 2,
            300 + (30 - textBounds.height) / 2
        );
        
        // Configurar botón de registro en pantalla login
        registerButton.setSize(sf::Vector2f(200, 30));
        registerButton.setPosition(300, 350);
        registerButton.setFillColor(sf::Color(50, 200, 50));
        registerButtonText.setFont(font);
        registerButtonText.setString("Registrarse");
        registerButtonText.setCharacterSize(16);
        registerButtonText.setFillColor(sf::Color::White);
        // Centrar el texto en el botón
        textBounds = registerButtonText.getLocalBounds();
        registerButtonText.setPosition(
            300 + (200 - textBounds.width) / 2,
            350 + (30 - textBounds.height) / 2
        );
        
        // Configurar botón de enviar registro
        registerSubmitButton.setSize(sf::Vector2f(200, 30));
        registerSubmitButton.setPosition(300, 350);
        registerSubmitButton.setFillColor(sf::Color(50, 200, 50));
        registerSubmitButtonText.setFont(font);
        registerSubmitButtonText.setString("Completar Registro");
        registerSubmitButtonText.setCharacterSize(16);
        registerSubmitButtonText.setFillColor(sf::Color::White);
        // Centrar el texto en el botón
        textBounds = registerSubmitButtonText.getLocalBounds();
        registerSubmitButtonText.setPosition(
            300 + (200 - textBounds.width) / 2,
            350 + (30 - textBounds.height) / 2
        );
        
        // Configurar botón de volver
        backButton.setSize(sf::Vector2f(100, 30));
        backButton.setPosition(50, 50);
        backButton.setFillColor(sf::Color(150, 150, 150));
        backButtonText.setFont(font);
        backButtonText.setString("Volver");
        backButtonText.setCharacterSize(16);
        backButtonText.setFillColor(sf::Color::White);
        // Centrar el texto en el botón
        textBounds = backButtonText.getLocalBounds();
        backButtonText.setPosition(
            50 + (100 - textBounds.width) / 2,
            50 + (30 - textBounds.height) / 2
        );
    
        // Configurar botón de post
        postButton.setSize(sf::Vector2f(100, 30));
        postButton.setPosition(50, 400);
        postButton.setFillColor(sf::Color(50, 150, 250));
        postButtonText.setFont(font);
        postButtonText.setString("Publicar");
        postButtonText.setCharacterSize(16);
        postButtonText.setFillColor(sf::Color::White);
        postButtonText.setPosition(55, 405);
    
        // Configurar botón de logout
        logoutButton.setSize(sf::Vector2f(100, 30));
        logoutButton.setPosition(650, 50);
        logoutButton.setFillColor(sf::Color(250, 50, 50));
        logoutButtonText.setFont(font);
        logoutButtonText.setString("Cerrar Sesion");
        logoutButtonText.setCharacterSize(16);
        logoutButtonText.setFillColor(sf::Color::White);
        logoutButtonText.setPosition(655, 55);
    }

bool GUI::isMouseOverButton(const sf::RectangleShape& button, sf::Vector2i mousePos) {
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void GUI::clearInputStates() {
    isEnteringUsername = false;
    isEnteringPassword = false;
    isEnteringConfirmPassword = false;
    isEnteringPost = false;
}

void GUI::attemptLogin() {
    std::cout << "Intentando login con usuario: '" << currentInputUsername 
              << "' y password: '" << currentInputPassword << "'" << std::endl;
    
    if (!currentInputUsername.empty() && !currentInputPassword.empty()) {
        if (socialNetwork.verifyPassword(currentInputUsername, currentInputPassword)) {
            std::cout << "Verificacion exitosa para " << currentInputUsername << std::endl;
            isLoggedIn = true;
            currentUser = currentInputUsername;
            clearInputStates();
            currentInputUsername.clear();
            currentInputPassword.clear();
            loginFailed = false;
            statusText.setString("");
        } else {
            std::cout << "Verificacion fallida para " << currentInputUsername << std::endl;
            loginFailed = true;
            errorTimer.restart();
            statusText.setString("Credenciales incorrectas");
        }
    } else {
        std::cout << "Usuario o contrasena vacios" << std::endl;
        loginFailed = true;
        errorTimer.restart();
        statusText.setString("Por favor ingrese usuario y contrasena");
    }
}

void GUI::attemptRegister() {
    std::cout << "Intentando registrar usuario: '" << currentInputUsername << "'" << std::endl;
    
    // Validar username
    auto usernameValidation = validateUsername(currentInputUsername);
    if (!usernameValidation.isValid) {
        registrationFailed = true;
        errorTimer.restart();
        statusText.setString(usernameValidation.message);
        return;
    }
    
    // Validar password
    auto passwordValidation = validatePassword(currentInputPassword);
    if (!passwordValidation.isValid) {
        registrationFailed = true;
        errorTimer.restart();
        statusText.setString(passwordValidation.message);
        return;
    }
    
    // Verificar que las contraseñas coincidan
    if (currentInputPassword != currentInputConfirmPassword) {
        registrationFailed = true;
        errorTimer.restart();
        statusText.setString("Las contrasenas no coinciden");
        return;
    }
    
    // Verificar si el usuario ya existe
    if (socialNetwork.userExists(currentInputUsername)) {
        registrationFailed = true;
        errorTimer.restart();
        statusText.setString("El usuario ya existe");
        return;
    }
    
    // Registrar al usuario
    if (socialNetwork.addUser(currentInputUsername, currentInputPassword)) {
        std::cout << "Usuario " << currentInputUsername << " registrado exitosamente" << std::endl;
        
        // Guardar los datos
        try {
            socialNetwork.saveToFile("social_network.json");
            std::cout << "Datos guardados tras registro" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error al guardar tras registro: " << e.what() << std::endl;
        }
        
        isRegistering = false;
        clearInputStates();
        currentInputUsername.clear();
        currentInputPassword.clear();
        currentInputConfirmPassword.clear();
        registrationFailed = false;
        statusText.setString("");
    } else {
        registrationFailed = true;
        errorTimer.restart();
        statusText.setString("Error al registrar usuario");
    }
}

void GUI::handleLoginEvents(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        // Manejar entrada de caracteres
        if (event.text.unicode == '\t') {  // Tab key
            if (isEnteringUsername) {
                isEnteringUsername = false;
                isEnteringPassword = true;
            } else if (isEnteringPassword) {
                isEnteringPassword = false;
                isEnteringUsername = true;
            }
        }
        else if (event.text.unicode == '\r' || event.text.unicode == '\n') {  // Enter key
            attemptLogin();
        }
        else if (event.text.unicode == '\b') {  // Backspace
            if (isEnteringUsername && !currentInputUsername.empty()) {
                currentInputUsername.pop_back();
            }
            else if (isEnteringPassword && !currentInputPassword.empty()) {
                currentInputPassword.pop_back();
            }
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 128) {  // Caracteres ASCII imprimibles
            if (isEnteringUsername) {
                currentInputUsername += static_cast<char>(event.text.unicode);
            }
            else if (isEnteringPassword) {
                currentInputPassword += static_cast<char>(event.text.unicode);
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        // Click en caja de usuario
        sf::FloatRect usernameBounds = inputBox.getGlobalBounds();
        usernameBounds.left = 275;
        usernameBounds.top = 220;
        usernameBounds.width = 250;
        usernameBounds.height = 40;
        
        if (usernameBounds.contains(mousePos.x, mousePos.y)) {
            isEnteringUsername = true;
            isEnteringPassword = false;
            std::cout << "Click en campo de usuario" << std::endl;
        }
        
        // Click en caja de contraseña
        sf::FloatRect passwordBounds = inputBox.getGlobalBounds();
        passwordBounds.left = 275;
        passwordBounds.top = 270;
        passwordBounds.width = 250;
        passwordBounds.height = 40;
        
        if (passwordBounds.contains(mousePos.x, mousePos.y)) {
            isEnteringPassword = true;
            isEnteringUsername = false;
            std::cout << "Click en campo de contraseña" << std::endl;
        }
        
        // Click fuera de las cajas de texto
        if (!usernameBounds.contains(mousePos.x, mousePos.y) && 
            !passwordBounds.contains(mousePos.x, mousePos.y)) {
            // No desactivar la entrada de texto si se hace clic en los botones
            if (!isMouseOverButton(loginButton, mousePos) && 
                !isMouseOverButton(registerButton, mousePos)) {
                isEnteringUsername = false;
                isEnteringPassword = false;
            }
        }
        
        // Click en botones
        if (isMouseOverButton(loginButton, mousePos)) {
            std::cout << "Boton de login presionado" << std::endl;
            attemptLogin();
        }
        else if (isMouseOverButton(registerButton, mousePos)) {
            std::cout << "Boton de registro presionado" << std::endl;
            isRegistering = true;
            clearInputStates();
            currentInputUsername.clear();
            currentInputPassword.clear();
            loginFailed = false;
            statusText.setString("");
        }
    }
}

void GUI::handleRegistrationEvents(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\t') {  // Tab key
            if (isEnteringUsername) {
                isEnteringUsername = false;
                isEnteringPassword = true;
            } else if (isEnteringPassword) {
                isEnteringPassword = false;
                isEnteringConfirmPassword = true;
            } else if (isEnteringConfirmPassword) {
                isEnteringConfirmPassword = false;
                isEnteringUsername = true;
            }
        }
        else if (event.text.unicode == '\r' || event.text.unicode == '\n') {  // Enter key
            // Intentar registro
            attemptRegister();
        }
        else if (event.text.unicode == '\b') {  // Backspace
            if (isEnteringUsername && !currentInputUsername.empty()) {
                currentInputUsername.pop_back();
            }
            else if (isEnteringPassword && !currentInputPassword.empty()) {
                currentInputPassword.pop_back();
            }
            else if (isEnteringConfirmPassword && !currentInputConfirmPassword.empty()) {
                currentInputConfirmPassword.pop_back();
            }
        }
        else if (event.text.unicode >= 32) {  // Cualquier carácter imprimible
            if (isEnteringUsername) {
                currentInputUsername += static_cast<char>(event.text.unicode);
            }
            else if (isEnteringPassword) {
                currentInputPassword += static_cast<char>(event.text.unicode);
            }
            else if (isEnteringConfirmPassword) {
                currentInputConfirmPassword += static_cast<char>(event.text.unicode);
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        // Click en caja de usuario
        sf::FloatRect usernameBounds(300, 150, 200, 30);
        if (usernameBounds.contains(mousePos.x, mousePos.y)) {
            isEnteringUsername = true;
            isEnteringPassword = false;
            isEnteringConfirmPassword = false;
        }
        
        // Click en caja de contraseña
        sf::FloatRect passwordBounds(300, 200, 200, 30);
        if (passwordBounds.contains(mousePos.x, mousePos.y)) {
            isEnteringUsername = false;
            isEnteringPassword = true;
            isEnteringConfirmPassword = false;
        }
        
        // Click en caja de confirmar contraseña
        sf::FloatRect confirmBounds(300, 250, 200, 30);
        if (confirmBounds.contains(mousePos.x, mousePos.y)) {
            isEnteringUsername = false;
            isEnteringPassword = false;
            isEnteringConfirmPassword = true;
        }
        
        // Click en botón de registro
        if (isMouseOverButton(registerSubmitButton, mousePos)) {
            std::cout << "Botón de completar registro presionado" << std::endl;
            attemptRegister();
        }
        
        // Click en botón de volver
        if (isMouseOverButton(backButton, mousePos)) {
            std::cout << "Botón de volver presionado" << std::endl;
            isRegistering = false;
            clearInputStates();
            currentInputUsername.clear();
            currentInputPassword.clear();
            currentInputConfirmPassword.clear();
            registrationFailed = false;
            statusText.setString("");
        }
    }
}

void GUI::handleMainScreenEvents(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\r' || event.text.unicode == '\n') {  // Enter key
            if (isEnteringPost && !currentInputPost.empty()) {
                auto postValidation = validatePost(currentInputPost);
                if (postValidation.isValid) {
                    socialNetwork.addPost(currentUser, currentInputPost);
                    currentInputPost.clear();
                    isEnteringPost = false;
                    statusText.setString("");
                } else {
                    statusText.setString(postValidation.message);
                    errorTimer.restart();
                }
            }
        }
        else if (event.text.unicode == '\b') {  // Backspace
            if (isEnteringPost && !currentInputPost.empty()) {
                currentInputPost.pop_back();
            }
        }
        else if (event.text.unicode < 1024) {  // Caracteres válidos
            if (isEnteringPost) {
                if (currentInputPost.length() < MAX_POST_LENGTH) {
                    currentInputPost += static_cast<char>(event.text.unicode);
                } else {
                    statusText.setString("Has alcanzado el limite de caracteres");
                    errorTimer.restart();
                }
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        // Click en botón de post
        if (isMouseOverButton(postButton, mousePos)) {
            if (!isEnteringPost) {
                isEnteringPost = true;
                currentInputPost.clear();
                statusText.setString("");
            } else {
                auto postValidation = validatePost(currentInputPost);
                if (postValidation.isValid) {
                    socialNetwork.addPost(currentUser, currentInputPost);
                    currentInputPost.clear();
                    isEnteringPost = false;
                    statusText.setString("");
                } else {
                    statusText.setString(postValidation.message);
                    errorTimer.restart();
                }
            }
        }
        
        // Click en botón de logout
        if (isMouseOverButton(logoutButton, mousePos)) {
            isLoggedIn = false;
            currentUser.clear();
            clearInputStates();
            // Guardar al cerrar sesión
            try {
                socialNetwork.saveToFile("social_network.json");
                std::cout << "Datos guardados al cerrar sesion" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error al guardar al cerrar sesion: " << e.what() << std::endl;
                statusText.setString("Error al guardar los datos");
                errorTimer.restart();
            }
        }
        
        // Click en lista de amigos
        auto friends = socialNetwork.getUserFriends(currentUser);
        float yPos = 150;
        for (const auto& friend_name : friends) {
            sf::FloatRect friendBounds(500, yPos, 200, 30);
            if (friendBounds.contains(mousePos.x, mousePos.y)) {
                // Aquí se podría implementar la funcionalidad de ver perfil de amigo
                std::cout << "Click en amigo: " << friend_name << std::endl;
            }
            yPos += 50;  // Mismo espaciado que en drawFriendCard
        }
        
        // Click fuera del área de post cancela la entrada
        if (isEnteringPost) {
            sf::FloatRect postArea(40, 150, 400, 60);
            if (!postArea.contains(mousePos.x, mousePos.y) && 
                !isMouseOverButton(postButton, mousePos)) {
                isEnteringPost = false;
                if (currentInputPost.empty()) {
                    statusText.setString("");
                }
            }
        }
    }
}

void GUI::drawLoginScreen() {
    window.clear(BACKGROUND_COLOR);
    
    // Título principal
    titleText.setString("Red Social");
    titleText.setCharacterSize(32);
    titleText.setFillColor(TEXT_COLOR);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition((800 - titleBounds.width) / 2, 50);
    window.draw(titleText);
    
    // Card de login
    createCardBackground(250, 150, 300, 300);
    window.draw(cardBackground);
    
    // Subtítulo
    titleText.setString("Iniciar Sesion");
    titleText.setCharacterSize(24);
    titleBounds = titleText.getLocalBounds();
    titleText.setPosition((800 - titleBounds.width) / 2, 170);
    window.draw(titleText);
    
    // Campos de entrada
    inputBox.setSize(sf::Vector2f(250, 40));
    inputBox.setFillColor(INPUT_BACKGROUND);
    inputBox.setOutlineColor(sf::Color(100, 100, 100));
    inputBox.setOutlineThickness(1);
    
    // Campo de usuario
    inputBox.setPosition(275, 220);
    if (isEnteringUsername) {
        inputBox.setOutlineColor(PRIMARY_COLOR);
    } else {
        inputBox.setOutlineColor(sf::Color(100, 100, 100));
    }
    window.draw(inputBox);
    
    inputText.setFillColor(TEXT_COLOR);
    if (currentInputUsername.empty() && !isEnteringUsername) {
        inputText.setString("Usuario");
        inputText.setFillColor(sf::Color(150, 150, 150)); // Color más claro para placeholder
    } else {
        inputText.setString(currentInputUsername);
        inputText.setFillColor(TEXT_COLOR);
    }
    inputText.setPosition(285, 230);
    window.draw(inputText);
    
    // Campo de contraseña
    inputBox.setPosition(275, 270);
    if (isEnteringPassword) {
        inputBox.setOutlineColor(PRIMARY_COLOR);
    } else {
        inputBox.setOutlineColor(sf::Color(100, 100, 100));
    }
    window.draw(inputBox);
    
    if (currentInputPassword.empty() && !isEnteringPassword) {
        inputText.setString("Contrasena");
        inputText.setFillColor(sf::Color(150, 150, 150)); // Color más claro para placeholder
    } else {
        inputText.setString(std::string(currentInputPassword.length(), '*'));
        inputText.setFillColor(TEXT_COLOR);
    }
    inputText.setPosition(285, 280);
    window.draw(inputText);
    
    // Botones
    loginButton.setPosition(275, 330);
    loginButton.setSize(sf::Vector2f(250, 40));
    registerButton.setPosition(275, 380);
    registerButton.setSize(sf::Vector2f(250, 40));
    
    styleButton(loginButton, loginButtonText, "Iniciar Sesion");
    styleButton(registerButton, registerButtonText, "Registrarse");
    
    // Efectos hover
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (isMouseOverButton(loginButton, mousePos)) {
        loginButton.setFillColor(BUTTON_HOVER_COLOR);
    }
    if (isMouseOverButton(registerButton, mousePos)) {
        registerButton.setFillColor(BUTTON_HOVER_COLOR);
    }
    
    window.draw(loginButton);
    window.draw(loginButtonText);
    window.draw(registerButton);
    window.draw(registerButtonText);
    
    // Mensaje de error
    if (loginFailed && errorTimer.getElapsedTime().asSeconds() < 3.0) {
        statusText.setFillColor(sf::Color::Red);
        sf::FloatRect errorBounds = statusText.getLocalBounds();
        statusText.setPosition((800 - errorBounds.width) / 2, 430);
        window.draw(statusText);
    }
    
    window.display();
}

ValidationResult GUI::validateUsername(const std::string& username) {
    // Verificar longitud
    if (username.length() < MIN_USERNAME_LENGTH) {
        return ValidationResult(false, "El usuario debe tener al menos " + 
                              std::to_string(MIN_USERNAME_LENGTH) + " caracteres");
    }
    if (username.length() > MAX_USERNAME_LENGTH) {
        return ValidationResult(false, "El usuario no puede exceder " + 
                              std::to_string(MAX_USERNAME_LENGTH) + " caracteres");
    }

    // Verificar caracteres válidos
    if (containsInvalidChars(username)) {
        return ValidationResult(false, "El usuario solo puede contener letras, numeros y guiones bajos");
    }

    // Verificar que el primer carácter sea una letra
    if (!std::isalpha(username[0])) {
        return ValidationResult(false, "El usuario debe comenzar con una letra");
    }

    return ValidationResult(true, "");
}

ValidationResult GUI::validatePassword(const std::string& password) {
    // Verificar longitud
    if (password.length() < MIN_PASSWORD_LENGTH) {
        return ValidationResult(false, "La contrasena debe tener al menos " + 
                              std::to_string(MIN_PASSWORD_LENGTH) + " caracteres");
    }
    if (password.length() > MAX_PASSWORD_LENGTH) {
        return ValidationResult(false, "La contrasena no puede exceder " + 
                              std::to_string(MAX_PASSWORD_LENGTH) + " caracteres");
    }

    // Verificar complejidad
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    const std::string specialChars = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    for (char c : password) {
        if (std::isupper(c)) hasUpper = true;
        else if (std::islower(c)) hasLower = true;
        else if (std::isdigit(c)) hasDigit = true;
        else if (specialChars.find(c) != std::string::npos) hasSpecial = true;
    }

    std::string requirements;
    if (!hasUpper) requirements += "- Debe contener al menos una mayuscula\n";
    if (!hasLower) requirements += "- Debe contener al menos una minuscula\n";
    if (!hasDigit) requirements += "- Debe contener al menos un numero\n";
    if (!hasSpecial) requirements += "- Debe contener al menos un caracter especial\n";

    if (!requirements.empty()) {
        return ValidationResult(false, "La contraseña debe cumplir los siguientes requisitos:\n" + requirements);
    }

    return ValidationResult(true, "");
}

ValidationResult GUI::validatePost(const std::string& post) {
    // Verificar longitud
    if (post.empty()) {
        return ValidationResult(false, "La publicacion no puede estar vacia");
    }
    if (post.length() > MAX_POST_LENGTH) {
        return ValidationResult(false, "La publicacion no puede exceder " + 
                              std::to_string(MAX_POST_LENGTH) + " caracteres");
    }

    // Verificar contenido inapropiado (ejemplo básico)
    std::vector<std::string> inappropriateWords = {"palabrota1", "palabrota2", "palabrota3"};
    for (const auto& word : inappropriateWords) {
        if (post.find(word) != std::string::npos) {
            return ValidationResult(false, "La publicacion contiene contenido inapropiado");
        }
    }

    return ValidationResult(true, "");
}

bool GUI::containsInvalidChars(const std::string& str) {
    return std::any_of(str.begin(), str.end(), [](char c) {
        return !(std::isalnum(c) || c == '_');
    });
}

void GUI::drawRegistrationScreen() {
    window.clear(sf::Color(100, 150, 200));
    
    titleText.setString("Registro de Usuario");
    titleText.setPosition(300, 80);
    window.draw(titleText);
    
    // Botón de volver
    window.draw(backButton);
    window.draw(backButtonText);
    
    // Caja de usuario
    inputBox.setPosition(300, 150);
    window.draw(inputBox);
    
    // Texto de usuario
    inputText.setString(currentInputUsername.empty() && !isEnteringUsername ? "Usuario" : currentInputUsername);
    inputText.setPosition(310, 155);
    window.draw(inputText);
    
    // Caja de contraseña
    inputBox.setPosition(300, 200);
    window.draw(inputBox);
    
    // Texto de contraseña (mostrar asteriscos)
    std::string passwordDisplay;
    if (currentInputPassword.empty() && !isEnteringPassword) {
        passwordDisplay = "Contrasena";
    } else {
        passwordDisplay = std::string(currentInputPassword.length(), '*');
    }
    inputText.setString(passwordDisplay);
    inputText.setPosition(310, 205);
    window.draw(inputText);
    
    // Caja de confirmar contraseña
    inputBox.setPosition(300, 250);
    window.draw(inputBox);
    
    // Texto de confirmar contraseña (mostrar asteriscos)
    std::string confirmDisplay;
    if (currentInputConfirmPassword.empty() && !isEnteringConfirmPassword) {
        confirmDisplay = "Confirmar Contrasena";
    } else {
        confirmDisplay = std::string(currentInputConfirmPassword.length(), '*');
    }
    inputText.setString(confirmDisplay);
    inputText.setPosition(310, 255);
    window.draw(inputText);
    
    // Botón de completar registro
    window.draw(registerSubmitButton);
    window.draw(registerSubmitButtonText);
    
    // Mostrar mensajes de error si corresponde
    if (registrationFailed) {
        if (errorTimer.getElapsedTime().asSeconds() < 3.0) {
            window.draw(statusText);
        } else {
            registrationFailed = false;
            statusText.setString("");
        }
    }
    
    window.display();
}

void GUI::drawMainScreen() {
    window.clear(BACKGROUND_COLOR);
    
    // Header
    sf::RectangleShape header;
    header.setSize(sf::Vector2f(800, 80));
    header.setFillColor(PRIMARY_COLOR);
    window.draw(header);
    
    // Título de bienvenida
    titleText.setString("Bienvenido " + currentUser);
    titleText.setCharacterSize(24);
    titleText.setFillColor(TEXT_COLOR);
    titleText.setPosition(20, 25);
    window.draw(titleText);
    
    // Botón de logout
    logoutButton.setPosition(650, 20);
    logoutButton.setSize(sf::Vector2f(120, 40));
    styleButton(logoutButton, logoutButtonText, "Cerrar Sesion");
    window.draw(logoutButton);
    window.draw(logoutButtonText);
    
    // Área de publicaciones
    createCardBackground(20, 100, 440, 480);
    window.draw(cardBackground);
    
    titleText.setString("Publicaciones");
    titleText.setPosition(30, 110);
    window.draw(titleText);
    
    // Área de entrada de nuevo post
    if (isEnteringPost) {
        sf::RectangleShape postInput;
        postInput.setSize(sf::Vector2f(400, 60));
        postInput.setPosition(40, 150);
        postInput.setFillColor(INPUT_BACKGROUND);
        postInput.setOutlineThickness(1);
        postInput.setOutlineColor(sf::Color(100, 100, 100));
        window.draw(postInput);
        
        inputText.setString(currentInputPost);
        inputText.setPosition(50, 160);
        inputText.setFillColor(TEXT_COLOR);
        window.draw(inputText);
    }
    
    // Botón de post
    postButton.setPosition(40, 220);
    postButton.setSize(sf::Vector2f(120, 40));
    styleButton(postButton, postButtonText, "Publicar");
    window.draw(postButton);
    window.draw(postButtonText);
    
    // Lista de posts
    float postsYPos = 280;
    auto posts = socialNetwork.getUserPosts(currentUser);
    for (const auto& post : posts) {
        drawPostCard(post, postsYPos);
    }
    
    // Área de amigos
    createCardBackground(480, 100, 300, 480);
    window.draw(cardBackground);
    
    titleText.setString("Amigos");
    titleText.setPosition(490, 110);
    window.draw(titleText);
    
    // Lista de amigos
    float friendsYPos = 150;
    auto friends = socialNetwork.getUserFriends(currentUser);
    for (const auto& friend_name : friends) {
        drawFriendCard(friend_name, friendsYPos);
    }
    
    window.display();
}

void GUI::drawPostScreen() {
    auto posts = socialNetwork.getUserPosts(currentUser);
    float yPos = 150;
    
    titleText.setString("Publicaciones");
    titleText.setPosition(50, 100);
    window.draw(titleText);
    
    for (const auto& post : posts) {
        inputText.setString(post);
        inputText.setPosition(50, yPos);
        window.draw(inputText);
        yPos += 30;
    }
}

void GUI::drawFriendsList() {
    auto friends = socialNetwork.getUserFriends(currentUser);
    float yPos = 150;
    
    titleText.setString("Amigos");
    titleText.setPosition(500, 100);
    window.draw(titleText);
    
    for (const auto& friend_name : friends) {
        inputText.setString(friend_name);
        inputText.setPosition(500, yPos);
        window.draw(inputText);
        yPos += 30;
    }
}

void GUI::styleButton(sf::RectangleShape& button, sf::Text& text, const std::string& buttonText) {
    button.setFillColor(PRIMARY_COLOR);
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color(100, 100, 100));
    
    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(16);
    text.setFillColor(TEXT_COLOR);
    
    // Centrar texto
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    text.setPosition(
        buttonBounds.left + (buttonBounds.width - textBounds.width) / 2,
        buttonBounds.top + (buttonBounds.height - textBounds.height) / 2
    );
}

void GUI::createCardBackground(float x, float y, float width, float height) {
    cardBackground.setSize(sf::Vector2f(width, height));
    cardBackground.setPosition(x, y);
    cardBackground.setFillColor(INPUT_BACKGROUND);
    cardBackground.setOutlineThickness(1);
    cardBackground.setOutlineColor(sf::Color(100, 100, 100));
}

void GUI::drawPostCard(const std::string& post, float& yPos) {
    sf::RectangleShape postCard;
    postCard.setSize(sf::Vector2f(380, 80));
    postCard.setPosition(50, yPos);
    postCard.setFillColor(INPUT_BACKGROUND);
    postCard.setOutlineThickness(1);
    postCard.setOutlineColor(sf::Color(100, 100, 100));
    
    window.draw(postCard);
    
    inputText.setString(post);
    inputText.setPosition(60, yPos + 10);
    inputText.setFillColor(TEXT_COLOR);
    window.draw(inputText);
    
    yPos += 90; // Espacio entre posts
}

void GUI::drawFriendCard(const std::string& friendName, float& yPos) {
    sf::RectangleShape friendCard;
    friendCard.setSize(sf::Vector2f(200, 40));
    friendCard.setPosition(500, yPos);
    friendCard.setFillColor(INPUT_BACKGROUND);
    friendCard.setOutlineThickness(1);
    friendCard.setOutlineColor(sf::Color(100, 100, 100));
    
    window.draw(friendCard);
    
    inputText.setString(friendName);
    inputText.setPosition(510, yPos + 10);
    inputText.setFillColor(TEXT_COLOR);
    window.draw(inputText);
    
    yPos += 50; // Espacio entre amigos
}

void GUI::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Guardar antes de cerrar
                try {
                    socialNetwork.saveToFile("social_network.json");
                    std::cout << "Datos guardados al cerrar la ventana" << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Error al guardar al cerrar: " << e.what() << std::endl;
                }
                window.close();
            }
            
            if (!isLoggedIn) {
                if (isRegistering) {
                    handleRegistrationEvents(event);
                } else {
                    handleLoginEvents(event);
                }
            }
            else {
                handleMainScreenEvents(event);
            }
        }
        
        if (!isLoggedIn) {
            if (isRegistering) {
                drawRegistrationScreen();
            } else {
                drawLoginScreen();
            }
        }
        else {
            drawMainScreen();
        }
    }
}