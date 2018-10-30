# Assignment 4 - Render a Normal Mapped .obj model



*TODO*: Please edit the following information in your assignment

* Name and partners name(At most 1 partner for this Assignment): 
* How many hours did it take you to complete this Assignment? 
* Did you collaborate or share ideas with any other students/TAs/Professors? 
* Did you use any external resources? 
  * (tbd if any)
  * (tbd if any)
  * (tbd if any)
* (Optional) What was the most interesting part of the assignment? How would you improve this assignment?
  
## Description

The grand finale! err, at least for our .obj model loader. The final step we will take is to make use of the normal map and normal data with each model. Normal maps allow us to lighten and darken pixels at a per-pixel granularity, increasing the realism of our scene. 

For this assignment you will now need to modify your previous model loader to make use of the 'vn' data. By the end of this assignment you will have a good understanding of one of the best tricks in graphics that most games/movies use!

> Student: "Dear Mike, my partner and mines model loader has been broken since assignment 2."
>
> Mike: "Okay, let me offer a compromise."
>
> Student: *Puts hands together* "I am listening."
>
> Mike: "Provided in the 'starter' folder is a starter project for normal mapping a brick wall"
>
> Mike: "Get your frag.glsl and vert.glsl working on that, and I'll give you 95% of the credit."
>
> Mike: "Then, if you can add it to your .obj loader, you can get a full 100%"
>
> Student: "So definitely get the brick wall working? Then push for that extra 5% for the .obj model loader?"
>
> Mike: "Correct!"
>
> Students: "________" (I don't know how you'll respond to that?)
>
> Mike: "It will be helpful for folks trying to incorporate normal mapping in their .obj loader to know the shader is working at the very least!"


### Assignment Strategy

Ideally, you are working from your assignment 3 as your starter code. Here are my recommendations:

* If you do not understand tangent space, go back and understand model and world space first.
  * The idea again is that you can multiply through a 'tangent matrix' (TBN) to figure out how to properly light up fragments based on a normal map at any angle. 

* Read the slides and read the tutorial. Normal mapping is all about math. We are diving in a little deep, but I have done some of the setup in the code to assist you. www.learnopengl.com also provides some good notes.
  * We have not discussed much on lighting quite yet, just assume there is a fixed light at 0,0,0 in our scene.
    * Rotating your model will show if things are working.
* Read the code. There is a new abstraction called Geometry.h. I think it will come in handy, and it's worth thinking about ways of how to make OpenGL easy.
* Explore other sources, but cite them! If you find other tutorials please cite them.
* You should scratch your head a few times when you look at the code. When you do this, you should dive into the support code and figure out what things are doing.
  * You are welcome to abandon the support code and write something from scratch, but I recommend using the support code or your previous assignments!

## Part 1 - Object-Oriented Programming Strategies (C++ refresh)

I want to continue to give a little bit more background on C++ and thinking about data. There is no deliverable for part 1, but it will be useful to at the very least think about.

### Task 1 Program arguments

Once again, your .obj loader should read in a model from the program arguments. Below is an example.

```cpp
// clang++ args.cpp -o args
// ./args "./object/chapel/chapel_obj.obj"

#include <iostream>

int main(int argc, char** argv){

    std::cout << "My argument is: " << argv[1] << "\n";

    return 0;
}
```

### Task 2 - Structs

**Very small updates from previous assignment here**

structs in C++ while functionally the same as a class (except for the default access modifier level) are typically used as plain old datatypes--i.e. a way to create a composite data type.

Shown below is an example of a struct in C++

```cpp
struct VertexData{
	float x,y,z;	// x,y,z positions
	float xn,yn,zn; // x,y,z normals
	float s,t;		// s,t texture coordinates
};
```

It is further important to note the order of our variables in the VertexData struct. In memory, they will be arranged as x,y,z,xn,yn,zn,s,t in that order. This is potentially convenient as in our current buffer data strategy we have been laying out values of the first vertices x,y,z,xn,yn,zn,s,t,etc. in a specific order defined by our vertex layout.

It may further be useful to add a constructor to our struct for convenience.

```cpp
struct VertexData{
	float x,y,z;	// x,y,z positions
	float xn,yn,zn; // x,y,z normals
	float s,t;		// s,t texture coordinates

	VertexData(float _x, float _y, float _z,float _xn, float _yn, float _zn, float _s, float _t): x(_x),y(_y),z(_z),xn(_xn),yn(_yn),zn(_zn),s(_s),t(_t) { }
};
```

Often with structs, because they are a datatype, it can be helpful to define mathematical operators with them. Below a test showing how to test for equality is done.

```cpp

struct VertexData{
	float x,y,z;	// x,y,z positions
	float xn,yn,zn; // x,y,z normals
	float s,t;		// s,t texture coordinates

	VertexData(float _x, float _y, float _z,float _xn, float _yn, float _zn, float _s, float _t): x(_x),y(_y),z(_z),xn(_xn),yn(_yn),zn(_zn),s(_s),t(_t) { }
	
	// Tests if two VertexData are equal
	bool operator== (const VertexData &rhs){
		if( (x == rhs.x) && (y == rhs.y) && (z == rhs.z) 
			 && (xn == rhs.xn) && (yn == rhs.yn) && (zn == rhs.zn) 
			 && (s == rhs.s) && (t == rhs.t) ){
			return true;
		}
		return false;
	}
};

```

More information on structs can be found here: 
- http://www.cplusplus.com/doc/tutorial/structures/
- https://www.learncpp.com/cpp-tutorial/47-structs/

