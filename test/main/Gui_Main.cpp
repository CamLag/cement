#include "lib/gui/MainWindow.h"

#include <QApplication>

int main(int a_argc, char **a_argv)
{
    QApplication app(a_argc, a_argv);

    cement::MainWindow main_window;

    main_window.show();

    app.exec();
}
