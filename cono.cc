#include "cono.h"

Cono::Cono(const int num_instancias_perf, 
			  const float altura, 
			  const float radio){
	
	double tanalfa = tan(altura/radio);
	Tupla3f v = {radio, 0, 0};
	float ccontiguo = 0;
	float copuesto = radio;

	
	perfil_creado.push_back({radio,-altura/2,0});
	perfil_creado.push_back({radio/2,0,0});
	perfil_creado.push_back({0,altura/2,0});
	
	instancias = num_instancias_perf;

	//El cono solo se puede contruir con la tapa inferior
	tapaI = true;
	tapaS = true;
	
	crearMalla(perfil_creado, num_instancias_perf);
	
	tam_vcaras = f.size();
	
	//Llenar caras pares e impares
	for(int i=0; i<tam_vcaras; i++){
		if(i%2 == 0)	f_par.push_back(f[i]);
		else				f_impar.push_back(f[i]);
	}
	
	calcular_normales();
	calculaCT();
};
