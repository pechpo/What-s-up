#include "director.h"

Director::Director(QObject *parent)
    : QObject{parent} {

}

Director::~Director() {

}

Director* Director::self = nullptr;
Director* Director::getInstance() {
    if (!self) {
        self = new Director();
    }
    return self;
}
