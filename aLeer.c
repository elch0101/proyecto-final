#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*crear funciones*/
void Leer_Datos_Usuario(void);/*lee el archivo que contiene los usuarios*/
int Comprobar_Usuario(void);/*compara el usuario y contraseña ingresados  con el archivo de texto*/
void Registro(void);/*permite que se puedan registrar*/

void Menu_Admin (void);
void Baja_Usuario(void); /*poder dar de baja a usuarios*/
void Alta_Baja_Libros(void); /*poder añadir o quitar libros*/
void Informe_Libros(void); /*da informacion sobre los libros que estan prestados*/
void Informe_Usuarios_Libros(void); /*informacion sobre los usuarios y que libros tienen rentados*/
void Popular(void); /*informacion sobre que categoria, autor y libro son los mas populares*/

void Menu_Usuario (void);
void Catalogo(void); /*hacer que el usuario puedo ver el catalogo de libros*/
void Mis_Libros(void); /*poder ver los libros que uno tiene rentado*/
void Devolucion(void);/*regresar los libros rentados para poder rentar diferentes*/

/*hacer todas las estructuras necesarias*/
struct Fecha_Nacimiento /*struct para la fecha de nacimiento*/
{
  int dia;
  int mes;
  int anyo;
};

struct Datos_Usuario/*struct para datos del usuario, incluye struct de la fecha de nacimiento*/
{
  char nombre[31];
  char apellido[31];
  char direccion[51];
  char email[51];
  struct Fecha_Nacimiento fecha; 
  char contrasenya[21];
}cliente[30];

struct Datos_Admin/*obtiene los datos de los administradores*/
{
  char nombre[31];
  char apellido[31];
  char contrasenya[21];
}admin[3];

struct Datos_Libro
{
  char titulo[51];
  char autor[51];
  int genero;
}libro[30];

/*variables globales*/
char nombre[30], apellido[30], contrasenya[20];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*lee todos los datos que estan en el txt file datos_cliente.
  almacena el valor del nombre, direccion, email, fecha de nacimiento y su contraseña.*/
