#include <SFML/Graphics.hpp>

class Hitbox: public sf::Rect // or maybe sf::RectangleShape for drawing capabilities
{
public:
    virtual ~AbstractHitbox(){};
    virtual bool check(AbstractHitbox b) = 0;
protected:
};