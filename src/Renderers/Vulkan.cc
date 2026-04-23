module;
#include <vulkan/vulkan_raii.hpp>
export module FVulkan;

import "GLFW/glfw3.h";

import std;
import FResource;
import FObjects;
import FRenderer;
import glm;
import FError;

export
{
    class VulkanRenderer : public Renderer
    {
    public:
        ~VulkanRenderer();

        void free();

        // Load resources
        void load(Resource* res) override;
        // Unload resources
        void unload(Resource* res) override;
        void update();
    private:
    };
}
