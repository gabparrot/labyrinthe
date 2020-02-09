/**
 * \file Porte.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Porte
 * \author Étudiant(e)
 * \version 0.1
 * \date janvier 2020
 *
 */

#include "pch.h"
#include "Porte.h"

namespace TP1
{

    Porte::Porte() {};
	
    Porte::Porte(Couleur c, Piece* d) : color(c), destination(d) {};
	
    Porte::Porte(const Porte&)
    {
        //TODO ne sais pas comment implémenter sans nom d'argument
    }
    Porte::~Porte() {};
	
    const Porte& Porte::operator=(const Porte& source)
    {
	    if (this != &source)
	    {
            destination = source.getDestination();
            color = source.getCouleur();
	    }
    	
        return *this;
    }

    bool Porte::operator==(const Porte& source) const
    {
    	return((color == source.getCouleur() && destination == source.getDestination()) ? true: false);
    }

	Couleur Porte::getCouleur() const
	{
        return color;
	}

	Piece* Porte::getDestination() const
	{
        return destination;
	}



}
