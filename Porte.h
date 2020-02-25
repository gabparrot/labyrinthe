/**
 * \file Porte.h
 * \brief Ce fichier contient l'interface d'une porte.
 * \author Gabriel Chevrette-Parot, Gabrielle Lévêque Huot
 * \version 0.1
 * \date 24 février 2020
 *
 */

#pragma once

#ifndef PORTE_H_
#define PORTE_H_


namespace TP1
{
/**
 * \enum Couleur
 * \brief La couleur d'un joueur
 *
 * Couleur peut prendre cinq valeurs : Rouge, Bleu, Jaune ou Vert ou Aucun
 */
	enum class Couleur { Rouge, Vert, Bleu, Jaune, Aucun };

/*!
 * \class Piece
 * \brief classe repredetant les portes
 */
class Piece;


/*!
 * \class Porte
 * \brief classe représentant les portes
 * 
 * La classe qui représente une porte d'une couleur donnée entre deux pièces
 */
class Porte
{
public:

	/*! 
	 *  \brief Constructeur par défaut
	 */
	Porte();

	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe Porte
	 *
	 * \param c : couleur de la porte
	 * \param d : pièce de destination
	 */
	Porte(Couleur c, Piece * d);

	/*!
	 * \brief Constructeur de copie
	 *
	 * Constructeur copie de la classe Porte
	 *
	 * \param Porte : un objet Porte
	 */
	Porte(const Porte&);

	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe Porte qui ne fera rien
	 *
	 */
	~Porte();

	/*!
	 * \brief Surchage
	 *
	 * Surcharge de l'opérateur =
	 *
	 * \param Porte : un objet Porte
	 */
	const Porte& operator =(const Porte&);

	/*!
	 * \brief Surchage
	 *
	 * Surcharge de l'opérateur ==
	 *
	 * \param source : un objet Porte
	 */
	bool operator ==(const Porte& source) const;

	/*!
	 * \brief Accesseur
	 *
	 * Accesseur de la couleur d'une porte
	 */
	Couleur getCouleur() const;

	/*!
	 * \brief Accesseur
	 *
	 * Accesseur de la piece de destination
	 */
	Piece * getDestination() const;


private:
	
	Couleur color; /*!< Vers où la porte mène.*/
	Piece * destination; /*!< Couleur de la porte.*/
	/*!< Cette couleur spécifie en même temps quel est le joueur qui a le droit de franchir cette porte.*/

};

}

#endif /* PORTE_H_ */
