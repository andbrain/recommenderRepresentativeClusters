#include "hash.h"

Hash::Hash()
{
	mV = new unordered_map<string, unordered_map<string,double>* >();
}

Hash::~Hash()
{
	for (unordered_map<string,unordered_map<string,double>* >::iterator it = mV->begin(); it!=mV->end(); ++it)
	{
		delete(it->second);
	}

	delete(mV);
}

void Hash::operator ()(string row, string column, double value)
{
	SetAresta(row,column, value);
}

double Hash::operator ()(string row, string column)
{
	return mV->at(row)->at(column);
}

unordered_map <string, unordered_map<string,double>* >* Hash::GetMap()
{
	return this->mV;
}

Hash* Hash::Copiar()
{
	Hash *copia = new Hash();
	unordered_map<string,double> *v;

	for (unordered_map<string,unordered_map<string,double>* >::iterator it = mV->begin(); it!=mV->end(); ++it)
	{
		v = new unordered_map<string,double>();

		for (unordered_map<string,double>::iterator it_aresta = it->second->begin(); it_aresta!=it->second->end(); ++it_aresta)
		{
			v->insert(pair<string,double>(it_aresta->first, it_aresta->second));
		}

		copia->GetMap()->insert(pair<string, unordered_map<string,double>* >(it->first, v));
	}

	return copia;
}

void Hash::Imprime()
{
	unordered_map<string,double>* arestas;

	for (unordered_map<string,unordered_map<string,double>* >::iterator it = mV->begin(); it!=mV->end(); ++it)
	{
		cout << it->first << " =>" << endl;    		
		arestas = it->second;

		for (unordered_map<string,double>::iterator it_aresta = arestas->begin(); it_aresta!=arestas->end(); ++it_aresta)
		{
			cout << "\t\t[" << it_aresta->first << "][" << it_aresta->second << "]" << endl;
		}
	}
}

void Hash::PrintForAP()
{
	string simFile = "Similarities.txt";
	fstream fs(simFile, ios::out);
	unordered_map<string,double>* arestas;

	for (unordered_map<string,unordered_map<string,double>* >::iterator it = mV->begin(); it!=mV->end(); ++it)
	{
		arestas = it->second;

		for (unordered_map<string,double>::iterator it_aresta = arestas->begin(); it_aresta!=arestas->end(); ++it_aresta)
		{
			fs << it->first << "  ";
			fs << it_aresta->first << "  " << it_aresta->second << endl;
		}
	}

	fs.close();

	cout << "Similarity Matrix file created: " << simFile << endl;
}

void Hash::AddVertice(string v)
{
	unordered_map<string, unordered_map<string,double>* >::iterator it = mV->begin();	
	mV->insert(it, pair<string,unordered_map<string,double>* >(v,new unordered_map<string,double>()));
}

bool Hash::Vazio()
{
	for (unordered_map<string,unordered_map<string,double>* >::iterator it = mV->begin(); it!=mV->end(); ++it)
	{
		if(it->second->size() != 0)
			return false;
	}

	return true;
}

void Hash::AddAresta(string a, string b, double peso)
{
		unordered_map<string,double> *v = mV->at(a);		
		unordered_map<string,double>::iterator it = v->begin();
		v->insert(it, pair<string,double>(b,peso));	
}

unordered_map<string,double>* Hash::ListaAdj(string v)
{
	unordered_map<string,double> *lista = NULL;
	unordered_map<string,unordered_map<string,double>* >::iterator it = mV->find(v);
		if(it != mV->end())
			lista = mV->at(v);
	return lista;
}

int Hash::TamanhoListaAdj(string v)
{
	unordered_map<string,double> *lista = ListaAdj(v);
	return lista->size();
}

int Hash::NumeroVertices()
{
	return mV->size();
}

bool Hash::Adjacente(string v1, string v2)
{
	unordered_map<string,double> *lista = ListaAdj(v1);
	unordered_map<string,double>::iterator it = lista->find(v2);
	if(it != lista->end())
		return true;

	return false;
}

void Hash::SetAresta(string v1, string v2, double novo_peso)
{
	unordered_map<string,double> *lista = ListaAdj(v1);

	if(lista != NULL)
	{
		unordered_map<string,double>::iterator it = lista->find(v2);
		if(it != lista->end())
			it->second = novo_peso;
	}
	else
	{
		AddVertice(v1);
		AddAresta(v1,v2,novo_peso);
	}
}

double Hash::GetAresta(string v1, string v2)
{
	double result = 0;
	unordered_map<string,double> *lista = ListaAdj(v1);
	if(lista != NULL)
	{
		unordered_map<string,double>::iterator it = lista->find(v2);
		if(it != lista->end())
			result = it->second;
	}
	
	return result;
}

void Hash::LimparArestas(double value_default)
{
	unordered_map<string,double>* arestas;

	for (unordered_map<string,unordered_map<string,double>* >::iterator it = mV->begin(); it!=mV->end(); ++it)
	{
		arestas = it->second;

		for (unordered_map<string,double>::iterator it_aresta = arestas->begin(); it_aresta!=arestas->end(); ++it_aresta)
		{
			it_aresta->second = value_default;
		}
	}
}

vector<string> Hash::GetVertices()
{
	vector<string> vertices;

	for (unordered_map<string,unordered_map<string,double>* >::iterator it = mV->begin(); it!=mV->end(); ++it)
	{
		vertices.push_back(it->first);
	}

	return vertices;
}

unordered_map<string,unordered_map<string,double>* >::iterator Hash::begin()
{
	return mV->begin();	
}

unordered_map<string,unordered_map<string,double>* >::iterator Hash::end()
{
	return mV->end();	
}


