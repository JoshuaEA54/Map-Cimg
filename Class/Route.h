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
	bool status;// selected or not

	unsigned char* color;

	unsigned char red[3] = { 255,0,0 };
	unsigned char blue[3] = { 0,0,255 };
	unsigned char yellow[3] = { 255,255,0 };

public:
	Route() : header(nullptr), nameOfRoute(""), color(red), status(false) {}
	Route(const Route& newRoute) :header(newRoute.header), nameOfRoute(newRoute.nameOfRoute), color(newRoute.color), status(newRoute.status) {}
	~Route() {
		while (header) {
			RouteNodo* temp = header;
			header = header->next;
			temp = nullptr;
			delete temp;
		}

	}

public:
	void setNameOfRoute(string _nameOfRoute) { this->nameOfRoute = _nameOfRoute; }
	void setHeader(RouteNodo* newHeader) { this->header = newHeader; }
	void setColor(unsigned char* _color) { this->color = _color; }
	void setStatus(bool newStatus) { this->status = newStatus; }

public:
	string getNameOfRoute() { return nameOfRoute; }
	RouteNodo* getHeader() { return header; }
	bool getStatus() { return status; }

public: //colors
	unsigned char* getColor() { return color; }
	unsigned char* getRed() { return red; }
	unsigned char* getYellow() { return yellow; }
	unsigned char* getBlue() { return blue; }

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
		if (header) {
			if (!header->next) {
				_background->draw_point(header->data.getX(), header->data.getY(), color);
			}
			while (aux->next) {
				_background->draw_line(aux->data.getX(), aux->data.getY(),
					aux->next->data.getX(), aux->next->data.getY(), color);

				aux = aux->next;
			}
		}

		aux = nullptr;
		delete aux;
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
		while (aux) {
			if (window->button() && (calculateDistance(mouseX, mouseY, aux->data) <= 10)) {//radio de 10 pixeles
				status = true;//this route is selected
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