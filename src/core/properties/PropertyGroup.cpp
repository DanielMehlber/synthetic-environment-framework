#include "PropertyGroup.hpp"

using namespace emit::core::data;

emit::core::data::PropertyGroup::PropertyGroup(
    std::string id, std::string display_name = "Unnamed Group")
    : m_id{id}, m_display_name{display_name} {}

emit::core::data::PropertyGroup::~PropertyGroup() {
    RemoveAllChangeListeners();
}

void emit::core::data::PropertyGroup::Apply() {
    // TODO: this could be async
    for (auto listener : m_change_listeners) {
        listener->ApplyProperties(m_id, m_changed_props);
    }

    m_changed_props.clear();
}

void PropertyGroup::AddChangeListener(PropertyGroupChangeListener *listener) {
    if (!/* not */ HasChangeListener(listener)) {
        m_change_listeners.push_back(listener);
    }
}

void PropertyGroup::RemoveChangeListener(
    PropertyGroupChangeListener *listener) {
    if (HasChangeListener(listener)) {
        m_change_listeners.remove(listener);
    }
}

void PropertyGroup::RemoveAllChangeListeners() { m_change_listeners.clear(); }
