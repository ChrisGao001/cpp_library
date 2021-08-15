##  简介

事件总线架构是典型的订阅/发布模式，用于解耦业务间复杂的调用关系。

## 使用方式

每个事件类型建立自己的EventBus

```c++
    using IntEventBus = serving::EventBus<int>;
	auto bus = IntEventBus::CreateEventBus();
    IntEventBus::Callback callback =
      [](IntEventBus::EventAndTime event_and_time) {
        logger("event " << event_and_time.event << ",time:" << event_and_time.event_time_micros);
      };
    std::unique_ptr<IntEventBus::Subscription> subscription = bus->Subscribe(callback);
    bus->Publish(42);
    bus->Publish(12);

