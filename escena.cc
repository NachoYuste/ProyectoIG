#include "escena.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );
	
	//Objetos de la escena
	cubo = new Cubo(10);
	tetraedro = new Tetraedro(10);
	ply = new ObjPLY("./plys/beethoven.ply");
	ply_rev = new ObjRevolucion("./plys/peon.ply", 10, true, true);
	coke = new ObjRevolucion("./plys/lata-pcue.ply",40,true,true);
	cilindro = new Cilindro(15, 20, 15.0, 7.0);
	cono = new Cono(20,15,7);
	esfera = new Esfera(20, 30, 10);

	cajamusical = new CajaMusical();
	
	//Luces de la escena
	Tupla3f pos_luz_posicional = {-300, 0, 0};
	Tupla3f pos_luz_posicional2 = {0,100,0};
	Tupla2f pos_luz_direccional = {0, 50};
	Tupla3f pos_luz_posicional3 = { 200.0f, 300.0f, 100.0f};

	Tupla4f color_luces_amb = { 0.2f, 0.2f, 0.2f, 1.0f };
	Tupla4f color_luces_diff = { 1.0f, 1.0f, 1.0f, 1.0f };
	Tupla4f color_luces_spe = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	luz0 = new LuzPosicional(pos_luz_posicional, GL_LIGHT1, color_luces_amb, color_luces_spe, color_luces_diff);
	luz1 = new LuzDireccional(pos_luz_direccional, GL_LIGHT2, color_luces_amb, color_luces_spe, color_luces_diff);
	luz2 = new LuzPosicional(pos_luz_posicional2, GL_LIGHT3, color_luces_amb, color_luces_spe, color_luces_diff);
	luz3 = new LuzPosicional(pos_luz_posicional3, GL_LIGHT4, color_luces_amb, color_luces_spe, color_luces_diff);

	
	//Animacion
	factor_velocidad = 1;
	animacionAutomatica = false;
	grado_libertad = 2;
	parte_sel = NINGUNA;

	printMenu();
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	 glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	 glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer
	 glEnable(GL_NORMALIZE);
	 glEnable(GL_RESCALE_NORMAL);
	 glEnable(GL_CULL_FACE);
	 glShadeModel(GL_SMOOTH);

	 Width  = UI_window_width/10;
	 Height = UI_window_height/10;
		
	 change_projection( float(UI_window_width)/float(UI_window_height) );
	 glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	
	change_observer();
	glDisable(GL_LIGHTING);
   ejes.draw();
	
	objSeleccionado = MOD_JER;
	visualizacion.insert(LUZ);
	visualizacion.insert(TEXTURA);
	
	activaLuces();
	aplicaMateriales();
	aplicaTexturas();
	
	glPushMatrix();
		cajamusical->draw(visualizacion,modo_dif);
	glPopMatrix();
	
	
	
	
