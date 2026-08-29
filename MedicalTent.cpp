#include "MedicalTent.h"
#include <iostream>

MedicalTent::MedicalTent(const std::string& name, int capacity)
    : EventUnit(name, capacity) {}

void MedicalTent::open() {
    open_ = true;
    std::cout << name << ": medical tent staffed and operational.\n";
}

void MedicalTent::close() {
    // Medical stays open even when "close" is called on the tree, unless
    // this is a full evacuation; 
    std::cout << name << ": medical remains operational.\n";
}

void MedicalTent::reportStatus() const {
    std::cout << "[MedicalTent] " << name << " - ALWAYS STAFFED"
              << ", capacity=" << capacity << "\n";
}
