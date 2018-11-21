#ifndef PUNKT_H
#define PUNKT_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>

GLuint VAO;
GLuint VBO;
GLuint wielkoscPunktu = 10;

class Punkt
{
private:
	int wysokoscOkna;
	int szerokoscOkna;
	int polozenieOknaX;
	int polozenieOknaY;

public:
	Punkt(void);
	Punkt(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY);
	~Punkt(void);
	void stworzenieOkna(int argc, char** argv);
	void inicjalizacjaGlew();
	static void wyswietl();
	static void usun();
	void stworzenieVAO();
	void stworzenieVBO();
	void sprawdzenieWersji();
};

#endif /* PUNKT_H */