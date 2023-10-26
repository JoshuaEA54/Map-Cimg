#pragma once
#include "Route.h"

template<typename T>
class Map
{
private:

	struct MapNodo {
		T route;
		MapNodo* next;
		MapNodo* prev;
		MapNodo(T _route) : route(_route), next(nullptr), prev(nullptr) {}
	};
	MapNodo* header;

	int amountOfRoutes;

public:
	Map() : header(nullptr), amountOfRoutes(0) {}

	MapNodo* getHeader() { return header; }
	int getAmountOfRoutes() { return amountOfRoutes; }

	void setHeader(MapNodo* _newHeader) { header = _newHeader; }
	void setAmountOfRoutes(int _amountOfRoutes) { this->amountOfRoutes = _amountOfRoutes; }

	void addRouteInTheList(T _route) {
		MapNodo* nodoAdded = new MapNodo(_route);
		MapNodo* aux = header;

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
		amountOfRoutes += 1;

		//memory part
		nodoAdded = nullptr;
		delete nodoAdded;
		aux = nullptr;
		delete aux;
	}

	void gameMethod() {
		CImgDisplay* window = new CImgDisplay(windowWidth, windowHeight, "Proyecto Progra 1", 0);
		CImg<unsigned char>* background = new CImg<unsigned char>;
		background->assign(windowWidth, windowHeight, 1, 3, 255);
		//////////////////////////////////////////////////////////////////////////////////

		const char* Image = "MyNewMap.png"; // Se iguala "menuImagen" a la imagen del menu
		background->load(Image); // Se carga "menuImagen" en "menu"

		bool editorMode = false;

	    Route<coordenates> tempRoute;

		///////////////////////////////////////////////////////////////////////////////////
		window->display(*background);

		while (!window->is_closed()) {
			
			float mouseX = window->mouse_x();
			float mouseY = window->mouse_y();
			cout << "X: " << mouseX << endl << "Y: " << mouseY << endl;

			if (!editorMode) {
				
				//addRoute buttom
				if (window->button() && mouseX > 37 && mouseY > 634 && mouseX < 304 && mouseY < 729) {

					string aux;
					cout << " Digite el nombre de la nueva ruta: ";
					cin >> aux;
					tempRoute.setNameOfRoute(aux);
					cout << " Ahora digite el inicio de la nueva ruta en el mapa..." << endl;

					// it would get inside the editor mode
					editorMode = true;
				}
			}
			else {
				if (window->button() && (mouseX > 323 && mouseY > 633 && mouseX < 595 && mouseY < 726) == false) {
					
					coordenates coords(mouseX, mouseY);
					tempRoute.addNodoInTheEnd(coords);
					//metodo de dibujar lineas, calcula la distancia entre nodos 
					tempRoute.drawRoute(background);

				}
				//end route buttom
				if (window->button() && mouseX > 323 && mouseY > 633 && mouseX < 595 && mouseY < 726) {
					Route<coordenates> aux;
					tempRoute = aux;//inicializo route

					editorMode = false;
					addRouteInTheList(tempRoute);

					// ya cuando tengo la ruta completamente creada y le doy al boton guardar				
				}
			}
			window->display(*background);
			window->wait();
		}
	}
};
