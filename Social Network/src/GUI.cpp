#include "GUI.h"
#include <iostream>

GUI::GUI(SocialGraph& network)
    :window(sf::VideoMode(800,600), "Red Social"),
    socialNetwork(network),
    isLoggedIn(false),
    isRegistering(false),
    isEnteringUsername(false),
    isEnteringPassword(false),
    isEnteringConfirmPassword(false),
    isEnteringPost(false),
    loginFailed(false),
    registrationFailed(false){
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
            std::cout << "Verificación exitosa para " << currentInputUsername << std::endl;
            isLoggedIn = true;
            currentUser = currentInputUsername;
            clearInputStates();
            currentInputUsername.clear();
            currentInputPassword.clear();
            loginFailed = false;
            statusText.setString("");
        } else {
            std::cout << "Verificación fallida para " << currentInputUsername << std::endl;
            loginFailed = true;
            errorTimer.restart();
            statusText.setString("Credenciales incorrectas");
        }
    } else {
        std::cout << "Usuario o contraseña vacíos" << std::endl;
        loginFailed = true;
        errorTimer.restart();
        statusText.setString("Por favor ingrese usuario y contrasena");
    }
}

void GUI::attemptRegister() {
    std::cout << "Intentando registrar usuario: '" << currentInputUsername << "'" << std::endl;
    
    if (currentInputUsername.empty() || currentInputPassword.empty() || currentInputConfirmPassword.empty()) {
        registrationFailed = true;
        errorTimer.restart();
        statusText.setString("Todos los campos son obligatorios");
        return;
    }
    
    if (currentInputPassword != currentInputConfirmPassword) {
        registrationFailed = true;
        errorTimer.restart();
        statusText.setString("Las contrasenas no coinciden");
        return;
    }
    
    if (socialNetwork.userExists(currentInputUsername)) {
        registrationFailed = true;
        errorTimer.restart();
        statusText.setString("El usuario ya existe");
        return;
    }
    
    // Registrar al usuario
    if (socialNetwork.addUser(currentInputUsername, currentInputPassword)) {
        std::cout << "Usuario " << currentInputUsername << " registrado exitosamente" << std::endl;
        
        // Guardar los datos de inmediato
        try {
            socialNetwork.saveToFile("social_network.json");
            std::cout << "Datos guardados tras registro" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error al guardar tras registro: " << e.what() << std::endl;
        }
        
        // Volver a pantalla de login
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
            // Intentar login
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
        else if (event.text.unicode >= 32) {  // Cualquier carácter imprimible
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
        sf::FloatRect usernameBounds(300, 200, 200, 30);
        if (usernameBounds.contains(mousePos.x, mousePos.y)) {
            isEnteringUsername = true;
            isEnteringPassword = false;
        }
        
        // Click en caja de contraseña
        sf::FloatRect passwordBounds(300, 250, 200, 30);
        if (passwordBounds.contains(mousePos.x, mousePos.y)) {
            isEnteringPassword = true;
            isEnteringUsername = false;
        }
        
        // Click en botón de login
        if (isMouseOverButton(loginButton, mousePos)) {
            std::cout << "Botón de login presionado" << std::endl;
            attemptLogin();
        }
        
        // Click en botón de registro
        if (isMouseOverButton(registerButton, mousePos)) {
            std::cout << "Botón de registro presionado" << std::endl;
            isRegistering = true;
            clearInputStates();
            currentInputUsername.clear();
            currentInputPassword.clear();
            currentInputConfirmPassword.clear();
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
                socialNetwork.addPost(currentUser, currentInputPost);
                currentInputPost.clear();
                isEnteringPost = false;
            }
        }
        else if (event.text.unicode == '\b') {  // Backspace
            if (isEnteringPost && !currentInputPost.empty()) {
                currentInputPost.pop_back();
            }
        }
        else if (event.text.unicode < 1024) {  // Caracteres ASCII
            if (isEnteringPost) {
                currentInputPost += static_cast<char>(event.text.unicode);
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        // Click en botón de post
        if (isMouseOverButton(postButton, mousePos)) {
            isEnteringPost = !isEnteringPost;
        }
        
        // Click en botón de logout
        if (isMouseOverButton(logoutButton, mousePos)) {
            isLoggedIn = false;
            currentUser.clear();
            clearInputStates();
            // Guardar al cerrar sesión
            try {
                socialNetwork.saveToFile("social_network.json");
                std::cout << "Datos guardados al cerrar sesión" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error al guardar al cerrar sesión: " << e.what() << std::endl;
            }
        }
        
        // Click en lista de amigos
        auto friends = socialNetwork.getUserFriends(currentUser);
        float yPos = 150;
        for (const auto& friend_name : friends) {
            sf::FloatRect friendBounds(500, yPos, 200, 30);
            if (friendBounds.contains(mousePos.x, mousePos.y)) {
                // Mostrar perfil del amigo o realizar alguna acción
                // Por ejemplo, podríamos cambiar a una vista del perfil del amigo
            }
            yPos += 30;
        }
    }
}

void GUI::drawLoginScreen() {
    window.clear(sf::Color(100, 100, 200));
    
    titleText.setString("Iniciar Sesion");
    titleText.setPosition(300, 100);
    window.draw(titleText);
    
    // Caja de usuario
    inputBox.setPosition(300, 200);
    window.draw(inputBox);
    
    // Texto de usuario
    inputText.setString(currentInputUsername.empty() && !isEnteringUsername ? "Usuario" : currentInputUsername);
    inputText.setPosition(310, 205);
    window.draw(inputText);
    
    // Caja de contraseña
    inputBox.setPosition(300, 250);
    window.draw(inputBox);
    
    // Texto de contraseña (mostrar asteriscos)
    std::string passwordDisplay;
    if (currentInputPassword.empty() && !isEnteringPassword) {
        passwordDisplay = "Contrasena";
    } else {
        passwordDisplay = std::string(currentInputPassword.length(), '*');
    }
    inputText.setString(passwordDisplay);
    inputText.setPosition(310, 255);
    window.draw(inputText);
    
    // Botón de login
    window.draw(loginButton);
    window.draw(loginButtonText);
    
    // Botón de registro
    window.draw(registerButton);
    window.draw(registerButtonText);
    
    // Mostrar mensajes de error si corresponde
    if (loginFailed) {
        if (errorTimer.getElapsedTime().asSeconds() < 3.0) {
            window.draw(statusText);
        } else {
            loginFailed = false;
            statusText.setString("");
        }
    }
    
    window.display();
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
    window.clear(sf::Color(100, 100, 200));
    
    titleText.setString("Bienvenido " + currentUser);
    titleText.setPosition(300, 50);
    window.draw(titleText);
    
    // Área de nuevo post
    if (isEnteringPost) {
        inputBox.setSize(sf::Vector2f(400, 60));
        inputBox.setPosition(50, 300);
        window.draw(inputBox);
        
        inputText.setString(currentInputPost);
        inputText.setPosition(60, 305);
        window.draw(inputText);
    }
    
    // Botones
    window.draw(postButton);
    window.draw(postButtonText);
    window.draw(logoutButton);
    window.draw(logoutButtonText);
    
    drawPostScreen();
    drawFriendsList();
    
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