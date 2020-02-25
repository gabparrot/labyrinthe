/**
 * \file Porte.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Porte
 * \author Gabriel Chevrette-Parot, Gabrielle Lévêque Huot
 * \version 0.1
 * \date 24 février 2020
 *
 */

#include "pch.h"
#include "Porte.h"

namespace TP1
{
     /**
     * \brief Constructeur de la classe Porte
     * \return Un objet Porte
     */
    Porte::Porte() {}
	
     /**
     * \brief Constructeur de la classe Porte
     * \param[in] Couleur c : couleur de la porte
     * \param[in] Piece d : pièce de destination
     * \return Un objet Porte
     */
    Porte::Porte(Couleur c, Piece* d) : color(c), destination(d) {}
	
     /**
     * \brief Constructeur de copie de la classe Porte
     * \param[in] Porte source
     * \return Objet Porte
     */
    Porte::Porte(const Porte& source)
    {
        *this = source;
    }
	
     /**
     * \brief Destructeur de la classe Porte
     */
    Porte::~Porte() {};
	
     /**
     * \brief surcharge de l'opérateur = entre la destination et la couleur de la porte
     * \param[in] Porte source
     * \return un objet Porte
     */
    const Porte& Porte::operator=(const Porte& source)
    {

	    if (this != &source)
	    {
            destination = source.getDestination();
            color = source.getCouleur();
	    }
    	
        return *this;
    }

     /**
     * \brief surcharge de l'opérateur == correspondance entre la couleur de la porte et la destination
     * \param[in] Porte source
     * \return true si la porte correspond selon sa couleur et sa destination sinon false 
     */
    bool Porte::operator==(const Porte& source) const
    {
    	return((color == source.getCouleur() && destination == source.getDestination()) ? true: false);
    }

    /**
     * \brief Fonction accesseur récupérant la couleur de la Porte
     * \return Couleur porte
     */
	Couleur Porte::getCouleur() const
	{
        return color;
	}

     /**
     * \brief Fonction accesseur récupérant la destination de la Porte
     * \return Piece Porte
     */
	Piece* Porte::getDestination() const
	{
        return destination;
	}

}
