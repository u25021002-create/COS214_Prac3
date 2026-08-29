#include "EventComponent.h"

EventComponent::EventComponent(const std::string& name) : name(name), open_(false) {}

EventComponent::~EventComponent() {}

const std::string& EventComponent::getName() const { return name; }
