#ifndef HASH_H
#define HASH_H

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Hash
{
private:
	unordered_map <string, unordered_map<string,double>* > *mV;
	unordered_map <string, unordered_map<string,double>* >* GetMap();
public:
	Hash();
	~Hash();
	//overload operator () for access
	double operator ()(string row, string column);
	void operator ()(string row, string column, double value);
	//copia o grafo atual
	Hash* Copiar();
	//verifica se o grafo esta vazio
	bool Vazio();
	//imprime todos os vertices e arestas do grafo
	void Imprime();
	void PrintForAP();
	//Adiciona Vertice
	void AddVertice(string v);
	//Adiciona aresta
	void AddAresta(string a, string b, double peso=1);
	//retorna a lista de adjacentes ao vertice
	unordered_map<string,double>* ListaAdj(string v);
	//tamanho da lista de adjacentes
	int TamanhoListaAdj(string v);
	//retorna o numero de vertices
	int NumeroVertices();
	//verifica se um vertice @v1 é adjacente ao vertice @v2
	bool Adjacente(string v1, string v2);
	//altera aresta de um vertice para outro vertice
	void SetAresta(string v1, string v2, double novo_peso);
	//retorna a aresta entre um vertice v1 e vertice v2
	//0 se não houver aresta entre os vertices
	double GetAresta(string v1, string v2);
	//Altera todas arestas com um valor padrao
	void LimparArestas(double value_default = 0);
	//Retorna vertices
	vector<string> GetVertices();

	unordered_map<string,unordered_map<string,double>* >::iterator begin();
	unordered_map<string,unordered_map<string,double>* >::iterator end();
};

#endif