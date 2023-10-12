/*
	================================================================
	File name	: glxt.с
	Created		: 01.10.2023
	Modified	: 01.10.2023
	Author		: bolatulyerdos
	Description	: OpenGL Extensions (GLXT)
	================================================================
*/

#include <math.h>

#if defined(_WIN32_)
#include <windows.h>
#endif

#include <GL/gl.h>

#include "glxt.h"

// Константы
static const float pi = 3.14159265358979323846264338327950f;

// Нормализация вектора
static void	normalize		(float vec[3])
{
	float len = (float)sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);

	if (len == 0.f)
		return;

	vec[0] /= len;
	vec[1] /= len;
	vec[2] /= len;
}

// Векторное произведение двух векторов
static void	cross			(float vec1[3], float vec2[3], float res[3])
{
	res[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	res[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	res[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

// Расширение (аналог gluLookAt)
void		glxtLookAt		(float eye_x, float eye_y, float eye_z, float center_x, float center_y, float center_z, float up_x, float up_y, float up_z)
{
	float forward[3], up[3], side[3];

	forward[0]		= center_x - eye_x;
	forward[1]		= center_y - eye_y;
	forward[2]		= center_z - eye_z;

	up[0]			= up_x;
	up[1]			= up_y;
	up[2]			= up_z;

	normalize		(forward);
	cross			(forward, up, side);
	normalize		(side);
	cross			(side, forward, up);

	float matrix[16] =
	{
		side[0],	up[0],	-forward[0],	0.f,
		side[1],	up[1],	-forward[1],	0.f,
		side[2],	up[2],	-forward[2],	0.f,
		0.f,		0.f,	0.f,			1.f
	};

	// OpenGL
	glMultMatrixf	(matrix);
	glTranslated	(-eye_x, -eye_y, -eye_z);
}

// Расширение (аналог gluPerspective)
void		glxtPerspective	(float fov_y, float aspect_ratio, float near_plane, float far_plane)
{
	if (fov_y <= 0.f || aspect_ratio <= 0.f || far_plane - near_plane <= 0.f)
		return;

	float height	= (float)tan(fov_y * pi / 360.f) * near_plane;
	float width		= height * aspect_ratio;

	// OpenGL
	glFrustum		(-width, width, -height, height, near_plane, far_plane);
}