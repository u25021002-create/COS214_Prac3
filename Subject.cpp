#include "Subject.h"
#include "Observer.h"
#include "EventNotice.h"
#include <algorithm>

Subject::Subject() {}

Subject::~Subject() {
    // Non-owning: the pointers are dropped, the observers are not deleted.
    observers.clear();
}

bool Subject::attach(Observer* observer) {
    if (observer == NULL) return false;
    if (std::find(observers.begin(), observers.end(), observer) != observers.end()) {
        return false;                       // already registered: duplicate ignored
    }
    observers.push_back(observer);
    return true;
}

bool Subject::detach(Observer* observer) {
    std::vector<Observer*>::iterator it =
        std::find(observers.begin(), observers.end(), observer);
    if (it == observers.end()) return false;   // not registered: not an error
    observers.erase(it);
    return true;
}

void Subject::notify(const EventNotice& notice) {
    std::vector<Observer*> snapshot(observers);
    for (Observer* observer : snapshot) {
        observer->update(notice);
    }
}

int Subject::getObserverCount() const {
    return static_cast<int>(observers.size());
}
