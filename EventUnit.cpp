#include "EventUnit.h"

EventUnit::EventUnit(const std::string& name, int capacity)
    : EventComponent(name), capacity(capacity) {}

EventUnit::~EventUnit() {}

int EventUnit::getCapacity() const { return capacity; }
