/*
	================================================================
	File name	: glxt.h
	Created		: 01.10.2023
	Modified	: 04.12.2023
	Author		: bolatulyerdos
	Description	: OpenGL Extensions (GLXT)
	================================================================
*/

#ifndef	GLXT_H
#define	GLXT_H

#ifdef __cplusplus
extern "C" {
#endif

// Расширение (аналог gluLookAt)
void			glxtLookAt		(double eye_x, double eye_y, double eye_z, double center_x, double center_y, double center_z, double up_x, double up_y, double up_z);

// Расширение (аналог gluPerspective)
void			glxtPerspective	(double fov_y, double aspect_ratio, double near_plane, double far_plane);

#ifdef __cplusplus
}
#endif

#endif	// GLXT_H