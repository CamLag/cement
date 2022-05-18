#include "../MainWindow.h"

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QAction>
#include <QDockWidget>
#include <QPushButton>
#include <QToolButton>

namespace cement
{
    MainWindow::MainWindow(QWidget *a_parent) : QMainWindow(a_parent)
    {
        setMinimumSize(1000, 800);

        size = m_registry.CreateProperty<long>("Size", false);
//        auto size = m_registry.CreateProperty<long>("Size", false);
        auto color = m_registry.CreateProperty<std::string>("Color", true);
        auto thing = m_registry.CreateModel("Thing", true);
        // auto nothing = m_registry.CreateModel("NoThing", true);
        auto thing_size = m_registry.AddProperty(thing, size, "Thing_Size");
        auto thing_color = m_registry.AddProperty(thing, color, "Thing_Color");

        auto blue_instance = color->Instanciate();
        auto red_instance = color->Instanciate();
        color->SetValue(blue_instance, "Blue");
        color->SetValue(red_instance, "Red");

        auto th1 = thing->Instanciate(); // size 1, red
        thing_color->SetValue(th1, red_instance);
        size->SetValue(thing_size->Get(th1), 1);

        auto th2 = thing->Instanciate(); // size 2, red
        thing_color->SetValue(th2, red_instance);
        size->SetValue(thing_size->Get(th2), 2);

        auto th3 = thing->Instanciate(); // size 3, blue
        thing_color->SetValue(th3, blue_instance);
        size->SetValue(thing_size->Get(th3), 3);

        std::cout << m_registry.Print() << std::endl;

        QTabWidget *m_tab_bar = new QTabWidget();

        m_registry_model = new RegistryModel(&m_registry);
        m_registry_widget = new RegistryWidget(m_registry_model, true);
        m_concrete_widget = new RegistryWidget(m_registry_model, false);
        m_tab_bar->addTab(m_registry_widget, "Core Interface");
        m_tab_bar->addTab(m_concrete_widget, "Concrete Interface");

        setCentralWidget(m_tab_bar);

        QDockWidget* m_dock = new QDockWidget();
        addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, m_dock);
        m_dock->setFeatures(QDockWidget::NoDockWidgetFeatures);

        m_button_group = new QButtonGroup();
        QWidget* m_dock_widget = new QWidget();
        QVBoxLayout* m_button_layout = new QVBoxLayout();
        m_dock_widget->setLayout(m_button_layout);
        m_dock->setWidget(m_dock_widget);

        m_add_property = new QAction("Add Property", this);
        connect(m_add_property, &QAction::triggered, this, &MainWindow::AddProperty);
        auto b1 = new QToolButton();
        b1->setDefaultAction(m_add_property);
        m_button_group->addButton(b1);
        m_button_layout->addWidget(b1);

        m_delete_property = new QAction("Delete Property", this);
        connect(m_delete_property , &QAction::triggered, this, &MainWindow::DeleteProperty);
        auto b2 = new QToolButton();
        b2->setDefaultAction(m_delete_property);
        m_button_group->addButton(b2);
        m_button_layout->addWidget(b2);

        m_instanciate = new QAction("Instanciate", this);
        connect(m_instanciate, &QAction::triggered, this, &MainWindow::Instanciate);
        auto b3 = new QToolButton();
        b3->setDefaultAction(m_instanciate);
        m_button_group->addButton(b3);
        m_button_layout->addWidget(b3);

        m_delete_instance = new QAction("Delete Instance", this);
        connect(m_delete_instance, &QAction::triggered, this, &MainWindow::DeleteInstance);
        auto b4 = new QToolButton();
        b4->setDefaultAction(m_delete_instance);
        m_button_group->addButton(b4);
        m_button_layout->addWidget(b4);

        addActions({m_add_property, m_delete_property, m_instanciate, m_delete_instance});

        m_button_layout->addStretch();

        m_registry.m_property_created.Connect([=](Property* a_property){m_registry_model->AddProperty(a_property);});
    }

    void MainWindow::AddProperty()
    {
        m_registry.CreateProperty<std::string>("Hello", true);
    }

    void MainWindow::DeleteProperty()
    {
    }

    void MainWindow::Instanciate()
    {
        auto selected = m_registry_widget->SelectedProperties();
        for (auto prop : selected)
        {
            if (prop->Type() != PropertyType::pt_index)
            {
                prop->Instanciate();
            }
        }
    }

    void MainWindow::DeleteInstance()
    {
        auto selected = m_registry_widget->SelectedValues();
        if (selected.size() == 1)
        {
            selected.first().m_property->DeleteInstance(selected.first().m_index);
        }
    }

    void MainWindow::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Alt)
        {
            long val = size->Get(0);
            val++;
            size->SetValue(0, val);
        }

        if (event->key() == Qt::Key_F1)
        {
            std::cout << m_registry.Print() << std::endl;
        }
    }

} // end namespace cement
