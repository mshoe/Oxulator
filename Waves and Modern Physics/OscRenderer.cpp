#include "OscRenderer.h"

OscRenderer::OscRenderer(CoreManager * core)
{
	this->core = core;
	Init();
}

OscRenderer::~OscRenderer()
{
	Cleanup();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void OscRenderer::Init()
{
	Cleanup();

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	

	model = new glm::mat4;
	camera = new Camera(glm::vec3(0.0f, 1.0f, 3.0f));

	buildPend(new Pendulum);
}

void OscRenderer::Cleanup()
{
	if (ourShader != NULL) {
		Shader *temp = ourShader;
		delete temp;
	}
	if (model != NULL) {
		glm::mat4 *temp = model;
		delete temp;
	}
	if (camera != NULL) {
		Camera *temp = camera;
		delete temp;
	}
}

void OscRenderer::buildSHO(SHO *sho)
{
	if (this->sho != NULL) {
		SHO *temp = this->sho;
		delete temp;
	}

	this->sho = sho;
	float size = 0.5;

	if (ourShader != NULL) {
		Shader *temp = ourShader;
		delete temp;
	}

	ourShader = new Shader("..\\Waves and Modern Physics\\SHOshader1.vs", "..\\Waves and Modern Physics\\SHOshader1.frag");

	(*ourShader).Use();

	std::vector<GLfloat> vertices = cubeVerts();
	std::vector<GLuint> indices = cubeInds();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	std::cout << "SHO building complete" << std::endl;

	selection = 1;
}

void OscRenderer::renderSHO()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	(*ourShader).Use();

	float angle = core->deltaTime * 45.f;
	//rotate3(angle, 1.f, 1.f, 1.f);


	// model
	GLuint modelLoc = glGetUniformLocation((*ourShader).Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(*model));

	// view
	GLuint viewLoc = glGetUniformLocation((*ourShader).Program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	// perspective
	glm::mat4 projection = glm::perspective(camera->Zoom, (float)core->image_width / (float)core->image_height, 0.1f, 100.0f);
	GLuint projectionLoc = glGetUniformLocation((*ourShader).Program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLuint xPosLoc = glGetUniformLocation((*ourShader).Program, "xPos");
	glUniform1f(xPosLoc, sho->x(core->totalTime));

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	SDL_GL_SwapWindow(core->mainWindow);
}

void OscRenderer::buildPend(Pendulum * pend)
{
	if (this->pend != NULL) {
		Pendulum *temp = this->pend;
		delete temp;
	}

	pend->theta = M_PI/1.1f;
	pend->updateXY();
	this->pend = pend;
	float size = 0.1;

	if (ourShader != NULL) {
		Shader *temp = ourShader;
		delete temp;
	}

	ourShader = new Shader("..\\Waves and Modern Physics\\PendulumShader.vs", "..\\Waves and Modern Physics\\PendulumShader.frag");

	(*ourShader).Use();

	std::vector<GLfloat> vertices = sphereVerts(size, 20, 20);
	std::vector<GLuint> indices = sphereInds(20, 20);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	std::cout << "SHO building complete" << std::endl;

	selection = 2;
}

void OscRenderer::renderPend()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	(*ourShader).Use();

	// Put this before updatePendulum
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(-pend->x, -pend->y + pend->L, 0);
	glEnd();

	pend->updatePendulum(core->deltaTime);
	
	
	

	

	// model
	GLuint modelLoc = glGetUniformLocation((*ourShader).Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(*model));

	// view
	GLuint viewLoc = glGetUniformLocation((*ourShader).Program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	// perspective
	glm::mat4 projection = glm::perspective(camera->Zoom, (float)core->image_width / (float)core->image_height, 0.1f, 100.0f);
	GLuint projectionLoc = glGetUniformLocation((*ourShader).Program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLuint xPosLoc = glGetUniformLocation((*ourShader).Program, "xPos");
	glUniform1f(xPosLoc, pend->x);

	GLuint yPosLoc = glGetUniformLocation((*ourShader).Program, "yPos");
	glUniform1f(yPosLoc, pend->y);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 20 * 20 * 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	

	SDL_GL_SwapWindow(core->mainWindow);
}

void OscRenderer::Render()
{
	switch (selection)
	{
	case 1:
		renderSHO();
		break;
	case 2:
		renderPend();
		break;
	default:
		break;
	}
}

void OscRenderer::rotate3(float angle, float x, float y, float z)
{
	*model = glm::rotate(*model, glm::radians(angle), glm::vec3(x, y, z));
}

std::vector<GLfloat> OscRenderer::cubeVerts()
{
	std::vector<GLfloat> vertices(4 * 3 * 2 * 6);
	glm::vec3 color(1, 1, 1);
	float size = 0.25;
	// TOP

	//0
	vertices[0] = -size;
	vertices[1] = +size;
	vertices[2] = +size;
	vertices[3] = color.x;
	vertices[4] = color.y;
	vertices[5] = color.z;

	//1
	vertices[6] = -size;
	vertices[7] = +size;
	vertices[8] = -size;
	vertices[9] = color.x;
	vertices[10] = color.y;
	vertices[11] = color.z;

	//2
	vertices[12] = +size;
	vertices[13] = +size;
	vertices[14] = -size;
	vertices[15] = color.x;
	vertices[16] = color.y;
	vertices[17] = color.z;

	//3
	vertices[18] = +size;
	vertices[19] = +size;
	vertices[20] = +size;
	vertices[21] = color.x;
	vertices[22] = color.y;
	vertices[23] = color.z;

	//FRONT

	//0
	vertices[24] = -size;
	vertices[25] = -size;
	vertices[26] = +size;
	vertices[27] = color.x;
	vertices[28] = color.y;
	vertices[29] = color.z;

	//1
	vertices[30] = -size;
	vertices[31] = +size;
	vertices[32] = +size;
	vertices[33] = color.x;
	vertices[34] = color.y;
	vertices[35] = color.z;

	//2
	vertices[36] = +size;
	vertices[37] = +size;
	vertices[38] = +size;
	vertices[39] = color.x;
	vertices[40] = color.y;
	vertices[41] = color.z;

	//3
	vertices[42] = +size;
	vertices[43] = -size;
	vertices[44] = +size;
	vertices[45] = color.x;
	vertices[46] = color.y;
	vertices[47] = color.z;

	//LEFT

	//0
	vertices[48] = -size;
	vertices[49] = -size;
	vertices[50] = -size;
	vertices[51] = color.x;
	vertices[52] = color.y;
	vertices[53] = color.z;

	//1
	vertices[54] = -size;
	vertices[55] = +size;
	vertices[56] = -size;
	vertices[57] = color.x;
	vertices[58] = color.y;
	vertices[59] = color.z;

	//2
	vertices[60] = -size;
	vertices[61] = +size;
	vertices[62] = +size;
	vertices[63] = color.x;
	vertices[64] = color.y;
	vertices[65] = color.z;

	//3
	vertices[66] = -size;
	vertices[67] = -size;
	vertices[68] = +size;
	vertices[69] = color.x;
	vertices[70] = color.y;
	vertices[71] = color.z;

	//BACK

	//0
	vertices[72] = +size;
	vertices[73] = -size;
	vertices[74] = -size;
	vertices[75] = color.x;
	vertices[76] = color.y;
	vertices[77] = color.z;

	//1
	vertices[78] = +size;
	vertices[79] = +size;
	vertices[80] = -size;
	vertices[81] = color.x;
	vertices[82] = color.y;
	vertices[83] = color.z;

	//2
	vertices[84] = -size;
	vertices[85] = +size;
	vertices[86] = -size;
	vertices[87] = color.x;
	vertices[88] = color.y;
	vertices[89] = color.z;

	//3
	vertices[90] = -size;
	vertices[91] = -size;
	vertices[92] = -size;
	vertices[93] = color.x;
	vertices[94] = color.y;
	vertices[95] = color.z;

	//RIGHT

	//0
	vertices[96] = +size;
	vertices[97] = -size;
	vertices[98] = +size;
	vertices[99] = color.x;
	vertices[100] = color.y;
	vertices[101] = color.z;

	//1
	vertices[102] = +size;
	vertices[103] = +size;
	vertices[104] = +size;
	vertices[105] = color.x;
	vertices[106] = color.y;
	vertices[107] = color.z;

	//2
	vertices[108] = +size;
	vertices[109] = +size;
	vertices[110] = -size;
	vertices[111] = color.x;
	vertices[112] = color.y;
	vertices[113] = color.z;

	//3
	vertices[114] = +size;
	vertices[115] = -size;
	vertices[116] = -size;
	vertices[117] = color.x;
	vertices[118] = color.y;
	vertices[119] = color.z;

	//BOTTOM

	//0
	vertices[120] = -size;
	vertices[121] = -size;
	vertices[122] = -size;
	vertices[123] = color.x;
	vertices[124] = color.y;
	vertices[125] = color.z;

	//1
	vertices[126] = -size;
	vertices[127] = -size;
	vertices[128] = +size;
	vertices[129] = color.x;
	vertices[130] = color.y;
	vertices[131] = color.z;

	//2
	vertices[132] = +size;
	vertices[133] = -size;
	vertices[134] = +size;
	vertices[135] = color.x;
	vertices[136] = color.y;
	vertices[137] = color.z;

	//3
	vertices[138] = +size;
	vertices[139] = -size;
	vertices[140] = -size;
	vertices[141] = color.x;
	vertices[142] = color.y;
	vertices[143] = color.z;
	return vertices;
}

std::vector<GLuint> OscRenderer::cubeInds()
{
	std::vector<GLuint> indices(6 * 6);
	for (int i = 0; i < 6; i++) {
		indices[i * 6 + 0] = i * 4 + 0;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 3;
		indices[i * 6 + 3] = i * 4 + 1;
		indices[i * 6 + 4] = i * 4 + 2;
		indices[i * 6 + 5] = i * 4 + 3;
	}
	return indices;
}

std::vector<GLfloat> OscRenderer::sphereVerts(float radius, unsigned int rings, unsigned int sectors)
{
	std::vector<GLfloat> vertices(rings * sectors * 3 * 3);
	glm::vec3 color(1, 1, 1);
    float const R = 1./(float)(rings-1);
    float const S = 1./(float)(sectors-1);
    int r, s;

    //vertices.resize(rings * sectors * 3 * 3);
    //normals.resize(rings * sectors * 3);
    //texcoords.resize(rings * sectors * 2);
    std::vector<GLfloat>::iterator v = vertices.begin();
    //std::vector<GLfloat>::iterator n = normals.begin();
    //std::vector<GLfloat>::iterator t = texcoords.begin();
    for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
            float const y = sin( -M_PI/2.f + M_PI * r * R );
            float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
            float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

            //*t++ = s*S;
            //*t++ = r*R;

            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;
			*v++ = color.x;
			*v++ = color.y;
			*v++ = color.z;

            //*n++ = x;
            //*n++ = y;
            //*n++ = z;
    }

	return vertices;
}

std::vector<GLuint> OscRenderer::sphereInds(unsigned int rings, unsigned int sectors)
{
	std::vector<GLuint> indices(rings * sectors * 4);
    std::vector<GLuint>::iterator i = indices.begin();

	int r, s;

    for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s+1);
            *i++ = (r+1) * sectors + (s+1);
            *i++ = (r+1) * sectors + s;
    }

	return indices;
}
