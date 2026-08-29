#include "EventGroup.h"
#include "VehicleDisplay.h"
#include "DroidShow.h"
#include "AutographBooth.h"
#include "MerchStall.h"
#include "FoodStall.h"
#include "MainGate.h"
#include "MedicalTent.h"
#include "AnnouncementBooth.h"
#include <iostream>

/**
 * @brief Builds a sample Star Wars Fan Day event tree with 3 levels of
 *        Composite nesting below the root, then demonstrates recursive
 *        operations and single, complete destruction of the whole tree.
 */
int main() {
    // ---- Root ----
    EventGroup* root = new EventGroup("StarWarsFanDay");

    // ---- Level 1: PrepZone (no leaves for now) ----
    EventGroup* prepZone = new EventGroup("PrepZone");
    root->add(prepZone);

    // ---- Level 1: FanZone ----
    EventGroup* fanZone = new EventGroup("FanZone");
    root->add(fanZone);

    // ---- Level 2: sub-zones of FanZone (gives the 3rd nesting level) ----
    EventGroup* entryArea = new EventGroup("EntryArea");
    EventGroup* marketArea = new EventGroup("MarketArea");
    EventGroup* serviceArea = new EventGroup("ServiceArea");
    fanZone->add(entryArea);
    fanZone->add(marketArea);
    fanZone->add(serviceArea);

    // ---- Level 3: leaves inside the sub-zones ----
    entryArea->add(new MainGate("Main Gate", 500));

    marketArea->add(new MerchStall("Collectibles Stall", 50));
    marketArea->add(new FoodStall("Cantina Snacks", 80));

    serviceArea->add(new AutographBooth("Meet the Cast", 60));
    serviceArea->add(new MedicalTent("First Aid", 20));

    // ---- Level 1: DisplayZone ----
    EventGroup* displayZone = new EventGroup("DisplayZone");
    root->add(displayZone);
    displayZone->add(new VehicleDisplay("X-wing Replica", 30));
    displayZone->add(new VehicleDisplay("Speeder Bike Replica", 30));

    // ---- Level 1: ShowZone ----
    EventGroup* showZone = new EventGroup("ShowZone");
    root->add(showZone);
    showZone->add(new DroidShow("Droid Demo Stage", 150));
    showZone->add(new AnnouncementBooth("PA Booth", 0));

    std::cout << "=== Opening the whole event via the root ===\n";
    root->open();

    std::cout << "\n=== Status report (recursive traversal) ===\n";
    root->reportStatus();

    std::cout << "\n=== Total event capacity ===\n";
    std::cout << "Root capacity (sum of all leaves): " << root->getCapacity() << "\n";

    std::cout << "\n=== Closing the whole event via the root ===\n";
    root->close();

    std::cout << "\n=== Destroying the root ===\n";
    std::cout << "A single 'delete root' releases the entire owned subtree\n"
              << "exactly once: EventGroup::~EventGroup() deletes each direct\n"
              << "child via a virtual EventComponent* destructor call, and each\n"
              << "child (if itself an EventGroup) recursively does the same for\n"
              << "its own children, all the way down to the leaves.\n";
    delete root; // Recursively destroys prepZone, fanZone (+ sub-zones + leaves),
                 // displayZone (+ leaves), showZone (+ leaves) -- exactly once each.

    std::cout << "\nAll objects destroyed. Program complete.\n";
    return 0;
}
