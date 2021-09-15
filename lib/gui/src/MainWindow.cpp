#include "../MainWindow.h"
#include "../Factory.h"

#include <QHBoxLayout>

namespace cement
{
    MainWindow::MainWindow(QWidget *a_parent) : QMainWindow(a_parent)
    {
        setMinimumSize(1000, 800);

        auto size = m_registry.CreateProperty<long>("Size");
        auto color = m_registry.CreateProperty<std::string>("Color");
        auto candle = m_registry.CreateModel("Candle");
        candle->AddProperty(size);
        candle->AddProperty(color);
        auto candle1 = candle->Instanciate();
        auto candle2 = candle->Instanciate();
        candle->SetValue<long>(size, candle1, 32);
        candle->SetValue<long>(size, candle2, 10);
        candle->SetValue<std::string>(color, candle1, "Blue");
        candle->SetValue<std::string>(color, candle2, "Red");

        auto central_widget = new QWidget();
        auto layout = new QVBoxLayout();

        layout->addWidget(Factory::MakeWidget(size));
        layout->addWidget(Factory::MakeWidget(color));

        central_widget->setLayout(layout);
        setCentralWidget(central_widget);
    }

} //end namespace cement
