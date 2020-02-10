/**
 * \file Labyrinthe.cpp
 * \brief Le code des méthodes membres et privés de la classe Labyrinthe.
 * \author IFT-2008, Étudiant(e)
 * \version 0.1
 * \date janvier 2020
 * 
 */

//Fichiers à compléter par les autres méthodes de la classe Labyrinthes demandées

#include "pch.h"
#include "Labyrinthe.h"


using namespace std;

namespace TP1
{
	// -------------------------------------------------------------------------------------------------
	//	Méthodes fournies
	// -------------------------------------------------------------------------------------------------

	/**
	 * \fn Labyrinthe::chargeLabyrinthe(Couleur couleur, std::ifstream & entree)
	 * \brief Fonction déjà fournie permettant de charger un labyrinthe depuis un fichier
	 * \param[in] couleur La couleur du jouer auquel le labyrinthe chargé s'applique
	 * \param[in] entree Fichier contenant la définition du labyrinthe
	 */
	void Labyrinthe::chargeLabyrinthe(Couleur couleur, std::ifstream& entree)
	{
		int nbCols, nbRangs;

		if (!entree.is_open())
			throw logic_error("Labyrinthe::chargeLabyrinthe: Le fichier n'est pas ouvert !");

		entree >> nbCols >> nbRangs;
		entree.ignore(); // Pour consommer le \n (le caractère fin de ligne)

		const int MAX_LIGNE = 1000;
		char ligne[MAX_LIGNE];

		entree.getline(ligne, MAX_LIGNE);
		entree.getline(ligne, MAX_LIGNE);

		std::ostringstream s; // Une chaîne pour écrire dedans, cette chaîne servira pour nommer les pièces du labyrinthe

		for (int i = 0; i < nbCols; i++)
		{
			for (int j = 0; j < nbRangs; j++)
			{
				s << i << "," << j;
				Piece p(s.str());
				s.str("");
				ajoutePieceLabyrinthe(p);
			}
		}

		for (int i = 0; i < nbCols; i++)
		{
			if (ligne[i * 4 + 1] == 'D' || ligne[i * 4 + 1] == 'd')
			{
				std::string nom;
				s << i << ",0";
				nom = s.str();
				s.str("");
				placeDepart(nom);
			}
			if (ligne[i * 4 + 1] == 'F' || ligne[i * 4 + 1] == 'f' || ligne[i * 4
				+ 1] == 'A' || ligne[i * 4 + 1] == 'a')
			{
				std::string nom;
				s << i << ",0";
				nom = s.str();
				s.str("");
				placeArrivee(nom);
			}
		}

		for (int j = 0; j < nbRangs; j++)
		{
			entree.getline(ligne, MAX_LIGNE);

			for (int i = (j == nbRangs - 1 && (j & 1)) ? 1 : 0; i < nbCols; i++)
			{
				if (j & 1)
				{
					if (j < nbRangs - 2 && ligne[i * 4 + 3] == ' ')
					{
						ajoutePassage(couleur, i, j, i, j + 2);
					}
					if (j < nbRangs - 1 && ligne[i * 4 + 2] == ' ')
					{
						ajoutePassage(couleur, i, j, i, j + 1);
					}
					if (j < nbRangs - 1 && ligne[i * 4 + 0] == ' ')
					{
						ajoutePassage(couleur, i - 1, j, i, j + 1);
					}
					if (j < nbRangs - 1 && (ligne[i * 4 + 1] == 'D' || ligne[i * 4
						+ 1] == 'd'))
					{
						std::string nom;
						s << i << "," << j + 1;
						nom = s.str();
						s.str("");
						placeDepart(nom);
					}
					if (j < nbRangs - 1 && (ligne[i * 4 + 1] == 'F' || ligne[i * 4
						+ 1] == 'f' || ligne[i * 4 + 1] == 'A' || ligne[i * 4
						+ 1] == 'a'))
					{
						std::string nom;
						s << i << "," << j + 1;
						nom = s.str();
						s.str("");
						placeArrivee(nom);
					}
				}
				else
				{
					if (j < nbRangs - 1 && ligne[i * 4 + 0] == ' ')
					{
						ajoutePassage(couleur, i - 1, j + 1, i, j);
					}
					if (j < nbRangs - 2 && ligne[i * 4 + 1] == ' ')
					{
						ajoutePassage(couleur, i, j, i, j + 2);
					}
					if (j < nbRangs - 1 && ligne[i * 4 + 2] == ' ')
					{
						ajoutePassage(couleur, i, j, i, j + 1);
					}
					if (j < nbRangs - 1 && (ligne[i * 4 + 3] == 'D' || ligne[i * 4
						+ 3] == 'd'))
					{
						std::string nom;
						s << i << "," << j + 1;
						nom = s.str();
						s.str("");
						placeDepart(nom);
					}
					if (j < nbRangs - 1 && (ligne[i * 4 + 3] == 'F' || ligne[i * 4
						+ 3] == 'f' || ligne[i * 4 + 3] == 'A' || ligne[i * 4
						+ 3] == 'a'))
					{
						std::string nom;
						s << i << "," << j + 1;
						nom = s.str();
						s.str("");
						placeArrivee(nom);
					}
				}
			}
		}
	}


