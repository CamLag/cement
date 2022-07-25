#pragma once

#include "Instances.h"

namespace cement
{
    class Model;
    class Index : public Instances<unsigned long>
    {
        friend class Registry;

    public:
        virtual PropertyType Type() const override;

        virtual void GetPointedValue(Id a_instance, std::string &a_string_value) override;

        Property* GetIndexed() const;
        Model* GetModel() const;

        virtual std::string Print() const override;

    private:
        Index(Id a_id, const std::string &a_name, Property *a_indexed, Model* a_model);

        Property* m_indexed{ nullptr };
        Model* m_model{ nullptr };
    };
} // end namespace cement
