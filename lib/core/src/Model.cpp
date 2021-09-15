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

    size_t Model::Size()
    {
        return m_size;
    }

    std::string Model::Print()
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

    int Model::Type()
    {
        return 1;
    }
} //end namespace cement