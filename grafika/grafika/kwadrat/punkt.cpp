#include "punkt.h"
#include <ctime>

Punkt::Punkt(void)
{
	wysokoscOkna = 768;
	szerokoscOkna = 1024;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
}

Punkt::Punkt(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY)
{
	this->wysokoscOkna = wysokoscOkna;
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
}

Punkt::~Punkt()
{

}

void Punkt::stworzenieOkna(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(szerokoscOkna, wysokoscOkna);
	glutInitWindowPosition(polozenieOknaX, polozenieOknaY);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("punkt");
}

void Punkt::inicjalizacjaGlew()
{
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK)
	{
		std::cerr << "Nie udalo sie zainicjalizowac GLEW. Blad: " << glewGetErrorString(wynik) << std::endl;
		system("pause");
		exit(1);
	}
}

void  Punkt::wyswietl()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glPointSize(wielkoscPunktu);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 3, 3);
	glDrawArrays(GL_TRIANGLES, 7, 3);
	glDrawArrays(GL_TRIANGLES, 6, 3);

	glDrawArrays(GL_TRIANGLE_FAN, 10, 30);
	
	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

void Punkt::usun()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Punkt::stworzenieVAO()
{
	glGenVertexArrays(1, &VAO);
	std::cout << "VAO: " << VAO << std::endl;
	glBindVertexArray(VAO);
}

void Punkt::stworzenieVBO()
{
	const int triangleAmount = 30;

	glm::vec3 Wierzcholki[10 + triangleAmount] = {
		glm::vec3(0.0f, 0.1f, 0.0f),
		glm::vec3(0.1f, -0.1f, 0.0f),
		glm::vec3(-0.1f, -0.1f, 0.0f),
		glm::vec3(0.6f, 0.4f, 0.0f),
		glm::vec3(0.2f, 0.1f, 0.0f),
		glm::vec3(0.8f, 0.1f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3(-0.7f, 0.5f, 0.0f),
		glm::vec3(-0.5f, 0.7f, 0.0f),
		glm::vec3(-0.7f, 0.7f, 0.0f)
	};
	GLfloat twicePi = 2.0f * 3.14;

	for (int i = 10; i < triangleAmount + 10; i++){
		Wierzcholki[i] = glm::vec3(
			(0.1f * cos((i - 10) * twicePi / triangleAmount)) + 0.5f,
			(-0.1f * sin((i - 10) * twicePi / triangleAmount)) - 0.5f,
			0.0f);
	}

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	std::cout << "VBO: " << VBO << std::endl;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Wierzcholki), Wierzcholki, GL_STATIC_DRAW);

}

void Punkt::sprawdzenieWersji()
{
	std::cout << "Wersja GLEW: " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "Wersja VENDOR: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Wersja REDERER: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Wersja GL: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Wersja GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}


int main(int argc, char** argv)
{
	std::srand(time(NULL));
	Punkt punkt(786, 786, 100, 100);

	punkt.stworzenieOkna(argc, argv);
	punkt.inicjalizacjaGlew();
	punkt.sprawdzenieWersji();
	punkt.stworzenieVAO();

	punkt.stworzenieVBO();

	glutDisplayFunc(punkt.wyswietl);
	glutCloseFunc(punkt.usun);

	glClearColor(0.2f, 0.1f, 0.0f, 0.0f);

	glutMainLoop();

	return 0;
}
