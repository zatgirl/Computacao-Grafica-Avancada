//Autor: Cesar Tadeu Pozzer

uniform sampler2D texture_0; //se nao for inicializada, vale 0, referente a textura 0
uniform sampler2D texture_1; //se nao for inicializada, vale 0, referente a textura 0
uniform float     brilho;
uniform int dim; //dimensao real da imagem
uniform int mode;
uniform int qtd_parts;
varying float  x_coord;

void main()
{
   vec2 position = gl_TexCoord[0].st;
   vec3 cor;

   ///cube
   if (mode == 4){

   }

   ///colunas intercalando a textura
   if (mode == 3)
   {
      float fatia = dim/(dim/qtd_parts);

      int divisao = (int)((position.x * dim)/fatia);

      float resto = mod(divisao, fatia);
      float teste_par = mod(resto, 2.0);

      if((teste_par == 0.0)){
        cor = texture2D(texture_0, position).rgb;
      }
      else {
        cor = texture2D(texture_1, position).rgb;
      }
   }

   ///grayscale
   if (mode == 2){
      cor = texture2D(texture_0, position).r * 0.3 + texture2D(texture_0, position).g * 0.59 + texture2D(texture_0, position).b * 0.11;
   }

   ///literalmente 100pixels de cada, horizontal
   if (mode == 1){
      int pos = ((position.y * dim)* dim) + position.x * dim;
      int intervalo0 = (int)(pos / 100);
      int intervalo1 = intervalo0 + 100;
      float resto;
      resto = mod(intervalo1, 2.0);

      if(resto == 0.0){
       cor = texture2D(texture_0, position).rgb;
      }
      else{
       cor = texture2D(texture_1, position).rgb;
       //cor = vec3(1.0, 0.0, 0.0);
      }
   }

   ///sobreposicao
   if (mode == 0){
       vec3 p0, p1;
       p0 = texture2D(texture_0, position).rgb;
       p1 = texture2D(texture_1, position).rgb;
       cor = (1 - brilho) * p0 + brilho * p1;
   }

   //gl_FragColor = texture2D(texture, position).rgba;
   gl_FragColor = vec4( cor, 1);
}
