#include "../PropertyWidget.h"

#include <iostream>

namespace cement
{
    PropertyWidget::PropertyWidget(Property *a_property, QWidget *a_parent) : VectorWidget(a_parent)
    {
        setVerticalHeaderItem(0, new QTableWidgetItem(QString::fromStdString(a_property->m_name)));
        setMaximumHeight(80);
    }

} //end namespace cement
