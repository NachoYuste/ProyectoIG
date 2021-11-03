#include "material.h"

Material::Material(Tupla4f amb, Tupla4f dif, Tupla4f esp, GLfloat bri){
	ambiente = amb;
	difuso = dif;
	especular = esp;
	brillo = bri;

}

void Material::aplicar(){
 
//Definir material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
	glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &brillo);

}

Material::Material(Material &mat){
	ambiente = mat.ambiente;
	difuso = mat.difuso;
	especular = mat.especular;
	brillo = mat.brillo;
}



