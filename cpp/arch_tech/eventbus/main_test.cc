#include "event_bus.h"
#include <iostream>

#define logger(text) do { \
	std::cout << text << std::endl; \
} while (0) 

using IntEventBus= serving::EventBus<int>;
int main(int argc, char** argv) {
	auto bus = IntEventBus::CreateEventBus();
    IntEventBus::Callback callback =
      [](IntEventBus::EventAndTime event_and_time) {
        logger("event " << event_and_time.event << ",time:" << event_and_time.event_time_micros);
      };
    std::unique_ptr<IntEventBus::Subscription> subscription = bus->Subscribe(callback);
    bus->Publish(42);
    bus->Publish(12);

	return 0;
}
