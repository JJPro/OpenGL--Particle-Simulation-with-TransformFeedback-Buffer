#ifndef ERROR_H
#define ERROR_H

// This assert inserts a breakpoint in your code!
// That way we can get the line number and file.
// #define ASSERT(x) if(!(x)) __debugbreak(); (__debugbreak() is only available
// on MSVC)
#define GLCall(x) GLClearErrorStates(); x ; GLCheckError(#x,__LINE__);

// New error handling routine
static void GLClearErrorStates(){
    // Return all of the errors that occur.
    while(glGetError() != GL_NO_ERROR){
        ;
    }
}

// Returns false if an error occurs
static bool GLCheckError(const char* function, int line){
    while(GLenum error = glGetError()){
        // __LINE__ is a special preprocessor macro that
        // Can tell us what line any errors occurred on.
        std::cout << "[OpenGL Error]" << error << "|" << function << " Line: " << line << "\n";
        return false;
    }
    return true;
}

#endif
