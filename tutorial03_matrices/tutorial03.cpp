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
#include <glm/gtc/matrix_transform.hpp>
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

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 03 - Matrices", NULL, NULL);
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

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleTransform.vertexshader", "SingleColor.fragmentshader" );
    GLuint programIDGreen = LoadShaders( "SimpleTransformGreen.vertexshader", "SingleColorGreen.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    // Get a handle for our "MVPGreen" uniform
    GLuint MatrixIDGreen = glGetUniformLocation(programIDGreen, "MVPGreen");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(15.0f, 4.0f / 3.0f, 0.1f, 50.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	// Camera matrix
//	glm::mat4 View       = glm::lookAt(
//								//glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
//                                       glm::vec3(0,0,10),
//								glm::vec3(0,0,0), // and looks at the origin
//								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
    
//    under dev glm::mat4 ModelGreenUnit      = glm::mat4(1.0f);
//    under dev glm::vec3 ModelGreenRotationAxis(1.0f, 0.0f, 0.0f);
//    under dev glm::mat4 ModelGreenRotate = glm::rotate(ModelGreenUnit, 1.0f, ModelGreenRotationAxis);

	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f,  0.0f, 0.0f,
		 1.0f,  0.0f, 0.0f,
		 0.0f,  2.0f, 0.0f,

        -1.0f, -0.05f, 0.0f,
         1.0f, -0.05f, 0.0f,
         0.0f, -2.0f, 0.0f,

        -1.0f,  0.0f, 0.05f,
         0.0f,  2.0f, 0.05f,
        -0.5f,  1.0f, 2.0f,

         1.0f,  0.0f, 0.05f,
         0.0f,  2.0f, 0.05f,
         0.5f,  1.0f, 2.0f,
	};
	//static const GLushort g_element_buffer_data[] = { 0, 1, 2 };

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    float tempSBx = -10.0;

	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

        // Camera matrix
        glm::mat4 View       = glm::lookAt(
                                           //glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
                                           glm::vec3(tempSBx,0,20),
                                           glm::vec3(0,0,0), // and looks at the origin
                                           glm::vec3(0,1,0.5)  // Head is up (set to 0,-1,0 to look upside-down)
                                           );

        tempSBx += 0.1;
        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
        glm::mat4 MVPGreen        = Projection * View * Model;
		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        
        
        
        // 1st Use our shader
        glUseProgram(programID);
        
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(10);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			10,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 1rst Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 6); // "(GL_TRIANGLES,0,3)" means 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(10);

        
        
        // 2nd Use our shader
        glUniformMatrix4fv(MatrixIDGreen, 1, GL_FALSE, &MVPGreen[0][0]);
        glUseProgram(programIDGreen);

        // 2nd attribute buffer : vertices
        glEnableVertexAttribArray(11);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                             11,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );

        // 2nd Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 6, 6);

        glDisableVertexAttribArray(11);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
    glDeleteProgram(programIDGreen);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

