/**
 * \file Labyrinthe.h
 * \brief Ce fichier contient l'interface d'un labyrinthe.
 * \author Gabriel Chevrette-Parot, Gabrielle Lévêque Huot
 * \version 0.1
 * \date 24 février 2020
 *
 */

#pragma once

#ifndef LABYRINTHE_H_
#define LABYRINTHE_H_

// Fournis
#include <iostream> // Pour les flux d'entrée/sortie
#include <fstream>  // Pour les fichiers
#include <sstream>  // Lecture/écriture dans un string, voir la méthode chargeLabyrinthe() fournie
#include <string>   // Pour le nom de la pièce
#include <queue>	// Pour utiliser la file de la STL afin de solutionner le labyrinthe
#include <limits>   // Pour l'utilisation de numeric_limits<int>::max()
#include <vector>
#include "Porte.h"
#include "Piece.h"

static const  int INFINI = std::numeric_limits<int>::max();

// Ajouté
#include <vector>   // Pour graphe, paires chemins + distance

namespace TP1
{
	/*!
	 * \class Labyrinthe
	 * \brief classe représentant un labyrinthe
	 *
	 * La classe représentant un labyrinthe formé de plusieurs pièces dotées de portes de couleur
	 */
	class Labyrinthe
	{
	public:
		/*!
		 *  \brief Constructeur par défaut
		 */
		Labyrinthe();

		/*!
		 * \brief Constructeur de copie
		 *
		 * Constructeur copie de la classe Labyrinthe
		 *
		 * \param source : un objet Labyrinthe
		 */
		Labyrinthe(const Labyrinthe& source);

		/*!
		 * \brief Destructeur
		 *
		 * Destructeur de la classe Labyrinthe
		 *
		 */
		~Labyrinthe();

		/*!
		 * \brief Surchage
		 *
		 * Surcharge de l'opérateur =
		 *
		 * \param source : un objet Labyrinthe
		 */
		const Labyrinthe& operator =(const Labyrinthe& source);

		/*!
		 * \brief Charge un fichier
		 *
		 * Charge un fichier contenant un labyrinthe d'une certaine couleur
		 *
		 * \param couleur : Peut prendre quatre valeurs : Rouge, Bleu, Jaune ou Vert
		 * \param entree : un fichier .txt contenant le labyrinthe d'une certaine couleur
		 */
		void chargeLabyrinthe(Couleur couleur, std::ifstream& entree);

		/*!
		 * \brief Ajoute une pièce à un labyrinthe
		 *
		 * Ajouter la pièce p à un labyrinthe si elle n'est pas déjà présente
		 *
		 * \param p : objet Pièce à ajouter au labyrinthe
		 */
		void ajoutePieceLabyrinthe(const Piece& p);
	
		/*!
		 * \brief Solutionner un labyrinthe
		 *
		 * solutionner un labyrinthe pour le joueur spécifié par joueur.
		 *
		 * \param p : objet Pièce à ajouter au labyrinthe
		 * \return Nombre d'étapes au minimum pour le joueur spécifié peut solutionner le labyrinthe
		 * ou -1 si un labyrinthe ne peut pas être solutionné par le joueur
		 */
		int solutionner(Couleur joueur);


		/*!
		 * \brief Calcule le chemin le plus court
		 *
		 * Calcule le chemin le plus court pour un joueur.
		 *
		 * \param adj Liste liste adjacente
		 * \param taille 
		 * \return un vecteur de vecteur
		 */
		std::vector<int> Labyrinthe::calcCheminPlusCourt(std::vector<std::vector<std::pair<int, int>>> &adjListe, int taille);

		/*!
		 * \brief Trouve le joueur gagnant
		 *
		 * Détermine quel est le joueur qui peut solutionner le labyrinthe en le moins de déplacements
		 *
		 * \return la couleur du gagnant
		 */
		Couleur trouveGagnant();

		/*!
		 * \brief Accesseur
		 *
		 * Accesseur pour le membre depart
		 *
		 * \return un pièce de départ
		 */
		Piece* getDepart() const { return depart; }

		/*!
		 * \brief Accesseur
		 *
		 * Accesseur pour le membre arrivee
		 *
		 * \return un pièce d'arrivée
		 */
		Piece* getArrivee() const { return arrivee; }

		/*!
		 * \brief  Vérifie si une pièce se trouve dans le labyrinthe
		 *
		 * Méthode qui vérifie si une pièce portant le nom de la pièce fournie se trouve dans le labyrinthe
		 *
		 * \return true si la pièce est dans le labyrinthe sinon false 
		 */
		bool appartient(const Piece& p) const;

	private:

		/*!
		 * \brief Ajoute un passage dans un labyrinthe
		 *
		 * \param Couleur couleur Couleur de la porte à ajouter
		 * \param int i1
		 * \param int j1
		 * \param int i2
		 * \param int j2
		 */
		void ajoutePassage(Couleur couleur, int i1, int j1, int i2, int j2);

		/*!
		 * \brief Ajuste le pointeur depart d'un labyrinthe
		 *
		 * Ajuste le pointeur depart d'un labyrinthe pour qu'il
		 * contienne l'adresse de la pièce correspondant au nom spécifié par nom
		 *
		 * \param string& nom : nom de la pièce
		 */
		void placeDepart(const std::string& nom);

		/*!
		 * \brief Ajuste le pointeur arrivee d'un labyrinthe
		 *
		 * Ajuste le pointeur arrivee d'un labyrinthe pour qu'il
		 * contienne l'adresse de la pièce correspondant au nom spécifié par nom
		 *
		 * \param string& nom : nom de la pièce
		 */
		void placeArrivee(const std::string& nom);



		/*!
		 * \class NoeudListePieces
		 * \brief Noeud typique d'une liste chaînée circulaire
		 *
		 */
		class NoeudListePieces
		{
		public:
			/*!
			*  \brief Constructeur par défaut
			*/
			NoeudListePieces();
			
			/*!
			* \brief Constructeur de copie
			*
			* Constructeur copie de la classe NoeudListePieces
			*
			* \param source : un objet NoeudListePieces
			*/
			NoeudListePieces(const NoeudListePieces& source);

			Piece piece; //!< La piece contenue dans un noeud d'une liste chaînée circulaire.

			NoeudListePieces* suivant = nullptr; //!< Le noeud suivant
		};

		/*!
		* \brief Trouve l'adresse de la pièce dans le labyrinthe
		*
		* Retourne l'adresse du noeud de la liste de pièces contenue dans le labyrinthe
		* qui correspond à la pièce portant le nom nom
		*
		* \param nom : nom de la pièce
		* \return L'adresse du noeud de la liste de pièces contenue dans le labyrinthe
		*/
		NoeudListePieces* trouvePiece(const std::string& nom) const;

		NoeudListePieces* dernier = nullptr; /*!< Le dernier noeud de la liste chaînée circulaire.*/
		/*!<  Ce noeuds ne contient pas nécessairement les pièces de départ ou d'arrivée. */
		
		Piece* depart; /*!< Adresse de la pièce de départ (et non du noeud qui la contient) */
		Piece* arrivee; /*!< Adresse de la pièce d'arrivée (et non du noeud qui la contient) */

	};

}

#endif /* LABYRINTHE_H_ */

