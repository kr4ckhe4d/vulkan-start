#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

int main() {
    // Initialize Vulkan instance
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Test";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    VkInstance instance;
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if (result == VK_SUCCESS) {
        std::cout << "Vulkan instance created successfully!!!!" << std::endl;
        
        // Enumerate physical devices
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        
        if (deviceCount == 0) {
            std::cout << "No Vulkan-compatible devices found." << std::endl;
        } else {
            std::cout << "Found " << deviceCount << " Vulkan-compatible device(s)." << std::endl;
        }
        
        vkDestroyInstance(instance, nullptr);
    } else {
        std::cout << "Failed to create Vulkan instance. Error code: " << result << std::endl;
        return -1;
    }

    return 0;
}
