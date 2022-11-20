#pragma once

#include "Instances.h"

namespace cement
{
    class Model;

    class Index : public Instances<Id>
    {
        friend class Registry;

    public:
        virtual PropertyType Type() const override;

        virtual void GetPointedValue(Id a_instance, std::string &a_string_value) override;

        Property* GetIndexed() const;
        Model* GetModel() const;

        virtual Id Instanciate() override;
        virtual void InternalDeleteInstance(Id a_instance) override;

        size_t Depth() const;
        virtual std::string Print() const override;

        template<typename T>
        void SetPointedValue(Id a_model_instance, const T& a_val)
        {
            if (GetPropType<T>() == m_indexed->Type())
            {
                auto prop = static_cast<Instances<T>*>(m_indexed);
                auto sub_instance = Get(a_model_instance);
                prop->SetValue(sub_instance, a_val);
            }
        }

    private:
        Index(Id a_id, const std::string &a_name, Property *a_indexed, Model* a_model);

        Property* m_indexed{ nullptr };
        Model* m_model{ nullptr };

    };
} // end namespace cement
