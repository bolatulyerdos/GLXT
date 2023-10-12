/*
	================================================================
	File name	: glxt.h
	Created		: 01.10.2023
	Modified	: 01.10.2023
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
void		glxtLookAt		(float eye_x, float eye_y, float eye_z, float center_x, float center_y, float center_z, float up_x, float up_y, float up_z);

// Расширение (аналог gluPerspective)
void		glxtPerspective	(float fov_y, float aspect_ratio, float near_plane, float far_plane);

#ifdef __cplusplus
}
#endif

#endif	// GLXT_H