void  Leer_Datos_Usuario(void)
{
  FILE* archivo;
  char linea[100];
  int i=0;
  
  archivo = fopen("datos_usuario.txt", "rt"); /*lee archivo que tiene guardado todos los datos de los usuarios*/
  if (archivo != NULL) /*si el archivo existe hacer...*/
    {
      while (!feof(archivo))/*leer hasta el final del archivo*/
	{
	  /*lee las letras que corresponden al nombre*/
	  if (feof(archivo))break;
	  fgets(linea,30,archivo);
	  linea[strlen(linea)-1]='\0';
	  strcpy(cliente[i].nombre, linea);

	  /*lee las letras que corresponden al apellido*/
	  if (feof(archivo))break;
	  fgets(linea,30,archivo);
	  linea[strlen(linea)-1]='\0';
	  strcpy(cliente[i].apellido, linea);
	  
	  /*lee las letras que corresponden a la direccion*/
	  if(feof(archivo))break;
	  fgets(linea,50,archivo);
	  linea[strlen(linea)-1]='\0';
	  strcpy(cliente[i].direccion,linea);
	  
	  /*lee las letras que corresponden al email*/
	  if(feof(archivo))break;
	  fgets(linea,50,archivo);
	  linea[strlen(linea)-1]='\0';
	  strcpy(cliente[i].email,linea);
	  
	  /*lee los numeros que corresponden a la fecha de nacimento*/
	  fgets(linea, 10, archivo);
	  if (feof(archivo)) break;
	  sscanf(linea, "%d %d %d", &cliente[i].fecha.dia, &cliente[i].fecha.mes, &cliente[i].fecha.anyo);
	  fgets(linea, 10, archivo);
	  //fgets(linea,1,archivo);

	  /*lee las letras que corresponden a la contraseña*/
	  if(feof(archivo))break;
	  fgets(linea,50,archivo);
	  linea[strlen(linea)-1]='\0';
	  strcpy(cliente[i].contrasenya,linea);
	  
	  i++;
	}
      fclose(archivo);  
    }
  /* for (i=0;i<4;i++)
    {
      printf("\nAQUI\n");
      printf("nombre: %s\n",cliente[i].nombre);
      printf("apellido: %s\n",cliente[i].apellido);
      printf("dirección: %s\n",cliente[i].direccion);
      printf("email: %s\n",cliente[i].email);
      printf("fecha: %d/%d/%d\n",cliente[i].fecha.dia,cliente[i].fecha.mes,cliente[i].fecha.anyo);
      printf("contrasenya: %s\n",cliente[i].contrasenya);
    }
  */
}
////////////
/*comprueba si el usuario ingresado es administrador o cliente normal.
lee datos de archivos y compara con los datos ingresados por el usuario.
automaticamente ingresa como administrador si es que esta dentro de la lista.
verifica que el usuario y contraseña coinsidan, ya sea adminitrador o cliente regular*/
int Comprobar_Usuario (void)
{
  FILE* archivo;
  char linea[100];
  int i=0;
  int na=1, aa=1, ca=1;/*nombre admin, apellido admin, contraseña admin*/
  int n=1, a=1, c=1; /*nombre, apellido, contraseña*/
    
  archivo = fopen("usuarios_admin.txt", "rt");/*lee archivo que tiene guardado el usuario y contraseña del admin para poder reconocerlo*/
  if (archivo != NULL)/*si el archivo existe hacer...*/
    {
      while (!feof(archivo))/*leer hasta el final del archivo*/
	{	    
	  /*lee las letras que corresponden al nombre*/
	  if (feof(archivo))break;
	  fgets(linea,30,archivo);
	  linea[strlen(linea)-1]='\0';
	  strcpy(admin[i].nombre, linea);

	  /*lee las letras que corresponden al apellido*/
	  if (feof(archivo))break;
	  fgets(linea,30,archivo);
	  linea[strlen(linea)-1]='\0';
	  strcpy(admin[i].apellido, linea);
	    
	  /*lee las letras que corresponden a la contraseña*/
	  if(feof(archivo))break;
	  fgets(linea,20,archivo);
	  linea[strlen(linea)-1]='\0';
	  strcpy(admin[i].contrasenya,linea);
	  if(feof(archivo))break;
	  i++;
	}
      fclose(archivo);
    }
  for(i=0;i<=2;i++)/*compara el usuario y contraseña ingresadas con los admins*/
    {
      if((na!=0)||(aa!=0)||(ca!=0))
	{
	  na=strcmp(nombre,admin[i].nombre);
	  aa=strcmp(apellido,admin[i].apellido);
	  ca=strcmp(contrasenya,admin[i].contrasenya);
	}
      if((na==0)&&(aa==0)&&(ca==0))
	{
	  i=3;
	}
    }
  
  if ((na==0)&&(aa==0)&&(ca==0)) /*decidir si se entro como administrador*/
    {
      printf("\nHa ingresado como administrador\n");
      return 1;
    }
  
  /*si no entra como administrador leer los datos del texto de usuarios normales*/
  Leer_Datos_Usuario();
  for(i=0;i<=29;i++) /*compara el usuario y contraseña ingresadas con los usuarios*/
    {
      if((n!=0)||(a!=0)||(c!=0))
	{
	  n=strcmp(nombre,cliente[i].nombre);
	  a=strcmp(apellido,cliente[i].apellido);
	  c=strcmp(contrasenya,cliente[i].contrasenya);
	}
      if((n==0)&&(a==0)&&(c==0))
	{
	  i=100;
	}
    }
  
  if((n==0)&&(a==0)&&(c==0))/*decidir si se entro como cliente*/
    {
      printf("\nHa ingresado como cliente\n");
      return 2;
    }
  else/*no es valido el usuario*/
    {
      printf("\nSu usuario o contraseña esta mal\n");
      return 3;
    }
}
///////////////
/*perimite al cliente poder registrarse por su cuenta.
  sus datos son guardados en un archivo de texto llamado datos_cliente*/
