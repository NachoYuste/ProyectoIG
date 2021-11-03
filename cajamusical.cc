#include "cajamusical.h"

CajaMusical::CajaMusical(){
	caja = new Cubo(1);
	tapa = new Cubo(1);
	agujero = new Cubo(1);
	bailarinagir = new BailarinaGiratoria();
	
	alfa = 0;
	elevacion = -70;

	caja_tapa = new Material({0.19225,0.19225,0.19225,1}, {0.50754,0.50754,0.50754,1},{0.508273,0.508273,0.508273,1},0.4*1280.0f);
	mat_agujero = new Material({0.05375f, 0.05f, 0.06625f, 0.82f},{.18275f, 0.17f, 0.22525f, 0.82f},{0.332741f, 0.328634f, 0.346435f, 0.82f},38.4f);
	mat_on = false;
	
	tex_caja = new Textura("./texturas/caja.jpg");
	
	factor_velocidad = 0.01;
	esta_arriba = false;
}

CajaMusical::BailarinaGiratoria::BailarinaGiratoria(){
	base = new Cilindro(20,80,1,1);
	bailarina = new Bailarina();
	
	beta = 0;
	
	mat_base = new Material({ 0.1745f, 0.01175f, 0.01175f, 0.55f },{0.61424f, 0.04136f, 0.04136f, 0.55f },{0.727811f, 0.626959f, 0.626959f, 0.55f },76.8f);
	mat_on = false;	
}

void CajaMusical::draw(set<modo_vis> modos, bool modo_dif){
	glPushMatrix();
		//Caja
		glPushMatrix();
			glScalef(200,200,200);
			caja->draw(modos,modo_dif);
		glPopMatrix();
		
		//Tapa
		glPushMatrix();
			glTranslatef(0,100,0);
			glTranslatef(0,0,-100);
			glRotatef(alfa,1,0,0);
			glTranslatef(0,0,100);
			glScalef(200,30,200);
			tapa->draw(modos,modo_dif);
		glPopMatrix();
		
		if(modos.find(TEXTURA)!=modos.end())
			modos.erase(modos.find(TEXTURA));
		
		//Agujero
		glPushMatrix();
			glTranslatef(0,100,0);
			glScalef(110,5,110);
			agujero->draw(modos,modo_dif);
		glPopMatrix();
		
		//BailarinaGiratoria
		glPushMatrix();
			glTranslatef(0,elevacion,0);
			bailarinagir->draw(modos,modo_dif);
		glPopMatrix();
		

	glPopMatrix();
}

void CajaMusical::BailarinaGiratoria::draw(set<modo_vis> modos, bool modo_dif){
	glPushMatrix();
		
		//Base
		glPushMatrix();
			glScalef(50,10,50);
			base->draw(modos,modo_dif);
		glPopMatrix();
		
		//Bailarina
		glPushMatrix();
			glTranslatef(0,58,0);
			glRotatef(beta,0,1,0);
			bailarina->draw(modos,modo_dif);
		glPopMatrix();
	
	glPopMatrix();
	
}

void CajaMusical::BailarinaGiratoria::rotaBailarina(float b){
	beta+=b;
	
	if(beta>360) beta=0;
}

void CajaMusical::rotaTapa(float a){
	alfa-=a;
	
	if (alfa<-75) alfa=-75;
	if (alfa>0)	alfa=0;
}

void CajaMusical::rotaBailarina(float giro){
	bailarinagir->rotaBailarina(giro);
}

void CajaMusical::subeBase(float ele, float giro){
	bailarinagir->rotaBailarina(giro);
	rotaTapa(ele);
	elevacion+=ele;
	
	if(elevacion>105) elevacion = 105;	
}

bool CajaMusical::estaArriba(){
	return elevacion==105;
}

void CajaMusical::activaMateriales(bool activar){
	
	if(activar){
		bailarinagir->activaMateriales(activar);
		caja->setMaterial(*caja_tapa);
		tapa->setMaterial(*caja_tapa);
		agujero->setMaterial(*mat_agujero);
		mat_on = true;
	}
	else
		mat_on = false;
}

void CajaMusical::setTexturas(){
	caja->setTextura(tex_caja);
	tapa->setTextura(tex_caja);
}

void CajaMusical::BailarinaGiratoria::setTexturas(){
	bailarina->setTexturas();
}


void CajaMusical::BailarinaGiratoria::activaMateriales(bool activar){
	bailarina->activaMateriales(activar);
	
	if(activar){ base->setMaterial(*mat_base); mat_on = true;}
	else	mat_on = false;
}

void CajaMusical::animar(){
	float valor_rotaciones = 0.2;
	valor_rotaciones *= factor_velocidad;
	subeBase(valor_rotaciones,valor_rotaciones);
	if(estaArriba()){
		bailarinagir->cambiaFactorVelocidad(factor_velocidad);
		bailarinagir->animar();
	} 
}

void CajaMusical::animaBailarina(){
	bailarinagir->animar();
}

void CajaMusical::BailarinaGiratoria::animar(){
	bailarina->animar();
}

void CajaMusical::cambiaFactorVelocidad(float new_factor){	
	factor_velocidad = new_factor;
}
void CajaMusical::BailarinaGiratoria::cambiaFactorVelocidad(float new_factor){
	bailarina->cambiaFactorVelocidad(new_factor);
}


void CajaMusical::aumentaGradosLibBD(float gl){
	bailarinagir->aumentaGradosLibBD(gl);
}

void CajaMusical::aumentaGradosLibBI(float gl){
	bailarinagir->aumentaGradosLibBI(gl);
}

void CajaMusical::aumentaGradosLibPD(float gl){
	bailarinagir->aumentaGradosLibPD(gl);
}

void CajaMusical::aumentaGradosLibPI(float gl){
	bailarinagir->aumentaGradosLibPI(gl);
}

void CajaMusical::BailarinaGiratoria::aumentaGradosLibBD(float gl){
	bailarina->aumentaGradosLibBD(gl);
}

void CajaMusical::BailarinaGiratoria::aumentaGradosLibBI(float gl){
	bailarina->aumentaGradosLibBI(gl);
}

void CajaMusical::BailarinaGiratoria::aumentaGradosLibPD(float gl){
	bailarina->aumentaGradosLibPD(gl);
}

void CajaMusical::BailarinaGiratoria::aumentaGradosLibPI(float gl){
	bailarina->aumentaGradosLibPI(gl);
}

void CajaMusical::setTPose(){
	bailarinagir->setTPose();
}

void CajaMusical::BailarinaGiratoria::setTPose(){
	bailarina->setTPose();
}

void CajaMusical::setPoseBaile(){
	bailarinagir->setPoseBaile();
}

void CajaMusical::BailarinaGiratoria::setPoseBaile(){
	bailarina->setPoseBaile();
}

void CajaMusical::imprimeValores(){
	bailarinagir->imprimeValores();
}

void CajaMusical::BailarinaGiratoria::imprimeValores(){
	bailarina->imprimeValores();
}




















