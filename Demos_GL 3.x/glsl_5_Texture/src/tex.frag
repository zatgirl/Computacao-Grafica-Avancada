//Autor: Cesar Tadeu Pozzer

uniform sampler2D texture_0; //se nao for inicializada, vale 0, referente a textura 0
uniform sampler2D texture_1; //se nao for inicializada, vale 0, referente a textura 0
uniform float     brilho;
uniform int dim; //dimensao real da imagem
uniform int mode;
uniform int qtd_parts;
uniform float taxa_blur;
uniform float radius;
uniform int mouseX;
uniform int mouseY;
uniform float zoom;
varying float x_coord;


void main()
{
   vec2 position = gl_TexCoord[0].st;
   vec3 cor = vec3(0.0, 0.0, 0.0);
   int dim_screen = 600;

   ///zoom no circulo
   if(mode == 7){
     vec2 mouse_texCoord = vec2((mouseX*1.0)/dim_screen, (mouseY*1.0)/dim_screen);
     float distPoint = distance(position, mouse_texCoord);
     vec2 vetorDir = normalize(mouse_texCoord - position);
     vec2 scale = vetorDir * position;

     if(distPoint < radius){

        float zoomFactor = 1 + zoom;
        vec2 vectorDir = (position - mouse_texCoord);
        cor = texture2D(texture_0, (mouse_texCoord + vectorDir*zoomFactor)).rgb;

        //cor = texture2D(texture_0, position).rgb;
                /*
        for (float i = zoom*0.6; i <= zoom; i += zoom*0.6){
           cor += texture2D(texture_0, position + i*scale).rgb;
           cor /= 2;
        }*/
        //cor /= 0.6;
     }
     else {
        vec2 posImg;
        int amostras = 0;

        taxa_blur = (taxa_blur * distPoint);
        for(float x = -taxa_blur; x < taxa_blur; x += 0.001){
            for(float y = -taxa_blur; y < taxa_blur; y += 0.001){
            posImg = vec2(position.x  + x, (position.y + y));
            cor += texture2D(texture_0, posImg).rgb;
            amostras ++;
            }
        }
        cor /= amostras;
     }
     if((distPoint > radius*0.980) && (distPoint < radius*1.010)){
        cor = vec3(0.0,0.0,0.0);
     }
     if(distPoint < radius){
         if((position.y - mouse_texCoord.y) > -0.001 && (position.y - mouse_texCoord.y < 0.001)){
            if((distPoint > 0.01)){
                cor = vec3(0.0,0.0,0.0);
            }
         } else if ((position.x - mouse_texCoord.x) > -0.001 && (position.x - mouse_texCoord.x < 0.001)){
            if((distPoint > 0.01)){
                cor = vec3(0.0,0.0,0.0);
            }
         }
     }
   }

   ///circulo ao redor do mouse
   if(mode == 6){
     float distPoint = distance(position, vec2((mouseX*1.0)/dim_screen, (mouseY*1.0)/dim_screen));

     if(distPoint <= radius){
        cor = texture2D(texture_1, position).rgb;
     }
     else {
        cor = texture2D(texture_0, position).rgb;
     }
   }

   ///linha girando alterando texturas
   if(mode == 5){
      float ang = brilho;
      vec2 rot = vec2(cos(ang), sin(ang));
      vec2 dist = position - vec2(0.5, 0.5);
      float dotProduct = dot(rot, dist);

      if(dotProduct > 0.0){
          cor = texture2D(texture_0, position).rgb;
      }
      else{
          cor = texture2D(texture_1, position).rgb;
      }
    }

   ///blur parametrizado
   if (mode == 4){
      vec2 posImg;
      int amostras = 0;

      for(float x = -taxa_blur; x < taxa_blur; x += 0.001){
        for(float y = -taxa_blur; y < taxa_blur; y += 0.0001){
          posImg = vec2(position.x  + x, (position.y + y));
          cor += texture2D(texture_0, posImg).rgb;
          amostras ++;
        }
      }
      cor /= amostras;
   }

   ///colunas intercalando a textura verticalmente
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