## Part 2 - Rendering a Normal mapped Model

### Task 1 - .obj and Normal Coordinates

For this assignment you are going to render a single textured **and normal mapped** 3D model. Several objects are provided in the 'objects' folder with their associated normal maps. I have personally tested with the 'house' model for most of my iterations, so I recommend you do the same.

The tasks for rendering in this assignment are the following:
1. Make sure you can parse the .obj file format and associated material file. 
	- read in the vertex (v), vertex texture (vt), vertex normal(vn), and face(f) information.
2. The .obj file should be read in from the command line arguments
	- e.g. `./lab "./object/chapel/chapel_obj.obj"`

**You may assume one texture per model for this assignment**

A few of the additional fields are specified in [Paul Burke's guide](http://paulbourke.net/dataformats/obj/minobj.html), which are primarily used for rendering a scene. For now, we are only interested in the color.

### Loading your own models for this assignment

It is totally fine to provide your own school appropriate normal mapped 3D .obj files for this assignment. Some notes that may save you time debugging:

- Make sure you push the model, texture(s), and material file to the repository.
- If you use blender3D to export your own .obj model, make sure to scale it to about the size of a unit cube in Blender3D. This will save you time from moving the camera around a lot.
- Triangulate the faces within the blender3D (there is an option when you export)
- Check your material file to make sure it is loading .ppm images which we know how to handle. Use a program like [GIMP](https://www.gimp.org/) to convert them to ASCII format .ppm images otherwise.
- The .ppm image may be 'mirrored', meaning you have to flip it horizontally for the actual texture coordinates to line up with the appropriate vertices.

### Task 2 - Interactive Graphics

The tasks for interactivity in this assignment are the following:
- Pressing the 'w' key toggles drawing your scene in wireframe mode or textured polygon mode.
- Pressing the 'q' key exits the application.

A resource for performing keyboard input with SDL is provided here: http://lazyfoo.net/tutorials/SDL/04_key_presses/index.php

### Task 3 - Perspective Camera

Make sure your scene is being rendered in perspective. Make modifications to the vert.glsl as needed. This should be similar to what you have done in a previous lab.

### More Assignment strategy 

My suggested strategy for this project is:

* You can use any of the code from the labs or previous assignments that you may find useful.
	* In fact, I highly recommend it!
* Have a special C++ class(in a .h and .cpp file) for loading OBJ models--not doing so is bad style!
	* Utilize any data structure you like in the STL (e.g. std::vector)
  	* You may assume all faces are triangles (though if you download any test .obj files from the web that may not be the case)
* Think about how you can load a line of text and then split it into individual tokens.
  	* A resource loading files (Filo I/O) in C++ can be found here: http://www.cplusplus.com/doc/tutorial/files/
  	* The reference on strings may be useful: http://www.cplusplus.com/reference/string/string/
    		* Some ideas on string splitting: http://www.martinbroadhurst.com/how-to-split-a-string-in-c.html
* You do not need to use any complex shaders. In fact, I recommend using the most basic ones for this assignment.
* I recommend using this webpage for help with OpenGL: http://docs.gl/gl3/glPolygonMode

## How to run your program

Your solution should compile using the `build.py` file. That is, we will run your program by typing 'python build.py' and it should just work.

Your program should then run by typing in: `./lab "./object/chapel/chapel_obj.obj"`

## Deliverables

- You should be able to display a triangulated .obj 3D normal mapped textured model (several are provided).
	- If you would like you can make it spin, move around, or load multiple models. Please just document this in this readme.

* You need to commit your code to this repository.
* You need to use the build.py script provided. Anything else used is at your own risk--and you should provide complete documentation. If your program does not compile and run, you get a zero!

## Rubric

<table>
  <tbody>
    <tr>
      <th>Points</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>30% (Core)</td>
      <td align="left">Is the code clearly documented? Are there no memory leaks? Did you close the file after opening it? How well was your abstraction to create a loader (or was it one giant ugly main function)? Did you make sure your code worked with the 'build.py' or did we have a headache compiling your code? Did you read in the model from the command line arguments or hard code the path?</td>
    </tr>   
    <tr>
      <td>40% (Core)</td>
      <td align="left">(20%)Can you render at least the geometry correctly? (10%) Did you implement the interactive components of this assignment? (10%) Did you implement a perspective camera</td>
    </tr>
      <td>30% (Advanced)</td>
      <td align="left">(25%) Does your shader work with the brick wall? (%5) Does your shader work with the .obj model?</td>
    </tr>
  </tbody>
</table>

## More Resources

(New for this assignment)
* http://paulbourke.net/dataformats/obj/minobj.html (I recommend reading this one first for a minimal texture example)


Links on the OBJ Model Format (From last assignment)
* https://people.cs.clemson.edu/~dhouse/courses/405/docs/brief-obj-file-format.html (I recommend reading this one for more information)
* https://www.cs.cmu.edu/~mbz/personal/graphics/obj.html
* https://en.wikipedia.org/wiki/Wavefront_.obj_file

## F.A.Q

* Q: Why the obj format?
  * A: It is a standard data format understood by most programs.
* Q: Can I load my own models that I have made to show off?
  * A: Sure -- just make sure they are added to the repository (Including the texture)
* Q: Why are my texture coordinates messed up? The geometry looks right?
  * A: Try a different model first to confirm. Then you may have to flip the texture in a modeling program or within your .ppm loader depending on how the coordinates were assigned. 
