#pragma once

#include <QComboBox>
#include "RegistryModel.h"

namespace cement
{
    class ValueComboBox : public QComboBox
    {
        Q_OBJECT

    public:
        ValueComboBox(RegistryModel *a_model, size_t a_row, QWidget *parent = nullptr);

    protected:
        RegistryModel *m_model;
        size_t m_row;
    };
} // end namespace cement
