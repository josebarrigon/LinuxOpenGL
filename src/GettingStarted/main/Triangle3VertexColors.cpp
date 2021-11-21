#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
float getColor();


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Declare vertex of array
	GLfloat vertices[] = {
	//Positions          //Colors	
	 -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left  
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // right 
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top 
	};

	//Create Window Object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//ViewPort
	glViewport(0, 0, 800, 600);

	Shader ourShader("Shaders/GettingStarted/CH6/vert.glsl", "Shaders/GettingStarted/CH6/frag.glsl"); // you can name your shader files however you like


	/*---Pass data from the cpu to the gpu using buffers---*/
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);//create attribute buffer object
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); //vertex array now points to vao

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//array buffer now points to vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//send data cpu -> array buffer -> vbo 

	glEnableVertexAttribArray(0); //set to on vertex attrib array
	glVertexAttribPointer(0/*0 attribute*/, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//indicate three floats starting in offset zero

	glVertexAttribPointer(1/*0 attribute*/, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));//indicate three floats starting in offset zero
	glEnableVertexAttribArray(1);

	//Resizing window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//set the refresh interval for the window
	glfwSwapInterval(30);
	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//Rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //state setting command
		glClear(GL_COLOR_BUFFER_BIT); //state using command 
		ourShader.use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//Terminate the process
	glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

float getColor() {

	float t = glfwGetTime();
	return abs(sin(t + rand()));
}