#pragma once

#include <memory>
#include <string>
#include <typeinfo>

namespace emit::core::data {
/**
 * @brief This base class in necessary to store the Property without type
 * arguments in an unordered map. When loading a Property by its id, we do not
 * know the type of its value.
 */
class PropertyBase {
  public:
    /**
     * @return type information of this properties value
     */
    virtual inline std::type_info const &GetType() const = 0;

    /**
     * @return id of this property
     */
    virtual inline const std::string &GetId() const = 0;

    /**
     * @brief checks if the type of this property is equal to the passed type
     * @tparam T type to check
     * @return true, if passed type equals type of properties value
     */
    template <typename T> inline bool IsOfType() const {
        return GetType() == typeid(T);
    }
};

/**
 * @brief A Property holding a value of some type.
 */
template <typename T> class Property : public PropertyBase {
  protected:
    const std::string m_id;
    const std::string m_display_name;
    std::shared_ptr<T> m_value;

  public:
    // constructors
    Property() = delete;

    /**
     * @brief creates a new property by value
     * @param prop_id id of the property
     * @param prop_value init value of the property and its type
     * @param prop_display_name optional display name
     */
    Property(std::string prop_id, T prop_value, std::string prop_display_name);

    Property(const Property &);
    Property(Property &&) = delete;

    // member functions
    inline std::type_info const &GetType() const override { return typeid(T); }
    inline const std::string &GetId() const override { return m_id; }
    inline T GetValue() const;
    inline void SetValue(const T &new_value);
};

template <typename T>
Property<T>::Property(std::string prop_id, T prop_value,
                      std::string prop_display_name)
    : m_id{prop_id}, m_display_name{prop_display_name} {
    m_value = std::make_shared<T>(prop_value);
}

template <typename T>
Property<T>::Property(const Property &other_property)
    : m_id{other_property.m_id}, m_display_name{other_property.m_display_name} {
    // duplicates shared pointer. Both the current and copied properties access
    // the same value
    m_value = other_property.m_value;
}

template <typename T> inline T Property<T>::GetValue() const {
    return *m_value.get();
}

template <typename T> inline void Property<T>::SetValue(const T &new_value) {
    *(m_value.get()) = new_value;
}

} // namespace emit::core::data
