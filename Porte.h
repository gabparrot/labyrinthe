/**
 * \file Porte.h
 * \brief Ce fichier contient l'interface d'une porte.
 * \author IFT-2008
 * \version 0.1
 * \date janvier 2020
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
 * Elle peut prendre 5 valeurs : Rouge, Bleu, Jaune ou Vert ainsi que la
 * valeur "Aucun" qui est une valeur spéciale utilisée dans la fonction "trouveGagnant".
 */
	enum class Couleur { Rouge, Vert, Bleu, Jaune, Aucun };

//! La ligne qui suit sert à signifier au compilateur que la classe "Piece" existe.
//! On le fait, car la structure "Porte" comporte des pointeurs vers la classe "Piece", et vice versa.
class Piece;


/**
 * \class Porte
 * \brief Classe qui représente une porte d'une couleur donnée entre deux pièces
 */
class Porte
{
public:

	//! Constructeur par défaut
	Porte();

	//! Constructeur, en argument la couleur de la porte ainsi que la pièce de destination
	Porte(Couleur c, Piece * d);

	//! Constructeur de copie
	Porte(const Porte&);

	//! Un destructeur qui ne fera rien
	~Porte();

	//! Surcharge de l'opérateur =
	const Porte & operator =(const Porte&);

	//! Surcharge de l'opérateur ==
	bool operator ==(const Porte& source) const;

	//! Accesseur de la couleur d'une porte
	Couleur getCouleur() const;

	//! Accesseur de la piece de destination
	Piece * getDestination() const;


private:
	
	Couleur color; /*!< Couleur de la porte.*/
	/*!< Cette couleur spécifie en même temps quel est le joueur qui a le droit de franchir cette porte.*/
	
	Piece * destination; /*!< Vers où la porte mène.*/

};

}

#endif /* PORTE_H_ */
