#pragma once 
#include <SFML/Graphics.hpp>

class ResourceManager {
    private:
        std::map<std::string, sf::Font> fonts;
        std::map<std::string, sf::Texture> textures;
        
    public:
        static ResourceManager& getInstance();
        sf::Font& getFont(const std::string& name);
        sf::Texture& getTexture(const std::string& name);
        bool loadFont(const std::string& name, const std::string& filename);
        bool loadTexture(const std::string& name, const std::string& filename);
    };