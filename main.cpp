#include "EventGroup.h"
#include "DisplayZone.h"
#include "PrepZone.h"
#include "VehicleDisplay.h"
#include "DroidShow.h"
#include "AutographBooth.h"
#include "MerchStall.h"
#include "FoodStall.h"
#include "MainGate.h"
#include "MedicalTent.h"
#include "AnnouncementBooth.h"
#include "EventControl.h"
#include <iostream>

/** @brief Prints a banner so each part of the demonstration is easy to find. */
static void banner(const std::string& title) {
    std::cout << "\n============================================================\n"
              << title
              << "\n============================================================\n";
}

/** @brief Prints the outcome of an attach/detach call. */
static void showResult(const std::string& call, bool result) {
    std::cout << "  " << call << " -> " << (result ? "true" : "false") << "\n";
}

/**
 * @brief Builds the Star Wars Fan Day event tree (Task 2), wires up the
 *        observer registrations (Task 3), then drives notices through it.
 */
int main() {
    // ================== Task 2: the ownership tree ==================
    EventGroup* root = new EventGroup("StarWarsFanDay");

    PrepZone* prepZone = new PrepZone("PrepZone");
    root->add(prepZone);

    EventGroup* fanZone = new EventGroup("FanZone");
    root->add(fanZone);

    EventGroup* entryArea   = new EventGroup("EntryArea");
    EventGroup* marketArea  = new EventGroup("MarketArea");
    EventGroup* serviceArea = new EventGroup("ServiceArea");
    fanZone->add(entryArea);
    fanZone->add(marketArea);
    fanZone->add(serviceArea);

    MainGate*       mainGate       = new MainGate("Main Gate", 500);
    MerchStall*     merchStall     = new MerchStall("Collectibles Stall", 50);
    FoodStall*      foodStall      = new FoodStall("Cantina Snacks", 80);
    AutographBooth* autographBooth = new AutographBooth("Meet the Cast", 60);
    MedicalTent*    medicalTent    = new MedicalTent("First Aid", 20);

    entryArea->add(mainGate);
    marketArea->add(merchStall);
    marketArea->add(foodStall);
    serviceArea->add(autographBooth);
    serviceArea->add(medicalTent);

    DisplayZone* displayZone = new DisplayZone("DisplayZone", true);
    root->add(displayZone);
    VehicleDisplay* xwing   = new VehicleDisplay("X-wing Replica", 30);
    VehicleDisplay* speeder = new VehicleDisplay("Speeder Bike Replica", 30);
    displayZone->add(xwing);
    displayZone->add(speeder);

    EventGroup* showZone = new EventGroup("ShowZone");
    root->add(showZone);
    DroidShow*         droidShow         = new DroidShow("Droid Demo Stage", 150);
    AnnouncementBooth* announcementBooth = new AnnouncementBooth("PA Booth", 0);
    showZone->add(droidShow);
    showZone->add(announcementBooth);

    // ================== Task 3: the registration list ==================
    // add(...) established containment. attach(...) is a separate decision:
    // nothing is registered simply because it is contained.
    EventControl* eventControl = new EventControl("Star Wars Fan Day");

    eventControl->attach(root);
    eventControl->attach(announcementBooth);   // cross-tree: hears control directly

    root->attach(fanZone);
    root->attach(displayZone);
    root->attach(showZone);
    root->attach(prepZone);

    fanZone->attach(entryArea);
    fanZone->attach(marketArea);
    fanZone->attach(serviceArea);

    entryArea->attach(mainGate);
    marketArea->attach(merchStall);
    marketArea->attach(foodStall);
    serviceArea->attach(autographBooth);
    displayZone->attach(xwing);
    displayZone->attach(speeder);
    displayZone->attach(medicalTent);          // cross-tree: contained by ServiceArea
    showZone->attach(droidShow);

    banner("3.1  Registration policy: duplicates and unknown observers");
    showResult("marketArea.attach(merchStall)  [already registered] ",
               marketArea->attach(merchStall));
    showResult("marketArea.attach(NULL)        [null observer]      ",
               marketArea->attach(NULL));
    showResult("marketArea.detach(mainGate)    [never registered]   ",
               marketArea->detach(mainGate));
    showResult("marketArea.detach(foodStall)   [registered]         ",
               marketArea->detach(foodStall));
    showResult("marketArea.detach(foodStall)   [detached twice]     ",
               marketArea->detach(foodStall));
    showResult("marketArea.attach(foodStall)   [registered again]   ",
               marketArea->attach(foodStall));
    std::cout << "  MarketArea observer count: "
              << marketArea->getObserverCount() << "\n";

    banner("3.4  Cascade: Control -> StarWarsFanDay -> FanZone -> MarketArea -> stalls");
    eventControl->issueNotice(OPEN, "doors open, Fan Day is live");
    mainGate->admit(480);
    autographBooth->joinQueue(40);

    banner("3.3  Ordinary operational change: SCHEDULE_CHANGE");
    eventControl->issueNotice(SCHEDULE_CHANGE, "15:30");

    banner("3.3  Capacity-related change: CAPACITY_ALERT");
    if (!mainGate->admit(40)) {
        std::cout << "  Main Gate refused 40 more attendees.\n";
    }
    mainGate->admit(20);
    if (mainGate->atCapacity()) {
        eventControl->issueNotice(CAPACITY_ALERT,
                                  "the Main Gate has reached its limit");
    }

    banner("3.3  Safety-related change: WEATHER_ALERT");
    eventControl->issueSafetyNotice(WEATHER_ALERT,
                                    "high winds over the display field", 2);

    banner("3.3  PAUSE, with one observer detached at runtime");
    std::cout << "  marketArea.detach(foodStall) -> "
              << (marketArea->detach(foodStall) ? "true" : "false")
              << "  (Cantina Snacks will not hear the next notice)\n";
    eventControl->issueNotice(PAUSE, "hold all activity for ten minutes");

    banner("3.3  RESUME, with the observer attached again");
    std::cout << "  marketArea.attach(foodStall) -> "
              << (marketArea->attach(foodStall) ? "true" : "false") << "\n";
    eventControl->issueNotice(RESUME, "normal programme restarts");

    banner("3.3  Safety-related change: EVACUATE");
    eventControl->issueSafetyNotice(EVACUATE, "clear the display field", 3);

    banner("Status report through the Component interface (Task 2 traversal)");
    root->reportStatus();
    std::cout << "\n  Total event capacity: " << root->getCapacity() << "\n"
              << "  Notices issued by control: "
              << eventControl->getNoticesIssued() << "\n";

    banner("3.2  Destruction in lifetime order");
    std::cout << "  Deleting the control centre first: it holds "
              << eventControl->getObserverCount()
              << " registration(s) and owns none of them.\n";
    delete eventControl;   // the subject dies first; it deletes nothing

    std::cout << "  Deleting the root: a single delete releases the entire\n"
              << "  owned subtree exactly once, and every group detaches each\n"
              << "  child before destroying it.\n";
    delete root;           // the owner dies second; the whole tree goes with it

    std::cout << "\nAll objects destroyed. Program complete.\n";
    return 0;
}
