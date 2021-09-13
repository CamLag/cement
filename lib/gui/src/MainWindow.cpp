#include "../MainWindow.h"

#include <QPushButton>

namespace cement
{
    MainWindow::MainWindow(QWidget *a_parent) : QMainWindow(a_parent)
    {
        setMinimumSize(1000, 800);
    }

} //end namespace cement
