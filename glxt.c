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

#if defined(WIN32)
#include <windows.h>
#endif

#include <GL/gl.h>

#include "glxt.h"

// Константы
static const double pi = 3.14159265358979323846264338327950;

typedef struct
{
	double x, y, z;
}
Vector3d;

// Конвертеры
static double	rad2deg			(double val)	// Радианы в градусы
{
	return val * 180.0 / pi;
}

static double	deg2rad			(double val)	// Градусы в радианы
{
	return val * pi / 180.0;
}

// Нормализация вектора
static void	normalize		(Vector3d* vec)
{
	double len = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);

	// Проверка на ноль
	if (len == 0.0)
		return;

	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
}

// Векторное произведение двух векторов
static void	cross			(Vector3d* vec1, Vector3d* vec2, Vector3d* res)
{
	res->x = vec1->y * vec2->z - vec1->z * vec2->y;
	res->y = vec1->z * vec2->x - vec1->x * vec2->z;
	res->z = vec1->x * vec2->y - vec1->y * vec2->x;
}

// Расширение (аналог gluLookAt)
void		glxtLookAt		(double eye_x, double eye_y, double eye_z, double center_x, double center_y, double center_z, double up_x, double up_y, double up_z)
{
	Vector3d forward, side, up;

	up.x			= up_x;
	up.y			= up_y;
	up.z			= up_z;

	// Расчет и нормализация вектора направления (forward)
	forward.x		= center_x - eye_x;
	forward.y		= center_y - eye_y;
	forward.z		= center_z - eye_z;
	normalize		(&forward);

	// Расчет и нормализация бокового вектора (side)
	cross			(&forward, &up, &side);
	normalize		(&side);

	// Расчет вектора вверх (up)
	cross			(&side, &forward, &up);

	// Создание матрицы преобразования
	double matrix[16] =
	{
		side.x,	up.x,	-forward.x,	0.0,
		side.y,	up.y,	-forward.y,	0.0,
		side.z,	up.z,	-forward.z,	0.0,
		0.0,	0.0,	0.0,		1.0
	};

	// Загрузка в OpenGL
	glMultMatrixd	(matrix);
	glTranslated	(-eye_x, -eye_y, -eye_z);
}

// Расширение (аналог gluPerspective)
void		glxtPerspective	(double fov_y, double aspect_ratio, double near_plane, double far_plane)
{
	if (fov_y <= 0.0 || aspect_ratio <= 0.0 || near_plane <= 0.0 || far_plane <= 0.0 || far_plane - near_plane <= 0.0)
		return;

	double height	= tan(deg2rad(fov_y / 2.0)) * near_plane;
	double width	= height * aspect_ratio;

	// Загрузка в OpenGL
	glFrustum		(-width, width, -height, height, near_plane, far_plane);
}