# Lab 10 - Framebuffer Objects

<img align="right" src="./media/fbo.JPG" width="300px" alt="picture">

> "Back to rendering a single quad!"

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

Last lab we created a nice landscape using heightmaps.

- We learned heightfields (i.e. heightmaps) which is simply image data used to represent the 'y' height of each vertex in a terrain.
- We learned about drawing a triangle strip as a grid and lay a texture over it. 

Today we are going to redraw the scene and apply post-processing effects to our scene using a framebuffer object.

## Part 1 - C++/glsl Refresh?


### Task 1 - Composition in C++

Today we are introducing the 'Framebuffer' class. If you remember previously, we discussed in our C++ refresh the idea of inheritance where one class builds off of another. We call this a 'is-a' relationship, because one class 'is a' descencdent of another, or can act as another class.

Another way to build relationships between classes is what is known as a 'has-a` relationship. This is the idea that a member variable is another instance of a class. In this way we can also compose a more complex class with many instances of other objects.

```cpp
class FrameBuffer{
// ...
// ...
// ...
private:
	Shader* myShader; // A FrameBuffer 'has-a' Shader.

};

```

## Part 1 - Post-processing

Today the trick is that we are drawing to a buffer that we are not going to see, until we capture that image as a texture. This means we are going to have a seperate texture for our frameBuffer (shaders/fboVert.glsl and shaders/fboFrag.glsl) that you will modify to create a post-processing effect on our scene.

**Lab Goal:** Render the terrain using a 'kernel'. https://learnopengl.com/Advanced-OpenGL/Framebuffers provides some samples.

### Vertex Shader in a glance

This is what is given today.

```c
// ==================================================================
#version 330 core
// Read in our attributes stored from our vertex buffer object
// We explicitly state which is the vertex information
// (The first 3 floats are positional data, we are putting in our vector)
layout(location=0)in vec3 position; 
layout(location=1)in vec2 texCoord; // Our second attribute - texture coordinates.

// If we have texture coordinates we can now use this as well
out vec2 v_texCoord;


void main()
{

    gl_Position = vec4(position.x,position.y,0.0f, 1.0f);

    // Store the texture coordinaets which we will output to
    // the next stage in the graphics pipeline.
    v_texCoord = texCoord;
}
// ==================================================================

```

### Fragment Shader in a glance

This is what is given today.

```c
// ====================================================
#version 330 core

// ======================= uniform ====================
// If we have texture coordinates, they are stored in this sampler.
uniform sampler2D u_DiffuseMap; 

// ======================= IN =========================
in vec2 v_texCoord; // Import our texture coordinates from vertex shader

// ======================= out ========================
// The final output color of each 'fragment' from our fragment shader.
out vec4 FragColor;

void main()
{
    // Store our final texture color
    vec3 diffuseColor;
    diffuseColor = texture(u_DiffuseMap, v_texCoord).rgb;
        
    FragColor = vec4(diffuseColor,1.0);
}
// ==================================================================


```

## Helpful Resources

- [SDL API Wiki](https://wiki.libsdl.org/CategoryAPI)
- [docs.gl](http://docs.gl/) useful programming resource
- Start writing some OpenGL 3.3 from here! [learnopengl.com](https://learnopengl.com/) Use this time for graphics!
- https://learnopengl.com/Advanced-OpenGL/Framebuffers
- One or multiple FBO's? https://www.opengl.org/discussion_boards/showthread.php/183185-Multiple-FBOs-or-attachment-swapping


## Deliverables

1. Create one post-processing effect. Some samples are provided at: https://learnopengl.com/Advanced-OpenGL/Framebuffers

## Rubric

You (and any partner(s)) will receive the same grade from a scale of 0-2.

- 0 for no work completed by the deadline
- 1 for some work completed, but something is not working properly
- 2 for a completed lab (with possible 'going further' options completed)

## Going Further

What is that, you finished Early? Did you enjoy this lab? Here are some (optional) ways to further this assignment.

- Create a second framebuffer with a second set of shaders, such that pressing the '1' and '2' numbers flips between the different effects in your scene.
	- Note, you can implement this with one framebuffer, and have user input passed in through a uniform variable.

## Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this lab, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

- Fun fact: The famous computer scientist Donald Knuth would pay folks one $2.56 for errors in his published works. [[source](https://en.wikipedia.org/wiki/Knuth_reward_check)]
- Unfortunately, there is no monetary reward in this course :)
