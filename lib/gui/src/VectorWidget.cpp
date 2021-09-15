#include "../VectorWidget.h"

namespace cement
{
    VectorWidget::VectorWidget(QWidget *a_parent) : QTableWidget(a_parent)
    {
        setRowCount(1);
    }

} //end namespace cement