void Registro(void)
{
  FILE* archivo;
  int count;
  int lim=0;
  int i,x=0;
  int numRand,numRand2;
  char contrasenya[5];

  for (i=0;i<=4;i++)
    {
      contrasenya[i]='1'+(rand()%9);
    }
  for (i=0;i<=3;i++)
    {
      strcat(contrasenya[i],contasenya[i+1]);
    }

  printf(%s)
  Leer_Datos_Usuario();/*lee los datos que ya estan guardados*/
  //x=strcmp(cliente[0].nombre,"\0");
  
  archivo=fopen("datos_usuario.txt","wt");
  if (archivo!=NULL)
    {
      do
	{
	  x=strcmp(cliente[i].nombre,"\0");
	  if (x!=0)
	    {
	      i++;
	    }
	} while(x!=0);
      
      i--;
      lim=i;
      
      printf("Ingrese su nombre: ");
      gets(cliente[i].nombre);
      printf("Ingrese su apellido: ");
      gets(cliente[i].apellido);
      printf("Ingrese su dirección: ");
      gets(cliente[i].direccion);
      printf("Ingrese su email: ");
      gets(cliente[i].email);
      printf("Ingrese su fecha de nacimineto (dd/mm/yyyy): ");
      scanf("%d %d %d", &cliente[i].fecha.dia, &cliente[i].fecha.mes,
	    &cliente[i].fecha.anyo);
      //getchar();
      printf("Su contraseña es: ");
      for (i=0;i<=4;i++)
	{
	  printf("%c",contrasenya[i]);
	}
      
      for(i=0;i<=lim;i++)
	{
	  fprintf(archivo,"%s\n",cliente[i].nombre);
	  fprintf(archivo,"%s\n",cliente[i].apellido);
	  fprintf(archivo,"%s\n",cliente[i].direccion);
	  fprintf(archivo,"%s\n",cliente[i].email);
	  fprintf(archivo,"%d %d %d\n",cliente[i].fecha.dia, cliente[i].fecha.mes, cliente[i].fecha.anyo);
	  fprintf(archivo,"%s\n",cliente[i].contrasenya);
	}
    }
  fclose(archivo);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*al ingresar comoa dministrador desplegar todas las opciones posibles*/
void Menu_Admin(void)
{
  int count=1;
  int hacer;

  while (count!=0)
    {
      printf("\nIngrese:\n[1] Baja de un usuario\n[2] Alta y baja de libros\n[3]");
      printf(" Informe de libros en préstamo\n[4] Informe de usuarios dados de alta y libros rentados");
      printf("\n[5] Información categoría, autor y título más popular\n[6] Ayuda\n[0] Log out\n");
      scanf("%d", &hacer);
      if (hacer==1)
	{
	  Baja_Usuario(); /*poder dar de baja a usuarios*/
	}
      else if (hacer==2)
	{
	  Alta_Baja_Libros(); /*poder añadir o quitar libros*/
	}
      else if (hacer==3)
	{
	  Informe_Libros(); /*da informacion sobre los libros que estan prestados*/
	}
      else if (hacer==4)
	{
	  Informe_Usuarios_Libros(); /*informacion sobre los usuarios y que libros tienen rentados*/
	}
      else if(hacer==5)
	{
	  Popular(); /*informacion sobre que categoria, autor y libro son los mas populares*/
	}
      else if (hacer==6)
	{
	  printf("AYUDA");
	}
      else if (hacer==0)
	{
	  count=hacer; /*regresar al menu anterior*/
	}
      else
	{
	  printf("El número que ingreso no es válido");
	}
    }      
}
void Baja_Usuario(void)
{

}
///////
void Alta_Baja_Libros(void)/*poder añadir o quitar libros*/
{

}
//////
void Informe_Libros(void) /*da informacion sobre los libros que estan prestados*/
{

}
//////
void Informe_Usuarios_Libros(void) /*informacion sobre los usuarios y que libros tienen rentados*/
{

}
/////
void Popular(void)
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*al ingresar como usuario deplegar las opciones que puede realizar*/
void Menu_Usuario(void)
{
  int count=1;
  int hacer;

  while(count!=0)
    {
      printf("\nIngrese:\n[1] Ver catálogo de libros\n[2] Libros en préstamo\n[3]");
      printf(" Devolución de libros\n[0] Log out\n");
      scanf("%d", &hacer);
      if (hacer==1)
	{
	  Catalogo(); /*hacer que el usuario puedo ver el catalogo de libros*/
	}
      else if (hacer==2)
	{
	  //Mis_Libros(); /*poder ver los libros que uno tiene rentado*/
	}
      else if (hacer==3)
	{
	  //Devolucion();/*regresar los libros rentados para poder rentar diferentes*/
	}
      else if (hacer==0)
	{
	  count=hacer; /*regresar al menu anterior*/
	}
      else
	{
	  printf("El número que ingreso no es válido");
	}
    }
}
////////////
/*lee los datos del catalogo para enseñar los libros que hay y poder escojer entre ellos*/
void Catalogo(void)
{
  int hacer=1;
 
  while (hacer!=0)
    {
      printf("ingrese:\n[1] Infantiles\n[2] Terror\n[3] Ciencia ficción\n[4] Amor\n[5] Ver todo\n[0] Regresar\n");
      scanf("%d",&hacer);
      if (hacer==1)
	{
	 
	}
      else if(hacer==0)
	{
	  hacer=0;
	}
    }
}
////////////
/*poder ver los libros que uno tiene rentado*/
void Mis_Libros(void) 
{
  
}
////////////////
/*regresar los libros rentados para poder rentar diferentes*/
void Devolucion(void)
{
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
  int i;
  int count=1;
  int hacer;
  srand(time(0));
 
  /*correr el programa hasta que el usuario quiera*/
  while (count!=0)
    {
      /*pedir si ingresar o crear nuevo usuario.*/
      printf ("\nprecione:\n[1] ingresar\n[2] registrarse\n[0] salir\n");
      scanf("%d", &hacer);
      getchar();
      if (hacer==1)
	{
	  /*pedir el usuario y la contraseña*/
	  printf("nombre: ");
	  gets(nombre);
	  printf("apellido: ");
	  gets(apellido);
	  printf("contraseña: ");
	  gets(contrasenya);
	  
	  hacer=Comprobar_Usuario();
	      if(hacer==1)
		{
		  Menu_Admin(); /*despliega todas las opciones como administrador*/
		}
	      else if(hacer==2)
		{
		  Menu_Usuario(); /*enseña todo lo que se puede hacer como cliente*/
		}
	}
      else if (hacer==2)
	{
	  Registro(); /*hacer que el usuario se registre si no tiene cuenta*/
	}
      else if (hacer==3)
	{

	}
      else if (hacer==0)
	{
	  count=hacer;/*terminar el programa*/
	}
      else
	{
	  printf("\nEl número que ingreso no es válido\n");
	}
    }
  return 0;
}
