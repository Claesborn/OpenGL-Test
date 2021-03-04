#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include "Shader.h"



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		float positions[] = {
			-0.5f,	-0.5f,
			 0.5f,	-0.5f,
			 0.5f,	 0.5f,
			-0.5f,	 0.5f,

		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		
		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));
		
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		

		IndexBuffer ib(indices, 6);

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		
		shader.SetUniform4f("u_Color", 0.2f, 0.8f, 0.8f, 1.0f);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();
	

		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float rincrement = 0.005f;
		float gincrement = 0.003f;
		float bincrement = 0.001f;
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			shader.Bind();
			shader.SetUniform4f("u_Color", r, g, b, 1.0f);

			va.Bind();
			ib.Bind();


			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			if (r > 1.0f)
				rincrement *= -1.0f;
			else if (r < 0.0f)
				rincrement *= -1.0f;
			if (g > 1.0f)
				gincrement *= -1.0f;
			else if (g < 0.0f)
				gincrement *= -1.0f;
			if (b > 1.0f)
				bincrement *= -1.0f;
			else if (b < 0.0f)
				bincrement *= -1.0f;
			r += rincrement;
			g += gincrement;
			b += bincrement;

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

	}
	glfwTerminate();
	return 0;
}