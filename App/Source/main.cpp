#include <iostream>
#include <vector>

#include "wgpu.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "wgpu/glfw3webgpu.h"

WGPUAdapter requestAdapter(WGPUInstance instance, const WGPURequestAdapterOptions* options)
{
    struct RequestData
    {
        WGPUAdapter adapter = nullptr;
        bool requestEnded = false;
    } requestData;

    auto adapterRequestCallback = [](WGPURequestAdapterStatus status, WGPUAdapter adapter, const char* message, void* userData)
    {
        RequestData& data = *(RequestData*)userData;
        // Dont do any error checking, lmao weaklings
        data.adapter = adapter;
        data.requestEnded = true;
    };

    wgpuInstanceRequestAdapter(instance, options, adapterRequestCallback, (void*)&requestData);

    return requestData.adapter;
}

void inspectAdapter(WGPUAdapter adapter) {
	std::vector<WGPUFeatureName> features;
	size_t featureCount = wgpuAdapterEnumerateFeatures(adapter, nullptr);
	features.resize(featureCount);
	wgpuAdapterEnumerateFeatures(adapter, features.data());

	std::cout << "Adapter features:" << '\n';
	for (auto f : features) {
		std::cout << " - " << f << '\n';
	}

	WGPUSupportedLimits limits = {};
	limits.nextInChain = nullptr;
	bool success = wgpuAdapterGetLimits(adapter, &limits);
	if (success) {
		std::cout << "Adapter limits:" << '\n';
		std::cout << " - maxTextureDimension1D: " << limits.limits.maxTextureDimension1D << '\n';
		std::cout << " - maxTextureDimension2D: " << limits.limits.maxTextureDimension2D << '\n';
		std::cout << " - maxTextureDimension3D: " << limits.limits.maxTextureDimension3D << '\n';
		std::cout << " - maxTextureArrayLayers: " << limits.limits.maxTextureArrayLayers << '\n';
		std::cout << " - maxBindGroups: " << limits.limits.maxBindGroups << '\n';
		std::cout << " - maxDynamicUniformBuffersPerPipelineLayout: " << limits.limits.maxDynamicUniformBuffersPerPipelineLayout << '\n';
		std::cout << " - maxDynamicStorageBuffersPerPipelineLayout: " << limits.limits.maxDynamicStorageBuffersPerPipelineLayout << '\n';
		std::cout << " - maxSampledTexturesPerShaderStage: " << limits.limits.maxSampledTexturesPerShaderStage << '\n';
		std::cout << " - maxSamplersPerShaderStage: " << limits.limits.maxSamplersPerShaderStage << '\n';
		std::cout << " - maxStorageBuffersPerShaderStage: " << limits.limits.maxStorageBuffersPerShaderStage << '\n';
		std::cout << " - maxStorageTexturesPerShaderStage: " << limits.limits.maxStorageTexturesPerShaderStage << '\n';
		std::cout << " - maxUniformBuffersPerShaderStage: " << limits.limits.maxUniformBuffersPerShaderStage << '\n';
		std::cout << " - maxUniformBufferBindingSize: " << limits.limits.maxUniformBufferBindingSize << '\n';
		std::cout << " - maxStorageBufferBindingSize: " << limits.limits.maxStorageBufferBindingSize << '\n';
		std::cout << " - minUniformBufferOffsetAlignment: " << limits.limits.minUniformBufferOffsetAlignment << '\n';
		std::cout << " - minStorageBufferOffsetAlignment: " << limits.limits.minStorageBufferOffsetAlignment << '\n';
		std::cout << " - maxVertexBuffers: " << limits.limits.maxVertexBuffers << '\n';
		std::cout << " - maxVertexAttributes: " << limits.limits.maxVertexAttributes << '\n';
		std::cout << " - maxVertexBufferArrayStride: " << limits.limits.maxVertexBufferArrayStride << '\n';
		std::cout << " - maxInterStageShaderComponents: " << limits.limits.maxInterStageShaderComponents << '\n';
		std::cout << " - maxComputeWorkgroupStorageSize: " << limits.limits.maxComputeWorkgroupStorageSize << '\n';
		std::cout << " - maxComputeInvocationsPerWorkgroup: " << limits.limits.maxComputeInvocationsPerWorkgroup << '\n';
		std::cout << " - maxComputeWorkgroupSizeX: " << limits.limits.maxComputeWorkgroupSizeX << '\n';
		std::cout << " - maxComputeWorkgroupSizeY: " << limits.limits.maxComputeWorkgroupSizeY << '\n';
		std::cout << " - maxComputeWorkgroupSizeZ: " << limits.limits.maxComputeWorkgroupSizeZ << '\n';
		std::cout << " - maxComputeWorkgroupsPerDimension: " << limits.limits.maxComputeWorkgroupsPerDimension << '\n';
	}

	WGPUAdapterProperties properties = {};
	properties.nextInChain = nullptr;
	wgpuAdapterGetProperties(adapter, &properties);
	std::cout << "Adapter properties:" << '\n';
	std::cout << " - vendorID: " << properties.vendorID << '\n';
	std::cout << " - deviceID: " << properties.deviceID << '\n';
	std::cout << " - name: " << properties.name << '\n';
	if (properties.driverDescription) {
		std::cout << " - driverDescription: " << properties.driverDescription << '\n';
	}
	std::cout << " - adapterType: " << properties.adapterType << '\n';
	std::cout << " - backendType: " << properties.backendType << '\n';
}

