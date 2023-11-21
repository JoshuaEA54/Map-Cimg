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
	fstream file;

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

	void addRouteInTheList(T& _route) {
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
		

	}

	void addRouteButton(CImgDisplay* window, float mouseX, float mouseY, T& tempRoute, bool& editorMode)
	{
		if (window->button() && mouseX > 37 && mouseY > 634 && mouseX < 304 && mouseY < 729) {
			system("cls");
			string aux;
			cout << " Digite el nombre de la nueva ruta: ";
			getline(cin, aux);//gets the entire line
			tempRoute.setNameOfRoute(aux);
			cout << " Ahora dibuje el inicio de la nueva ruta en el mapa..." << endl;

			// it would get inside the editor mode
			editorMode = true;
		}
	}

	void endRouteButton(CImgDisplay* window, float mouseX, float mouseY, T& tempRoute, bool& editorMode)
	{
		if (window->button() && mouseX > 323 && mouseY > 633 && mouseX < 595 && mouseY < 726) {

			editorMode = false;
			addRouteInTheList(tempRoute);
			amountOfRoutes += 1;

			Route<coordenates> aux;
			aux.setColor(tempRoute.getColor());
			aux.setColorC(tempRoute.getColorC());//to actualize the value of the string
			tempRoute = aux;//inicializo route

			// ya cuando tengo la ruta completamente creada y le doy al boton guardar				
		}
	}

	void deleteVertexButton(CImgDisplay* window, float mouseX, float mouseY, bool& deleteNodo, CImg<unsigned char>*& _background) {
		if (header) {	
			if (window->button() && mouseX > 1009 && mouseY > 526 && mouseX < 1324 && mouseY < 611) {
				//delete vertex button
				deleteNodo = true;

				//draw circles in all the routes
				MapNodo* aux = header;
				while (aux) {
					aux->route.drawCirclesInRoute(_background);//to know that you pressed the button
					aux = aux->next;
				}

			}
		}
	}

	void deleteRouteButton(CImgDisplay* window, float mouseX, float mouseY, CImg<unsigned char>*& _background, const char* Image) {
		if (header != nullptr) {
			MapNodo* aux = header;
			while (aux->route.getStatus() == false && aux->next != nullptr) {
				aux = aux->next;
			}
			if (aux->route.getStatus() == true && window->button() && mouseX > 657 && mouseY > 642 && mouseX < 971 && mouseY < 722) {
				//delete button
				aux->route.deleteRoute();
				amountOfRoutes--;

				reDrawAllRoutes(_background, Image);
				aux->route.setStatus(false);
			}
		}
	}

	void showOrHideButton(CImgDisplay* window, float mouseX, float mouseY, CImg<unsigned char>*& _background, const char* Image) {
		if (header != nullptr) {
			MapNodo* aux = header;
			while (aux->route.getStatus() == false && aux->next != nullptr) {
				aux = aux->next;
			}
			if (aux->route.getStatus() == true && window->button() && mouseX > 1014 && mouseY > 643 && mouseX < 1322 && mouseY < 724) {
				//show/hidebutton

				if (!aux->route.getHideOrNot()) {
					aux->route.setHideOrNot(true);
				}
				else {
					aux->route.setHideOrNot(false);
				}

				//this method verifies the status of hideOrNot
				aux->route.drawRoute(_background);

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
							aux->route.setColorC("yellow");
						}
						else if (i == 1) {
							aux->route.setColor(aux->route.getRed());
							aux->route.setColorC("red");
						}
						else {
							aux->route.setColor(aux->route.getBlue());
							aux->route.setColorC("blue");
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
		//this is to borrow the things I deleted
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

	void drawingOnWindow(CImgDisplay* window, float mouseX, float mouseY, T& tempRoute, CImg<unsigned char>*& background)
	{
		if (window->button() && (mouseX > 323 && mouseY > 633 && mouseX < 595 && mouseY < 726) == false) {

			coordenates coords(mouseX, mouseY);
			tempRoute.addNodoInTheEnd(coords);
			tempRoute.setAmountVertex(tempRoute.getAmountVertex() + 1);
			//metodo de dibujar lineas 
			tempRoute.drawRoute(background);
		}
	}

	void deleteVertex(CImgDisplay* window, float mouseX, float mouseY, bool& deleteNodo)
	{
		MapNodo* aux = header;
		while (aux) {
			aux->route.clickUser(window, mouseX, mouseY, deleteNodo);
			aux = aux->next;
		}
	}

	void saveRoutes(CImgDisplay* window, float mouseX, float mouseY) {

		if (window->button() && mouseX > 17 && mouseY > 18 && mouseX < 256 && mouseY < 96) {
			file.open("Routes.txt", ios::out);

			// See if the file opened correctly
			if (!file.is_open()) {
				cout << "No se pudo abrir el archivo." << endl;
				exit(1);
			}
			file << amountOfRoutes << endl;
			//this appears just once
			if (header) {
				MapNodo* aux = header;
				while (aux) {
					//2 //cantidad de rutas
					//3 //cantidad de vertices de la ruta 1
					//San Jose,red, // nombre y color
					//456,324,345,67,21,45, // todos los vertices separados por comas 
					//2 // cantidad de vertices de la ruta 2
					//Nose nombre,blue,
					//32,35,556,700,
					file << aux->route.getAmountVertex() << endl;
					file << aux->route.getNameOfRoute() << "," << aux->route.getColorC() << "," << endl;
					aux->route.routeCoordenates(file);
					file << endl;

					aux = aux->next;
				}
			}
			else {
				file << " There is no routes on the map " << endl;
			}
			file.close();
		}
	}

	void loadRoutes(CImgDisplay* window, float mouseX, float mouseY, CImg<unsigned char>*& _background, const char* Image) {
		if (window->button() && mouseX > 1105 && mouseY > 18 && mouseX < 1347 && mouseY < 96) {
			string name = "";
			cout << " Digite el nombre del archivo: ";
			getline(cin, name);
			try {
				file.open(name + ".txt", ios::in);//open it but in lecture mode
				if (file.is_open()) {
					deleteAllRoutes();//check
					loadRoutesFromFile(); //method shows the routes that are on the file
					file.close();
					reDrawAllRoutes(_background, Image);
				}
				else {
					throw(name);
				}
			}
			catch (string name) {
				cout << "El archivo " << name << " no existe o no se pudo abrir..." << endl;
			}
		}
	}

	void deleteAllRoutes() {

		while (header) {
			header->route.deleteRoute();
			if (header) {
				delete header->prev;
				header->prev = nullptr;
				if (!header->next) {
					delete header;
					header = nullptr;
				}
				if (header) {
					header = header->next;
				}
			}

		}
		amountOfRoutes = 0;
	}

	void loadRoutesFromFile() {
		//agarro los atributos del archivo
		//  2
		//  4
		//	ruta de san jose, yellow,
		//	276, 531, 352, 339, 534, 191, 718, 203,
		//	2
		//	nose, red,
		//	646, 384, 799, 290,

        string line = "";

		getline(file, line);
		int pos = line.find(" ");
		amountOfRoutes = stoi(line.substr(0, pos));
		for (int i = 0; i < amountOfRoutes; i++) {// las vueltas de cada ruta
            Route<coordenates> newRoute;

			getline(file, line);
			pos = line.find(" ");
			newRoute.setAmountVertex(stoi(line.substr(0, pos)));//that is gonna help for another for

			getline(file, line);
			pos = line.find(",");
			newRoute.setNameOfRoute(line.substr(0, pos));

			line.erase(0, pos + 1);
			pos = line.find(",");

			newRoute.setColor(line.substr(0, pos));
			
			getline(file, line);// los puntos

			for (int j = 0; j < newRoute.getAmountVertex(); j++) {
				int x = 0, y = 0;

				pos = line.find(",");
				x = stoi(line.substr(0, pos));
				line.erase(0, pos + 1);

				pos = line.find(",");
				y = stoi(line.substr(0, pos));
				line.erase(0, pos + 1);

				coordenates aux(x, y);
				newRoute.addNodoInTheEnd(aux);//añado los vertices
			}
			
			addRouteInTheList(newRoute);
			
		}

	}

	void gameMethod() {
		CImgDisplay* window = new CImgDisplay(windowWidth, windowHeight, "Proyecto Progra 1", 0);
		CImg<unsigned char>* background = new CImg<unsigned char>;
		background->assign(windowWidth, windowHeight, 1, 3, 255);

		//////////////////////////////////////////////////////////////////////////////////

		const char* Image = "MyNewMap2.png";
		background->load(Image);

		bool editorMode = false;//used for the addRouteButton
		bool deleteNodo = false;//used for the deleteVertexButton

		Route<coordenates> tempRoute;

		///////////////////////////////////////////////////////////////////////////////////
		window->display(*background);

		while (!window->is_closed()) {

			float mouseX = window->mouse_x();
			float mouseY = window->mouse_y();

			/*system("cls");
			cout << "X: " << mouseX << endl << "Y: " << mouseY << endl;*/

			if (!editorMode) {
				if (!deleteNodo) {
					//addRoute buttom
					addRouteButton(window, mouseX, mouseY, tempRoute, editorMode);

					//see if the mouse touches a vertex
					detectMouseInRoutes(window, mouseX, mouseY, background);

					//colors palet with the changes if you touch it
					detectMouseInColors(window, mouseX, mouseY, background, Image);

					deleteRouteButton(window, mouseX, mouseY, background, Image);

					showOrHideButton(window, mouseX, mouseY, background, Image);

					deleteVertexButton(window, mouseX, mouseY, deleteNodo, background);

					saveRoutes(window, mouseX, mouseY);

					loadRoutes(window, mouseX, mouseY, background, Image);
				}
				else {
					deleteVertex(window, mouseX, mouseY, deleteNodo);
					if (!deleteNodo)
						reDrawAllRoutes(background, Image);
				}
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
