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
        if (m_indexes.find(a_property) == m_indexes.end())
        {
            m_indexes.insert(std::make_pair(a_property, Pool<size_t>(1000)));
        }
    }

    void Model::SetIndex(Property *a_property, size_t a_model_instance, size_t a_property_instance)
    {
        // TODO check if index is valid
        auto &index_pointer = m_indexes.at(a_property)[a_model_instance];
        if (index_pointer == NO_VALUE) // the property is shared and this instance has never been set
        {
            index_pointer = a_property_instance;
            a_property->AddReference(a_property_instance, &index_pointer);
        }
        else if (index_pointer != a_property_instance) // the instance points elsewhere
        {
            a_property->RemoveReference(a_property_instance, &index_pointer);
            index_pointer = a_property_instance;
            a_property->AddReference(a_property_instance, &index_pointer);
        }
    }

    size_t Model::Instanciate()
    {
        for (auto &pair : m_indexes)
        {
            auto index = pair.first->Instanciate();
            pair.second.PushBack(index);
        }
        m_size++;
        return m_size - 1;
    }

    void Model::DeleteInstance(size_t a_index)
    {
        auto last_index = m_size - 1;

        for (auto &pair : m_indexes)
        {
            pair.second.Delete(a_index);
        }
        for (auto &reference : m_references[a_index])
        {
            *reference = last_index;
        }
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

            // for (auto it = pair.second.begin(); it != pair.second.end() - 1; it++)
            // {
            //     result += StringConversions::ToString(*it);
            //     result += ", ";
            // }

            // result += StringConversions::ToString(pair.second.back());
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

    const std::unordered_map<Property *, Pool<size_t>> &Model::Children() const
    {
        return m_indexes;
    }

    std::vector<std::vector<Property *>> Model::VisitProperties()
    {
        std::vector<std::vector<Property *>> result;

        for (auto &pair : m_indexes)
        {
            for (auto &child : pair.first->VisitProperties())
            {
                result.emplace_back();
                result.back().push_back(this);
                std::copy(child.begin(), child.end(), std::back_inserter(result.back()));
            }
        }

        return result;
    }
} // end namespace cement