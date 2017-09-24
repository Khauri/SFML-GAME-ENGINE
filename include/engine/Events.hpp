#ifndef EVENTSMANAGER_HPP
#define EVENTSMANAGER_HPP

class BasicEvent
{
public:
    std::unique_ptr<GameObject> get
private:
    std::unique_ptr<GameObject> target;
};

class EventListener
{
    public:
        virtual void onEvent(BasicEvent e) = 0;
};

// publish/subscribe 
class EventManager
{
public:
    enum EVENT_TYPE {KEYDOWN, KEYUP, MOUSEDOWN};
    void addEventListener();
private:
    std::vector<std::shared_ptr<EventHandler>> key_pressed;
};

#endif