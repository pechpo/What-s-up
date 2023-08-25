#include "connection.h"

connection::connection() {
    connect(this, SIGNAL(readyRead()),this, SLOT(readMessage()));
}

void connection::readMessage() {

}
