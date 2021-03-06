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

        virtual void GetPointedValue(size_t a_instance, std::string &a_string_value) override;

        Property* GetIndexed() const;
        Model* GetModel() const;

        virtual std::string Print() const override;

    private:
        Index(const std::string &a_name, Property *a_indexed, Model* a_model);

        Property* m_indexed{ nullptr };
        Model* m_model{ nullptr };
    };
} // end namespace cement