	/**
	 * \fn Labyrinthe::ajoutePassage(Couleur couleur, int i1, int j1, int i2, int j2)
	 * \brief Fonction déjà fournie permettant d'ajouter une porte à une pièce
	 * \param[in]	Couleur couleur Couleur de la porte à ajouter
	 * \param[in]	int i1
	 * \param[in]	int j1
	 * \param[in]	int i2
	 * \param[in]	int j2
	 */
	void Labyrinthe::ajoutePassage(Couleur couleur, int i1, int j1, int i2, int j2)
	{

		NoeudListePieces* piece1, * piece2;
		string nomPiece1, nomPiece2;
		ostringstream s;

		s << i1 << "," << j1;
		nomPiece1 = s.str();

		s.str("");

		s << i2 << "," << j2;
		nomPiece2 = s.str();

		s.str("");

		piece1 = trouvePiece(nomPiece1);
		piece2 = trouvePiece(nomPiece2);

		Porte nouvellePorte(couleur, &(piece2->piece));

		piece1->piece.ajoutePorte(nouvellePorte);
	}

	/**
	 * \fn Labyrinthe::calcCheminPlusCourt(std::vector<std::vector<std::pair<int, int>>>& adjListe, int& start)
	 * \brief Retourne le chemin le plus court étant donné une liste d'adjacence
	 * \param[in] adjList La liste d'adjacence
	 * \param[in] debut Le point de départ
	 */
	std::vector<int> Labyrinthe::calcCheminPlusCourt(
		std::vector<std::vector<std::pair<int, int>>>& adjListe, int& debut)
	{
		vector<int> distance;

		// Donner une valeur de départ "infinie" à tous les chemins
		int compteurPiece = adjListe.size();
		for (int i = 0; i < compteurPiece; i++)
		{
			//TODO RENDU ICI
		}
	}


	/**
	 * \fn Labyrinthe::ajoutePieceLabyrinthe(Piece & p)
	 * \brief Fonction déjà fournie permettant d'ajouter une pièce au labyrinthe (si elle ne s'y trouve pas déjà)
	 * \param[in]	p La pièce à ajouter
	 * \post	La pièce appartient au labyrinthe;
	 */
	void Labyrinthe::ajoutePieceLabyrinthe(const Piece& p)
	{
		Labyrinthe::NoeudListePieces* noeud = new Labyrinthe::NoeudListePieces;
		noeud->piece = p;

		if (dernier == nullptr)
		{
			noeud->suivant = noeud;
			dernier = noeud;
		}
		else if (!appartient(p)) {
			noeud->suivant = dernier->suivant;
			dernier->suivant = noeud;
		}
	}


    //==================================================
	//= Nos méthodes                                   =
	//==================================================

	Labyrinthe::Labyrinthe(){}

	Labyrinthe::Labyrinthe(const Labyrinthe& source)
	{
		*this = source;
	}

	Labyrinthe::~Labyrinthe()
	{
		//TODO effacer les noeuds de NoeudListePieces par iteration (pointer pointeurs vers adresse 0)
	}

	const Labyrinthe& Labyrinthe::operator=(const Labyrinthe& source)
	{
		depart = source.getDepart();
		arrivee = source.getArrivee();
		dernier = source.trouvePiece(source.getArrivee()->getNom());
		//TODO copier source.NoeudListePieces par iteration

		return *this;
	}

