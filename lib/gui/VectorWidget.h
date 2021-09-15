#pragma once

#include "lib/core/StringConversions.h"

#include <QTableWidget>

namespace cement
{
    class VectorWidget : public QTableWidget
    {
        Q_OBJECT

    public:
        VectorWidget(QWidget *a_parent = nullptr);

        template <typename T>
        void Init(const std::vector<T> &a_vector)
        {
            setColumnCount(a_vector.size());

            for (size_t i = 0; i < a_vector.size(); i++)
            {
                setItem(0, i, new QTableWidgetItem(QString::fromStdString(StringConversions::ToString<T>(a_vector[i]))));
            }
        }
    };
} //end namespace cement
