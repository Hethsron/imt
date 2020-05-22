#include <controller/manager.hpp>

Manager::Manager()
    : Observer(), splash(new SplashView()), win(new MainView()) {
        attach();
    }

Manager::~Manager() {
    // The observer need to clear current state of the subject
    detach();
}

void Manager::attach() {
    // The observer need to get the current state of the subject
    update();
}

void Manager::update() {

}

void Manager::detach() {

}

void Manager::exec() {
    static const int LOAD_TIME_MSEC = 5 * 2000;

    splash->show();
    QApplication::processEvents();

    QTime time;
    time.start();

    while (time.elapsed() < LOAD_TIME_MSEC) {
        const int progress = static_cast<double>(time.elapsed()) / LOAD_TIME_MSEC * 100.0;

        splash->setProgress(progress);

        QApplication::processEvents();
    }

    win->show();
    splash->finish(win);
}