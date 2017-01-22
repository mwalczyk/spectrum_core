#pragma once

#include <memory>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <functional>

#include "Platform.h"

namespace vksp
{
	
	class Instance;
	using InstanceRef = std::shared_ptr<Instance>;

	class Instance
	{
	public:

		class Options
		{
		public:
			
			Options();

			//! Specify the names of all instance layers that should be enabled. By default,
			//! only the VK_LAYER_LUNARG_standard_validation layer is enabled.
			Options& requiredLayers(const std::vector<const char*> tRequiredLayers) { mRequiredLayers = tRequiredLayers; return *this; }

			//! Add a single name to the list of instance layers that should be enabled.
			Options& appendRequiredLayer(const char* tLayerName) { mRequiredLayers.push_back(tLayerName); return *this; }

			//! Specify the names of all instance extensions that should be enabled.
			Options& requiredExtensions(const std::vector<const char*> tRequiredExtensions) { mRequiredExtensions = tRequiredExtensions; return *this; }
			
			//! Add a single name to the list of instance extensions that should be enabled. By default,
			//! only the VK_EXT_debug_report instance extension is enabled.
			Options& appendRequiredExtensions(const char* tExtensionName) { mRequiredExtensions.push_back(tExtensionName); return *this; }
			
			//! Specify a complete VkApplicationInfo structure that will be used to create this instance.
			Options& applicationInfo(const VkApplicationInfo &tApplicationInfo) { mApplicationInfo = tApplicationInfo; return *this; }
			
		private:

			std::vector<const char*> mRequiredLayers;
			std::vector<const char*> mRequiredExtensions;
			VkApplicationInfo mApplicationInfo;

			friend class Instance;
		};

		//! Factory method for returning a new InstanceRef.
		static InstanceRef create(const Options &tOptions = Options()) { return std::make_shared<Instance>(tOptions); }

		Instance(const Options &tOptions = Options());
		~Instance();

		inline VkInstance getHandle() const { return mInstanceHandle; }
		inline const std::vector<VkExtensionProperties>& getInstanceExtensionProperties() const { return mInstanceExtensionProperties; }
		inline const std::vector<VkLayerProperties>& getInstanceLayerProperties() const { return mInstanceLayerProperties; }
		inline const std::vector<VkPhysicalDevice>& getPhysicalDevices() const { return mPhysicalDevices; }
		VkPhysicalDevice pickPhysicalDevice(const std::function<bool(VkPhysicalDevice)> &tCandidacyFunc);

	private:

		bool checkInstanceLayerSupport();
		void setupDebugReportCallback();

		VkInstance mInstanceHandle;
		VkDebugReportCallbackEXT mDebugReportCallback;

		std::vector<VkExtensionProperties> mInstanceExtensionProperties;
		std::vector<VkLayerProperties> mInstanceLayerProperties;
		std::vector<VkPhysicalDevice> mPhysicalDevices;

		std::vector<const char*> mRequiredLayers;
		std::vector<const char*> mRequiredExtensions;

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags,
															VkDebugReportObjectTypeEXT objType,
															uint64_t obj,
															size_t location,
															int32_t code,
															const char* layerPrefix,
															const char* msg,
															void* userData)
		{
			std::cerr << "VALIDATION LAYER: " << msg << std::endl;
			return VK_FALSE;
		}
	};

} // namespace vksp