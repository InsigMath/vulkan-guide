---
layout: default
title: Vulkan API
nav_order: 1
parent: introduction
---

![VulkanLogo](/assets/images/Vulkan_170px_Dec16.jpg)

## What is Vulkan?

Vulkan is a multiplatform API (Application Program Interface) created as a successor to OpenGl by the same authors at the Khronos Group.
Vulkan is developed by a committee of GPU vendors and other partners, and the API is a standard that anyone can implement.

Vulkan is a fresh start that breaks away from the design decisions of OpenGL. It is designed for multithreaded high performance applications, and the much more explicit API helps drivers have much less guesswork to do. If used right, Vulkan can provide a really high level of performance, low latency, and more consistent frametimes.


## When to use Vulkan

While Vulkan is the newest API, you should not be using Vulkan if you don't need its features.
Writing a Vulkan engine is an order of magnitude harder than using OpenGl, and the GPU-side performance will not necessarily be better.

The big things Vulkan improves is CPU overhead, multithreading, and control over GPU hitches.
When Vulkan is used right, it is possible to almost completely eliminate hitches, achieving a very smooth framerate, with a very low CPU overhead.

If your application is GPU bound, where the performance is limited to fast your GPU runs, Vulkan's extra complexity is unlikely to improve performance enough to be worth it.

If you want to make big maps and dynamic worlds, or CAD type scenes with a lot of objects, the multithreaded capabilities of Vulkan will likely be very useful.

On the mobile market, there is the problem of fragmentation. Not every phone implements Vulkan (especially older phones) and of those that do, you may have problems with driver quality. On the phones that do implement Vulkan and have good drivers, the lower CPU overhead and the better mapping to mobile hardware will mean you can improve the performance of the application extensively all while using less battery.


# Overview of Vulkan API

Vulkan is an API, which means its essentially a list of functions to call, the parameters to pass in, and what return values you receive. 
The API is based on the C programming language, so it can be used from almost every other language. While this tutorial is written in C++, what is done here can be relatively easily written in other low level languages such as Rust or even plain C.

## Multiplatform

Vulkan is unique in its design compared to other GPU APIs because it has the same API for Mobile and Desktop GPUs. Due to that design, many features in Vulkan are optional and using them requires explicitly turning them on. It is not uncommon to have a feature which no Mobile GPU supports but is available on most desktop GPUs. In this tutorial, we are focusing on the Desktop side of things, so we can use features that wont directly run on smartphones and tablets. 

If you wish to have a Vulkan application that will run on both Desktop and Mobile GPUs, its recommended to have two core render paths. As the API is the same, much of code can be shared, but the differences in features and fast-paths between the 2 targets means that having just one render code path will have suboptimal performance on at least one of the two platforms. 

During this guide we will explain many of the differences between the two types of GPUs.

## Validation layers

The Vulkan API is very large and rather easy to make mistakes with. Fortunately, when Vulkan was being designed, the creators realized that and made the Validation Layers to fix it. The Validation Layers is a bunch of error checking code that detects and reports 'invalid usage' of the API. They check for all kinds of errors such as using the wrong enums, threading violations, and object lifetimes. The layers are separate from the driver, and to work, they must intercept every function call, perform validation, then call the driver for you. The reason for that is when you want to turn off validation, you Vulkan calls go directly to the driver and can run as fast as possible.

While developing a Vulkan application, you should have the Validation Layers enabled. The obvious reason is that they detect bugs, but another big reason is that by having a clean validation output you can reasonably assume your application will work across a wide variety of hardware. This is especially important for synchronization, which is tricky to get right, and what may work perfectly fine on one GPU may fail spectacularly on another GPU.

It is important to note that the Validation Layers can't catch every possible bug, like uninitialized memory and bad pointers. There are tools that can check for these bugs, such as Address Sanitizer and valgrind, and using them is highly advised. Unfortunately, graphics drivers often create false positives while using these tools, making their output quite noisy. 

## Usage and general mindset

In the Vulkan API, almost everything is designed around objects that you create manually and then use. This is not only for the actual gpu resources such as Images/Textures and Buffers (for memory or things like Vertex data) but also for a lot of "internal" configuration structures.

For example, things like gpu fixed function, like rasterizer mode, are stored into a Pipeline object which holds shaders and other configuration. In Opengl and DX11, this is calculated "on the fly" while rendering.
When you use Vulkan, you need to think if its worth to cache these objects, or create them while rendering on-the-fly. Some objects like Pipelines are expensive to create, so its best to create them on load screens or background threads. Other objects are cheaper to create, such as DescriptorSets and its fine to create them when you need them during rendering.

Because everything in Vulkan is "pre-built" by default, it means that most of the state validation in the GPU will be done when you create the object, and the rendering itself does less work and is faster. Good understanding of how these objects are created and used will allow you to control how everything executes in a way that will make the framerate smooth.

When doing actual GPU commands, all of the work on the gpu has to be recorded into a CommandBuffer, and submitted into a Queue. You first allocate a command buffer, start encoding things on it, and then you execute it by adding it to a Queue. When you submit a command buffer into a queue, it will start executing on the GPU side. You have tools to control when that execution has finished. If you submit multiple command buffers into different queues, it is possible that they execute in parallel.

There is no concept of a frame in Vulkan. This means that the way you render is entirely up to you. The only thing that matters is when you have to display the frame to the screen, which is done through a swapchain. But there is no fundamental difference between rendering and then sending the images over the network, or saving the images into a file, or displaying it into the screen through the swapchain.

This means it is possible to use Vulkan in an entirely headless mode, where nothing is displayed to the screen. You can render the images and then store them onto the disk (very useful for testing!) or use Vulkan as a way to perform GPU calculations such as a raytracer or other compute tasks.

Next: [Vulkan Render flow]({{ site.baseurl }}{% link docs/introduction/vulkan_execution.md %})