#pragma once

#include <QStyledItemDelegate>
#include "RegistryModel.h"

namespace cement
{
    // class ValueComboBox : public QComboBox
    // {
    //     Q_OBJECT

    // public:
    //     ValueComboBox(RegistryModel *a_model, size_t a_row, size_t a_column, QWidget *a_parent = nullptr);

    // protected:
    //     RegistryModel *m_model;
    // };

    class SharedValueDelegate : public QStyledItemDelegate
    {
        Q_OBJECT

    public:
        SharedValueDelegate(RegistryModel *a_model, QObject *parent = nullptr);

        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
        void setEditorData(QWidget *editor, const QModelIndex &index) const override;
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
        // void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    protected:
        RegistryModel *m_model;
    };
} // end namespace cement