WGPUDevice requestDevice(WGPUAdapter adapter, const WGPUDeviceDescriptor* desc)
{
    struct RequestData
    {
        WGPUDevice device = nullptr;
        bool requestEnded = false;
    } requestData;

    auto deviceRequestCallback = [](WGPURequestDeviceStatus status, WGPUDevice device, const char* message, void* userData)
    {
        RequestData& data = *(RequestData*)userData;
        data.device = device;
        data.requestEnded = true;
    };

    wgpuAdapterRequestDevice(adapter, desc, deviceRequestCallback, (void*)&requestData);

    return requestData.device;
}

void inspectDevice(WGPUDevice device) {
	std::vector<WGPUFeatureName> features;
	size_t featureCount = wgpuDeviceEnumerateFeatures(device, nullptr);
	features.resize(featureCount);
	wgpuDeviceEnumerateFeatures(device, features.data());

	std::cout << "Device features:" << '\n';
	for (auto f : features) {
		std::cout << " - " << f << '\n';
	}

	WGPUSupportedLimits limits = {};
	limits.nextInChain = nullptr;
	bool success = wgpuDeviceGetLimits(device, &limits);
	if (success) {
		std::cout << "Device limits:" << '\n';
		std::cout << " - maxTextureDimension1D: " << limits.limits.maxTextureDimension1D << '\n';
		std::cout << " - maxTextureDimension2D: " << limits.limits.maxTextureDimension2D << '\n';
		std::cout << " - maxTextureDimension3D: " << limits.limits.maxTextureDimension3D << '\n';
		std::cout << " - maxTextureArrayLayers: " << limits.limits.maxTextureArrayLayers << '\n';
		std::cout << " - maxBindGroups: " << limits.limits.maxBindGroups << '\n';
		std::cout << " - maxDynamicUniformBuffersPerPipelineLayout: " << limits.limits.maxDynamicUniformBuffersPerPipelineLayout << '\n';
		std::cout << " - maxDynamicStorageBuffersPerPipelineLayout: " << limits.limits.maxDynamicStorageBuffersPerPipelineLayout << '\n';
		std::cout << " - maxSampledTexturesPerShaderStage: " << limits.limits.maxSampledTexturesPerShaderStage << '\n';
		std::cout << " - maxSamplersPerShaderStage: " << limits.limits.maxSamplersPerShaderStage << '\n';
		std::cout << " - maxStorageBuffersPerShaderStage: " << limits.limits.maxStorageBuffersPerShaderStage << '\n';
		std::cout << " - maxStorageTexturesPerShaderStage: " << limits.limits.maxStorageTexturesPerShaderStage << '\n';
		std::cout << " - maxUniformBuffersPerShaderStage: " << limits.limits.maxUniformBuffersPerShaderStage << '\n';
		std::cout << " - maxUniformBufferBindingSize: " << limits.limits.maxUniformBufferBindingSize << '\n';
		std::cout << " - maxStorageBufferBindingSize: " << limits.limits.maxStorageBufferBindingSize << '\n';
		std::cout << " - minUniformBufferOffsetAlignment: " << limits.limits.minUniformBufferOffsetAlignment << '\n';
		std::cout << " - minStorageBufferOffsetAlignment: " << limits.limits.minStorageBufferOffsetAlignment << '\n';
		std::cout << " - maxVertexBuffers: " << limits.limits.maxVertexBuffers << '\n';
		std::cout << " - maxVertexAttributes: " << limits.limits.maxVertexAttributes << '\n';
		std::cout << " - maxVertexBufferArrayStride: " << limits.limits.maxVertexBufferArrayStride << '\n';
		std::cout << " - maxInterStageShaderComponents: " << limits.limits.maxInterStageShaderComponents << '\n';
		std::cout << " - maxComputeWorkgroupStorageSize: " << limits.limits.maxComputeWorkgroupStorageSize << '\n';
		std::cout << " - maxComputeInvocationsPerWorkgroup: " << limits.limits.maxComputeInvocationsPerWorkgroup << '\n';
		std::cout << " - maxComputeWorkgroupSizeX: " << limits.limits.maxComputeWorkgroupSizeX << '\n';
		std::cout << " - maxComputeWorkgroupSizeY: " << limits.limits.maxComputeWorkgroupSizeY << '\n';
		std::cout << " - maxComputeWorkgroupSizeZ: " << limits.limits.maxComputeWorkgroupSizeZ << '\n';
		std::cout << " - maxComputeWorkgroupsPerDimension: " << limits.limits.maxComputeWorkgroupsPerDimension << '\n';
	}
}

