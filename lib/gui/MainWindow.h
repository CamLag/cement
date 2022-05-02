#pragma once

#include <QMainWindow>
#include <QTabBar>
#include <QButtonGroup>

#include "lib/core/Registry.h"
#include "lib/core/Value.h"
#include "lib/gui/RegistryWidget.h"

namespace cement
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT;

    public:
        MainWindow(QWidget *a_parent = nullptr);
        Registry m_registry;
        RegistryWidget* m_registry_widget;
        RegistryWidget* m_concrete_widget;
        RegistryModel* m_registry_model;

        QButtonGroup* m_button_group;

        QAction* m_add_property;
        QAction* m_delete_property;
        QAction* m_instanciate;
        QAction* m_delete_instance;

        // test
        Instances<long> *size;

    public slots:
        void AddProperty();
        void DeleteProperty();
        void Instanciate();
        void DeleteInstance();

    protected:
        void keyPressEvent(QKeyEvent *event);
    };
} // end namespace cement
