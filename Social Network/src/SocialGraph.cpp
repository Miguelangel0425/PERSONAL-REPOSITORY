#include "SocialGraph.h"
#include <openssl/sha.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <iomanip>
#include <iostream>

using json = nlohmann::json;

std::string hashPassword(const std::string &password){
    unsigned char hash[SHA256_DIGEST_LENGTH];//tamaño del hash
    SHA256_CTX sha256;//estructura de datos para el hash
    SHA256_Init(&sha256);//inicializar la estructura
    SHA256_Update(&sha256, password.c_str(), password.length());//actualizar la estructura con la contraseña
    SHA256_Final(hash, &sha256);//finalizar la estructura y guardar el hash en hash

    std::stringstream ss;

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
       ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);//convertir en hash en un string
    }
    return ss.str();
}

bool SocialGraph::addUser(const std::string& username, const std::string& password) {//Agregar usuario
    if (users.find(username) != users.end()) {//Si el usuario ya existe
        return false;
    }
    std::string hashedPass = hashPassword(password);
    std::cout << "Creando usuario: '" << username << "' con hash: " << hashedPass << std::endl;
    users.emplace(username, User(username, hashedPass));//Agregar usuario
    return true;
}

bool SocialGraph::addConnection(const std::string& user1, const std::string& user2){
    if(users.find(user1) == users.end() || users.find(user2) == users.end()){
        return false;
    }
    users.at(user1).addFriend(user2);
    users.at(user2).addFriend(user1);
    return true;    
}

bool SocialGraph::addPost(const std::string& username, const std::string& post){
    if(users.find(username) == users.end()){
        return false;
    }
    users.at(username).addPost(post);
    return true;
}

bool SocialGraph::userExists(const std::string& username) const{//Verificar si el usuario existe
    return users.find(username) != users.end();//Si el usuario existe
}

bool SocialGraph::verifyPassword(const std::string& username, const std::string& password) const{//Verificar contraseña
    if(!userExists(username)){
        std::cout << "Usuario no existe: " << username << std::endl;
        return false;
    }
    std::string inputHash = hashPassword(password);
    std::string storedHash = users.at(username).getHashedPassword();
    std::cout << "Verificando:\nHash ingresado: " << inputHash << "\nHash almacenado: " << storedHash << std::endl;
    return storedHash == inputHash;
}

const std::string SocialGraph::getUserHashedPassword(const std::string& username) const {
    if (!userExists(username)) {
        return "";
    }
    return users.at(username).getHashedPassword();
}

std::vector<std::string> SocialGraph::getUserPosts(const std::string& username) const {//Obtener los posts de un usuario
    if (!userExists(username)) {
        return {};
    }
    return users.at(username).getPosts();
}

std::vector<std::string> SocialGraph::getUserFriends(const std::string& username) const {//Obtener los amigos de un usuario
    if (!userExists(username)) {
        return {};
    }
    return users.at(username).getFriends();
}

void SocialGraph::saveToFile(const std::string& filename) const {//Guardar en un archivo
    json j;
    for (const auto& [username, user] : users) {
        j[username] = {
            {"password", user.getHashedPassword()},
            {"posts", user.getPosts()},
            {"friends", user.getFriends()}
        };
    }
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << filename << " para escritura" << std::endl;
        return;
    }
    file << std::setw(4) << j << std::endl;
    std::cout << "Guardado exitoso en " << filename << std::endl;
}

void SocialGraph::loadFromFile(const std::string& filename) { // Cargar de un archivo
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << filename << " para lectura" << std::endl;
        return;
    }
    
    json j;
    file >> j;
    
    users.clear();
    for (const auto& [username, data] : j.items()) {
        users.emplace(username, User(username, data["password"]));
        for (const auto& post : data["posts"]) {
            users.at(username).addPost(post);
        }
        for (const auto& friend_name : data["friends"]) {
            users.at(username).addFriend(friend_name);
        }
    }
    std::cout << "Carga exitosa desde " << filename << std::endl;
}