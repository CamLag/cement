#include "../ConcreteWidget.h"

namespace cement
{
    ConcreteWidget::ConcreteWidget(Registry *a_registry, QWidget *a_parent) : QWidget(a_parent),
                                                                              m_registry(a_registry)
    {
    }
} // end namespace cement
