#include "textura.h"
#include "jpg_imagen.hpp"



Textura::Textura(const string & archivo){
	jpg::Imagen * img = new jpg::Imagen(archivo);

	unsigned char * leidos = img->leerPixels();

	width = img->tamX();
	height = img->tamY();
	
	for (unsigned i = 0; i < height*width*3; i++){
		data.push_back(*(leidos+i));
	}

	// inicializamos a valor nulo
	textura_id = -1;
}


void Textura::activar(){

	glEnable( GL_TEXTURE_2D );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	
	if (textura_id == -1 ){
		glGenTextures(1, &textura_id);
		glBindTexture(GL_TEXTURE_2D, textura_id);
		gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,width,height,GL_RGB,GL_UNSIGNED_BYTE,data.data());

	}

	glBindTexture(GL_TEXTURE_2D, textura_id);
}


