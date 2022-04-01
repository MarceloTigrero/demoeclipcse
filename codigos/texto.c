#include "texto.h"

int CodigoAnsi(unsigned char caracter)
{
  for(int i=0;i<127;i++)//255
  {
    if(caracter==i)
    {
      return i;
    }else{
      if(126==i)
      { 
        return 0;
      }
    }
  }
}

int encontrarNseparador(const char* origin,int ansi)
{
  const int len = strlen(origin);
  int encontrado=0;
  for(int i=0;i<len+1;i++)
  {
    if(origin[i]==ansi)
    {
      encontrado++;
    }
  }
  return encontrado;
}

int encontrarDchar(const char* origin,int ubicacion,unsigned char caracter)
{
  int ansi =CodigoAnsi(caracter);
  const int len = strlen(origin);
  int encontrado=0;
  int dimencion[encontrarNseparador(origin,ansi)];
  int ubi[encontrarNseparador(origin,ansi)-1];
  for(int i=0;i<len-1;i++)
  {
    if(i==0){dimencion[encontrado]=0;}
    if(origin[i]==ansi)
    {
      ubi[encontrado]=i+1;
      encontrado++;
      dimencion[encontrado]=0;
    }else{
      dimencion[encontrado]+=1;
    }
  }
  return dimencion[ubicacion];
}

int encontrarUchar(const char* origin,int ubicacion,unsigned char caracter)
{
  int ansi =CodigoAnsi(caracter);
  const int len = strlen(origin);
  int encontrado=0;
  int dimencion[encontrarNseparador(origin,ansi)];
  int ubi[encontrarNseparador(origin,ansi)-1];
  for(int i=0;i<len-1;i++)
  {
    if(i==0){dimencion[encontrado]=0;}
    if(origin[i]==ansi)
    {
      ubi[encontrado]=i+1;
      encontrado++;
      dimencion[encontrado]=0;
    }else{
      dimencion[encontrado]+=1;
    }
  }
  if(ubicacion == 0)
  {
    return 0;
  }else{
    return ubi[ubicacion-1];
  }
}

const char* encontrarXchar(const char* origin,int ubicacion,unsigned char caracter)
{
  int ansi = CodigoAnsi(caracter);
  int dim=encontrarDchar(origin,ubicacion,ansi);
  int ubi=encontrarUchar(origin,ubicacion,ansi);
  char word[dim];
  for(int i=0;i<=dim;i++)
  { 
    word[i]=origin[ubi+i];
    if(word[i]==ansi)
    {
      word[i]=0;
    }
  }
  return word;
}

int comparar(const char* text1,const char* text2)
{
  int l,menor;
  if(strlen(text1)<strlen(text2))
  {
    menor=1;
  }else if(strlen(text1)>strlen(text2)){
    menor=2;
  }else{
    menor=0;
  }
  if(menor==2){l=strlen(text1);}else{l=strlen(text2);}
  for(int i=0;i<l;i++)
  {
    if (i<strlen(text1)&&i<strlen(text2))
    {  
      if(CodigoAnsi(text1[i])!=CodigoAnsi(text2[i]))
      {  
        return 0;
      }
    }else{
      if(menor==2)
      {  
        if(CodigoAnsi(text1[i])!=CodigoAnsi(' '))
        {  
          return 0;
        }
      }else{
        if(CodigoAnsi(text2[i])!=CodigoAnsi(' '))
        {  
          return 0;
        }
      }
    }
  }
  return 1;
}

const char* armarJson(const char* clave,const char* valor)
{
  const int lenClave = strlen(clave);
  const int lenValor = strlen(valor);
  char word[lenClave+lenValor+8];
  word[0] = CodigoAnsi('{');
  word[1] = CodigoAnsi('"');
  for(int i=0;i<lenClave;i++)
  {
      word[2+i] = clave[i];
  }
  word[lenClave+2] = CodigoAnsi('"');
  word[lenClave+3] = CodigoAnsi(':');
  word[lenClave+4] = CodigoAnsi('"');
  for(int i=0;i<lenValor;i++)
  {
    word[lenClave+5+i] = CodigoAnsi(valor[i]);
  }
  word[lenClave+lenValor+5] = CodigoAnsi('"');
  word[lenClave+lenValor+6] = CodigoAnsi('}');
  word[lenClave+lenValor+7] ='\0';
  printf(":word: %i %s\n",strlen(word),word);
  return word;
}