int main(int argc, char const *argv[])
{
    WGPUInstanceDescriptor instanceDesc = {};
    instanceDesc.nextInChain = nullptr;
    WGPUInstance instance = wgpuCreateInstance(&instanceDesc);

    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window;
    window = glfwCreateWindow(1280, 720, "Title", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    WGPUSurface surface = glfwGetWGPUSurface(instance, window);

	WGPURequestAdapterOptions adapterOpts = {};
	adapterOpts.nextInChain = nullptr;
	adapterOpts.compatibleSurface = surface;
    WGPUAdapter adapter = requestAdapter(instance, &adapterOpts);
    inspectAdapter(adapter);

    WGPUDeviceDescriptor deviceDesc = {};
    deviceDesc.nextInChain = nullptr;
    deviceDesc.label = "MyDevice";
    deviceDesc.requiredFeatureCount = 0;
    deviceDesc.requiredLimits = nullptr;
    deviceDesc.defaultQueue.nextInChain = nullptr;
    deviceDesc.defaultQueue.label = "Default queue";
    WGPUDevice device = requestDevice(adapter, &deviceDesc);

    auto onDeviceError = [](WGPUErrorType type, const char* message, void*)
    {
        std::cout << "Uncaptured wgpu device error:\n Type:" << type;
        if(message) std::cout << "\n(" << message << ")\n";
    };
    wgpuDeviceSetUncapturedErrorCallback(device, onDeviceError, nullptr);
    inspectDevice(device);
    

    while(!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    wgpuInstanceRelease(instance);
    return 0;
}
