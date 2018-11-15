#include <glad/glad.h> 
#include <GLFW\glfw3.h>

#include "Shader.h"


#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


const char *vertexShaderSource	=	" #version 330 core \n "
									"layout(location = 0) in vec3 aPos; \n"
									"void main() \n"
									"{ \n "
									"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
									"} \0";

const char *fragmentShaderSource = "#version 330 core \n"
									"out vec4 FragColor; \n"
									"void main() \n"
									"{ \n"
										"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
									"} \0";
const char *fragmentShaderSource2 = "#version 330 core\n"
									"out vec4 FragColor;\n"
									"void main()\n"
									"{\n"
									"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
									"}\n\0";



const char *uniformFragmentShaderSource = "#version 330 core \n"
										   "out vec4 FragColor; \n"
											"uniform vec4 ourColor; \n"
											"void main() \n"
											"{ \n"
												"FragColor = ourColor;\n"
											"}\n";

const char *vertexShaderSource2 = "#version 330 core \n"
									"layout (location = 0) in vec3 aPos;\n"
									"layout (location = 1) in vec3 aColor;\n"
									"out vec3 ourColor;\n"
									"void main()\n"
									"{\n"
									"    gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);\n"
									"    ourColor = aColor;\n"
									"}\n";

const char *fragmentShaderSource3 = "#version 330 core \n"
									"out vec4 FragColor;\n"
									"in vec3 ourColor;\n"
									"void main()\n"
									"{\n"
									"    FragColor = vec4(ourColor, 1.0);\n"
									"}\n";



int main()
{
	//Initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);




	//GLFW Window Creation
	GLFWwindow* window = glfwCreateWindow(800, 600, "FirstOpenGLProject", NULL, NULL);

	if (window == NULL)
	{

		std:: cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Load all OpenGL Functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	//Build and Compile our shader program

	//vertex Shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//check for shader compilation success
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error:: Shader::VERTEX::COMPILATION_FAILED\N" << infoLog << std::endl;
	}

	//our second vertex shader

	unsigned int vertexShader2;
	vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
	glCompileShader(vertexShader2);





	//fragment shader (original)
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &uniformFragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//Check the shader
	/*glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Error::Shader::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	*/

	//Yellow Fragment Shader
	unsigned int yellowShader;
	yellowShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(yellowShader, 1, &fragmentShaderSource2, NULL);
	glCompileShader(yellowShader);


	//Our third Fragment shader
	unsigned int rainbowShader;
	rainbowShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(rainbowShader, 1, &fragmentShaderSource3, NULL);
	glCompileShader(rainbowShader);




	//Shader Program (original)
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//Linking Shaders (original)
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	//Shader Program (yellow)
	unsigned int shaderProgramYellow;
	shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, yellowShader);
	glLinkProgram(shaderProgramYellow);


	//Shader Program (rainbow)
	unsigned int shaderProgramRainbow;
	shaderProgramRainbow = glCreateProgram();
	glAttachShader(shaderProgramRainbow, vertexShader2);
	glAttachShader(shaderProgramRainbow, rainbowShader);
	glLinkProgram(shaderProgramRainbow);



	//Linking 




	//Check the shader program for errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}


	//Delete shader objects once we have linked them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader2);
	glDeleteShader(yellowShader);
	glDeleteShader(rainbowShader);
	   	


	//Vertex Array


	float vertices2[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};


	float texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 1.0f


	};



	//Create our Vertex Buffer Obejcts

	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	   	  



	//glUseProgram(shaderProgramRainbow);

	Shader ourShader("C:/Projects/OpenGL/Shaders/shader.vs", "C:/Projects/OpenGL/Shaders/shader.fs");
	ourShader.use();

	//Keeps the window open and keeps rednering
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);
		//Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		
		//Telling the application which shader program to use
		//In this case we are using the shader created by compiling uniformFragmentShaderSource
		

		//Set uniform value
//		float timeValue = glfwGetTime();												//Get time
//		float greenValue = sin(timeValue) / 2.0f + 0.5f;								//Set shade of green based on formula
//		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");		//gets the uniform "ourColor" from the shader program
//		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);					//Sets the ourColor value using a generated "greenValue"


		float timeValue = glfwGetTime();
		float xTime = sin(timeValue);
	//	float yTime = sin(timeValue);
	//	float zTime = sin(timeValue);
		ourShader.setFloat("xOffset", xTime);
	//	ourShader.setFloat("yOffset", yTime);
	//	ourShader.setFloat("zOffset", zTime); 


		//Draw Triangle 1	
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		//Tell program to use our yellow shader program
//		glUseProgram(shaderProgramYellow);

		//Draw Triangle 2
//		glBindVertexArray(VAO[1]);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);




		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}