#pragma once
#ifndef EVENTS_HPP
#define EVENTS_HPP

class Event
{
public:
  virtual~ Event();

  using DescriptorType const char*;

  virtual DescriptorType type() const = 0;
};


class DemoEvent : public Event
{
public:
  DemoEvent();
  virtual ~DemoEvent();

  static constexpr DescriptorType descriptor = "DemoEvent";

  virtual DescriptorType type() const
  {
    return descriptor;
  }
};


class Dispatcher
{
public:

  using SlotType = std::function< void( const Event& ) >;

  void subscribe( const Event::DescriptorType& descriptor, SlotType&& slot );

  void post( const Event& event ) const;

private:

 std::map< Event::DescriptorType, std::vector<SlotType> > _observers;
};


void Dispatcher::subscribe( const Event::DescriptorType& descriptor, SlotType&& slot )
{
  _observers[descriptor].push_back( slot );
}

void Dispatcher::post( const Event& event ) const
{
  auto type = event.type();

  // Ignore events for which we do not have an observer (yet).
  if( _observers.find( type ) == _observers.end() )
    return;

  auto&& observers = _observers.at( type );

  for( auto&& observer : observers )
    observer( event );
}

class ClassObserver
{
public:
  void handle( const Event& e )
  {
    if( e.type() == DemoEvent::descriptor )
    {
      // This demonstrates how to obtain the underlying event type in case a
      // slot is set up to handle multiple events of different types.
      const DemoEvent& demoEvent = static_cast<const DemoEvent&>( e );
      std::cout << __PRETTY_FUNCTION__ << ": " << demoEvent.type() << std::endl;
    }
  }
};

#endif