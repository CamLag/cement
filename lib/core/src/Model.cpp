#include "../Model.h"
#include "../StringConversions.h"

namespace cement
{
    Model::Model(const std::string &a_name) : Property(a_name),
                                              m_size(0)
    {
    }

    void Model::AddProperty(Property *a_property)
    {
        m_indexes[a_property];
    }

    size_t Model::Instanciate()
    {
        for (auto &pair : m_indexes)
        {
            auto index = pair.first->Instanciate();
            pair.second.push_back(index);
        }
        m_size++;
        return m_size - 1;
    }

    const size_t Model::Size() const
    {
        return m_size;
    }

    std::string Model::Print() const
    {
        std::string result;

        result += Property::Print();

        for (auto &pair : m_indexes)
        {
            result += "\n  ";
            result += pair.first->Property::Print();
            result += "[";

            for (auto it = pair.second.begin(); it != pair.second.end() - 1; it++)
            {
                result += StringConversions::ToString(*it);
                result += ", ";
            }

            result += StringConversions::ToString(pair.second.back());
            result += "]";
        }
        result += "\n";

        return result;
    }

    const int Model::Type() const
    {
        return 1;
    }

    const size_t Model::Depth() const
    {
        size_t counter = 1;
        size_t max = 1;
        for (auto &pair : m_indexes)
        {
            size_t depth = pair.first->Depth();
            if (depth > max)
            {
                max = depth;
            }
        }
        counter += max;

        return counter;
    }

    const size_t Model::PropertyCount() const
    {
        return m_indexes.size();
    }
} //end namespace cement