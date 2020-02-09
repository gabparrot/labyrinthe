/**
 * \file Piece.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Piece
 * \author Étudiant(e)
 * \version 0.1
 * \date janvier 2020
 *
 */

#include "pch.h"
#include "Piece.h"

namespace TP1
{

    Piece::Piece() {}

    Piece::Piece(const std::string& nom) : nom(nom) {}

	Piece::Piece(const Piece& source)
    {
        *this = source;
    }

	Piece::~Piece()
    {
        portes.clear();
    }

	const Piece& Piece::operator=(const Piece& source)
	{
        portes.clear();
        portes = source.getPortes();
        parcourue = source.getParcourue();
        nom = source.getNom();
        distanceDuDebut = source.getDistanceDuDebut();

        return *this;
	}

	std::string Piece::getNom() const
	{
        return nom;
	}

	void Piece::setParcourue(bool p)
	{
        parcourue = p;
	}

    void Piece::setDistanceDuDebut(int d)
    {
        distanceDuDebut = d;
    }

	bool Piece::getParcourue() const
	{
        return parcourue;
	}

	const std::list<Porte>& Piece::getPortes() const
	{
        return portes;
	}

	int Piece::getDistanceDuDebut() const
	{
        return distanceDuDebut;
	}

	void Piece::ajoutePorte(const Porte& p)
	{
        portes.push_front(p);
	}






}
