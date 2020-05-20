#include <controller/cthread.hpp>

CThread::CThread()
    : QThread() {}

CThread::~CThread() {}

void CThread::run() {
    int i = 0;

    while (i < 101) {
        sleep(0.1);
        emit mysignal(i);
        i++;
    }
}