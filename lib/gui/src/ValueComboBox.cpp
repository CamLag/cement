#include "../ValueComboBox.h"
#include <QComboBox>

namespace cement
{
    ValueComboBox::ValueComboBox(RegistryModel *a_model, size_t a_row, QWidget *parent)
        : QComboBox(parent),
          m_model(a_model),
          m_row(a_row)
    {
        for (qulonglong column = 2; column < m_model->columnCount(); column++)
        {
            addItem(m_model->GetValue(a_row, column), QVariant(column - 2));
                }
    }

} // end namespace cement
