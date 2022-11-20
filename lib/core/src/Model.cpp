#include "../Model.h"
#include "../StringConversions.h"


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
            index->Instanciate();
        }

        auto id = m_sparse.AddElem(m_size);
        m_instance_added.Emit(id);
        ++m_size;
        return id;
    }

    void Model::InternalDeleteInstance(Id a_instance)
    {
        for (auto index : m_indexes)
        {
            index->DeleteInstance(a_instance);
        }

        --m_size;
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
            if (index == *--m_indexes.end())
            {
                result += "└";
            }
            else
            {
                result += "├";
            }
            result += index->Print();
            result += "\n";
        }

        return result;
    }

    PropertyType Model::Type() const
    {
        return pt_model;
    }

    size_t Model::Depth() const
    {
        size_t max_depth = 0;

        auto greatest_depth = [&](const Index* a_index1)
        {
            max_depth = std::max(a_index1->Depth(), max_depth);
        };

        std::for_each(m_indexes.begin(), m_indexes.end(), greatest_depth);

        return max_depth;
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
