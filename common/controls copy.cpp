// Include GLFW
#include <glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::vec3 lightPos = glm::vec3(4,4,4);

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

glm::vec3 getLightPos() {
    return lightPos;
}

// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 ); 
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;



void computeMatricesFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
//	double xpos, ypos;
//	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
//	glfwSetCursorPos(window, 102/2, 76/2);

	// Compute new orientation
//	horizontalAngle += mouseSpeed * float(102/2 - xpos );
//	verticalAngle   += mouseSpeed * float( 76/2 - ypos );
    // look up
    if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
        verticalAngle += 1 * deltaTime * speed;
    }
    // look down
    if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
        verticalAngle -= 1 * deltaTime * speed;
    }
    // look right
    if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
        horizontalAngle += 1 * deltaTime * speed;
    }
    // look left
    if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
        horizontalAngle -= 1 * deltaTime * speed;
    }
    
    
//    if(((int)xpos != 102/2) && ((int)ypos != 76/2))    printf("pos = %f,%f,  angles = %f,%f\n", xpos, ypos, horizontalAngle, verticalAngle);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}

    
    
    
	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );
    
    
    
    // Compute new light position
    // move light up
    if (glfwGetKey( window, GLFW_KEY_I ) == GLFW_PRESS){
        lightPos += up * deltaTime * speed;
    }
    // move light  down
    if (glfwGetKey( window, GLFW_KEY_J ) == GLFW_PRESS){
        lightPos -= up * deltaTime * speed;
    }
    // move light  right
    if (glfwGetKey( window, GLFW_KEY_M ) == GLFW_PRESS){
        lightPos += right * deltaTime * speed;
    }
    // move light  left
    if (glfwGetKey( window, GLFW_KEY_N ) == GLFW_PRESS){
        lightPos -= right * deltaTime * speed;
    }
    // move light  forward
    if (glfwGetKey( window, GLFW_KEY_O) == GLFW_PRESS){
        lightPos += direction * deltaTime * speed;
    }
    // move light  backward
    if (glfwGetKey( window, GLFW_KEY_K ) == GLFW_PRESS){
        lightPos -= direction * deltaTime * speed;
    }


	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}