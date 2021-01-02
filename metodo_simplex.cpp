/* 
  by osvaldo velazquez
  https://github.com/valdolab
*/

#include<iostream>
#include<string.h>

using namespace std;

float matriz[10][10];
int opc,i,j,itera=0,des=0;
int e,v,v2,menor=0,con=0;
int aux_i,aux_j,aux_i2,aux_j2,aux_mi[10],aux_mj[10],x[10];
float aux_div,pigote,c_pi,pigo_ai=0,pigo_aj=0;

void menu();
void ingresar();
void hacer_matriz();
void simplex();
void minimizar();
void mostrar();
void mostrar_ma();
/*
v2=lado derecho
--- recorre columna -----    for(j=0;j<v2+1;j++)   
--- recorre fila ------      for(i=0;i<e+1;i++) 
   
for(i=0;i<e+1;i++)
{
	for(j=0;j<v2+1;j++)
	{

	}
*/
void simplex()
{
	cout<<"\n\n";
	mostrar_ma();
	do
	{
		for(j=0;j<v2+1;j++)
		{
			if(matriz[0][j]<menor)
			{
				menor=matriz[0][j];
				aux_j=j;// guardo pocicion del pigote -- j
				aux_mj[itera]=aux_j;
			}
		}
		menor=1000000000;
		for(i=0;i<e+1;i++)
		{
			aux_div=matriz[i][v2]/matriz[i][aux_j];//lado derecho entre pigote
			if(aux_div<menor && aux_div!=0 && aux_div>0)
			{
				menor=aux_div;
				aux_i=i;// guardo pocicion del pivote -- i
				aux_mi[itera]=aux_i;
			}
		}
		//matriz[aux_i][aux_j];    <--- pigote
		//hacer 1 el pigote
		pigote=matriz[aux_i][aux_j];
		for(j=0;j<v2+1;j++) 
		{
			matriz[aux_i][j]=matriz[aux_i][j]/pigote; //matriz[aux_i][aux_j];
		}
		for(i=0;i<e+1;i++)//hacer 0 la columna del pigote
		{
			if(i!=aux_i)
			{
				if(matriz[i][aux_j]!=0);//&& matriz[i][aux_j]!=matriz[aux_i][aux_j])
				{
					aux_i2=i;
					c_pi=matriz[aux_i2][aux_j];
					for(j=0;j<v2+1;j++)
					{
						matriz[aux_i2][j]=(((c_pi)*-1)*(matriz[aux_i][j]))+matriz[aux_i2][j];//matriz[aux_i2][j]-((matriz[aux_i][j])*(c_pi));   
						//gauss en toaa la fila para hacer 0
					}
				}
			}
		}
		//imprimir iteraciones
		itera++;
		//pigo_ai=aux_i;
		//pigo_aj=aux_j;
		cout<<"\n\nIteracion N. "<<itera<<"\n\n";
		mostrar_ma();
		des=0;
		for(j=0;j<v2+1;j++)
		{
			if(matriz[0][j]<0)
			{
				des=1;
			}
		}
		con++;
	}while(des!=0);
}

void mostrar()
{
	system("cls");
	cout<<"La matriz optenida que se uso en el metodo simplez es la siguiente:\n\n\n   |\n";
	mostrar_ma();
	cout<<"\n\n";
	cout<<"------------------------- Resultado de la optimisacion ------------------------ \n\n";
	for(i=0;i<itera;i++)
	{
		//cout<<"X"<<aux_j<<" = "<<matriz[aux_i][v2];
		cout<<"X"<<aux_mj[i]<<" = "<<matriz[aux_mi[i]][v2];
		cout<<"\n";
	}
	cout<<"\nZ = "<<matriz[0][v2];
}

void mostrar_ma()
{
	for(j=0;j<v2+1;j++)
	{
		if(j==v2)
		{
			cout<<"\tL.D";
		}
		else
		if(j==0)
		{
			cout<<"   |\tZ";
		}
		else
		{
			cout<<"\tX"<<j;
		}
	}
	cout<<"\n___|____________________________________________________________________\n   |\n";
	for(i=0;i<e+1;i++)
	{
		if(i==0)
		{
			cout<<"Z  |";
		}
		else
		{
			x[aux_i-1]=aux_j;
			cout<<"X"<<x[i-1]<<" |";
		}
		cout<<"\t";
		for(j=0;j<v2+1;j++)
		{
			printf("%0.1f",matriz[i][j]);
			cout<<"\t";
		}
		cout<<"\n   |\n";
	}
}

void hacer_matriz()
{
	int c;
	for(i=0;i<e+1;i++)
	{
		if(i!=0)
		{
			matriz[i][v+c]=1;
		}
		c++;
	}
	for(j=0;j<v+1;j++)
	{
		matriz[0][j]=(matriz[0][j])*(-1);
	}
	matriz[0][0]=1;
}

void ingresar()
{
	system("cls");
	cout<<"Ingrese el numero de ecuaciones de las restricciones(sin contar Z):\n";
	cin>>e;
	cout<<"Ingrese el numero de variables existentes:\n";
	cin>>v;
	v2=v+e+1;
	cout<<"Ingrese la ecuacion Z como se le pida:\n\n";
	for(j=1;j<v+1;j++)
	{
		cout<<"X"<<j<<" = ";
		cin>>matriz[0][j];
	}
	for(i=1;i<e+1;i++)
	{
		system("cls");
		cout<<"\nIngrese las restriciones como se le pida:\n";
		cout<<"Ingrese el los valeres de la restruccion N-"<<i<<"(Respetando signos)\n\n";
		for(j=0;j<v+1;j++)
		{
			if(j==v)
			{
				cout<<"Lado derecho = ";
				cin>>matriz[i][v2];				
			}
			else
			{
				cout<<"X"<<j+1<<" = ";
				cin>>matriz[i][j+1];
			}
		}
		x[i-1]=i+v;
	}
}

void menu()
{
	system("cls");
	cout<<"\t\t\tINVESTIGACION DE OPERACIONES\n";
	cout<<"\t\t\tMetodo Simplex solo con <=\n\n";
	cout<<"Elija una opcion:\n";
	cout<<"1. Maximizar\n";
	cout<<"2. Miminizar\n";	
	cout<<"3. Mostrar estado actual\n";
	cout<<"4. Salir\n\n";
	cout<<"--> ";
	cin>>opc;
	switch(opc)
	{
		case 1:
			ingresar();
			hacer_matriz();
			simplex();
			break;
		case 2:
			ingresar();
			hacer_matriz();
			minimizar();
			simplex();
			break;
		case 3:
			mostrar();
			break;
		case 4:
			exit(0);
			break;
		default:
			cout<<"Elije una opcion valida!! Intente de nuevo!";
			system("pause");
			menu();
			break;
	}
	cout<<"\n\n";
	system("pause");
	menu();
}
void minimizar()
{
	for(j=0;j<v+1;j++)
	{
		matriz[0][j]=(matriz[0][j])*(-1);
	}
}

main()
{
	menu();	
}
