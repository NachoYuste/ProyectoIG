#include "cilindro.h"

Cilindro::Cilindro(const int num_ver_perfil,
				const int num_instancias_perf,
				const float altura, 
				const float radio){
	
	float dif_h_vertices = altura/num_ver_perfil;
	
	Tupla3f v = {radio, -(altura/2), 0};
	Tupla3f aux = {0, dif_h_vertices, 0};
	
	for (int i=0; i<num_ver_perfil; i++){
		perfil_creado.push_back(v);
		v=v+aux;
	}

	instancias = num_instancias_perf;
	
	//El cilindro se puede construir con dos tapas
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
