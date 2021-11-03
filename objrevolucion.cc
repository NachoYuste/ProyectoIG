#include "aux.h"
#include "objrevolucion.h"


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


//*****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

const double epsilon = numeric_limits<double>::epsilon();

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   
	vector<Tupla3f> perfil;
	
	ply::read_vertices(archivo, perfil);
	*this = ObjRevolucion(perfil, num_instancias, tapa_sup, tapa_inf);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos) 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup, bool tapa_inf) {
	
	//Llenar caras pares e impares
	instancias = num_instancias;
	tapaS = tapa_sup;
	tapaI = tapa_inf; 
	
	crearMalla(perfil, num_instancias);
	
	tam_vcaras = f.size();
	
	for(int i=0; i<tam_vcaras; i++){
		if(i%2 == 0)	f_par.push_back(f[i]);
		else				f_impar.push_back(f[i]);
	}
	
	calcular_normales();
	calculaCT();
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int 
num_instancias) {
	
	vector<Tupla3f> perfil_mod = perfil_original;
	perfil = perfil_mod;
		
	//Comprobar sentido
	//Si no está en sentido ascendente lo invertimos para trabajar siempre en ese sentido
	if(!sentidoAscendente(perfil_mod)){
		vector<Tupla3f>inv(perfil_mod.rbegin(), perfil_mod.rend());
		perfil_mod = inv;
	}
	
	//Guardar polo norte  y sur 
	Tupla3f polo_n = perfil_mod.back();
	Tupla3f polo_s = perfil_mod.front();

	if (fabs(polo_s(0)) < epsilon && fabs(polo_s(2)) < epsilon){	//Punto más bajo con x=0 y z=0
		polo_s = *perfil_mod.begin();
		perfil_mod.erase(perfil_mod.begin());
	}
	
	if (fabs(polo_n(0)) < epsilon && fabs(polo_n(2)) < epsilon){	//Punto más alto con x=0 y z=0
		polo_n = *(perfil_mod.end()-1);
		perfil_mod.erase(perfil_mod.end()-1);
	}
	
	//Crear malla de vértices
	v.clear();
	for(int i=0; i<num_instancias; i++){
		float a = (2*M_PI*i)/num_instancias;
		for(int j=0; j<perfil_mod.size(); j++){
			//Calcular coords nueva instancia
			float coordx = cos(a)*perfil_mod[j](0) +
								sin(a)*perfil_mod[j](2);
			float coordz = (-sin(a)*perfil_mod[j](0)) +
								cos(a)*perfil_mod[j](2);
			Tupla3f coords = {coordx,perfil_mod[j](1), coordz};
			//Introducir tupla a vector de vértices
			v.push_back({coordx,perfil_mod[j](1), coordz});
		}
	}
	
	//Añadimos una fila de puntos extra para las texturas
	for(int i=0; i<perfil_mod.size(); i++)
		v.push_back(perfil_mod[i]);
	
	//Crear malla de caras
	f.clear();
	
	for(int i=0; i<num_instancias; i++){
		for(int j=0; j<perfil_mod.size()-1; j++){
			int a = perfil_mod.size()*i + j;
			int b = perfil_mod.size()*((i+1)%num_instancias) + j;
			f.push_back({a, b, b+1});
			f.push_back({a, b+1, a+1});
		}
	}
	
	tam_sin_caras = f.size();
	
	if (tapaS)
		aniadeTapaSuperior(polo_n, perfil_mod);

	if(tapaI)
		aniadeTapaInferior(polo_s,perfil_mod);
	
}

bool ObjRevolucion::sentidoAscendente(vector<Tupla3f> perfil){
	return perfil.front()(1) < perfil.back()(1);
}

void ObjRevolucion::aniadeTapaInferior(Tupla3f poloS,vector<Tupla3f> perfil_mod){
	//Añadir poloS al vector de vértices
	if (fabs(poloS(0)) < epsilon)
		v.push_back(poloS);
	
	else{
		poloS(0) = 0.0;	//x=0
		poloS(2) = 0.0;	//z=0
		
		v.push_back(poloS);
	}
	
	//Añadir la tapa inferior
	int v1, v2, v3;
	
	v2 = v.size()-1; //poloS
	 
	for(int i=0; i<instancias-1; i++){
		v1 = perfil_mod.size() * i; //Primer vértice de cada instancia
		v3 = v1 + perfil_mod.size();	//Seguiente vérice de la instancia anterior
		
		//Añado la cara en orden v1,v2,v3 para seguir el orden antihorario
		f.push_back({v1,v2,v3});
	}
	
	f.push_back({(int) perfil_mod.size()*(instancias-1), v2, 0});
	
}

void ObjRevolucion::aniadeTapaSuperior(Tupla3f poloN,vector<Tupla3f> perfil_mod){
//Añadir poloN al vector de vértices
	if (fabs(poloN(0)) < epsilon)
		v.push_back(poloN);
	
	else{
		poloN(0) = 0.0;	//x=0
		poloN(2) = 0.0;	//z=0
		
		v.push_back(poloN);
	}
	
	//Añadir la tapa superior
	int v1, v2, v3;
	
	v2 = v.size()-1; //poloN
	 
	for(int i=0; i<instancias-1; i++){
		v1 = perfil_mod.size()*(i+1) - 1; //Primer vértice de cada instancia
		v3 = v1 + perfil_mod.size();	//Seguiente vérice de la instancia anterior
		
		//Añado la cara en orden v3,v2,v1 para seguir el orden antihorario
		f.push_back({v3,v2,v1});
	}
	
	f.push_back({(int) perfil_mod.size()-1, v2,(int)perfil_mod.size()*instancias-1});
}

 void ObjRevolucion::calculaCT(){
	ct.clear();
	float alpha,s,t,h;
	float hmax = perfil.back()(1);
	float hmin = perfil.front()(1);
	
	for (int i=0; i<v.size();i++){
		alpha = atan2(v[i](2),v[i](0));
		h = v[i](1);
		
		s = (alpha/(2*M_PI)) + 0.5;
		t = (h-hmin)/(hmax-hmin);
		ct.push_back({s,t});
	}

}


void ObjRevolucion::setTapas(bool act){
	if (act)	tam_vcaras = f.size();
	else		tam_vcaras = tam_sin_caras;
}

























