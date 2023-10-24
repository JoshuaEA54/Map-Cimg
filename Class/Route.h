#pragma once
#include <iostream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

const int windowWidth = 1368;
const int windowHeight = 690;

template<typename T>
class Route {
private:

	struct RouteNodo {
		T data;//coordenates for each nodo
		RouteNodo* next;
		RouteNodo* prev;
		RouteNodo(T _data) : data(_data), next(nullptr), prev(nullptr) {}

	};
	RouteNodo* header;
	string nameOfRoute;

	unsigned char* color;

	unsigned char Red[3] = { 255,0,0 };
	unsigned char Blue[3] = { 0,0,255 };
	unsigned char Yellow[3] = { 255,255,0 };

public:
	Route(): header(nullptr),nameOfRoute(""),color(Red){}
	~Route() {
		while (header) {
			RouteNodo* temp = header;
			header = header->next;
			temp->prev = nullptr;//para no tener memoria suelta
			temp->next = nullptr;// no importa hacer un puntero nullptr a nullptr de nuevo
			temp = nullptr;
			delete temp;
		}

	}

	void setNameOfRoute(string _nameOfRoute) { this->nameOfRoute = _nameOfRoute; }
	void setHeader(RouteNodo* newHeader) { header = newHeader; }
	void setColor(unsigned char* _color) { color = _color; }

	string getNameOfRoute() { return nameOfRoute; }
	RouteNodo* getHeader() { return header; }
	unsigned char* getColor() { return color; }

	void addNodoInTheEnd(T value) {
		RouteNodo* nodoAdded = new RouteNodo(value);
		RouteNodo* aux = header;

		if (!header) {
			header = nodoAdded;
		}
		else {// means that the head next is with a nodo
			while (aux->next) {
				aux = aux->next;
			}
			aux->next = nodoAdded;
			aux->next->prev = aux;
		}

		nodoAdded = nullptr;
		delete nodoAdded;
		aux = nullptr;
		delete aux;
	}

};

struct coordenates {
	float x;
	float y;
	coordenates() { x = -1; y = -1; }
	coordenates(float _x, float _y) : x(_x), y(_y) {}
	void setX(float _x) { this->x = _x; }
	void setY(float _y) { this->y = _y; }
	float getX() { return x; }
	float getY() { return y; }
};