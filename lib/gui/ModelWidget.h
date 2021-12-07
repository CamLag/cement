#pragma once

#include <QWidget>
#include "lib/core/Model.h"

namespace cement
{
    class ModelWidget : public QWidget
    {
        Q_OBJECT

    public:
        ModelWidget(Property *a_model, size_t a_instance, QWidget *a_parent = nullptr);

        // virtual QSize sizeHint() const override;

    protected:
        Property *m_model;
        size_t m_instance;
    };
} // end namespace cement
