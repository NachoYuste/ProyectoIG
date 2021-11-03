#include "bailarina.h"

Bailarina::Bailarina(){
	//Objetos
	cuerpo = new Cuerpo();
	brazod = new Brazo();
	brazoi = new Brazo();
	piernad = new Pierna;
	piernai = new Pierna;
	cabeza = new Cabeza();
		
	//Ángulos de rotación en posicion original
	rot_hombrod = rot_hombroi = 0;
	ele_hombrod = ele_hombroi = 0;
	giro_brazod = giro_brazoi = 0;
	codod = codoi = 0;
	ele_caderad = ele_caderai =0;
	rodillad = rodillai = 360;
	rot_caderad = rot_caderai = 0;
	
	rotaBrazoD(0,75,0,45);
	rotaBrazoI(0,75,0,45);
	rotaPiernaD(0,45,90);
	rotaPiernaI(90,0,0);
	
	//Materiales
	piel = new Material({0.25f,0.20725f,0.20725f,0.922f},{1.0f, 0.829f, 0.829f, 0.922f},{0.296648f, 0.296648f, 0.296648f, 0.922f }, 11.264f);
	vestido = new Material({0.05f,0.0f,0.0f,1.0f},{0.5f,0.4f,0.4f,1.0f},{0.7f,0.04f,0.04f,1.0f}, 10.0f);
	mat_on = false;
	
	factor_velocidad = 0.1;
	moverBD = true;
	moverBI = moverPD = false;
	paso1 = true;
	paso2 = paso3 = false;
	paso1p = true;
	paso2p = false;
	
}

void Bailarina::draw(set<modo_vis> modos, bool modo_dif){
	glPushMatrix();
		//cuerpo
		cuerpo->draw(modos,modo_dif);	

		//Brazos
		glPushMatrix();
			glTranslatef(16,16,0);
			glRotatef(rot_hombroi,0,1,0); 	//valores negativos [0,-90]
			glRotatef(ele_hombroi,0,0,1);		//valores positivos [0,90]
			glRotatef(giro_brazoi,1,0,0);
			brazoi->draw(modos,modo_dif);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-16,16,0);
			glRotatef(-180,0,1,0);
			glRotatef(rot_hombrod,0,1,0);		//valores positivos [0,90]
			glRotatef(ele_hombrod,0,0,1);		//valores positivos [0,90]
			glRotatef(giro_brazod,1,0,0); 
			brazod->draw(modos,modo_dif);
		glPopMatrix();
		
		//Piernas
		glPushMatrix();
			glTranslatef(-8,-20,0);
			glRotatef(rot_caderad,0,1,0);		//valores negativos [-90,-180]
			glRotatef(ele_caderad,0,0,1);		//valores positivos [0,90]
			piernad->draw(modos,modo_dif);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(8,-20,0);
			glRotatef(rot_caderai,0,1,0);		//valore negativos [0,-90]
			glRotatef(ele_caderai,0,0,1);		//valores positivos [0,90]
			piernai->draw(modos,modo_dif);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,18,0);
			cabeza->draw(modos,modo_dif);
		glPopMatrix();
		
	glPopMatrix();
	
}

void Bailarina::rotaBrazoD(float rot_hombro, float ele_hombro, float girob, float codo)
{
	rot_hombrod += rot_hombro;
	ele_hombrod += ele_hombro;
	codod += codo;
	giro_brazod = girob;
	brazod->rotaCodo(codo);
	
	//cout << ele_hombrod << endl;
	
	if(rot_hombrod > 90) rot_hombrod = 90;
	if(rot_hombrod < 0) rot_hombrod = 0;
	if(ele_hombrod > 90) ele_hombrod = 90;
	if(ele_hombrod < -90) ele_hombrod = -90;
}

void Bailarina::rotaBrazoI(float rot_hombro, float ele_hombro, float girob, float codo){
	rot_hombroi -= rot_hombro;
	ele_hombroi += ele_hombro;
	codoi +=codo;
	giro_brazoi = girob;
	brazoi->rotaCodo(codo);
	
	if(rot_hombroi < -90) rot_hombroi = -90;
	if(rot_hombroi > 0) rot_hombroi = 0;
	if(ele_hombroi > 90) ele_hombroi = 90;
	if(ele_hombroi < -90) ele_hombroi = -90;
	
}

