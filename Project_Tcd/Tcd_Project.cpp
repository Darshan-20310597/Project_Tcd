#include"libs.h"


using namespace std;

const unsigned int width= 800;
const unsigned int Height = 600;

// vertex in the program 
Vertex vertices[] =
{
	// postions                      // colors                       //texture					 //Normals
	glm::vec3(-0.5f,0.5f,0.0f),      glm::vec3(1.0f,0.0f,0.0f),     glm::vec2(0.0f,1.0f),        glm::vec3(0.0f,0.0f,1.0f),
	glm::vec3(-0.5f,-0.5f,0.0f),     glm::vec3(0.0f,1.0f,0.0f),     glm::vec2(0.0f,0.0f),		 glm::vec3(0.0f,0.0f,1.0f),
	glm::vec3(0.5f,-0.5f,0.0f),      glm::vec3(0.0f,0.0f,1.0f),     glm::vec2(1.0f,0.0f),		 glm::vec3(0.0f,0.0f,1.0f),
	glm::vec3(0.5f,0.5f,0.0f),       glm::vec3(1.0f,1.0f,1.0f),     glm::vec2(1.0f,1.0f),		 glm::vec3(0.0f,0.0f,1.0f)
};

unsigned noofvertices = sizeof(vertices) / sizeof(Vertex);


unsigned int indeces[] =
{
	0,1,2,  //Traingle 1
	0,2,3
	
};

unsigned noofindeces = sizeof(indeces) / sizeof(GLint);


void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void UpdateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3 scale);
void processInput(GLFWwindow* window);
char infoLog[512];
static unsigned char wireframe;

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;
glm::vec3 camfront = glm::vec3(0.0f, 0.0f, -1.0f);


//static std::string ParseShader(const std::string& file)
//{
//	std::ifstream stream(file);
//	std::string line;
//	std::string shader = "";
//
//	while (getline(stream, line))
//	{
//		shader = shader + line;
//		shader = shader + "\n";
//	}
//
//
//	return shader;
//}
//
//static int compileShader(unsigned int type, const std::string& source)
//{
//	unsigned int id = glCreateShader(type);
//	const char* src = source.c_str();
//	glShaderSource(id, 1, &src, nullptr);
//	//unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
//
//	glCompileShader(id);
//
//	// Error Handling 
//	int success1;
//	glGetShaderiv(id, GL_COMPILE_STATUS, &success1);
//	if (!success1) {
//		glGetProgramInfoLog(id, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	return id;
//
//}
//
//static unsigned int createShader(const std::string& vertexShaderval, const std::string& fragmentShaderval)
//{
//	unsigned int program = glCreateProgram();
//	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderval);
//	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderval);
//
//
//	glAttachShader(program, vs);
//	glAttachShader(program, fs);
//	glBindAttribLocation(program, 0, "vertex_position");
//	glLinkProgram(program);
//	int success1;
//	glGetProgramiv(program, GL_LINK_STATUS, &success1);
//	if (!success1)
//	{
//		glGetProgramInfoLog(program, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	//-------
//
//
//	glValidateProgram(program);
//	//Delete the shader after linking 
//	glDeleteShader(vs);
//	glDeleteShader(fs);
//
//
//	return program;
//
//}



