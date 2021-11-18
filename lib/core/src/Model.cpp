#include "../Model.h"
#include "../StringConversions.h"

namespace cement
{
    Model::Model(const std::string &a_name) : Property(a_name),
                                              m_size(0)
    {
    }

    size_t Model::Instanciate()
    {
        for (auto &index : m_indexes)
        {
            auto instance = index->GetIndexed()->Instanciate();
            auto position = index->Instanciate();
            index->SetValue(position, instance);
        }
        m_size++;
        return m_size - 1;
    }

    void Model::DeleteInstance(size_t a_instance)
    {

        if (HasReference(a_instance))
        {
            // TODO LOG
            return;
        }

        auto last_index = m_size - 1;

        for (auto &index : m_indexes)
        {
            index->DeleteInstance(a_instance);
        }

        // for (auto &reference : m_references[a_instance])
        // {
        //     for (auto &index : reference.second)
        //     {
        //         dynamic_cast<Model *>(reference.first)->SetIndex(this, last_index, a_instance);
        //     }
        // }
    }

    const size_t Model::Size() const
    {
        return m_size;
    }

    std::string Model::Print() const
    {
        std::string result;

        result += Property::Print();

        for (auto &index : m_indexes)
        {
            result += "\n  ";
            result += index->Print();
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

    const size_t Model::PropertyCount() const
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

    std::set<Index *> Model::GetIndexes() const { return m_indexes; }
} // end namespace cement