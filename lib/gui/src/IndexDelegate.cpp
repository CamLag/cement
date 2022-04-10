#include "../IndexDelegate.h"
#include "../ValueComboBox.h"
#include <QComboBox>

namespace cement
{
    QWidget *SharedValueDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        auto combo_box = new QComboBox(parent);
        auto pointed_row = m_model->headerData(index.row(), Qt::Vertical, RegistryModel::dr_pointed_row).toInt();
        for (unsigned long column = 2; column < m_model->columnCount(); column++)
        {
            combo_box->addItem(m_model->GetValue(pointed_row, column), QVariant((qulonglong)(column - 2)));
        }
        return combo_box;
    }

    SharedValueDelegate::SharedValueDelegate(RegistryModel *a_model, QObject *parent)
        : QStyledItemDelegate(parent),
          m_model(a_model)
    {
    }

    void SharedValueDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        auto model = dynamic_cast<const RegistryModel *>(index.model());
        auto pointed_row = model->headerData(index.row(), Qt::Vertical, RegistryModel::dr_pointed_row).toInt();
        auto data = model->GetValue(index.row(), index.column());
        auto index_value = data.toULongLong();
        auto pointed_value = model->GetValue(pointed_row, index_value);
        static_cast<QComboBox *>(editor)->setCurrentText(pointed_value);
    }

    void SharedValueDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        auto value = static_cast<QComboBox *>(editor)->currentData();
        auto registry_model = dynamic_cast<RegistryModel *>(model);
        auto pointed_row = model->headerData(index.row(), Qt::Vertical, RegistryModel::dr_pointed_row).toInt();

        registry_model->SetValue(index.row(), index.column(), value.toString());
    }

    // void SharedValueDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    // {
    // }

} // end namespace cement