int main(void) 
{
	// Inital GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);

	// Important with Presepctive matrix
	
	int frameBufferWidth, frameBufferHeight = 0;
	//Create window 
	GLFWwindow* window = glfwCreateWindow(width,Height,"Window Only",NULL,NULL);
	//GLFWwindow* window_1 = glfwCreateWindow(width, Height, "Window 2 Only", NULL, NULL);
	glfwGetFramebufferSize(window, &frameBufferWidth,&frameBufferHeight);
	if (!window) {

		std::cout << " Failed to open Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Glew initialization and opengl context
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error:: main.cpp :: Failed to Initialize Glew" << std::endl;
		glfwTerminate();
	}
	// Using GL enable to enable stuff 

	glEnable(GL_DEPTH_TEST);

	// remove unnesseacry 


	Shader ourShader("vertex.glsl", "fragment.glsl");
	/*std::string vertexsource = ParseShader("vertex.glsl");
	std::cout << vertexsource << std::endl;
	std::string fragmentsource = ParseShader("fragment.glsl");
	std::cout << fragmentsource << std::endl;*/

	/*unsigned int program = createShader(vertexsource, fragmentsource);*/
	/***** ADDING NORMAL */
	//Shader core_program("vertex.glsl", "fragment.glsl","geometry.glsl");
	unsigned int VBO, VAO , EBO;
	glGenVertexArrays(1, &VAO);// VAO Big box that holders all the data
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO); // Elelment object 
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textcoord));
	glEnableVertexAttribArray(2);
	// adding normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);
	
	//glEnableVertexAttribArray(1);
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	//*********************** MESH MESH MESH *****************//

	Mesh test(vertices,noofvertices,indeces,noofindeces);



	// Texture Iinitialization
	//int image_width = 0;
	//int image_height = 0;
	//unsigned char* image = SOIL_load_image("Images/Tcd.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

	//// We create a texture id to load the images 
	//unsigned int Texture0;
	////generate textures and bind it
	//glGenTextures(1, &Texture0);
	//glBindTexture(GL_TEXTURE_2D, Texture0);

	////glTexParamteri() -- maping images to x and y coordinates in Textures (S and T)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//if (image)
	//{
	//	std::cout << "Image Loaded successfully" << std::endl;
	//	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, image_width, image_height,0, GL_RGBA,GL_UNSIGNED_BYTE,image);
	//	//glGenerateMipmap - makes smaller and bigger version of image we have given (Several sizes and 
	//	glGenerateMipmap(GL_TEXTURE_2D);
 //   
	//}
	//else {
	//	std::cout << "Error While Loading Image : Texture loading failed" << std::endl;
	//}

	//glActiveTexture(0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//SOIL_free_image_data(image);

	Texture texture_0("Images/wood.jpg", GL_TEXTURE_2D,0);
	Texture texture_1("Images/Tomato.png", GL_TEXTURE_2D,1);


	// Materials
	Material material0(glm::vec3(0.1f), glm::vec3(1.1f), glm::vec3(30.1f), texture_0.getTxtureunit(), texture_1.getTxtureunit());

	//Texture 2 
	//// Texture Iinitialization
	//int image_width1 = 0;
	//int image_height1 = 0;
	//unsigned char* image1 = SOIL_load_image("Images/Tcd.png", &image_width1, &image_height1, NULL, SOIL_LOAD_RGBA);

	//// We create a texture id to load the images 
	//unsigned int Texture1;
	////generate textures and bind it
	//glGenTextures(1, &Texture1);
	//glBindTexture(GL_TEXTURE_2D, Texture1);

	////glTexParamteri() -- maping images to x and y coordinates in Textures (S and T)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//if (image1)
	//{
	//	std::cout << "Image Loaded successfully" << std::endl;
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width1, image_height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
	//	//glGenerateMipmap - makes smaller and bigger version of image we have given (Several sizes and 
	//	glGenerateMipmap(GL_TEXTURE_2D);

	//}
	//else {
	//	std::cout << "Error While Loading Image : Texture loading failed" << std::endl;
	//}

	//glActiveTexture(0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//SOIL_free_image_data(image1);


	//Creates an identity matrix 4X4

	// We must store everything in variables and not in matrix for scaling rotating and position

	glm::vec3 position(0.0f);
	glm::vec3 rotation(0.0f);
	glm::vec3 scale(1.0f);

	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, scale);


	

	// FOV - Read about it in orthographic projection
	// Create up vector for the world (x , y(up) , Z )
	glm::vec3 CameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 Worldup = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 camfront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(Worldup, camfront));
	glm::vec3 cameraUp = glm::cross(camfront, cameraRight);
	glm::mat4 ViewMatrix = glm::mat4(1.0f);
	ViewMatrix = glm::lookAt(CameraPosition, CameraPosition + camfront, Worldup);

	float fov = 95.0f;
	float nearPlane = 0.5f;
	float farPlane = 1000.0f;
	glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float> (frameBufferWidth) / frameBufferHeight, nearPlane, farPlane);

	//glm::frustum();
	//Lights
	glm::vec3 lightpos0 = glm::vec3(0.0f, 0.0f, 1.0f);


	ourShader.setMat4fv(ModelMatrix, "ModelMatrix");
	ourShader.setMat4fv(ViewMatrix, "ViewMatrix");
	ourShader.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
	ourShader.setVec3f(lightpos0, "lightpos0");
	ourShader.setVec3f(CameraPosition, "CameraPosition");

	//main loop and drawing 
	//glfwRequestWindowAttention(window_1);
	//*************************************************************
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		processInput(window);
		UpdateInput(window, position, rotation, scale);
		//glfwRequestWindowAttention(window_1);
		glClearColor(0.0f, 0.0f, 0.0f, 1.f); //rgb a-opaque
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		
		ourShader.set1i(texture_0.getTxtureunit(), "texture0");
		ourShader.set1i(texture_1.getTxtureunit(), "texture1");
		material0.senToShader(ourShader);

		//ourShader.use();
		// Initialize model matrix here also
		// chnaging cat movements 
		// DOnt forget to add + and - sign else we will get a still image only 
		//position.z -= 0.01f;
		//rotation.x += 1.0f;
		/*glm::mat4 trans = glm::mat4(1.0f);
		glm::mat4 rotate = glm::mat4(0.0f);
		glm::mat4 scaleM = glm::mat4(0.0f);*/
		glm::mat4 ModelMatrix(1.0f);
		ModelMatrix = glm::translate(ModelMatrix, position);
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, scale);
		
		

		ourShader.setMat4fv(ModelMatrix, "ModelMatrix");
		glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
		ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float> (frameBufferWidth) / frameBufferHeight, nearPlane, farPlane);
		ourShader.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
		ourShader.use();
		
		// to use both texture we need to multiply both 

		// Activate Texture and bind it after this use it in the fragment shader
		
		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture0);*/
		// Activate Texture and bind it after this use it in the fragment shader to activate both textures
		/*glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Texture1);*/
		texture_0.bind();
		texture_1.bind();

		
		// Before Binding this i need to get my texture 
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, noofindeces, GL_UNSIGNED_INT, 0);

		test.render(&ourShader);
		glfwSwapBuffers(window);
		

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	//End of Program
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	

	return 0;
}
// Adding inputs from the keyboard here 
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, (wireframe = 1 - wireframe) ? GL_LINE : GL_FILL);
}

void UpdateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3 scale)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		position.z += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		position.z -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		position.x += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		position.x -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		rotation.y += 5.01f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		rotation.y -= 5.01f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


//mouse
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camfront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}
