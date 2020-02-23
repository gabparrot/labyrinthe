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
#include <list>
#include <functional>


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


     /**
     * \brief Constructeur de la classe Labyrinthe
     * \return Un objet Labyrinthe
     */
    Labyrinthe::Labyrinthe()
    {
    }


    /**
     * \brief Constructeur de copie de la classe Labyrinthe
     */
    Labyrinthe::Labyrinthe(const Labyrinthe& source)
    {
        *this = source;
    }


    /**
     * \brief Destructeur de la classe Labyrinthe
     */
    Labyrinthe::~Labyrinthe()
    {
        //TODO Libérer la mémoire correctement
    }


    /**
     * \brief surcharge de l'opérateur = entre les pièces et le labyrinthe
     * \param[in] Labyrinthe source
     * \return Objet Labyrinthe avec les pièces
     */
    const Labyrinthe& Labyrinthe::operator=(const Labyrinthe& source)
    {
        depart  = source.getDepart();
        arrivee = source.getArrivee();
        dernier = source.trouvePiece(source.getArrivee()->getNom());
        //TODO copier source.NoeudListePieces par iteration?

        return *this;
    }




    /**
     * \brief Nombre d'étape minimum pour solutionner le labyrinthe pour le joueur en ne passant que par les portes qui correspondent à sa couleur
     * \param[in] Couleur joueur
     * \return int représantant le nombre d'étape minimum
     */
    int Labyrinthe::solutionner(Couleur joueur)
    {
        
        if (depart == arrivee || trouvePiece(depart->getNom())->suivant == nullptr)
            return -1;

        int indexArrivee = -1;

        // Initialisation de la liste d'adjacence
        // Je pèse la distance entre chaque piece avec les autres, pas seulement origine avec les autres
        // chaque index = une piece, contenant chacun vecteurs <"IndexPieceDestination", "nbMinChemin entre piece origine et desti> 
        std::vector<std::vector<std::pair<int, int>>> adjListe; // Paire = < pièce destination , distance min avec origine (cet index)> 

        NoeudListePieces* noeudDepart  = trouvePiece(getDepart()->getNom());
        NoeudListePieces* noeudArrivee = trouvePiece(getArrivee()->getNom());
        NoeudListePieces* noeudCourant = noeudDepart;

        // Dictionnaire de numéros pour chaque nom de pièce
        std::map<std::string, int> idPieces; // <"Nom", "ID #">

        int nbPieces = 0;

        // Comptage du nb de pièces avec compteur jusqu'à revenir au même noeud
        do
        {
            // Ajouter une entrée vide <int, int> pour chaque pièce (contiendra <dest,dist> après)
            vector<pair<int, int>> unePiece;
            adjListe.push_back(unePiece);

            // Donner un numero au lieu d'un nom
            idPieces.insert({noeudCourant->piece.getNom(), nbPieces});

            noeudCourant = noeudCourant->suivant;
            nbPieces++;
        } while (noeudCourant != noeudDepart);

        // Mettre listes de toutes couleurs portes chaque piece dans vecteur
        // Boucle concentrique ici ne devrait pas causer O(n2) car chaque pièce aura tjr 1 seule liste portes
        noeudCourant = noeudDepart;

        for (int iterPieces = 0; iterPieces < nbPieces; iterPieces++)
        {
            std::list<Porte> listePortesIci = noeudCourant->piece.getPortes();
            int totalPortesIci = listePortesIci.size();

            for (int iterPortes = 0; iterPortes < totalPortesIci; iterPortes++)
            {
                Porte cettePorte = listePortesIci.front();
                listePortesIci.pop_front();

                // Obtenir idPiece destination porte
                std::map<std::string, int>::iterator iterIdPieces = idPieces.find(cettePorte.getDestination()->getNom());
                int idPorte = iterIdPieces->second;

                if (cettePorte.getCouleur() == joueur)
                {
                    adjListe[iterPieces].push_back(make_pair(idPorte, 1));
                    //cout << "Piece: " << iterPieces << " Porte: " << idPorte << endl;
                }

            }

            if (noeudCourant == noeudArrivee)
            {
                indexArrivee = iterPieces;
            }

            //TODO TEST
            /*
            std::map<std::string, int>::iterator iterIdPieces = idPieces.find(noeudDepart->piece.getNom());
            cout << "DEPART = :" << iterIdPieces->first << " et " << iterIdPieces->second << endl;
            iterIdPieces = idPieces.find(noeudArrivee->piece.getNom());
            cout << "ARRIVEE = :" << iterIdPieces->first << " et " << iterIdPieces->second << endl;
            */




            noeudCourant = noeudCourant->suivant;
        }

        // Calcul du plus court chemin entre depart et chacune des autres pieces
        std::vector<int> distMin= calcCheminPlusCourt(adjListe, nbPieces);

        return indexArrivee == -1 ? -1 : distMin[indexArrivee];
    }


    /**
        * \fn Labyrinthe::calcCheminPlusCourt(std::vector<std::vector<std::pair<int, int>>>& adjListe, int& start)
        * \brief Retourne le chemin le plus court étant donné une liste d'adjacence
        * \param[in] adjListe La liste d'adjacence
        * \param[in] debut Le point de départ
        */
    std::vector<int> Labyrinthe::calcCheminPlusCourt(std::vector<std::vector<std::pair<int, int>>> &adjListe, int taille)
    {
        std::vector<int> distance;
        
        // Donner une valeur de départ "infinie" à tous les chemins (et pas std::INFINITY car c'est un float)
        for (int i = 0; i < taille; i++)
        {
            distance.push_back(INFINI); 
        }

        std::priority_queue <std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> file;
        file.push(make_pair(0, 0)); // Paire("noeud de départ", "Distance avec départ")
        distance[0] = 0;  // Distance connue de 0 départ->départ, infinie ailleurs en attendant calcul

        while (!file.empty())
        {
            int u = file.top().first;
            file.pop();

            // Parcourir les pieces adjacentes à 
            for (unsigned long long i = 0; i < adjListe[u].size(); i++)
            {
                int v      = adjListe[u][i].first;
                int poids  = adjListe[u][i].second;

                if (distance[v] > distance[u] + poids)
                {
                    distance[v] = distance[u] + poids;
                    file.push(make_pair(v, distance[v]));
                }
            }
        }
        //std::cout << " EST LA DISTANCE[0] RETOURNÉE DANS CALCHEMIN" << distance[0] << endl;
        return distance;
    }



    /**
     * \brief Trouve le joueur qui peut solutionner le labyrinthe en le moins de déplacements. Si égalité,
     *	priorité au joueur rouge, vert, bleu, puis au jaune
     * \return Couleur du gagnant
     */
    Couleur Labyrinthe::trouveGagnant()
    {
        //std::cout << "Rendu dans trouveGagnent() " << endl;

        Couleur gagnant = Couleur::Aucun;
        int rouge = solutionner(Couleur::Rouge);
        int vert = solutionner(Couleur::Vert);
        int bleu = solutionner(Couleur::Bleu);
        int jaune = solutionner(Couleur::Jaune);
        
        int distParJoueur[4];
        distParJoueur[0] = rouge;
        distParJoueur[1] = vert;
        distParJoueur[2] = bleu;
        distParJoueur[3] = jaune;

        int* minimum = std::min_element(begin(distParJoueur), end(distParJoueur));

        if (*minimum == rouge)
        {
            gagnant = Couleur::Rouge;
        }
        else if (*minimum == vert)
        {
            gagnant = Couleur::Vert;
        }
        else if (*minimum == bleu)
        {
            gagnant = Couleur::Bleu;
        }
        else if (*minimum == jaune)
        {
            gagnant = Couleur::Jaune;
        }

        return gagnant;

    }


    /**
     * \brief Vérifie si une pièce portant le nom de la pièce fournie se trouve dans le labyrinthe
     * \return True si la pièce fournie se trouve dans le labyrinthe sinon False
     */
    bool Labyrinthe::appartient(const Piece& p) const
    {
        try
        {
            NoeudListePieces* verificateur = trouvePiece(p.getNom());
            if (verificateur != nullptr)
                return true;
        }
        catch (std::logic_error e1)
        {
            return false;
        }
        catch (std::invalid_argument e2)
        {
            return false;
        }
        return false;
    }
    

    /**
     * \brief Ajuste le pointeur depart au Labyrinthe
     * \param[in] String nom: le nom de la pièce
     */
    void Labyrinthe::placeDepart(const std::string& nom)
    {
        try
        {
            depart = &trouvePiece(nom)->piece;
        }
        catch (std::logic_error e1)
        {
            throw std::logic_error("La piece n'existe pas dans le labyrinthe");
        }
        catch (std::invalid_argument e2)
        {
            throw std::logic_error("Le nom de la piece demandee est vide ou invalide");
        }
        //TODO depart = adresse pointeur piece dans noeud depart, doit faire methode getter data dans noeud
    }


    /**
     * \brief Ajuste le pointeur arrivee au Labyrinthe
     * \param[in] String nom: le nom de la pièce
     */
    void Labyrinthe::placeArrivee(const std::string& nom)
    {
        try
        {
            arrivee = &trouvePiece(nom)->piece;
        }
        catch (std::logic_error e1)
        {
            throw std::logic_error("La piece n'existe pas dans le labyrinthe");
        }
        catch (std::invalid_argument e2)
        {
            throw std::logic_error("Le nom de la piece demandee est vide ou invalide");
        }
    }

    Labyrinthe::NoeudListePieces::NoeudListePieces()
    {
    }


    /**
     * \brief Trouver l'adresse du noeud de la liste de pièces du labyrinthe correspondant à la pièce portant le nom nom
     * \param[in] String nom: le nom de la pièce
     * \return NoeudListePieces : Adresse du noeud de la liste de pièces du labyrinthe correspondant à la pièce
     */

    Labyrinthe::NoeudListePieces* Labyrinthe::trouvePiece(const std::string& nom) const
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
                throw std::logic_error("Piece introuvable");
            }

            noeudCourant = noeudCourant->suivant;
        } while (noeudCourant != dernier);

        throw std::logic_error("Pièce introuvable - trouvePiece()");

    }

    Labyrinthe::NoeudListePieces::NoeudListePieces(const NoeudListePieces& source)
    {
        *this = source;
    }
}
