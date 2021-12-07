#include "../MainWindow.h"

#include <QHBoxLayout>

namespace cement
{
    MainWindow::MainWindow(QWidget *a_parent) : QMainWindow(a_parent)
    {
        setMinimumSize(1000, 800);

        auto size = m_registry.CreateProperty<long>("Size", false);
        auto color = m_registry.CreateProperty<std::string>("Color", true);
        auto thing = m_registry.CreateModel("Thing", true);
        auto nothing = m_registry.CreateModel("NoThing", true);
        auto thing_size = m_registry.AddProperty(thing, size, "Thing_Size");
        auto thing_color = m_registry.AddProperty(thing, color, "Thing_Color");

        auto blue_instance = color->Instanciate();
        auto red_instance = color->Instanciate();
        color->SetValue(blue_instance, "Blue");
        color->SetValue(red_instance, "Red");

        auto th1 = thing->Instanciate(); // size 1, red
        thing_color->SetValue(th1, red_instance);
        size->SetValue(thing_size->GetValue(th1), 1);

        auto th2 = thing->Instanciate(); // size 2, red
        thing_color->SetValue(th2, red_instance);
        size->SetValue(thing_size->GetValue(th2), 2);

        auto th3 = thing->Instanciate(); // size 3, blue
        thing_color->SetValue(th3, blue_instance);
        size->SetValue(thing_size->GetValue(th3), 3);

        std::cout << m_registry.Print() << std::endl;

        QTabWidget *m_tab_bar = new QTabWidget();

        m_registry_widget = new RegistryWidget(&m_registry);
        m_concrete_widget = new ConcreteWidget(&m_registry);
        m_tab_bar->addTab(m_registry_widget, "Core Interface");
        m_tab_bar->addTab(m_concrete_widget, "Concrete Interface");

        setCentralWidget(m_tab_bar);
    }

} // end namespace cement
