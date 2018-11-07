#include "SceneNode.h"
#include <string>

// The constructor
SceneNode::SceneNode(Object* ob){
	std::cout << "(SceneNode.cpp) Constructor called\n";
	object = ob;
	// By default, we do not know the parent
	// at the time of construction of this node.
	// If the SceneNode is the root of the tree,
	// then there is no parent.
	parent = nullptr;
	
	// Setup shaders for the node.
	std::string vertexShader = myShader.LoadShader("./shaders/vert.glsl");
	std::string fragmentShader = myShader.LoadShader("./shaders/frag.glsl");
	// Actually create our shader
	myShader.CreateShader(vertexShader,fragmentShader);       
}

// The destructor 
SceneNode::~SceneNode(){
	// Remove each object
	for(unsigned int i =0; i < children.size(); ++i){
		delete children[i];
	}
}

// Adds a child node to our current node.
void SceneNode::AddChild(SceneNode* n){
	// For the node we have added, we can set
	// it's parent now to our current node.
	// 'this' is the current instance of our
	// object, which is a pointer to our current
	// SceneNode.
	n->parent = this;
	// Add a child node into our SceneNode
	children.push_back(n);
}

// Draw simply draws the current nodes
// object and all of its children. This is done by calling directly
// the objects draw method.
void SceneNode::Draw(){
	myShader.Bind();
	if(object!=nullptr){
		object->render();
		for(int i =0; i < children.size(); ++i){
			children[0]->Draw();
		}
	}	
}

// Update simply updates the current nodes
// object. This is done by calling directly
// the objects update method.
// TODO: Consider not passting projection and camera here
void SceneNode::Update(glm::mat4 projectionMatrix, Camera* camera){
    if(object!=nullptr){
        // TODO: Implement here!
    
    // Now apply our shader transformation

		myShader.Bind();
    	// Set the uniforms in our current shader

        // For our object, we apply the texture in the following way
        // Note that we set the value to 0, because we have bound
        // our texture to slot 0.
        myShader.setUniform1i("u_DiffuseMap",0);  
        // Set the MVP Matrix for our object
        // Send it into our shader
        myShader.setUniformMatrix4fv("model", &worldTransform.getInternalMatrix()[0][0]);
        myShader.setUniformMatrix4fv("view", &camera->getWorldToViewmatrix()[0][0]);
        myShader.setUniformMatrix4fv("projection", &projectionMatrix[0][0]);

        // Create a 'light'
        myShader.setUniform3f("lightColor",1.0f,1.0f,1.0f);
        myShader.setUniform3f("lightPos",
                               camera->getEyeXPosition() + camera->getViewXDirection(),
                               camera->getEyeYPosition() + camera->getViewYDirection(),
                               camera->getEyeZPosition() + camera->getViewZDirection());
        myShader.setUniform1f("ambientIntensity",0.5f);
	
		for(int i =0; i < children.size(); ++i){
			children[0]->Update(projectionMatrix, camera);
		}
	}
}

// Returns the actual local transform stored in our SceneNode
// which can then be modified
Transform& SceneNode::getLocalTransform(){
    return localTransform; 
}

// Returns the worled  transform stored in our SceneNode
// which can then be modified
Transform& SceneNode::getWorldTransform(){
    return worldTransform; 
}
