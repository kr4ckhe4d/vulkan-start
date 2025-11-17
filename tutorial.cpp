#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
uint32_t glfwExtensionCount = 0;
const char **glfwExtensions;

const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class HelloTriangleApplication
{
public:
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow *window;
    VkInstance instance;

    void initWindow()
    {
        // Initialize the GLFW library
        glfwInit();

        // Because GLFW was originally designed to create an OpenGL context, we need to tell it to not create an OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // Because handling resized windows takes special care that we'll look into later, disable it for now with another window hint call
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // The first three parameters specify the width, height and title of the window.
        // The fourth parameter allows you to optionally specify a monitor to open the window on and the last parameter is only relevant to OpenGL.
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan()
    {
        createInstance();
    }

    void createInstance()
    {
        // Validation layers check
        if (enableValidationLayers && !checkValidationLayerSupport())
        {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        // This data is technically optional, but it may provide some useful information to the driver
        VkApplicationInfo appInfo{};
        // Many structs in Vulkan require you to explicitly specify the type in the sType member
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle!";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // This struct is mandatory
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // GLFW has a handy built-in function that returns the extension(s) it needs to do that which we can pass to the struct
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        // VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }

        // uint32_t extensionCount = 0;
        // vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        // std::vector<VkExtensionProperties> extensions(extensionCount);
        // vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        // std::cout << "available extensions:\n";

        // for (const auto &extension : extensions)
        // {
        //     std::cout << '\t' << extension.extensionName << '\n';
        // }
    }

    bool checkValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char *layerName : validationLayers)
        {
            bool layerFound = false;

            for (const auto &layerProperties : availableLayers)
            {
                if (strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound)
            {
                return false;
            }
        }

        return true;
    }

    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }
};

int main()
{
    HelloTriangleApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}