void Bailarina::rotaPiernaD(float rot_cadera, float ele_cadera, float rodilla){
	rot_caderad -= rot_cadera;
	ele_caderad += ele_cadera;
	rodillad -= rodilla;
	piernad->elevaRodilla(rodilla);

	if(rot_caderad < 180) rot_caderad = 180;
	if(rot_caderad > 360) rot_caderad = 360;
	if(ele_caderad > 90 ) ele_caderad = 90;
	if(ele_caderad < 0  ) ele_caderad = 0;
	if(rodillad<270) rodillad=270;
	if(rodillad>360) rodillad=360;
}

void Bailarina::rotaPiernaI(float rot_cadera, float ele_cadera, float rodilla){
	rot_caderai += rot_cadera;
	ele_caderai += ele_cadera;
	rodillai -= rodilla;
	piernai->elevaRodilla(rodilla);
	
	if(rot_caderai > 0) rot_caderai = 0;
	if(rot_caderai < -180) rot_caderai = -180;
	if(ele_caderai > 90) ele_caderai = 90;
	if(ele_caderai < 0 ) ele_caderai = 0;
	
}

void Bailarina::activaMateriales(bool activar){

	if(activar){
		mat_on = true;

		cuerpo->setMaterial(*vestido);
		brazod->setMaterial(*piel);
		brazoi->setMaterial(*piel);
		piernad->setMaterial(*piel);
		piernai->setMaterial(*piel);
		cabeza->setMaterial(*piel);
	}
	else
		mat_on = false;

}

void Bailarina::setTexturas(){
	cuerpo->setTexturas();
}


bool Bailarina::brazoDPos0(){
	return rot_hombrod == 0 &&
			 ele_hombrod == 75 &&
			 codod == 45;
}

bool Bailarina::brazoIPos0(){
	return rot_hombroi == 0 &&
			 ele_hombroi == 75 &&
			 codoi == 45;
}

bool Bailarina::piernaDPos0(){
	return ele_caderad == 45 &&
			 rodillad == -90 &&
			 rot_caderad == 180;
}

bool Bailarina::piernaIPos0(){

	return rot_caderai == 0 &&
			 ele_caderai == 0 &&
			 rodillai == 0;
}

