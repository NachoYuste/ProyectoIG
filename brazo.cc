#include "brazo.h"

Brazo::Brazo(){
	hombro = new Esfera(10,20,1);
	brazo = new Cilindro(10,20,1,1);
	antebrazo = new Antebrazo();	
	flex_codo= 0.0;
}

void Brazo::draw(set<modo_vis> modos, bool modo_dif){
	
	glPushMatrix();
		
		glPushMatrix();
			glScalef(3,3,3);
			hombro->draw(modos,modo_dif);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(7,0,0);
			glScalef(12,2,2);
			glRotatef(90,0,0,1);
			brazo->draw(modos,modo_dif);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(15,0,0);
			glRotatef(flex_codo,0,0,1);
			antebrazo->draw(modos,modo_dif);
		glPopMatrix();
	
	glPopMatrix();
}

Brazo::Antebrazo::Antebrazo(){
	codomunieca = new Esfera(10,20,1);
	antebrazo = new Cilindro(10,20,1,1);	
}

void Brazo::rotaCodo(float a){
	flex_codo += a;
	
	if(flex_codo>90) 	flex_codo=90;
	if(flex_codo<0)	flex_codo=0;	
}


void Brazo::Antebrazo::draw(set<modo_vis> modos, bool modo_dif){
	glPushMatrix();
		//codo
		glPushMatrix();
			glScalef(3,3,3);
			codomunieca->draw(modos, modo_dif);
		glPopMatrix();

		//antebrazo
		glPushMatrix();
			glTranslatef(9,0,0);
			glScalef(14,2,2);
			glRotatef(-90,0,0,1);
			antebrazo->draw(modos,modo_dif);
		glPopMatrix();

		//mano
		glPushMatrix();
			glTranslatef(15.5,0,0);
			glScalef(3,3,3);
			codomunieca->draw(modos,modo_dif);
		glPopMatrix();

	glPopMatrix();
}

void Brazo::setMaterial(Material mat){
	hombro->setMaterial(mat);
	brazo->setMaterial(mat);
	antebrazo->setMaterial(mat);
}

void Brazo::Antebrazo::setMaterial(Material mat){
	codomunieca->setMaterial(mat);
	antebrazo->setMaterial(mat);
}



