#pragma once

#include <QWidget>
#include "lib/core/Model.h"

namespace cement
{
    class ModelWidget : public QWidget
    {
        Q_OBJECT

    public:
        ModelWidget(Property *a_model, QWidget *a_parent = nullptr);

    protected:
        Property *m_model;
    };
} // end namespace cement
