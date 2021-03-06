#pragma once

#include "Extras/OVR_Math.h"
#include "VulkanFwd.h"
#include <iosfwd>

#include <string>

using namespace std;
using namespace OVR;

class Model;

namespace vulkan {
    class VulkanMemoryManager
    {
        private:
            VulkanContext& context;
            VulkanDescriptors& descriptors;

            VkBuffer vertexBuffer;
            VkDeviceMemory vertexMemory;
            VkBuffer indicesBuffer;
            VkDeviceMemory indicesMemory;
            VkBuffer uniformBuffer;
            VkDeviceMemory uniformMemory;
			VkImage depthImage;
			VkDeviceMemory depthMemory;
			VkImageView depthView;

			int colorUniformOffset;

            void allocateMemory(VkBuffer& buffer, VkDeviceMemory& memory, VkDeviceSize size, VkBufferUsageFlags usage, string objectName);
            uint32_t calculateMemoryTypeIndex(uint32_t typeBits, VkMemoryPropertyFlags requiredFlags);
        public:
            VulkanMemoryManager(VulkanContext& context, VulkanDescriptors& descriptors);
            void init();
            VkBuffer getVertexBuffer() { return vertexBuffer; }
            VkBuffer getIndicesBuffer() { return indicesBuffer; }
			VkImageView getDepthView() { return depthView; }
            void load(const Model& model);
            void setUniform(Matrix4f mvp, Matrix4f rot, Vector4f color);
			void createDepthBuffer(int width, int height);
            virtual ~VulkanMemoryManager();
    };
}
