#pragma once
#include <iostream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

const int windowWidth = 1368;
const int windowHeight = 767;

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

	unsigned char red[3] = { 255,0,0 };
	unsigned char blue[3] = { 0,0,255 };
	unsigned char yellow[3] = { 255,255,0 };

public:
	Route(): header(nullptr),nameOfRoute(""),color(red){}
	Route(const Route& newRoute) : header(nullptr), nameOfRoute(""), color(newRoute.color){}
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
	void drawRoute(CImg<unsigned char>* _background) {
		RouteNodo* aux = header;
		if (!header->next && header) {
			_background->draw_point(header->data.getX(), header->data.getY(), color);
		}
		//unsigned char redd[] = { 255,0,0 };
		while (aux->next) {
			_background->draw_line(aux->data.getX(), aux->data.getY(),
				aux->next->data.getX(), aux->next->data.getY(), color);//color
			//_background->draw_point(aux->data.getX(), aux->data.getY(),color)
			//el problema debe estar en el color
			
			aux = aux->next;
		}
		
	}

};

struct coordenates {
	float x;
	float y;
	coordenates() = delete;
	coordenates(float _x, float _y) : x(_x), y(_y) {}
	void setX(float _x) { this->x = _x; }
	void setY(float _y) { this->y = _y; }
	float getX() { return x; }
	float getY() { return y; }
};