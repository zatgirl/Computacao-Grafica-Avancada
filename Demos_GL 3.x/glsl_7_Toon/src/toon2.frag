// simple toon fragment shader
// www.lighthouse3d.com

//----------------------------------------------------------
//desenvovido por Victor Chitolina Schetinger  - ufsm 2009
//----------------------------------------------------------

varying vec3 normal, lightDir, lightDir2;
varying float px;
varying float py;
varying float pz;

varying float wawa;
void main()
{
	float intensity;
	float intensity2;
	vec4 color = vec4(0.6,0.6,1.0,1.0);

	intensity = max(dot(lightDir,normal),0.0);
	
	intensity2 = max(dot(lightDir2,normal),0.0);
	
	//�ngulo de incid�ncia
	float decide = acos(dot(lightDir,normal));
	
			
	if (intensity > 0.98){
		color = vec4(0.8,0.8,0.8,1.0);
		
		}
		
		
	else if (intensity > 0.5){
		color = vec4(0.5,0.5,0.9,1.0)
		//listras cossen�ides
		+ (cos(px*70)/40)*intensity;
		}	
	else if (intensity > 0.25){
		color = vec4(0.2,0.2,0.4,1.0)+ 
		//listras cossen�ides
		(cos(px*70)/40)*intensity;
		}
	else{
		//listras cossen�ides
		color = vec4(0.1,0.1,0.1,1.0)+ (cos(px*70)/40)*intensity;
		}
		
	//usando isso, a intensidade fica quadr�tica, ent�o valores de intensidade
	//maiores de intensidade maiores que 0.8 ficam >1, ent�o ser�o aumentados quadraticamente
	//e valores < 0.8 diminuir�o quadraticamente, isso deixa maior o efeito de sombra
	//intensity*=(0.05+intensity);
	
	//multiplicando a cor pela intensidade,
	//para real�ar o efeito da luz
	
	
	color*=intensity;
	
	//at� 1.57075 radianos de incid�ncia, o �ngulo influencia da ilumina��o
	//ap�s esse �ngulo, � escurecida a figura
	if(decide <= 1.57075) 
		color*=(0.1+(1.57075-decide));
	else
		color -= 0.1;
		
	
	gl_FragColor = color;
}
