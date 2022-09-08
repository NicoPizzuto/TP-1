#include <iostream>
#include <fstream>

using namespace std;

const int cod_prod = 5;
void kg_list(string nom_prod[], string nom_cliente[], float kg[][cod_prod],
             int cont[], int cant_cliente, int cant_prod)
{
	cout << "- Punto 1 " << endl;
    cout << "Los elementos que superan los 13000 kg son: " << endl;
    for (int i = 0; i < cant_cliente; i++)
	{
		cout << i << ") " << nom_cliente[i] << '\t';
        for (int j = 0; j < cant_prod; j++)
		{
			if (kg[i][j] > 13000)
			{
				cout << nom_prod[j] << '\t';
                cont[i] += 1;
            }
        }
        cout << endl;
    }
}

int pos_mayor(int cont_cliente[], int cod_cliente)
{
    int mayor = cont_cliente[0];
    int pos = 0;
    for (int i = 0; i < cod_cliente; i++)
	{
        if (cont_cliente[i] > mayor)
		{
            mayor = cont_cliente[i];
            pos = i;
        }
    }
	return pos;
}

void list_cliente_variedad (string nom_prod[], string nom_cliente[], int cod_cliente, 
                            int list_var[], int seg[], float km[][cod_prod])
{
	cout << "- Punto 2 " << endl;
    int pos = pos_mayor(list_var, cod_cliente);
    cout << "Variedad de " << nom_cliente[pos] << ", posicion " << pos << ": " << endl;
    int n = 0;
	int temp = 0;
    do
	{
		n = 0;
        for (int i = 1; i < cod_prod; i++)
		{
            if (km[pos][i - 1] < km[pos][i])
			{
                temp = km[pos][i - 1];
                km[pos][i - 1] = km[pos][i];
                km[pos][i] = temp;
                n++;
                temp = seg[i - 1];
                seg[i - 1] = seg[i];
                seg[i] = temp;
            }
        }
    }
    while (n != 0);
    for (int i = 0; i < cod_prod; i++)
	{
        cout << nom_prod[seg[i]] << '\t' << km[pos][i] << " km " << endl;
    }
}

void mayor_cant_entrega(string nom_prod[], string nom_cliente[],
                        int cant_entregas[][cod_prod], float cant_km[][cod_prod],
                        int cod_cliente, int seguimiento[], int cont_cliente[])
{
	cout << "- Punto 3 " << endl;
    cout << "Entregas de " << nom_prod[seguimiento[0]] << ": " << endl;
    for (int i = 0; i < cod_cliente; i++)
	{
        if (i == pos_mayor(cont_cliente, cod_cliente))
		{
            cout << i << ") " << nom_cliente[i] << '\t' << cant_entregas[i][0] << endl;
        }
        else
		{
            cout << i << ") " << nom_cliente[i] << '\t' << cant_entregas[i][seguimiento[0]] << endl;
        }
    }
}

int main()
{
    const int cod_cliente{8};
    string nom_cliente[cod_cliente];
    string nom_prod[cod_prod];
    float cant_peso[cod_cliente][cod_prod]{0};
    int cont_cliente[cod_cliente]{0};
    int seguimiento[cod_prod]{0, 1, 2, 3, 4};
    float cant_km[cod_cliente][cod_prod]{0};
    int cant_entregas[cod_cliente][cod_prod]{0};

    ifstream nombres;
    nombres.open("nombres.txt");
    if (!nombres)
	{
        cout << "Error al tratar de abrir el archivo de lectura " << endl;
        return 1;
    }
    for (int i = 0; i < cod_cliente; i++)
	{
        nombres >> nom_cliente[i];
    }
    for (int i = 0; i < cod_prod; i++)
	{
        nombres >> nom_prod[i];
    }
    nombres.close();

    ifstream datos;
    datos.open("datos.txt");
    if (!datos)
	{
        cout << "Error al tratar de abrir el archivo de lectura";
        return 1;
    }
    int tcliente = 0;
    int tprod = 0;
    float tkg = 0;
	float tkm = 0;
    while (datos >> tcliente >> tprod >> tkg >> tkm)
	{
        cant_entregas[tcliente][tprod] += 1;
        cant_peso[tcliente][tprod] += tkg;
        cant_km[tcliente][tprod] += tkm;
    }
    datos.close();

    kg_list(nom_prod, nom_cliente, cant_peso, cont_cliente, cod_cliente, cod_prod);
    list_cliente_variedad(nom_prod, nom_cliente, cod_cliente, cont_cliente, seguimiento, cant_km);
    mayor_cant_entrega(nom_prod, nom_cliente, cant_entregas, cant_km, cod_cliente, seguimiento, cont_cliente);
    return 0;
}