/*
	if(visualizacion.find(LUZ)!=visualizacion.end()){
		aplicaMateriales();
		activaLuces();
	}
	
	aplicaTexturas();
	
	switch (objSeleccionado){
		case CUBO:
			glPushMatrix();
				glScalef(5,5,5);
				cubo->draw(visualizacion, modo_dif);
				glDisable(GL_LIGHTING);
			glPopMatrix();
		break;
		
		case TETRAEDRO:
			glPushMatrix();
				glScalef(5,5,5);
				tetraedro->draw(visualizacion, modo_dif);
			glPopMatrix();
		break;
		
		case PLY:
			glPushMatrix();
				glScalef(10,10,10);
				ply->draw(visualizacion, modo_dif);
			glPopMatrix();
			
		case PLY_REV:
			glPushMatrix();
				glScalef(30,30,30);
				ply_rev->setTapas(tapas);
				ply_rev->draw(visualizacion, modo_dif);
			glPopMatrix();

		case CILINDRO:
			glPushMatrix();
				glScalef(5,5,5);
				cilindro->setTapas(tapas);
				cilindro->draw(visualizacion, modo_dif);
			glPopMatrix();
		break;
		
		case CONO:
			glPushMatrix();
				glScalef(5,5,5);
				cono->setTapas(tapas);
				cono->draw(visualizacion, modo_dif);
			glPopMatrix();
		break;
		
		case ESFERA:
			glPushMatrix();
				glScalef(5,5,5);
				esfera->setTapas(tapas);
				esfera->draw(visualizacion, modo_dif);
			glPopMatrix();
		break;
		
		case MULTIPLE:
			glPushMatrix(); //Dibujar PLY_REV
				glScalef(30,30,30);
				ply_rev->setTapas(tapas);
				ply_rev->draw(visualizacion, modo_dif);
			glPopMatrix();
			
			glPushMatrix();	//Dibujar CUBO
				glScalef(5,5,5);
				glTranslatef(20,0,0);
				cubo->draw(visualizacion, modo_dif);
			glPopMatrix();
		
			glPushMatrix(); //Dibujar TETRAEDRO
				glScalef(5,5,5);
				glTranslatef(0,0,20);
				tetraedro->draw(visualizacion, modo_dif);
			glPopMatrix();
		
			glPushMatrix(); //Dibujar ESFERA
				glScalef(5,5,5);
				glTranslatef(-20,0,0);
				esfera->setTapas(tapas);
				esfera->draw(visualizacion, modo_dif);
			glPopMatrix();		
		
			glPushMatrix(); //Dibujar CILINDRO
				glScalef(5,5,5);
				glTranslatef(0,0,-20);
				cilindro->setTapas(tapas);
				cilindro->draw(visualizacion, modo_dif);
			glPopMatrix();
		break;
		
		case MOD_JER:
			glPushMatrix();
				cajamusical->draw(visualizacion,modo_dif);
			glPopMatrix();
		break;
		
		case VACIO:break;
	};


/*

	else{	//Previsualizacion practica 3
		glEnable(GL_LIGHTING);
		luz0->activar();
		luz1->activar();
		luz2->activar();
		
		visualizacion.insert(LUZ);
	
		glEnable(GL_LIGHTING);
		glPushMatrix();
			glScalef(5,5,5);
			glTranslatef(0,-30,0);
			esfera->setMaterial(*mat3);
			esfera->setTapas(true);
			esfera->draw(visualizacion, modo_dif);
		glPopMatrix();

		glPushMatrix();
			glScalef(20,20,20);
			//glTranslatef(-5,0,0);
			ply_rev->setMaterial(*mat1);
			ply_rev->setTapas(true);
			ply_rev->draw(visualizacion,modo_dif);			
		glPopMatrix();

		glPushMatrix();
			glScalef(10,10,10);
			ply->setMaterial(*mat1);
			ply->draw(visualizacion, modo_dif);
		glPopMatrix();		
		
		glPushMatrix();
			glScalef(20,20,20);
			glTranslatef(5,0,0);
			ply_rev->setMaterial(*m_blanco);
			ply_rev->setTapas(true);
			ply_rev->draw(visualizacion,modo_dif);			
		glPopMatrix();
		
		glDisable(GL_LIGHTING);
		//visualizacion.erase(LUZ);
	}*/

	
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   bool salir=false;
   
	if(modoMenu==NADA){
		switch(toupper(tecla)){
			case 'V' :
      	   //MODO SELECCION DE MODO DE VISUALIZACION
      	   modoMenu=SELVISUALIZACION;
      	break ;
    
			case 'D' :
         	// MODO SELECCION DE DIBUJADO
         	modoMenu=SELDIBUJADO;
      	break ;
        
			case 'O' :
         	//MODO SELECCION DE OBJETO
         	modoMenu=SELOBJETO;
			break ;
			
			case 'S' :
         	//MODO SELECCION DE ANIMACION
         	modoMenu=ANIMACION;
			break;
			
			case 'Q' :
				salir = true;
			break;
		};
	}
	else if(toupper(tecla)=='Q')
		modoMenu = NADA;
	
	//MODOS DE DIBUJADO
	if(modoMenu == SELDIBUJADO){
		switch(toupper(tecla)){
		
			case '1':	//Modo Inmediato
				if(modoMenu==SELDIBUJADO){
					modo_dif = false;
					dibujar();
				}
			break;
			
			case '2':	//Modo Diferido
				if(modoMenu==SELDIBUJADO){
					modo_dif = true;
					dibujar();
				}
			break;
		};
	}
		
	//MODOS DE SELECCION DE OBJETO
	if(modoMenu == SELOBJETO){
		switch(toupper(tecla)){
			
			case 'T':	//Seleccion de Tetraedro
				objSeleccionado=TETRAEDRO;
				dibujar();         
			break;
	      
			case 'C':	//Seleccion de Cubo
				objSeleccionado=CUBO;
				dibujar();         
			break;
			
			case 'Y':	//Seleccion de PLY
				objSeleccionado=PLY;
				dibujar();         
			break;
		
			case 'R':	//Seleccion de PLY_REV
				objSeleccionado=PLY_REV;
				dibujar();         
			break;
			
			case 'B':	//Seleccion de CILINDRO
				objSeleccionado=CILINDRO;
				dibujar();         
			break;
			
			case 'N':	//Seleccion de CONO
				objSeleccionado=CONO;
				dibujar();         
			break;
			
			case 'E':	//Seleccion de ESFERA
				objSeleccionado=ESFERA;
				dibujar();         
			break;
			
			case 'M':	//Seleccion de MULTIPLE
					objSeleccionado=MULTIPLE;
					dibujar();         
			break;
				
			case 'K':	//Seleccion de Modelo Jerárquico
				objSeleccionado=MOD_JER;
				dibujar();         
			break;
		};
	}

	//MODOS DE VISUALIZACION
	if(modoMenu == SELVISUALIZACION){
		switch(toupper(tecla)){
			case 'P': //PUNTOS
				
				if(visualizacion.find(PUNTOS)==visualizacion.end()){
					visualizacion.insert(PUNTOS);
				}
				else{
					visualizacion.erase(PUNTOS);
				}
				if(visualizacion.find(LUZ)!=visualizacion.end()){
					visualizacion.erase(visualizacion.find(LUZ));
				}

				dibujar();
			break;
        
			case 'L': //LINEAS
				
				if(visualizacion.find(LINEAS)==visualizacion.end()){
					visualizacion.insert(LINEAS);
				}
				else{
					visualizacion.erase(LINEAS);
				}
					
				if(visualizacion.find(LUZ)!=visualizacion.end()){
					visualizacion.erase(visualizacion.find(LUZ));
				}
					
				dibujar();
	
			break;
				
			case 'S': //SOLIDO

				if(visualizacion.find(SOLIDO)==visualizacion.end())
					visualizacion.insert(SOLIDO);
			
				else
					visualizacion.erase(SOLIDO);
                
				if(visualizacion.find(LUZ)!=visualizacion.end()){
					visualizacion.erase(visualizacion.find(LUZ));
				}
            	
				dibujar();
            
			break;
        
			case 'A': //AJEDREZ
            
				if(visualizacion.find(AJEDREZ)==visualizacion.end()){
					visualizacion.clear();
					visualizacion.insert(SOLIDO);
					visualizacion.insert(AJEDREZ);
				}
				else{
					visualizacion.erase(AJEDREZ);          
				}

				if(visualizacion.find(LUZ)!=visualizacion.end()){
					visualizacion.erase(visualizacion.find(LUZ));
				}
					
				dibujar();
				
			break;
		
		  
			case 'Z': //ACTIVAR TAPA SUPERIOR

				if(esConTapas()){
            	
					if(!tapas){
						cout << "\tTapas ACTIVADAS" << endl;
						tapas = !tapas;						
					}
					else{
						cout << "\tTapas DESACTIVADAS" << endl;
						tapas = !tapas;
					}
            	
					dibujar();
				}
			break;
		
			case 'I': //LUZ
				if(visualizacion.find(LUZ)==visualizacion.end()){
					visualizacion.erase(visualizacion.begin(), visualizacion.end());
					visualizacion.insert(LUZ);
				}
				else{
					visualizacion.erase(LUZ);
				}
				
				dibujar();
			break;
			
			case 'T': //TEXTURA
				
				if(visualizacion.find(TEXTURA)==visualizacion.end()){
					visualizacion.insert(TEXTURA);
				}
				else{
					visualizacion.erase(TEXTURA);
				}

				dibujar();
			break;
		};
		
		if(visualizacion.find(LUZ)!=visualizacion.end()){
			//Estas dos lineas están para la presentación automática
			visualizacion.erase(visualizacion.begin(), visualizacion.end());
			visualizacion.insert(LUZ);
			//Activar luces
			switch(toupper(tecla)){
				
				case '0' :	//Activar/Desactivar luz 0
					
					if (luz0->getLuzActivada())
						luz0->setActivacion(false);
					else
						luz0->setActivacion(true);
				
				break;
				
				case '1' :	//Activar/Desactivar luz 1
					
					if (luz1->getLuzActivada())
						luz1->setActivacion(false);
					else
						luz1->setActivacion(true);
				
				break;
				
				case '2' :	//Activar/Desactivar luz 2
					
					if (luz2->getLuzActivada())
						luz2->setActivacion(false);
					else
						luz2->setActivacion(true);
				
				break;
				
				case '3' :	//Activar/Desactivar luz 2
					
					if (luz3->getLuzActivada())
						luz3->setActivacion(false);
					else
						luz3->setActivacion(true);
				
				break;
	
				case 'A' : //Variar angulo Alfa
					variarAlfa = true;
					variarBeta = false;
				break;
				
				case 'B' : //Variar angulo Beta
					variarBeta = true;
					variarAlfa = false;
				break;				
				
				case '<': //LUZ
					if (variarAlfa){
						alfa+=0.2*M_PI/180;
						luz1->variarAnguloAlpha(alfa);
					}
					if (variarBeta){
						beta+=0.2*M_PI/180;
						luz1->variarAnguloBeta(beta);
					}
					dibujar();
				break;
		  
		   	case '>': //LUZ
					if (variarAlfa){
						alfa-=0.2*M_PI/180;
						luz1->variarAnguloAlpha(alfa);
					}
					if (variarBeta){
						beta-=0.2*M_PI/180;
						luz1->variarAnguloBeta(beta);
					}
					dibujar();
				break;
			};
		}
	}
   
   //MODOS DE ANIMACIÓN
	if(modoMenu == ANIMACION){
		
		switch(toupper(tecla)){
			case 'A': //Animacion automatica
				animacionAutomatica = true;
				cajamusical->setPoseBaile();
			break;
			
			case 'M': //Animacion manual
				animacionAutomatica = false;
				cajamusical->setTPose();
			break;
			
			case '+':
				
				if(animacionAutomatica){
					factor_velocidad+=0.2;
					if(factor_velocidad>10) factor_velocidad=10;
					cout << factor_velocidad <<endl;
				}
				else{
					grado_libertad=abs(grado_libertad);
					animacionManual();
				}
			break;
			
			case '-':
				if(animacionAutomatica){
					factor_velocidad-=0.2;
					if(factor_velocidad<0.2) factor_velocidad=0.2;
				}
				else{
					grado_libertad=abs(grado_libertad);
					grado_libertad*=-1;
					animacionManual();
				}
			break;
			
			case '0':	//Brazo Derecho
				if(!animacionAutomatica){
					parte_sel = BD;
				}
			break;
			
			case '1':	//Brazo Izquierdo
				if(!animacionAutomatica){
					parte_sel = BI;
				}
			break;
			
			case '2':	//Piernda Derecha
				if(!animacionAutomatica){
					parte_sel = PD;
				}
			break;
			
			case '3':	//Pierna Izquierda
				if(!animacionAutomatica){
					parte_sel = PI;
				}
			break;
		};
	}
	
	printEstadoMenu();
   
	return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
