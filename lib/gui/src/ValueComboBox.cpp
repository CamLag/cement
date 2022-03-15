#include "../ValueComboBox.h"

namespace cement
{
    ValueComboBox::ValueComboBox(RegistryModel *a_model, size_t a_row, size_t a_column, QWidget *a_parent) : QComboBox(a_parent),
                                                                                                             m_model(a_model)
    {
        for (size_t i = 2; i < a_model->columnCount(); i++)
        {
            auto pointed_row = m_model->headerData(a_row, Qt::Vertical, RegistryModel::dr_pointed_row).toULongLong();
            std::cout << "ValueComboBox ctr : row " << a_row << " pointing to row " << pointed_row << std::endl;

            for (auto column = 3; column < m_model->ColumnCount(pointed_row); column++)
            {
                addItem(m_model->GetValue(pointed_row, column));
            }
            // a_index->GetIndexed()->GetValue(i, value);
            // addItem();
            // setModel(a_model);
            // setCurrentIndex(a_column);
        }
    }

} // end namespace cement