void Bailarina::animar(){
	float valor_rotaciones = 0.2;
	valor_rotaciones *= factor_velocidad;
	
	if(moverBD){
		double rel_elehombrocodo = (75/valor_rotaciones)/(45/valor_rotaciones);

		if(paso1){
			rotaBrazoD(0,-valor_rotaciones*rel_elehombrocodo,0,-valor_rotaciones); //primer movimiento
			
			if(ele_hombrod<=0 && codod<=0){
				paso1=false;
				paso2=true;
				ele_hombrod = 0;
				codod=0;
				giro_brazo_an = -90;
			}
		}
		
		if(paso2){ //segundo movimiento
			rotaBrazoD(valor_rotaciones, 0, giro_brazo_an, valor_rotaciones/rel_elehombrocodo);
			
			if(rot_hombrod>=75 && codod>=45){
				paso2=false;
				paso3=true;
				codod=45;
				rot_hombrod=75;
			}
		}
		
		if(paso3){
			rotaBrazoD(0,valor_rotaciones,giro_brazo_an,0);
		
			if(ele_hombrod >= 90){
				rot_hombrod = 0; 
 				ele_hombrod = 90;
				
				paso3=false,
				paso1=true;
				moverBI = true;
				moverBD = false;
				moverPD = true;
				
				rot_hombrod = 0;
				ele_hombrod = 75;
				codod = 45;
				giro_brazod = 0;
			}
 		}
	}
	
	if(moverBI){
		double rel_elehombrocodo = (75/valor_rotaciones)/(45/valor_rotaciones);
				
		if(paso1){
			rotaBrazoI(0,-valor_rotaciones*rel_elehombrocodo,0,-valor_rotaciones); //primer movimiento
			
			if(ele_hombroi<=0 && codoi<=0){
				paso1=false;
				paso2=true;
				ele_hombroi = 0;
				codoi=0;
				giro_brazo_an = 90;
			}
		}
		
 		
		if(paso2){ //segundo movimiento
			rotaBrazoI(valor_rotaciones, 0, giro_brazo_an, valor_rotaciones/rel_elehombrocodo);
			
			if(rot_hombroi<=-75 && codoi>=45){
				paso2=false;
				paso3=true;
				codoi=45;
				rot_hombroi=-75;
			}
		}
		
		if(paso3){
 			rotaBrazoI(0,valor_rotaciones,giro_brazo_an,0);

			if(ele_hombroi >= 90){
				rot_hombroi = 0; 
 				ele_hombroi = 90;
				
				paso3=false,
				paso1=true;
				moverBI = false;
				moverBD = true;
				moverPD = false;
				
				rot_hombroi = 0;
				ele_hombroi = 75;
				codod = 45;
				giro_brazoi = 0;
			}
 		}
	}
	
	if(moverPD){
		
		if(paso1){
			rotaPiernaD(0,valor_rotaciones*1.5,-valor_rotaciones*1.5);
			
			if(ele_caderad >= 90 && rodillad>=0){
				paso1p = false;
				paso2p = true;
			}
		}
		
		if(paso2){
			
			
			if(ele_caderad<=45){
				rotaPiernaD(0,0,valor_rotaciones*1.5);
			}
			else 
				rotaPiernaD(0,-valor_rotaciones,valor_rotaciones*1.5);
			
			if(ele_caderad<=45 && rodillad<=90){
				paso2p=false;
				paso1p=true;
				
				moverPD=false;
			}
		}
	}
}

void Bailarina::cambiaFactorVelocidad(float new_factor){
	factor_velocidad = new_factor;
}

void Bailarina::aumentaGradosLibBD(float gl){
	rotaBrazoD(gl,0,-90,gl);
}

void Bailarina::aumentaGradosLibBI(float gl){
	rotaBrazoI(gl,0,90,gl);
}

void Bailarina::aumentaGradosLibPD(float gl){
	rotaPiernaD(0,-gl,gl);
}

void Bailarina::aumentaGradosLibPI(float gl){
	rotaPiernaI(0,-gl,gl);
}

void Bailarina::setTPose()
{
	
	rotaBrazoD(-rot_hombrod,-ele_hombrod,-giro_brazod,-codod);
	rotaBrazoI(-rot_hombroi,-ele_hombroi,-giro_brazoi,-codoi);
	rotaPiernaD(-rot_caderad,-ele_caderad,-rodillad);
	rotaPiernaI(-rot_caderai,-ele_caderai,-rodillai);
	
}

void Bailarina::setPoseBaile(){

	setTPose();
	
	rotaBrazoD(0,75,0,45);
	rotaBrazoI(0,75,0,45);
	rotaPiernaD(180,45,90);
	rotaPiernaI(90,0,0);	
}

void Bailarina::imprimeValores(){
	cout <<"rot_hombrod="<<rot_hombrod<<" "<<"rot_hombroi="<<rot_hombroi<<endl;
	cout <<"ele_hombrod="<<ele_hombrod<<" "<<"ele_hombroi="<<ele_hombroi<<endl;
	cout <<"giro_brazod="<<giro_brazod<<" "<<"giro_brazoi="<<giro_brazoi<<endl;
	cout <<"codod="<<codod<<" "<<"codoi="<<codoi<<endl;
	cout <<"ele_caderad="<<ele_caderad<<" "<<"ele_caderai="<<ele_caderai<<endl;
	cout <<"rodillad="<<rodillad<<" "<<"rodillai="<<rodillai<<endl;
	cout <<"rot_caderad="<<rot_caderad<<" "<<"rot_caderai="<<rot_caderai<<endl;
}












