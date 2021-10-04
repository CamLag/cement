#include "../MainWindow.h"

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

        m_registry_widget = new RegistryWidget(&m_registry);
        setCentralWidget(m_registry_widget);
    }

} //end namespace cement
