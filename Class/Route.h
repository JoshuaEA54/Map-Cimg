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
	Route() : header(nullptr), nameOfRoute(""), color(red) {}
	Route(const Route& newRoute):header(newRoute.header),nameOfRoute(newRoute.nameOfRoute),color(newRoute.color){}
	
	~Route() {
		while (header) {
			RouteNodo* temp = header;
			header = header->next;
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
		
		while (aux->next) {
			_background->draw_line(aux->data.getX(), aux->data.getY(),
				aux->next->data.getX(), aux->next->data.getY(), color);

			aux = aux->next;
		}

	}

	void drawCirclesInRoute(CImg<unsigned char>* _background) {

		RouteNodo* aux = header;
		while (aux) {
			_background->draw_circle(aux->data.getX(), aux->data.getY(), 10, color);
			aux = aux->next;
		}
		delete aux;
	}

	void runThroughRoute(CImgDisplay* window, float mouseX, float mouseY, CImg<unsigned char>* _background) {

		RouteNodo* aux = header;
		while (aux) {//ojito con el while
			if (window->button() && (calculateDistance(mouseX, mouseY, aux->data) <= 10)) {
				cout << " si esta en rango" << endl;
				drawCirclesInRoute(_background);
			}
			aux = aux->next;
		}
		delete aux;
	}

	int calculateDistance(int mouseX, int mouseY, T chords) {
		return sqrt(pow(chords.getX() - mouseX, 2) + pow(chords.getY() - mouseY, 2));
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