//
// Método que se invoca al inicio de la ejecución
// Informa sobre las opciones del menú
//
//**************************************************************************

void Escena::printMenu(){
	cout << "\nMENU: " << endl;
	cout <<"\tO->Seleccion de objeto  V->Modos de visualizacion  D->Modo dibujado  S->Modos de animacion"<<endl;
	
	cout << "OBJETOS:" << endl;
	cout << "\tC->CUBO  T->TETRAEDRO  Y->PLY  R->PLY_REV\n"
			  "\tB->CILINDRO  N->CONO  E->ESFERA  M->MULTIPLE  K->MOD_JER" << endl;
	
	cout << "MODOS DE VISUALIZACION:" << endl;
	cout <<"\tP->PUNTOS  L->LINEAS  S->SOLIDO  A->AJEDREZ  I->LUZ Z->ACTIVAR TAPAS"<<endl;
	
	cout << "\tACTIVAR Y MODIFICAR LUCES:" <<endl;
	cout << "\t\t0-9->Activar luz   A->Variar angulo Alfa   B->Variar angulo B\n"
			  "\t\t'<'->Aumentar angulo   '>'->Disminuir angulo" <<endl;
	
	cout << "MODOS DE DIBUJADO:" << endl;
	cout << "\t1->INMEDIATO  2->DIFERIDO\n" << endl;
	
	cout << "MODOS DE ANIMACION:" << endl;
	cout << "\tA->AUTOMATICO M->MANUAL\n" << endl;
	
}

