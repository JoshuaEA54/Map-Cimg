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

	~Map() {
		while (header) {
			MapNodo* temp = header;
			header = header->next;
			if (header) {
				header->prev = nullptr;
			}
			temp->next = nullptr;
			temp->prev = nullptr; 
			delete temp;
		}
	}

	MapNodo* getHeader() { return header; }
	int getAmountOfRoutes() { return amountOfRoutes; }

	void setHeader(MapNodo* _newHeader) { header = _newHeader; }
	void setAmountOfRoutes(int _amountOfRoutes) { this->amountOfRoutes = _amountOfRoutes; }

	void addRouteInTheList(T _route) {
		MapNodo* nodoAdded = new MapNodo(_route);

		if (!header) {
			header = nodoAdded;
			
		}
		else {// means that the head next is with a nodo
			MapNodo* aux = header;
			while (aux->next) {
				aux = aux->next;
			}
			aux->next = nodoAdded;
			aux->next->prev = aux;
		}
		amountOfRoutes += 1;

	}

	void addRouteButton(CImgDisplay* window, float mouseX, float mouseY, Route<coordenates>& tempRoute, bool& editorMode)
	{
		if (window->button() && mouseX > 37 && mouseY > 634 && mouseX < 304 && mouseY < 729) {
			system("cls");
			string aux;
			cout << " Digite el nombre de la nueva ruta: ";
			cin >> aux;
			tempRoute.setNameOfRoute(aux);
			cout << " Ahora dibuje el inicio de la nueva ruta en el mapa..." << endl;

			// it would get inside the editor mode
			editorMode = true;
		}
	}

	void endRouteButton(CImgDisplay* window, float mouseX, float mouseY, Route<coordenates>& tempRoute, bool& editorMode)
	{
		if (window->button() && mouseX > 323 && mouseY > 633 && mouseX < 595 && mouseY < 726) {

			editorMode = false;
			addRouteInTheList(tempRoute);

			Route<coordenates> aux;
			aux.setColor(tempRoute.getColor());
			tempRoute = aux;//inicializo route

			// ya cuando tengo la ruta completamente creada y le doy al boton guardar				
		}
	}

	void deleteRouteButton(CImgDisplay* window, float mouseX, float mouseY,CImg<unsigned char>*& _background, const char* Image) {
		if (header != nullptr) {
			MapNodo* aux = header;
			while (aux->route.getStatus() == false && aux->next != nullptr) {
				aux = aux->next;
			}
			if (aux->route.getStatus() == true && window->button() && mouseX > 657 && mouseY > 642 && mouseX < 971 && mouseY < 722) {
				//delete button
				aux->route.deleteRoute();
				reDrawAllRoutes(_background, Image);
				aux->route.setStatus(false);
			}
		}
	}

	void detectMouseInRoutes(CImgDisplay* window, float mouseX, float mouseY, CImg<unsigned char>*& _background) {

		MapNodo* aux = header;
		while (aux) {
			aux->route.runThroughRoute(window, mouseX, mouseY, _background);
			aux = aux->next;
		}

	}

	void detectMouseInColors(CImgDisplay* window, int mouseX, int mouseY, CImg<unsigned char>*& background, const char* Image) {
		if (header != nullptr) {
			MapNodo* aux = header;
			while (aux->route.getStatus() == false && aux->next != nullptr) {
				aux = aux->next;
			}
			if (aux->route.getStatus() == true && window->button() && mouseX > 1255 && mouseY > 280 && mouseX < 1325 && mouseY < 500) {
				//esta condicion para saber que ademas de tener el estado tiene que tocar la paleta de colores

				int X = 1255;
				int X2 = 1325;  //area of each rectangle
				int Y = 280;
				int Y2 = 350;

				for (int i = 0; i < 3; i++) {
					if (window->button() && mouseX > X && mouseY > Y && mouseX < X2 && mouseY < Y2) {

						if (i == 0) {
							aux->route.setColor(aux->route.getYellow());
						}
						else if (i == 1) {
							aux->route.setColor(aux->route.getRed());
						}
						else {
							aux->route.setColor(aux->route.getBlue());
						}

						aux->route.setStatus(false);//important to do not keep doing changes to this route
					}
					Y = Y + 75;
					Y2 = Y2 + 75;
				}
				reDrawAllRoutes(background, Image);
			}

		}

	}

	void reDrawAllRoutes(CImg<unsigned char>*& _background, const char* Image) {
		//this is to borrow the circles
		_background->load(Image);

		//and draw all the routes again
		if (header) {
			MapNodo* aux = header;
			while (aux) {
				aux->route.drawRoute(_background);
				aux = aux->next;
			}
		}
	}

	void drawingOnWindow(CImgDisplay* window, float mouseX, float mouseY, Route<coordenates>& tempRoute, CImg<unsigned char>*& background)
	{
		if (window->button() && (mouseX > 323 && mouseY > 633 && mouseX < 595 && mouseY < 726) == false) {

			coordenates coords(mouseX, mouseY);
			tempRoute.addNodoInTheEnd(coords);
			//metodo de dibujar lineas 
			tempRoute.drawRoute(background);
		}
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

			/*system("cls");
			cout << "X: " << mouseX << endl << "Y: " << mouseY << endl;*/

			if (!editorMode) {

				//addRoute buttom
				addRouteButton(window, mouseX, mouseY, tempRoute, editorMode);

				//see if the mouse touches a vertex
				detectMouseInRoutes(window, mouseX, mouseY, background);

				//colors palet with the changes if you touch it
				detectMouseInColors(window, mouseX, mouseY, background, Image);

				deleteRouteButton(window, mouseX, mouseY, background, Image);
			}
			else {

				drawingOnWindow(window, mouseX, mouseY, tempRoute, background);

				//end route buttom
				endRouteButton(window, mouseX, mouseY, tempRoute, editorMode);
			}

			window->display(*background);
			window->wait();
		}
	}



};
