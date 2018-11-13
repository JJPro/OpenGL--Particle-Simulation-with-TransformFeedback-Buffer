# Lab 11 - Graphics APIs

<img align="right" src="https://i.ytimg.com/vi/CQQEE6RaJYE/maxresdefault.jpg" width="400px" alt="dota 2 comparison">

> "The API Wars"

**Lab materials must be pushed to your repository one week from now before the next class begins**

**Read:** *Labs are designed to be finished in class if you work diligently, but expected to take 1-2 hours outside of class. They are often more 'tutorial' in style, and sometimes the solution may even be provided in pieces for you to type in and experiment. Copying & Pasting is discouraged however--make mistakes, play, and you will further learn the material.*

## Modify this section

- How many hours did it take you to complete this lab?
- Did you collaborate with any other students/TAs/Professors?
- Did you use any external resources? (Cite them below)
  - tbd
  - tbd
- (Optional) What was your favorite part of the lab?
- (Optional) How would you improve the lab?

## Logistics

You will be working on your own laptop today.

## Description

Today you are going to work in whatever graphics or compute API you like to create a 'hello world' version of that API (This may mean a triangle, or some other compute task). It needs to be able to run on your machine using the 'build.py' script.

These are the APIs you may use:

- Direct3D 11 or 12 [web](https://docs.microsoft.com/en-us/windows/desktop/direct3d)
- Vulkan [web](https://www.khronos.org/vulkan/)
- Metal 2 [web](https://developer.apple.com/metal/)
- WebGL [web](https://www.khronos.org/webgl/)
- OpenCL [web](https://www.khronos.org/opencl/)
- CUDA [web](https://developer.nvidia.com/cuda-zone)
- Pixar's Renderman [web](https://renderman.pixar.com/)

**Note:** Some of these APIs require a specific operating system or graphics card. Read the deliverables section first.

## Part 1 - Hello World

### Task 1 - Installation

Whichever API you choose to explore, you may need to install respective tools. Please keep track of these in the 'Build Script' section.

### Task 2 - Hello World Research

I am unfortunately not an expert in all of the APIs above (Only so many hours in a day...). Do some research and find a good tutorial where you can get something to work. After a semester of working with OpenGL, I believe some of the concepts should transfer over to new and different technologies--this should be exciting! 

If you are investigating OpenCL for example, while it does not have a 'shader' it has a 'kernel' which is a similar idea of offloading data to be processed on the GPU and then returned.

### Task 3 - Build Script

Modify the build.py for your needs so that I can easily test your code. You only need to support the operating system you have tested on.

List any additional installations you made here:
- *edit me*

#### Q & A
*Can I use make, ninja, cmake, autotools, incredibuild, fastmake, a visual studio project, a codeblocks project, an xcode project. Those tools are all better than a silly python script for reason X, Y, and Z.*
*No--I am not going to install all of those tools. Make it work with build.py. Most IDEs have a way to see the command line you are running which can help with this.*

### Task 4 - Abstraction

You have done enough C++ this semester to get the hang of what a class is, what some of the STL data structure are, etc. Now you should take your tutorial that you found, and try to abstract at the least, the initialization part of the program.

That is, your main.cpp may look like the following, where you have abstracted most of the work into a little framework called 'myCuda.h':

```cpp
// Some include files here

#include "myCuda.h"

int main(){

	MyCuda test1;
	
	test1.runProgram();
	
	return 0;
}

```

## Helpful Resources

- I don't know??? You tell me! Fill in this section with what resources you found useful. What was the main guiding tutorial or documentation that made things click.

- *fill in a helpful resource here*

## Deliverables

1. Edit the readme and fill in at least one url in the 'Helpful Resources' section that you used.
1. Edit the readme and modify any downloads you made in the 'Build Script' section.
2. Submit a modified `build.py` so that I can run your sample by just typing 'python build.py'
3. Your code should have some 'class' with an abstraction.
	- i.e. The bare minimum requirement is that all of your code should not fall in main.
	- This may require some thinking on your part.
4. Your program should do something
	- For the compute APIs (e.g. CUDA or OpenCL) this probably means adding two numbers together.
	- For the graphics APIs (e.g. DirectX, Metal, WebGL) this probably means displaying a triangle.

## Rubric

You (and any partner(s)) will receive the same grade from a scale of 0-2.

- 0 for no work completed by the deadline
- 1 for some work completed, but something is not working properly
- 2 for a completed lab (with possible 'going further' options completed)

## Going Further

What is that, you finished Early? Did you enjoy this lab? Here are some (optional) ways to further this assignment.

- You can read about the history of API wars here: https://en.wikipedia.org/wiki/Comparison_of_OpenGL_and_Direct3D
	- I can also save you some time and just say--use whichever you prefer, and chances are you will learn at least 2 different APIs.

## Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this lab, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

- Fun fact: The famous computer scientist Donald Knuth would pay folks one $2.56 for errors in his published works. [[source](https://en.wikipedia.org/wiki/Knuth_reward_check)]
- Unfortunately, there is no monetary reward in this course :)
