#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
	v.resize(8);

	float mediolado = lado/2;
	
	v[0]={-mediolado,-mediolado,-mediolado};
	v[1]={mediolado,-mediolado,-mediolado};
	v[2]={mediolado,-mediolado,mediolado};
	v[3]={-mediolado,-mediolado,mediolado};
	v[4]={-mediolado,mediolado,-mediolado};
	v[5]={mediolado,mediolado,-mediolado};
	v[6]={mediolado,mediolado,mediolado};
	v[7]={-mediolado,mediolado,mediolado};

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

	f.resize(12);

	//cara frontal
	f[0]={3,2,6};
	f[1]={3,6,7};

	//cara derecha
	f[2]={2,1,5};
	f[3]={2,5,6};

	//cara izquierda
	f[4]={0,3,7};
	f[5]={0,7,4};

	//cara trasera
	f[6]={1,0,4};
	f[7]={1,4,5};

	//cara superior
	f[8]={7,6,5};
	f[9]={7,5,4};

	//cara inferior
	f[10]={3,0,1};
	f[11]={3,1,2};
	
	tam_vcaras = f.size();
	
	//Llenar caras pares e impares
	for(int i=0; i<tam_vcaras; i++){
		if(i%2 == 0)	f_par.push_back(f[i]);
		else				f_impar.push_back(f[i]);
	}
	
	calcular_normales();
	
	//Coordenadas de textura
	ct.resize(v.size());
	ct[0] = *new Tupla2f(0,0);
	ct[1] = *new Tupla2f(1,0);
	ct[2] = *new Tupla2f(0,0);
	ct[3] = *new Tupla2f(1,0);
	ct[4] = *new Tupla2f(0,1);
	ct[5] = *new Tupla2f(1,1);
	ct[6] = *new Tupla2f(0,1);
	ct[7] = *new Tupla2f(1,1);	
	
}

