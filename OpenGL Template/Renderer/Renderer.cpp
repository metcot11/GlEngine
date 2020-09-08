#include "Renderer.h"


Renderer::Renderer(Camera& m)
	:camera(m), r_FrameBuffer(), r_QuadBuffer(sizeof(quadVertices), quadVertices),
	r_QuadShader("Shader/Framebuffer/ScreenQuad.fshader", "Shader/Framebuffer/ScreenQuad.vshader"),
	r_BasicShader("Shader/BasicShader/Basic.fshader", "Shader/BasicShader/Basic.vshader"),
	r_Skybox({ "Textures/Cubemap/skybox/right.jpg",
				"Textures/Cubemap/skybox/left.jpg",
				"Textures/Cubemap/skybox/top.jpg",
				"Textures/Cubemap/skybox/bottom.jpg",
				"Textures/Cubemap/skybox/front.jpg",
				"Textures/Cubemap/skybox/back.jpg" }), r_SkyShader("Shader/CubeMap/Skybox.fshader", "Shader/CubeMap/Skybox.vshader")
{
	/* ----------Quad---------- */
	r_QuadBuffer.AttribPointer(0, 2, GL_FLOAT, 4, 0);
	r_QuadBuffer.AttribPointer(1, 2, GL_FLOAT, 4, 2);
	/* ----------Box---------- */
	r_BoxBuffer.CreateVertexBuffer(sizeof(vertices), vertices);
	r_BoxBuffer.AttribPointer(0, 3, GL_FLOAT, 8, 0);
	r_BoxBuffer.AttribPointer(2, 3, GL_FLOAT, 8, 3);
	r_BoxBuffer.AttribPointer(1, 2, GL_FLOAT, 8, 6);
	/* ----------Plane---------- */
	r_PlaneBuffer.CreateVertexBuffer(sizeof(PlaneData), PlaneData);
	r_PlaneBuffer.AttribPointer(0, 3, GL_FLOAT, 5, 0);
	r_PlaneBuffer.AttribPointer(1, 2, GL_FLOAT, 5, 3);
	r_PlaneTexture = Texture("Textures/Tex_images/concrete.png", "Texture", true);
	/* ----------Skybox---------- */
	r_SkyBuffer.CreateVertexBuffer(sizeof(skyboxVertices), skyboxVertices);
	r_SkyBuffer.AttribPointer(0, 3, GL_FLOAT, 3, 0);
}

Renderer::~Renderer()
{
}

void Renderer::UpdateFrame()
{

	r_FrameBuffer.Bind();
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawScene();

	r_FrameBuffer.UnBind();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawScene();
	r_FrameBuffer.DrawQuad(r_QuadShader, r_QuadBuffer);
}

void Renderer::UpdateInput()
{
}

void Renderer::DrawScene()
{

	camera.UpdateView(r_BasicShader);


	DrawCube(r_BasicShader, r_Skybox, r_BoxBuffer, glm::vec3(5.0f, 0.02f, 5.0f), 1.0f);
	DrawCube(r_BasicShader, r_Skybox, r_BoxBuffer, glm::vec3(3.0f, 0.02f, 4.0f), 1.0f);

	DrawPlane(r_BasicShader, r_PlaneTexture, r_PlaneBuffer, glm::vec3(0.0f));
	DrawSkyBox(r_SkyShader, r_Skybox, r_SkyBuffer);
}

void Renderer::DrawCube(Shader shader, CubeMap texture, BufferObject& Buffer, glm::vec3 pos, float f)
{
	shader.On();
	shader.SetUniformFloat("tex", true);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(f, f, f));

	shader.SetUniformVec3("cameraPos", camera.Position);
	shader.SetUniformMat4("model", model);
	texture.BindCubeMap(shader, 0);
	Buffer.BindBuffer();
	glDrawArrays(GL_TRIANGLES, 0, 36);

	Buffer.UnBindVertexBuffer();
	Buffer.UnBindVertexArrayBuffer();
	shader.Off();
}

void Renderer::DrawPlane(Shader shader, Texture texture, BufferObject& Buffer, glm::vec3 pos)
{
	shader.On();
	shader.SetUniformFloat("tex", false);
	Buffer.BindBuffer();
	shader.SetUniformMat4("model", glm::mat4(1.0f));
	texture.BindTexture2D(shader, 1);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Buffer.UnBindVertexArrayBuffer();
	Buffer.UnBindVertexBuffer();
	shader.Off();
}

void Renderer::DrawSkyBox(Shader shader, CubeMap Skybox, BufferObject& Buffer)
{
	glDepthFunc(GL_LEQUAL);
	shader.On();
	glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)1240 / (float)640, 0.1f, 100.0f);
	glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
	shader.SetUniformMat4("projection", proj);
	shader.SetUniformMat4("view", view);
	Buffer.BindBuffer();

	Skybox.BindCubeMap(shader, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Buffer.UnBindVertexArrayBuffer();
	Buffer.UnBindVertexBuffer();
	shader.Off();
	glDepthFunc(GL_LESS);
}



