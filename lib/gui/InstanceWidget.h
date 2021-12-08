#pragma once

#include <QWidget>
#include "lib/core/Model.h"

namespace cement
{
    class InstanceWidget : public QWidget
    {
        Q_OBJECT

    public:
        InstanceWidget(Property *a_model, size_t a_instance, QWidget *a_parent = nullptr);

    protected:
        Property *m_model;
        size_t m_instance;
    };
} // end namespace cement
