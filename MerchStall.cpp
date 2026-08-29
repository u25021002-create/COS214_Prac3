#include "MerchStall.h"
#include <iostream>

MerchStall::MerchStall(const std::string& name, int capacity)
    : EventUnit(name, capacity), stock(100) {}

void MerchStall::open() {
    open_ = true;
    std::cout << name << ": trading, stock=" << stock << ".\n";
}

void MerchStall::close() {
    open_ = false;
    std::cout << name << ": stall shut for the day.\n";
}

void MerchStall::reportStatus() const {
    std::cout << "[MerchStall] " << name << " - "
              << (open_ ? "TRADING" : "CLOSED")
              << ", stock=" << stock << ", capacity=" << capacity << "\n";
}

void MerchStall::sell(int units) {
    stock = (units > stock) ? 0 : stock - units;
}
