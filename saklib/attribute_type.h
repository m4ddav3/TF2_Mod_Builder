#ifndef ATTRIBUTE_TYPE_H
#define ATTRIBUTE_TYPE_H

#include "types.h"
#include "all_type_traits.h"
#include "fwd_attribute_type.h"
#include "attribute.h"
#include "attribute_definition_type.h"
//#include "constraint_type.h"
#include <cassert>

namespace Saklib
{
	/*
    Attribute_Type<T>
    ====================================================================================================
    Templated subclass for storage of simple types
    */ 
    template <typename T>
    class Attribute_Type :
        public Attribute
    {
    public:
        using stored_type = T;
        using stored_type_traits = Type_Traits < stored_type >;

        using definition_type = Attribute_Definition_Type < stored_type >;
        //using constraint_type = Constraint_Type < stored_type >;

        // Special 6
        //============================================================
        explicit Attribute_Type(Shptr<Attribute_Definition> const& definition) :
            Attribute(),
            m_definition(definition), // if this is nullptr the constructor will fail...
            mp_definition(dynamic_cast<definition_type*>(m_definition.get())),
            mr_name(m_definition->name()),
            //mp_constraint(mp_definition->constraint()),
            m_value()
        {
            assert(definition);                                 // there was actually a definition
            assert(mp_definition);                              // it was the right type
            assert(v_type_enum() != Type_Enum::Undefined);      // this isn't an Undefined Attribute
            stored_type_traits::set_to_default_value(m_value);
        }
        ~Attribute_Type() override = default;

        // NO COPYING
        Attribute_Type(Attribute_Type const& other) = delete;
        Attribute_Type& operator=(Attribute_Type const& other) = delete;
		/*
        // Constraint Interface
        //============================================================
        constraint_type const*const constraint() const
        {
            return mp_constraint;
        }
        bool can_set_to(stored_type const& value) const
        {
            if (mp_constraint != nullptr)
                return mp_constraint->can_be(value);
            else
                return true;
        }
		*/
        // Value Interface
        //============================================================
        stored_type& get()
        {
            return m_value;
        }
        stored_type const& get() const
        {
            return m_value;
        }
        void set(stored_type const& value)
        {
            m_value = value;
            //adjust_attribute_value(m_value);
        }
		/*
        bool try_set(stored_type const& value)
        {
            if (can_set_to(value))
            {
                set(value);
                return true;
            }
            else
                return false;
        }
		*/
    protected:
        // Virtuals
        //============================================================
        String const& v_name() const override final  { return mr_name; }
        Type_Enum v_type_enum() const override final      { return stored_type_traits::type_enum(); }
        String v_type_string() const override final  { return stored_type_traits::type_string(); }

        //bool v_is_constrained() const override final      { return mp_constraint != nullptr; }

    private:
        // shared_ptr ensures the definition's lifetime will be at least as long as this
        Shptr<Attribute_Definition> m_definition;

        // locally cached and pre-cast references
        definition_type const*const mp_definition;  // lifetime is that of m_definition
        String const& mr_name;                 // lifetime is that of m_definition
        //constraint_type const*const mp_constraint;  // lifetime is that of m_definition

        // stored data
        stored_type m_value;
    };



