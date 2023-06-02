#include <iostream>

#include "boost/stacktrace.hpp"
#include "core/core.hpp"
#include <string>

using namespace emit::core::data;

class MyChangeListener : public PropertyGroupChangeListener {
  public:
    virtual void
    ApplyProperties(const std::string &property_group_id) override {
        std::cout << "Group has changed: " << property_group_id << std::endl;
    }
};

int main() {
    std::cout << "Hello Vulkan" << std::endl;
    PropertyGroup group1("triton", "Water Surface");
    group1.RegisterProperty(
        Property<float>("height", 0.0f, "Ocean Height (m)"));

    PropertyGroup group2("silverlining", "Sky");
    group2.RegisterProperty(
        Property<float>("brightness", 0.0f, "Sky Brightness"));

    MyChangeListener listener;
    group1.AddChangeListener(&listener);
    group2.AddChangeListener(&listener);

    group1.Apply();
    group2.Apply();

    return 0;
}