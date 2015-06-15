// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // by default, it is true   glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    // error glfwWindowHint(GLFW_STEREO, GL_TRUE);
    // optional glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( /*1024*/100, /*767*/76, "Tutorial 02 - Red triangle", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    //SB begin
    int major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    int minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    printf("+Detected attrib: major=%d, minor=%d\n", major, minor);

	// Dark blue background
	glClearColor(0.1f, 0.0f, 0.4f, 0.0f);

	GLuint myVertexArrayID;
	glGenVertexArrays(1, &myVertexArrayID);
	glBindVertexArray(myVertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader",  "SimpleFragmentShader.fragmentshader" );
    GLuint programID2 = LoadShaders( "SimpleVertexShader2.vertexshader",  "SimpleFragmentShader2.fragmentshader" );


	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        0.0f,  0.5f, 0.0f,
	};

	GLuint myvertexbuffer;
	glGenBuffers(1, &myvertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, myvertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    float tempWidth = 100;
    float tempHeight = 100;
    int tempFBWidth = 75;
    int tempFBHeight = 75;
    int tempMonitorWidth = 1;
    int tempMonitorHeight = 1;
    int count = -1;

    GLFWmonitor* myMonitor = glfwGetPrimaryMonitor();
    glfwGetMonitorPhysicalSize(myMonitor, &tempMonitorWidth, &tempMonitorHeight);
    const char* myMonitorName = glfwGetMonitorName(myMonitor);
    const GLFWvidmode*  myVideoModes = glfwGetVideoModes(myMonitor, &count);
    for(int i =count-1; i < count; i++) {
        printf("\n\nvideo mode #%d:\n    width      =%d, /\n    height     =%d, /\n    redBits    =%d, /\n    greenBits  =%d, /\n    blueBits   =%d, /\n    refreshRate=%d",i,myVideoModes[i].width,myVideoModes[i].height,myVideoModes[i].redBits,myVideoModes[i].greenBits,myVideoModes[i].blueBits,myVideoModes[i].refreshRate
               );
    }

    do{

        //int tempWidth, tempHeight;
        //glfwGetWindowSize(window, &tempWidth, &tempHeight);
        tempWidth+=0.01;
        tempHeight+=0.01;
        glfwSetWindowSize(window, tempWidth, tempHeight);
        glfwGetFramebufferSize(window, &tempFBWidth, &tempFBHeight);
        
        // the following line returns the same pointer as the variable window.
        GLFWwindow* tempWindowOrContext = glfwGetCurrentContext();
        
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		glUseProgram(programID);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(10);
		glBindBuffer(GL_ARRAY_BUFFER, myvertexbuffer);
		glVertexAttribPointer(
			10,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
        
       
		// Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(10);

        
        
        
        // 2nd attribute buffer : vertices
        glUseProgram(programID2);
        glEnableVertexAttribArray(11);
        glBindBuffer(GL_ARRAY_BUFFER, myvertexbuffer);
        glVertexAttribPointer(
                              11,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        glDrawArrays(GL_TRIANGLES, 3, 3); // 3 indices starting at 0 -> 1 triangle
        glDisableVertexAttribArray(11);
        
        
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteBuffers(1, &myvertexbuffer);
	glDeleteVertexArrays(1, &myVertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