    /*
    Attribute_Type<Vector<T>>
    ====================================================================================================
    Specialisation for storage of vectors of simple types
    */
    template <typename T>
    class Attribute_Type<Vector<T>> :
        public Attribute
    {
    public:
        using stored_type = Vector<T>;
        using stored_type_traits = Type_Traits < stored_type >;

        using value_type = T;
        using value_type_traits = Type_Traits<value_type>;
		
        using definition_type = Attribute_Definition_Type < stored_type >;
        //using constraint_type = Constraint_Type < stored_type >;

        // Special 6
        //============================================================
        explicit Attribute_Type(Shptr<Attribute_Definition> const& definition) :
            Attribute(),
            m_definition(definition), // if this is nullptr the constructor will fail...
            mp_definition(dynamic_cast<definition_type*>(m_definition.get())),
            mr_name(m_definition->name()),
            //mp_constraint(mp_definition->constraint())
			m_vector()
        {
            assert(definition);                                 // there was actually a definition
            assert(mp_definition);                              // it was the right type
            assert(v_type_enum() != Type_Enum::Undefined);      // this isn't an Undefined Attribute
        }
        ~Attribute_Type() override = default;

        // NO COPYING
        Attribute_Type(Attribute_Type const& other) = delete;
        Attribute_Type& operator=(Attribute_Type const& other) = delete;
		/*
        // Constraint Interface
        //============================================================
        constraint_type const*const constraint() const
        {
            return mp_constraint;
        }
        bool can_set_vector_to(stored_type const& vector_value) const
        {
            if (mp_constraint)
                return mp_constraint->vector_can_be(vector_value);
            else
                return true;
        }
        bool can_set_value_to(value_type const& value) const
        {
            if (mp_constraint)
                return mp_constraint->value_can_be(value);
            else
                return true;
        }
		*/
        // Vector Interface
        //============================================================
        // TESTING TEMP
        stored_type& vector()
        {
            return m_vector;
        }
        stored_type const& vector() const
        {
            return m_vector;
        }
        void set_vector(stored_type const& vector_value)
        {
            m_vector = vector_value;
            //adjust_attribute_value(m_vector);
            //for (auto& value : m_vector)
             //   adjust_attribute_value(value);
        }
		/*
        bool try_set_vector(stored_type const& vector_value)
        {
            if (can_set_vector_to(vector_value))
            {
                set_vector(vector_value);
                return true;
            }
            else
                return false;
        }
		*/
        // Seriously how am I going to apply constraints to some of these operations...should I just let the user decide?
        bool empty() const;
        size_type size() const;
        void clear();

        value_type const& at(size_type index) const;
        value_type const& front() const;
        value_type const& back() const;

    protected:
        // Virtuals
        //============================================================
        String const& v_name() const override final  { return mr_name; }
        Type_Enum v_type_enum() const override final      { return stored_type_traits::type_enum(); }
        String v_type_string() const override final  { return stored_type_traits::type_string(); }

        //bool v_is_constrained() const override final      { return mp_constraint != nullptr; }

    private:
        // shared_ptr ensures the definition's lifetime will be at least as long as this
        Shptr<Attribute_Definition> m_definition;

        // locally cached and pre-cast references
        definition_type const*const mp_definition;  // lifetime is that of m_definition
        String const& mr_name;                 // lifetime is that of m_definition
        //constraint_type const*const mp_constraint;  // lifetime is that of m_definition

        // stored data
        stored_type m_vector;
    };


    /*
    Casting Functions
    ====================================================================================================
    If you want to use the enum instead, do it here
    */
    template <typename T>
    Attribute_Type<T>* attribute_type_cast(Attribute* attribute)
    {
        return dynamic_cast<Attribute_Type<T>*>(attribute);
    }
    template <typename T>
    Attribute_Type<T>const*const attribute_type_cast(Attribute const*const attribute)
    {
        return dynamic_cast<Attribute_Type<T>const*const>(attribute);
    }

    template <Type_Enum TE>
    Attribute_Type<TypeHolder_st<TE> >* attribute_enum_cast(Attribute* attribute)
    {
        return dynamic_cast<Attribute_Type<TypeHolder_st<TE> >*>(attribute);
    }
    template <Type_Enum TE>
    Attribute_Type<TypeHolder_st<TE> > const*const attribute_enum_cast(Attribute const*const attribute)
    {
        return dynamic_cast<Attribute_Type<TypeHolder_st<TE> > const*const>(attribute);
    }

} // namespace Saklib

#endif // ATTRIBUTE_TYPE_H
