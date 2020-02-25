/**
 * \file Piece.h
 * \brief Ce fichier contient l'interface d'une pièce.
 * \author Gabriel Chevrette-Parot, Gabrielle Lévêque Huot
 * \version 0.1
 * \date 24 février 2020
 *
 */

#pragma once


#ifndef PIECE_H_
#define PIECE_H_

#include <string>    // Pour le nom de la pièce
#include <list>	     // Pour utiliser la liste de la STL

#include "Porte.h"

namespace TP1
{
/*!
 * \class Piece
 * \brief classe représentant les Pièces
 *
 * La classe qui représentant une pièce dans un labyrinthe
 */
class Piece
{
public:

	/*!
	 *  \brief Constructeur par défaut
	 */
	Piece();

	/*!
	 * \brief Surchage
	 *
	 * Surcharge du constructeur
	 *
	 * \param nom : le nom de la pièce
	 */
	Piece(const std::string & nom);

	/*!
	 * \brief Constructeur de copie
	 *
	 * Constructeur copie de la classe Piece
	 *
	 * \param source : un objet Porte
	 */
	Piece(const Piece & source);

	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe Piece
	 *
	 */
	~Piece();

	/*!
	 * \brief Surchage
	 *
	 * Surcharge de l'opérateur =
	 *
	 * \param source : un objet Piece
	 */
	const Piece & operator=(const Piece & source);

	/*!
	 * \brief Accesseur
	 *
	 * Accesseur du nom d'une pièce
	 */
	std::string getNom() const;

	/*!
	 * \brief Initialise l'attribut parcourue
	 *
	 * Initialise l'attribut parcourue à true ou false
	 *
	 * \param p : true ou false
	 */
	void setParcourue(bool p);

	/*!
	 * \brief Initialise l'attribut distanceDuDebut
	 *
	 * Initialiser l'attribut distanceDuDebut
	 *
	 * \param d : entier standard
	 */
	void setDistanceDuDebut(int d);

	/*!
	 * \brief Accéder au membre parcourue
	 *	
	 * Méthode qui permet d'ajouter si un parcours est parcouru ou non
	 *
	 * True si parcourue ou False non parcourue
	 */
	bool getParcourue() const;

	/*!
	 * \brief Accesseur
	 *
	 * Accéder à la liste des portes qui partent de la pièce
	 *
	 */
	const std::list<Porte> & getPortes() const;

	/*!
	 * \brief Accesseur
	 *
	 * Accéder au membre distanceDuDebut
	 *
	 */
	int getDistanceDuDebut() const;

	/*!
	 * \brief Accesseur
	 *
	 * Ajoute une porte à la liste des portes qui partent de la pièce
	 *
	 * \param p : un objet Porte
	 */
	void ajoutePorte(const Porte & p);

private:
	std::list<Porte> portes; /*!< Les portes qui partent de la pièce. */
	/*!< Cette liste peut ne pas contenir toutes les portes qui
	communiquent avec la pièce. Une partie de ces portes peut être placée dans la liste de portes
	de l'autre pièce associée à la porte.*/

	bool parcourue; /*!< Indique si la pièce a été parcourue*/
	/*!< Le champ "parcourue" sert uniquement à la méthode solutionner() de la classe labyrinthe, afin de ne pas passer
	plusieurs fois par une même pièce et risquer de tourner en rond, et donc boucler sans fin. */

	std::string nom; /*!< Le nom de la pièce. Il doit être unique pour un même labyrinthe.*/
	int distanceDuDebut; /*!< Le nombre de déplacements qu'il est nécessaire d'effectuer depuis la pièce de départ pour se rendre à cette pièce. */ 

};

}

#endif /* PIECE_H_ */
