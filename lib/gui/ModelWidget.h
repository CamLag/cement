#pragma once

#include <QWidget>
#include "lib/core/Model.h"

namespace cement
{
    class ModelWidget : public QWidget
    {
        Q_OBJECT

    public:
        ModelWidget(Model *a_model, size_t a_instance, QWidget *a_parent = nullptr);

    protected:
        Model *m_model;
        size_t m_instance;
    };
} // end namespace cement
