// Vertex Shader
//
// Este vertex shader � extremamente simples. Ele apenas converte a posi��o do v�rtice utilizando
// a matriz ModelView. Tamb�m � passado adiante uma cor para cada v�rtice. A cor � determinada pela
// posi��o do v�rtice.
//
// Abril 2016 - Alex Frasson - afrasson@inf.ufsm.br

#version 400

layout (location = 0) in vec3 VertexPosition;

uniform mat4 ModelViewMatrix;
out vec3 vColor;

void main()
{	
	vColor = VertexPosition;
	gl_Position = ModelViewMatrix * vec4(VertexPosition,1.0);
}