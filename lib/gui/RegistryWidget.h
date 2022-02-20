#pragma once

#include "lib/core/StringConversions.h"

#include "lib/gui/RegistryModel.h"

#include <QTableWidget>
#include <QTableView>
#include <QStandardItemModel>

namespace cement
{
    class RegistryWidget : public QTableView
    {
        Q_OBJECT

    public:
        RegistryWidget(RegistryModel *a_registry_model, bool a_core, QWidget *a_parent = nullptr);

    protected:
        RegistryModel *m_registry_model;

    private:
        const bool m_core;
    };
} // end namespace cement
