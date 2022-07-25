#include "../Model.h"
#include "../StringConversions.h"
#include "../Log.h"

namespace cement
{
    Model::Model(size_t a_id, const std::string &a_name, bool a_shared) : Property(a_id, a_name, a_shared),
                                                             m_size(0)
    {
    }

    Id Model::Instanciate()
    {
        for (auto &index : m_indexes)
        {
            unsigned long instance = NO_VALUE;
            if (!index->GetIndexed()->IsShared())
            {
                instance = index->GetIndexed()->Instanciate();
            }
            auto position = index->Instanciate();
            index->SetValue(position, instance);
        }
        m_size++;
        m_instance_added.Emit(m_size - 1);
        return m_size - 1;
    }

    void Model::InternalDeleteInstance(Id a_instance)
    {
        for (auto index : m_indexes)
        {
            if (!index->GetIndexed()->IsShared()) // the property value is owned by this model and can be deleted
            {
                index->GetIndexed()->DeleteInstance(index->Get(a_instance));
            }
            index->DeleteInstance(a_instance);
        }
    }

    size_t Model::Size() const
    {
        return m_size;
    }

    std::string Model::Print() const
    {
        std::string result;

        result += Property::Print();

        result += "\n";
        for (auto &index : m_indexes)
        {
            result += "  ";
            result += index->Print();
        }

        return result;
    }

    PropertyType Model::Type() const
    {
        return pt_model;
    }

    size_t Model::Depth() const
    {
        size_t counter = 1;
        size_t max = 1;
        for (auto &index : m_indexes)
        {
            size_t depth = index->GetIndexed()->Depth();
            if (depth > max)
            {
                max = depth;
            }
        }
        counter += max;

        return counter;
    }

    size_t Model::PropertyCount() const
    {
        return m_indexes.size();
    }

    std::vector<std::vector<Property *>> Model::VisitProperties()
    {
        std::vector<std::vector<Property *>> result;

        for (auto &index : m_indexes)
        {
            for (auto &child : index->VisitProperties())
            {
                result.emplace_back();
                result.back().push_back(this);
                std::copy(child.begin(), child.end(), std::back_inserter(result.back()));
            }
        }

        return result;
    }

    void Model::AddIndex(Index *a_index)
    {
        m_indexes.insert(a_index);
    }

    const std::set<Index *> &Model::GetIndexes() const
    {
        return m_indexes;
    }

    void Model::GetPointedValue(Id a_instance, std::string &a_string_value)
    {
        a_string_value = GetName() + "#" + std::to_string(a_instance);
    }
} // end namespace cement
