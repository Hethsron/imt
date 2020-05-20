#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QWidget>
#include <QtWidgets/QAction>
#include <QtGui/QCloseEvent>
#include <QtGui/QIcon>

class MainView : public QMainWindow
{
    public:
        MainView();
        virtual ~MainView();

    protected:
        // void closeEvent(QCloseEvent *event) override;

    private slots:
        //virtual void newFile();
        // virtual void open();
        // virtual bool save();
        // virtual bool saveAs();
        // virtual void about();

    private:
        // virtual void createActions();
        // virtual void createStatusBar();
        // virtual void readSettings();
        // virtual void writeSettings();

        // bool maybeSave();
        // bool saveFile(const QString& filename);


};

#endif // ! MAINVIEW_HPP