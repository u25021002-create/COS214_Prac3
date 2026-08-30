#include "MerchStall.h"
#include "EventNotice.h"
#include <iostream>

MerchStall::MerchStall(const std::string& name, int capacity)
    : EventUnit(name, capacity), stock(100), lowStockRaised(false) {}

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

    if (stock < RESTOCK_THRESHOLD && !lowStockRaised) {
        lowStockRaised = true;
        std::cout << name << ": stock has fallen to " << stock
                  << ", raising a restock notice.\n";
        notify(EventNotice(LOW_STOCK, "restock needed", name, 1));
    } else if (stock >= RESTOCK_THRESHOLD) {
        lowStockRaised = false; // restocked externally; can raise again later
    }
}

void MerchStall::update(const EventNotice& notice) {
    switch (notice.getType()) {
        case OPEN:
        case RESUME:
            open();
            break;
        case WEATHER_ALERT:
            std::cout << name << ": indoors under canvas, trading continues.\n";
            break;
        case PAUSE:
        case CAPACITY_ALERT:
        case EVACUATE:
            close();
            break;
        default:
            break;
    }
}
