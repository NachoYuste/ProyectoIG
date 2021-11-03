#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(int l)
{
	lado = l;
	
   // inicializar la tabla de vértices
	v.resize(4);
	v[0]={-lado/2,-lado/2,-lado/2};
	v[1]={lado/2,-lado/2,-lado/2};
	v[2]={0.0,-lado/2,lado/2};
	v[3]={0,lado,0};

	

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

	f.resize(4);

	f[0]={0,3,1};
	f[1]={1,3,2};
	f[2]={0,2,3};
	f[3]={0,1,2};

	tam_vcaras = f.size();
	
	//Llenas caras pares e impares
	for(int i=0; i<tam_vcaras; i++){
		if(i%2 == 0)	f_par.push_back(f[i]);
		else				f_impar.push_back(f[i]);
	}

	calcular_normales();
}

