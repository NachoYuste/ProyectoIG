#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

//------------------------------------------------------------------------------
// Visualización en modo inmediato con 'glDrawElements'
void Malla3D::draw_ModoInmediato()
{
	// visualizar la malla usando glDrawElements,
	// completar (práctica 1)
	// ...

	//habilitar array de vértices y colores
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//indicar dirección de array de vértices

	glVertexPointer(3, GL_FLOAT, 0, v.data());
	
	
	if(modos_vis.find(AJEDREZ)!=modos_vis.end()){
		//indicar array de color blanco y visualizar caras pares
		glColorPointer(3, GL_FLOAT, 0, c1.data());	
		glDrawElements(GL_TRIANGLES,f_par.size()*3,GL_UNSIGNED_INT,f_par.data());

		//indicar array de color amarillo y visualizar caras impares
		glColorPointer(3, GL_FLOAT, 0, c2.data());
		glDrawElements(GL_TRIANGLES,f_impar.size()*3,GL_UNSIGNED_INT,f_impar.data());
	}
	
	 if(modos_vis.find(LUZ)!=modos_vis.end()){
		m->aplicar();
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, nv.data());
		
		if(modos_vis.find(TEXTURA)!=modos_vis.end()){
			glColorPointer(3, GL_FLOAT, 0, c.data());
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2,GL_FLOAT,0,ct.data());
		}
		
		glDrawElements(GL_TRIANGLES, tam_vcaras*3,GL_UNSIGNED_INT, f.data());
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	if(modos_vis.find(TEXTURA)!=modos_vis.end()){
			text->activar();
			glColorPointer(3, GL_FLOAT, 0, c.data());
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2,GL_FLOAT,0,ct.data());
			glDrawElements(GL_TRIANGLES, tam_vcaras*3,GL_UNSIGNED_INT, f.data());
		}
	
	else{
		//indicar array de color solido y visualizar 
		glColorPointer(3, GL_FLOAT, 0, c.data());
		glDrawElements(GL_TRIANGLES, tam_vcaras*3,GL_UNSIGNED_INT, f.data());
		
	}

	//deshabilitar array de vértices, de colores y de textura
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
   // (la primera vez, se deben crear los VBOs y guardar sus 
	//identificadores en el objeto)
   // completar (práctica 1)
   // .....

	//Crear VBOs
	if (id_vbo_ver==0)
		id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER,
		sizeof(float)*3*v.size(),v.data());	//VBO de vértices

	if(modos_vis.find(AJEDREZ)!=modos_vis.end()){

		if(id_vbo_tri_par==0)
			id_vbo_tri_par=CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 
			sizeof(int)*3*f_par.size(), f_par.data());

		if(id_vbo_tri_impar==0)
			id_vbo_tri_impar= CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 
			sizeof(int)*3*f_impar.size(), f_impar.data());

		if(id_vbo_c1==0)
			id_vbo_c1 = CrearVBO(GL_ARRAY_BUFFER,
			sizeof(float)*3*c1.size(), c1.data());

		if(id_vbo_c2==0)
			id_vbo_c2 = CrearVBO(GL_ARRAY_BUFFER, 
			sizeof(float)*3*c2.size(), c2.data());
	}
	
	else{
		if (id_vbo_tri==0)
			id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(int)*3*tam_vcaras, f.data());	//VBO de triángulos

		if (id_vbo_c==0)
			id_vbo_c = CrearVBO(GL_ARRAY_BUFFER, 
			sizeof(float)*3*c.size(),c.data());
		
		if(modos_vis.find(LUZ)!=modos_vis.end()){
			if(id_vbo_nv==0)
			id_vbo_nv = CrearVBO(GL_ARRAY_BUFFER,
			sizeof(float)*3*nv.size(),nv.data());	//VBO de normales de vértices
		}
	}


	//Especificar ubicación y formato de la tabla vértices, habilitar tabla
	glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);	//Activar VBO
	glVertexPointer(3, GL_FLOAT, 0, 0);				//Especificar formato y offset
	glBindBuffer(GL_ARRAY_BUFFER, 0);				//Desactivar VBO vértices
	glEnableClientState(GL_VERTEX_ARRAY);			//Habilitar tabla de vértices
	glEnableClientState(GL_COLOR_ARRAY);			//Habilitar tabla de colores

	//Visualizar triángulos con glDrawElements
	if(modos_vis.find(AJEDREZ)!=modos_vis.end()){
		glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c1);//Activar colores caras pares
		glColorPointer(3,GL_FLOAT,0 ,0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_par);	//Activar VBOs
		glDrawElements(GL_TRIANGLES, 3*c1.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//Activar colores caras impares
		glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c2); 
		glColorPointer(3, GL_FLOAT, 0, 0);		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_impar);
		glDrawElements(GL_TRIANGLES, 3*c2.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else if(modos_vis.find(LUZ)!=modos_vis.end()){
		glEnableClientState(GL_NORMAL_ARRAY);
		
		glBindBuffer(GL_ARRAY_BUFFER, id_vbo_nv);
		glNormalPointer(GL_FLOAT, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		m->aplicar();
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);	//Activar VBOs
		glDrawElements(GL_TRIANGLES, 3*tam_vcaras, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);		//Desactivar VBO
		
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	else{
		glBindBuffer(GL_ARRAY_BUFFER, id_vbo_c);
		glColorPointer(3,GL_FLOAT, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);	//Activar VBOs
		glDrawElements(GL_TRIANGLES, 3*tam_vcaras, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);		//Desactivar VBO
	}


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(set<modo_vis> mod, bool modo_dif)
{
	setModos(mod); //Actualizar los modos_vis de visualización
	
	if(modos_vis.find(SOLIDO)!=modos_vis.end()){
		PintaCaras();
		glPolygonMode(GL_FRONT, GL_FILL); 
		
		if(modo_dif) draw_ModoDiferido();
		else 			 draw_ModoInmediato();
	}

	if(modos_vis.find(LINEAS)!=modos_vis.end()){
		PintaLineas();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	 
		
		if(modo_dif) draw_ModoDiferido();
		else 			 draw_ModoInmediato();	
	}

	if(modos_vis.find(PUNTOS)!=modos_vis.end()){
		PintaLineas();
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glPointSize(5);
			
		if(modo_dif) draw_ModoDiferido();
		else 			 draw_ModoInmediato();
	}
	
	if(modos_vis.find(LUZ)!=modos_vis.end() || modos_vis.find(TEXTURA)!=modos_vis.end()){
		PintaCaras();
		
		if(modo_dif) draw_ModoDiferido();
		else 			 draw_ModoInmediato();
	}
	

}

// -----------------------------------------------------------------------------
// Función de creación de VBOs
// Transfiere los datos a la GPU, lo desactiva y devuelve su id

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * 
puntero_ram){

	GLuint id_vbo;
	glGenBuffers(1, &id_vbo);	//Crear VBO y guardar id en id_vbo
	glBindBuffer(tipo_vbo, id_vbo);	//activar el VBO usando su identificador

	//tranferir datos desde RAM a GPU
	glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

	glBindBuffer(tipo_vbo, 0);	//Desactivar VBO 
	return id_vbo;
}

// -----------------------------------------------------------------------------
// Función de pintado de caras
// Rellena los arrays de colores dependiendo del modo (Plano/Ajedrez)

void Malla3D::PintaCaras(){
	
	if(modos_vis.find(AJEDREZ)!=modos_vis.end()){
		c1.resize(v.size());
		c2.resize(v.size());
		Tupla3f amarillo = {255,255,0};
		Tupla3f negro = {0,0,0};
		vector<Tupla3f>color_amarillo_aj(c1.size(), amarillo);
		vector<Tupla3f>color_negro_aj(c2.size(), negro);

		c1.swap(color_amarillo_aj);
		c2.swap(color_negro_aj);
	}

	else{
		c.resize(v.size());
		Tupla3f solido = {0,255,255};
		vector<Tupla3f>color_solido(c.size(), solido);
		c = color_solido;
	}
}

// -----------------------------------------------------------------------------
// Función de pintado de lineas
// Llena el array de colores para el modo líneas

void Malla3D::PintaLineas(){
	c.resize(v.size());
	Tupla3f ins = {0,0,0};
	vector<Tupla3f>color_lineas(c.size(), ins);
	c.swap(color_lineas);	
}

// -----------------------------------------------------------------------------
// Función que establece los modos de visualización

void Malla3D::setModos(set<modo_vis>mod){
	modos_vis = mod;	
}

// -----------------------------------------------------------------------------
// Función que establece el material del objeto
// Llama al constructor de copia de Material (los materiales se crean en Escena)

void Malla3D::setMaterial(Material mat){
	m = new Material(mat);
}

void Malla3D::setTextura(Textura *tex){
	text = tex;
}

// -----------------------------------------------------------------------------
// Función de cálculo de normales
// Calcula y rellena el vector de normales de vértices para su uso en iluminación

void Malla3D::calcular_normales(){
	
	nv.resize(v.size());
	
	Tupla3f per, nor;	//Perpendicular y normal
	Tupla3f a, b;
	int v1,v2,v3;
	int x=0, y=1, z=2;
	
	for (int i=0; i<tam_vcaras; i++){
		a = v[f[i](y)]-v[f[i](x)];
		b = v[f[i](z)]-v[f[i](x)];
		
		//Producto vectorial de a y b
		per = a.cross(b);
		
		//Nomalizar aXb
		if(per.lengthSq()>0)
			nor = per.normalized();
		
		//Vértices adyacentes a la cara i
		v1 = f[i][x];
		v2 = f[i][y];
		v3 = f[i][z];
		
		//Sumar normal de cara i a los vértices adyacentes 
		nv[v1]=nv[v1]+nor;
		nv[v2]=nv[v2]+nor;
		nv[v3]=nv[v3]+nor;		
	}
	
	//Normalizar vector nv
	for(int i=0; i<nv.size(); i++){
		if(nv[i].lengthSq()>0)
			nv[i].normalized();
	}
	
}