//**************************************************************************
//
// Método que se invoca en cada iteración de la ejecución
// Informa sobre el estado actual del menú
//
//**************************************************************************

void Escena::printEstadoMenu(){
	
	string objetos[10] = {"NINGUNO","TETRAEDRO","CUBO","PLY","PLY_REV","CILINDRO","CONO", "ESFERA","MULTIPLE","MOD_JER"};
	string menus[5] = {"RAIZ","de objeto","de modo de visualizacion","de modo de dibujado","de animacion"};
	string modo_vis[6] = {"PUNTOS","LINEAS","SOLIDO","AJEDREZ","LUZ", "TEXTURA"};
	string parte_selec[5] = {"NINGUNA","B.DCHO","B.IZQ","P.DCHA","P.IZQ"};
	
	cout << endl;
	cout << "-------ESTADO ACTUAL-------" << endl;
	cout << "Menu de seleccion " << menus[modoMenu] << endl;
	
	cout << "Objeto seleccionado: " << objetos[objSeleccionado] << endl;				
	
	cout << "Modo(s) de visualizacion seleccionado(s): ";
			
	for(auto elem : visualizacion){
		cout << modo_vis[elem] << " ";
	}
	cout << endl;
	
	if(visualizacion.find(LUZ)!=visualizacion.end()){
		cout << "Luces activadas:";
		if(luz0->getLuzActivada()) cout<<"\tLuz0";
		if(luz1->getLuzActivada()) cout<<"\tLuz1";
		if(luz2->getLuzActivada()) cout<<"\tLuz2";
		if(luz3->getLuzActivada()) cout<<"\tLuz3";
		cout << endl;		
	}
		
		
	if(modo_dif)	cout << "Modo de dibujado: DIFERIDO" << endl;
	else				cout << "Modo de dibujado: INMEDIATO" << endl;
	
	if(animacionAutomatica)	cout <<"Modo de animacion: AUTOMATICA" <<endl;
	else {
		cout <<"Modo de animacion: MANUAL" <<endl;
		cout <<"\tParte seleccionada:"<<parte_selec[parte_sel]<<endl;
	}
	
	cout << "---------------------------"<<endl;
}



