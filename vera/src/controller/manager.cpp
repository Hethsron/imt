#include <controller/manager.hpp>

Manager::Manager()
    : Observer(), splash(new SplashView()), win(new MainView()) {}

Manager::~Manager() {}

void Manager::notify() {
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