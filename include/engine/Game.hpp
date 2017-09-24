#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "engine/GameObject.hpp"
// Basically the game states
class GameScene: public GameObject 
{
public:
    virtual void init(){};
    virtual bool onExit() { return true; };
    void addView(sf::View* v){ this->views.push_back(v); };
    std::string sceneID;
protected:
    sf::View view;
    std::vector<sf::View*> views;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
// Basically a state manager
class GameEngine
{
public:
    void start();
    void stop(); // pause
    void exit(); // exit the game
    void update(int dt);
    void draw();
    void changeGameScene(std::unique_ptr<GameScene> s);
    void setDebugMode(bool m){ isDebugMode = m; };
    //void pushGameScene(std::unique_ptr<GameScene> s);
    //void popGameScene(std::unique_ptr<GameScene> s);
    bool isRunning(){ return running; };
    sf::RenderWindow* getContext(){ return &window; };
private:
    bool running;
    bool isDebugMode = false;
    sf::RenderWindow window;
    std::string name = "New_Game";
    //std::vector<std::unique_ptr<GameScene>> scenes; // scene stack
    std::unique_ptr<GameScene> currScene;
    virtual void init(){}; // aka onStart
    //virtual void onStop(){};
    //virtual void onResume(){};
    virtual void onUpdate(int dt){};
    virtual bool onExit(){ return true; };
    void handleEvents();
    virtual void onEvent(){};

};

#endif