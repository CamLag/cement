#pragma once

#include <QComboBox>
#include "lib/core/Index.h"

namespace cement
{
    class ValueComboBox : public QComboBox
    {
        Q_OBJECT

    public:
        ValueComboBox(Index *a_index, size_t a_instance, QWidget *a_parent = nullptr);

    protected:
        Index *m_index;
    };
} // end namespace cement
