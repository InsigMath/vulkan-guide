﻿// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vk_types.h>

namespace vkinit {

	//vulkan init code goes here
	VkCommandPoolCreateInfo command_pool_create_info(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags = 0);
	VkCommandBufferAllocateInfo command_buffer_allocate_info(VkCommandPool pool, uint32_t count = 1, VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
	VkPipelineShaderStageCreateInfo pipeline_shader_stage_create_info(VkShaderStageFlagBits stage, VkShaderModule shaderModule);
	VkPipelineVertexInputStateCreateInfo vertex_input_state_create_info();
	VkPipelineInputAssemblyStateCreateInfo input_assembly_create_info(VkPrimitiveTopology topology);
	VkFenceCreateInfo fence_create_info(VkFenceCreateFlags flags);
	VkSemaphoreCreateInfo semaphore_create_info(VkSemaphoreCreateFlags flags = 0);
	VkSubmitInfo submit_info(VkCommandBuffer* cmd);
	VkPresentInfoKHR present_info();
	VkCommandBufferBeginInfo command_buffer_begin_info(VkCommandBufferUsageFlags flags = 0);
	VkRenderPassBeginInfo renderpass_begin_info(VkRenderPass renderPass, VkExtent2D windowExtent, VkFramebuffer framebuffer);
	VkPipelineRasterizationStateCreateInfo rasterization_state_create_info(VkPolygonMode polygonMode);
	VkPipelineMultisampleStateCreateInfo multisampling_state_create_info();
	VkPipelineColorBlendAttachmentState color_blend_attachment_state();
	VkPipelineLayoutCreateInfo pipeline_layout_create_info();
}

