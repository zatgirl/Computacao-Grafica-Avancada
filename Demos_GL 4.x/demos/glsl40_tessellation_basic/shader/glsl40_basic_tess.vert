// Vertex Shader
//
// Como as tranform��es ser�o aplicadas somente no est�gio Tessellation Evaluation Shader, este
// vertex shader apenas passa os v�rtices de entrada adiante para o Tessellation Control Shader.
//
// Abril 2016 - Alex Frasson - afrasson@inf.ufsm.br

#version 400

layout(location = 0) in vec3 VertexPosition;

void main()
{
	gl_Position = vec4(VertexPosition, 1.0);
}
