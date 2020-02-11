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
     /**
     * \brief Constructeur de la classe Piece
     * \return Un objet Piece
     */
    Piece::Piece() {}

     /**
     * \brief Surcharge du constructeur
     */
    Piece::Piece(const std::string& nom) : 
        nom(nom) 
    {
    }

     /**
     * \brief Constructeur de copie de la classe Piece
     */
	Piece::Piece(const Piece& source)
    {
        *this = source;
    }

     /**
     * \brief Destructeur de la classe Piece
     */
	Piece::~Piece()
    {
        portes.clear();
    }


	//TODO P2 Valider que 2 pièces n'ont pas le même nom ?
     /**
     * \brief surcharge de l'opérateur = correspondance entre les pièces et les portes
     * \param[in] Piece source
     * \return Piece avec les portes correspondantes
     */
	const Piece& Piece::operator=(const Piece& source)
	{
        portes.clear();
        portes = source.getPortes();
        parcourue = source.getParcourue();
        nom = source.getNom();
        distanceDuDebut = source.getDistanceDuDebut();

        return *this;
	}

    /**
     * \brief Fonction accesseur récupérant le nom d'une pièce
     */
	std::string Piece::getNom() const
	{
        return nom;
	}

    /**
     * \brief Initialiser l'attribut parcourue à true ou false
     */
	void Piece::setParcourue(bool p)
	{
        parcourue = p;
	}

    /**
     * \brief Initialiser l'attribut distanceDuDebut
     */
    void Piece::setDistanceDuDebut(int d)
    {
        distanceDuDebut = d;
    }

    /**
     * \brief Accéder au membre parcourue
     * \return True si parcourue ou False non parcourue
     */
	bool Piece::getParcourue() const
	{
        return parcourue;
	}

     /**
     * \brief Accéder à la liste des portes qui partent de la pièce
     * \return Une liste contenant les portes qui partent de la pièce
     */
	const std::list<Porte>& Piece::getPortes() const
	{
        return portes;
	}

     /**
     * \brief Fonction accesseur récupérant la distance du début
     */
	int Piece::getDistanceDuDebut() const
	{
        return distanceDuDebut;
	}

    
     /**
     * \brief Ajouter une porte à la liste des portes qui partent de la pièce
     * \param[in] Pièce p
     */
	void Piece::ajoutePorte(const Porte& p)
	{
        portes.push_front(p);
	}






}
