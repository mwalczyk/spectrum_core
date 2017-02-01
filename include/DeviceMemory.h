/*
*
* MIT License
*
* Copyright(c) 2017 Michael Walczyk
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/

#pragma once

#include <memory>

#include "Platform.h"
#include "Noncopyable.h"
#include "Device.h"

namespace graphics
{

	class DeviceMemory;
	using DeviceMemoryRef = std::shared_ptr<DeviceMemory>;

	class DeviceMemory : public Noncopyable
	{
	public:

		//! Factory method for returning a new DeviceMemoryRef.
		static DeviceMemoryRef create(const DeviceRef &tDevice, const vk::MemoryRequirements &tMemoryRequirements, vk::MemoryPropertyFlags tRequiredMemoryProperties)
		{
			return std::make_shared<DeviceMemory>(tDevice, tMemoryRequirements, tRequiredMemoryProperties);
		}

		//! Construct a stack allocated, non-copyable container that manages a device memory allocation.
		DeviceMemory(const DeviceRef &tDevice, const vk::MemoryRequirements &tMemoryRequirements, vk::MemoryPropertyFlags tRequiredMemoryProperties);
		~DeviceMemory();

		inline vk::DeviceMemory getHandle() const { return mDeviceMemoryHandle; }
		inline vk::DeviceSize getAllocationSize() const { return mAllocationSize; }
		inline uint32_t getSelectedMemoryIndex() const { return mSelectedMemoryIndex; }
		void* map(size_t tOffset, size_t tSize);
		void unmap();

	private:

		DeviceRef mDevice;
		vk::DeviceMemory mDeviceMemoryHandle;
		vk::DeviceSize mAllocationSize;
		uint32_t mSelectedMemoryIndex;
		bool mInUse;
	};

} // namespace graphics