	int Labyrinthe::solutionner(Couleur joueur)
	{
		//TODO P1
 	
		if (depart == arrivee || trouvePiece(depart->getNom())->suivant == nullptr)
		{
			return -1;
		}

			// Initialisation de la liste d'adjacence
			vector<vector<pair<string, int>>> adjListe;

			NoeudListePieces* noeudDepart = trouvePiece(getDepart()->getNom());
			NoeudListePieces* noeudArrivee = trouvePiece(getArrivee()->getNom());
			NoeudListePieces* noeudCourant = noeudDepart;

			// Ajouter un vector pour chaque piece
			int compteur = 0;
			do {
				int distance = 1;
				
				vector<pair<string, int>> piece_Pesee;
				adjListe.push_back(piece_Pesee);
				std::list<Porte> portesIci = noeudCourant->piece.getPortes();
				std::list<Porte>::const_iterator iterPortes = portesIci.begin();

				for (iterPortes = portesIci.begin(); iterPortes != portesIci.end(); ++iterPortes)
				{
					if (iterPortes->getCouleur() == joueur)
					{
						adjListe[compteur].push_back(make_pair(iterPortes->getDestination()->getNom(), 1));
					}
				}
				
				//TODO ??ajouter que distance depart->depart est 0 après la loop??
				noeudCourant = noeudCourant->suivant;
			} while (noeudCourant->suivant != noeudDepart);

			// Calcul du plus court chemin entre depart et chacune des autres pieces
			//TODO calcCheminPlusCourt()
			return -1;

			//for (int i = 0; i < adjListe.size(); i++)
			//{
			//	for (int = j; j < adjListe[i])
			//	adjListe[i].push_back(make_pair(, 1));
			//}
			
		/* Plan:
		 * Sur nodeDepart, set distance 0 et pour tous noeuds visité = true, ensuite pour chaque porte où couleur == couleur, aller à porte->destination
		 * puis attributer à piece destination ditance = noeudCourant.distance + 1. Ajouter à liste d'adjacence noeudCourant.
		 * Ensuite, parcourir tous les noeuds->piece->visité == false, puis verifier si a porte où destination == noeudCourant.
		 * Si oui, ajouter distance +1 et ajouter à liste d'adjacence noeudCourant
		 * Ensuite, 
		 */
		}

	Couleur Labyrinthe::trouveGagnant()
	{
 		//TODO P1
		return Couleur::Rouge;
	}

	bool Labyrinthe::appartient(const Piece& p) const
	{
		try
		{
			trouvePiece(p.getNom());
		}
		catch (logic_error e1)
		{
			return false;
		}
 		catch (invalid_argument e2)
 		{
			return false;
 		}
		return true;
	}

	void Labyrinthe::placeDepart(const std::string& nom)
	{
		try
		{
			trouvePiece(nom);
		}
 		catch(logic_error e1)
 		{
			throw logic_error("La piece n'existe pas dans le labyrinthe");
 		}
 		catch(invalid_argument e2)
 		{
			throw logic_error("Le nom de la piece demandee est vide ou invalide");
 		}
 		//TODO depart = adresse pointeur piece dans noeud depart, doit faire methode getter data dans noeud

	}

	void Labyrinthe::placeArrivee(const std::string& nom)
	{
		try
		{
			trouvePiece(nom);
		}
		catch (logic_error e1)
		{
			throw logic_error("La piece n'existe pas dans le labyrinthe");
		}
		catch (invalid_argument e2)
		{
			throw logic_error("Le nom de la piece demandee est vide ou invalide");
		}
		//TODO arrivee = adresse pointeur piece dans noeud arrivee, doit faire methode getter data dans noeud

	}

	TP1::Labyrinthe::NoeudListePieces* Labyrinthe::trouvePiece(const std::string& nom) const
	{
		if (nom.empty())
		{
			throw invalid_argument("Aucun nom de pièce reçu");
		}

		NoeudListePieces* noeudCourant = dernier;

		do
		{
			if (noeudCourant->piece.getNom() == nom)
			{
				return noeudCourant;
			}
			if (noeudCourant->suivant == nullptr)
			{
				throw logic_error("Piece introuvable");
			}
			noeudCourant = noeudCourant->suivant;
		} while (noeudCourant->suivant != dernier);

		throw logic_error("Pièce introubable");

	}

	Labyrinthe::NoeudListePieces::NoeudListePieces(const NoeudListePieces& source)
	{
		*this = source;
	}

}
