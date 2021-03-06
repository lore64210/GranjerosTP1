/*
 * interfazUsuario.cpp
 *
 *  Created on: 28 abr. 2018
 *      Author: administrador
 */

#include "interfazUsuario.h"
#include <cstdlib>
#include <iostream>


using namespace std;

InterfazUsuario::InterfazUsuario() {

	this->menuPrincipal = NULL;
	this->menuPartida = NULL;
}

void InterfazUsuario::mostrarBienvenida(){

	cout << "GRANJEROS 1.0" << endl << endl;
}

void InterfazUsuario::solicitarNombresJugadores(unsigned int cantidadJugadores, Lista<string>& listaNombres){

	cout << "Ingresa los nombres de los jugadores!" << endl << endl;
	for(unsigned int i = 0; i < cantidadJugadores; i++){

		cout << "Nombre jugador " + i << ": ";
		cout.flush();

		string nombreJugador;
		cin >> nombreJugador;
		listaNombres.agregar(nombreJugador);
	}
}

void InterfazUsuario::cargarMenuPrincipal(){

	this->menuPrincipal = crearMenuPrincipal();
	this->menues.apilar(this->menuPrincipal);
}

void InterfazUsuario::cargarMenuPartida(){

	this->menuPartida = crearMenuPartida();
	this->menues.apilar(menuPartida);
}

Menu* InterfazUsuario::obtenerMenuActual(){
	return this->menues.obtenerTope();
}

void InterfazUsuario::mostrarMenuActual(){

	if(!this->menues.estaVacia()){
		this->obtenerMenuActual()->mostrar();
	}
}

void InterfazUsuario::irAMenuAnterior(){

	this->menues.desapilar();
}

unsigned int InterfazUsuario::solicitarOpcion(){

	return this->obtenerMenuActual()->solicitarOpcion();
}

ResultadoOpcion* InterfazUsuario::ejecutarOpcion(unsigned int iMenuItem){

	ResultadoOpcion* respuesta = this->obtenerMenuActual()->ejecutarOpcion(iMenuItem);

	if(respuesta->obtenerTipo() == resultadoOpcion::SUBMENU){
		this->agregarMenu(respuesta->obtenerSubMenu());
	}

	return respuesta;
}

bool InterfazUsuario::salir(){
	return this->menues.estaVacia();
}

void InterfazUsuario::mostrarDespedida(){

	cout << "CHAU!" << endl << endl;
}

void InterfazUsuario::agregarMenu(Menu* menu){
	this->menues.apilar(menu);
}

Menu* InterfazUsuario::crearMenuPrincipal() {

	Menu* menu = new Menu("MENU PRINCIPAL", 2);
	Menu* menuConfiguracion = crearMenuConfiguracion();

	menu->cambiarOpcion(1, OpcionMenu("Configuracion", menuConfiguracion));
	menu->cambiarOpcion(2, OpcionMenu("Jugar", accion::JUGAR));

	return menu;
}

Menu* InterfazUsuario::crearMenuConfiguracion() {

	Menu* menu = new Menu("CONFIGURACION", 4);

	menu->cambiarOpcion(1, OpcionMenu("Cambiar Cantidad de Jugadores",
									  accion::CAMBIAR_CANTIDAD_JUGADORES,
									  "Indique la cantidad de jugadores"));

	menu->cambiarOpcion(2, OpcionMenu("Cambiar Parametro N",
									  accion::CAMBIAR_PARAMETRO_N,
									  "Indique el nuevo valor del parametro: "));

	menu->cambiarOpcion(3, OpcionMenu("Cambiar Parametro M",
									  accion::CAMBIAR_PARAMETRO_M,
									  "Indique el nuevo valor del parametro"));

	menu->cambiarOpcion(4, OpcionMenu("Cambiar Cantidad de Turnos",
									  accion::CAMBIAR_CANTIDAD_TURNOS,
									  "Indique la cantidad de turnos a jugar en cada partida"));

	return menu;
}

Menu* InterfazUsuario::crearMenuPartida() {

	Menu* menu = new Menu("ACCIONES", 9);

	menu->cambiarOpcion(1, OpcionMenu("Sembrar",
									  accion::SEMBRAR,
									  "Indique, separando con espacios, las coordenadas de la parcela y el cultivo a sembrar (ej: 1,2 A)"));

	menu->cambiarOpcion(2, OpcionMenu("Cosechar",
									  accion::COSECHAR,
									  "Indique las coordenadas de la parcela a cosechar (ej: 1,2)"));

	menu->cambiarOpcion(3, OpcionMenu("Regar",
									  accion::REGAR,
									  "Indique las coordenadas de la parcela a regar (ej 1,2)"));

	menu->cambiarOpcion(4, OpcionMenu("Enviar Cosecha",
									  accion::ENVIAR_COSECHA,
									  "Indique el nombre del cultivo de la cosecha a enviar a destino (ej: A)"));

	menu->cambiarOpcion(5, OpcionMenu("Comprar Terreno",
										accion::COMPRAR_TERRENO));

	menu->cambiarOpcion(6, OpcionMenu("Vender Terreno",
									  accion::VENDER_TERRENO,
									  "Indique numero de terreno a vender (ej: 3)"));

	menu->cambiarOpcion(7, OpcionMenu("Ampliar capacidad Tanque",
								  	  accion::COMPRAR_CAPACIDAD_AGUA));

	menu->cambiarOpcion(8, OpcionMenu("Ampliar Almacen",
			  	  	  	  	  	  	  accion::COMPRAR_CAPACIDAD_ALMACEN));

	menu->cambiarOpcion(9, OpcionMenu("Finalizar Turno",
				  	  	  	  	  	  accion::FINALIZAR_TURNO));

	return menu;
}

InterfazUsuario::~InterfazUsuario(){

	if(this->menuPartida != NULL){
			delete this->menuPartida;
	}

	if(this->menuPrincipal != NULL){
		delete this->menuPrincipal;
	}
}

