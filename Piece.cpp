/**
 * \file Piece.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Piece
 * \author Gabriel Chevrette-Parot, Gabrielle Lévêque Huot
 * \version 0.1
 * \date 24 février 2020
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
     * \param[in] string nom
     * \return Objet Piece
     */
    Piece::Piece(const std::string& nom) : 
        nom(nom) 
    {
        parcourue = false;
        distanceDuDebut = 0;
    }

     /**
     * \brief Constructeur de copie de la classe Piece
     * \param[in] Piece source
     * \return Objet Piece
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
     * \brief Accesseur du nom d'une pièce
     * \return String nom d'une pièce
     */
	std::string Piece::getNom() const
	{
        return nom;
	}

    /**
     * \brief Initialise l'attribut parcourue à true ou false
     * \param[in] bool p
     */
	void Piece::setParcourue(bool p)
	{
        parcourue = p;
	}

    /**
     * \brief Initialiser l'attribut distanceDuDebut
     * \param[in] int d
     */
    void Piece::setDistanceDuDebut(int d)
    {
        distanceDuDebut = d;
    }

    /**
     * \brief Initialise l'attribut parcourue à true ou false
     * \return bool true si parcourue ou false non parcourue
     */
	bool Piece::getParcourue() const
	{
        return parcourue;
	}

     /**
     * \brief Accéder à la liste des portes qui partent de la pièce
     * \return list : une liste contenant les portes qui partent de la pièce
     */
	const std::list<Porte>& Piece::getPortes() const
	{
        return portes;
	}

     /**
     * \brief Fonction accesseur récupérant la distance du début
     * \return int distance du début
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
