#pragma once

#include <QWidget>
#include <QStandardItemModel>
#include "lib/core/Registry.h"

namespace cement
{
    class RegistryModel : public QStandardItemModel
    {
        Q_OBJECT

    public:
        RegistryModel(Registry *a_registry, QObject *a_parent = nullptr);

    protected:
        Registry *m_registry;
    };
} // end namespace cement
