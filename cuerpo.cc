#include "cuerpo.h"

Cuerpo::Cuerpo(){
	partesup = new Cono(100,1,1);
	parteinf = new Cono(100,1,1);
	
	//Textura
	tex_falda = new Textura("./texturas/tutu.jpg");
	
}

void Cuerpo::draw(set<modo_vis> modos, bool modo_dif){
	
	glPushMatrix();
	//glTranslatef(0,-10,0);
	
		//Parte de arriba
		glPushMatrix();
			glTranslatef(0,-7,0);
			glScalef(16.0,22.0,16.0);
			partesup->draw(modos,modo_dif);
		glPopMatrix();
		
		//Parte de abajo
		glPushMatrix();
			glTranslatef(0,7,0);
			glRotatef(180.0,1.0,0,0);
			glScalef(16.0,22.0,16.0);
			parteinf->draw(modos,modo_dif);
		glPopMatrix();
	
	glPopMatrix();
}

void Cuerpo::setMaterial(Material mat){
	partesup->setMaterial(mat);
	parteinf->setMaterial(mat);
}

void Cuerpo::setTexturas(){
	parteinf->setTextura(tex_falda);
}

