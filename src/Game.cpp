#include <iostream>
#include "engine/Game.hpp"

// Initiates the render for all children
void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    this->onDraw(target/*, states*/);
    // if no view, push global view
    for(auto v = this->views.begin(); v!= this->views.end(); v++){
        target.setView(**v);
        for(auto a = this->children.begin(); a != this->children.end(); a++){
            target.draw(**a, states);
        }
    }
}

void GameEngine::start()
{
    // initialize game
    this->init();
    // create window
    window.create(sf::VideoMode(800, 600), this->name, sf::Style::Titlebar | sf::Style::Close);
    // main game loop
    this->running = true;
    while(window.isOpen())
    {
        this->handleEvents();
        this->update(0);
        this->draw();
    }
    this->running = false;
}

void GameEngine::update(int dt)
{
    if(this->currScene)
    {
        this->currScene->update(dt);
    }
}

void GameEngine::draw()
{
    window.clear(sf::Color::Black);
    if(this->currScene)
    {
        window.draw(*(this->currScene));
    }
    window.display();
}

void GameEngine::changeGameScene(std::unique_ptr<GameScene> s)
{
    bool canChange = true;
    if(this->currScene)
    {
        bool canChange = this->currScene->onExit();
    }
    if(canChange)
    {
        this->currScene = std::move(s);
        if(this->currScene)
        {
            this->currScene->setGame(this);
            this->currScene->init();
        }
    }
}

void GameEngine::handleEvents()
{
    //mousePos = sf::Mouse::getPosition(window);
    // process events
    // TODO: Move to another function
    sf::Event Event;
    while(window.pollEvent(Event))
    {
        switch(Event.type)
        {
            case sf::Event::Closed:
                this->exit();
                break;
            //case sf::Event::MouseButtonReleased:
                //this->ebus.postEvent(BasicEvent("MOUSEUP", mousePos.x, mousePos.y));
            //    break;
        }
    }

    // notify of all events that took place last frame
    //ebus.notify();
}
/**
* Gives you a chance to prevent the game from exiting and/or do
* some cleanup before the window closes
*/
void GameEngine::exit()
{
    bool canExit = this->onExit();
    if(canExit)
    {
        this->window.close();
    }
}