/**
* GameObject class
* Basically just a container
*/
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <list>

class GameEngine;

class GameObject: public sf::Transformable, public sf::Drawable
{
public:
    friend class GameEngine;
    typedef std::unique_ptr<GameObject> GameObjectPtr;
    GameObject();
    virtual void init(){};
    virtual void onUpdate(int dt){};
    virtual void onDraw(sf::RenderTarget& ctx/*, sf::RenderStates states*/) const{};
    //void addHitbox(AbstractHitbox h);
    void addChild(GameObjectPtr o);
    void removeChild();
    void forEachChild(std::function<void()>& lambda);
    void setGame(GameEngine* g){ game = g; };
protected:
    GameObject* parent;
    GameEngine* game;
    std::list<GameObjectPtr> children;
    //std::list<AbstractHitbox> hitboxes;
    void update(int dt);
    void updateHitboxes(); // recalculate relative hitbox positions
    //void drawHitboxes(sf::RenderWindow* ctx);
    void setParent(GameObject* o);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#include "engine/Game.hpp"

#endif