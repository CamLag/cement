#pragma once

#include <QComboBox>
#include "RegistryModel.h"

namespace cement
{
    class ValueComboBox : public QComboBox
    {
        Q_OBJECT

    public:
        ValueComboBox(RegistryModel *a_model, size_t a_row, size_t a_column, QWidget *a_parent = nullptr);

    protected:
        RegistryModel *m_model;
    };
} // end namespace cement
