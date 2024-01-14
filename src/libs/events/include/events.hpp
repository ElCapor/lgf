#pragma once
#ifndef EVENTS_HPP
#define EVENTS_HPP
#include <unordered_set>
#include <vector>
/*
https://www.linkedin.com/pulse/students-take-implementing-event-systems-games-using-matthew-rosen

Took the headers and implenting all the functions by myself - elcapor
*/

/*
SINGLETON Implementation
*/
template <typename T>
class Singleton {
public:
    static T& getInstance() {
        static T instance; // This will be created only once
        return instance;
    }

    // Delete copy constructor and assignment operator to prevent duplication
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() = default;
    virtual ~Singleton() = default;
};



template<typename T>
using UniqueContainer = std::unordered_set<T>;


enum EventType
{
  e_GameStartEvent = 0,

  e_EventTypeMax
};

class Event
{
public:
  explicit Event(EventType type) : m_type(type) {}
  EventType m_type;
};

class EventListener
{
public:
  virtual void OnEvent(Event *received) = 0;
  void Subscribe(EventType type);
  void Unsubscribe(EventType type);
  void UnsubscribeAll();

  virtual ~EventListener() { UnsubscribeAll(); }


private:
  UniqueContainer<EventType> m_subscribeList;
};


// assume singleton<T> exists

template<typename T>
using UniqueContainer = std::unordered_set<T>;
class EventManager : public Singleton<EventManager>
{
public:
  void Init();
  void Update();
  void Exit();

  void RemoveListener(EventListener *listener);
  void SendEvent(Event *sent);

  // future functionality:// void QueueEvent(Event *sent, float delay = 0.0f);  

private:
  friend class EventListener;
  void Subscribe(EventType type, EventListener *listener);
  void Unsubscribe(EventType type, EventListener *listener);

  std::vector<UniqueContainer<EventListener*>> m_listeners;
};

#endif