//**************************************************************************
//
// Método para aplicar materiales a todos los objetos
//
//**************************************************************************


void Escena::aplicaMateriales(){
	
 	Material mat_oro ({0.24725, 0.1995, 0.0745, 1}, {0.75164, 0.60648, 0.22648, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.4*128.0f); //Oro
 	Material mat_jade ({0.135,0.2225,0.1575,1},{0.54,0.89,0.63,1},{0.316228,0.316228,0.316228,1},0.1*128.0f); //Jade
 	Material mat_esmeralda ({0.0215,0.1745,0.0215,1},{0.07568,0.61424,0.07568,1},{0.633,0.727811,0.633,1},0.6*128.0f);
 	Material m_negro ({0.05375f, 0.05f, 0.06625f, 0.82f},{0.18275f, 0.17f, 0.22525f, 0.82f},{0.332741f, 0.328634f, 0.346435f, 0.82f},38.4f);
 	Material m_blanco ({0.19225,0.19225,0.19225,1}, {0.50754,0.50754,0.50754,1},{0.508273,0.508273,0.508273,1},0.4*1280.0f);
	
	if (cubo!=nullptr) cubo->setMaterial(mat_oro);
	if (tetraedro!=nullptr) tetraedro->setMaterial(mat_oro);
	if (ply!=nullptr) ply->setMaterial(mat_jade);
	if (ply_rev!=nullptr) ply_rev->setMaterial(mat_jade);
	if (cilindro!=nullptr) cilindro->setMaterial(mat_esmeralda);
	if (cono!=nullptr) cono->setMaterial(m_blanco);
	if (esfera!=nullptr) esfera->setMaterial(mat_esmeralda);
	if (cajamusical!=nullptr) cajamusical->activaMateriales(true);
}

//**************************************************************************
//
// Método para aplicar texturas a los objetos que la implementan
//
//**************************************************************************
void Escena::aplicaTexturas(){
	
	Textura *madera = new Textura("./texturas/text-lata-1.jpg");
	Textura *papelRegalo = new Textura("./texturas/caja.jpg");
	Textura *tutu = new Textura("./texturas/tutu.jpg");
	
	cilindro->setTextura(papelRegalo);
	cubo->setTextura(madera);
	cono->setTextura(tutu);
	cajamusical->setTexturas();
}

bool Escena::tieneTextura(){
	return objSeleccionado == CILINDRO ||
			 objSeleccionado == CUBO ||
			 objSeleccionado == CONO ||
			 objSeleccionado == MOD_JER;
}



//**************************************************************************
//
// Método para encender/apagar las luces
//
//**************************************************************************

void Escena::activaLuces(){


	glEnable(GL_LIGHTING);
	
	if(visualizacion.find(TEXTURA)!=visualizacion.end())
		glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
	
	luz0->activar();
	luz1->activar();
	luz2->activar();
	luz3->activar();
}


//**************************************************************************
//
// Método auxiliar para determinar si el objeto seleccionado se puede pintar
// con tapas o no
//
//**************************************************************************

bool Escena::esConTapas(){
	return objSeleccionado==PLY_REV || objSeleccionado==CILINDRO ||
			 objSeleccionado==CONO    || objSeleccionado==ESFERA   ||
			 objSeleccionado==MULTIPLE;
}

//**************************************************************************
//		Métodos para animación
//**************************************************************************
void Escena::animar(){
	if(!cajamusical->estaArriba() && objSeleccionado == MOD_JER)
		cajamusical->subeBase(factor_velocidad,factor_velocidad);
	
	if(animacionAutomatica){
		cajamusical->cambiaFactorVelocidad(factor_velocidad);
		cajamusical->animar();
		luz0->animar();
	}
}

void Escena::animacionManual(){
	cajamusical->imprimeValores();
	switch (parte_sel){
		case BD: cajamusical->aumentaGradosLibBD(grado_libertad); break;
		case BI: cajamusical->aumentaGradosLibBI(grado_libertad); break;
		case PD: cajamusical->aumentaGradosLibPD(grado_libertad); break;
		case PI: cajamusical->aumentaGradosLibPI(grado_libertad); break;
		case NINGUNA:break;
	};
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
