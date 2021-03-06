#ifndef ATTRIBUTE_DEFINITION_H
#define ATTRIBUTE_DEFINITION_H

#include "types.h"

namespace Saklib
{
	class Constraint;

    /*
    Attribute_Definition
    ====================================================================================================
    Abstract class the contains flyweight information to create a given Attribute based on it.

    */
    class Attribute_Definition
    {
    public:
        // Special 6
        //============================================================
        Attribute_Definition() = default;
        virtual ~Attribute_Definition() = default;

        Attribute_Definition(Attribute_Definition const& other) = delete;
        Attribute_Definition& operator=(Attribute_Definition const& other) = delete;
        
        String const& name() const { return v_name(); }
        Type_Enum type_enum() const     { return v_type_enum(); }
        String type_string() const { return v_type_string(); }
        //Constraint const*const constraint() const  { return v_constraint(); }
        
        bool is_simple_type() const     { return Saklib::is_simple_type(type_enum()); }
        bool is_vector_type() const     { return Saklib::is_vector_type(type_enum()); }
        //bool is_constrained() const     { return v_is_constrained(); }

    protected:
        // Virtuals
        //============================================================
        virtual String const& v_name() const = 0;
        virtual Type_Enum v_type_enum() const = 0;
        virtual String v_type_string() const = 0;
        //virtual Constraint const*const v_constraint() const = 0;

        //virtual bool v_is_constrained() const = 0;

    };

	Shptr<Attribute_Definition> make_shared_Attribute_Definition(String const& name, Type_Enum type);

	template <Type_Enum TE>
	Shptr<Attribute_Definition> make_shared_Attribute_Definition(String const& name)
	{
		return Shptr<Attribute_Definition>(new Attribute_Definition_Type<TypeHolder_st<TE> >(name));
	}

	/*
	Shptr<Attribute_Definition> make_shared_Attribute_Definition(String const& name, Type_Enum type, Uptr<Constraint>&& constraint = Uptr<Constraint>());

	template <Type_Enum TE, typename Constraint_Class, typename... Args>
	Shptr<Attribute_Definition> make_shared_Attribute_Definition(String const& name, Args... args)
	{
		return Shptr<Attribute_Definition>(new Attribute_Definition_Type<TypeHolder_st<TE> >(name, Uptr<Constraint_Class>(new Constraint_Class(std::forward<Args>(args)...))));
	}
	*/
} // namespace Saklib

#endif // ATTRIBUTE_DEFINITION_H
