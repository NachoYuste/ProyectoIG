#include "esfera.h"

Esfera::Esfera(const int num_ver_perfil, 
			  const int num_instancias_perf, 
			  const float radio){

	Tupla3f ver = {0, -radio, 0};

   float n_x;
   float n_y;
   float n_z;

   float angulo = M_PI / (num_ver_perfil - 1);

   // rotamos el punto superior con respecto al eje Z
   for (int i = 0; i < num_ver_perfil - 2; i++){
      n_x = ver(0) * cos(angulo) - ver(1) * sin(angulo);
      n_y = ver(0) * sin(angulo) + ver(1) * cos(angulo);
      
		ver = {n_x, n_y, 0};
		perfil_creado.push_back(ver);
   }
   perfil_creado.push_back({0,radio,0});

	instancias = num_instancias_perf;
	
   //La esfera se puede contruir con las dos tapas
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
