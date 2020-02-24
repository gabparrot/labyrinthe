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
        depart = source.getDepart();
        arrivee = source.getArrivee();
        dernier = source.trouvePiece(source.getArrivee()->getNom());
        //TODO copier source.NoeudListePieces par iteration?

        return *this;
    }



    //! Cette méthode doit solutionner un labyrinthe pour le joueur spécifié par joueur.
//! Elle doit donc trouver en combien d'étapes au minimum le joueur spécifié peut solutionner
//! le labyrinthe, en ne passant bien sûr que par les portes qui correspondent à sa couleur.
//!
//! Si un labyrinthe ne peut pas être solutionné par le joueur, il faut retourner -1. Dans ce cas,
//! nous ne considèrerons pas cela comme un appel anormal de la fonction.
//! Vous devez utiliser l'algorithme suivant pour solutionner le labyrinthe, en utilisant une file "queue" de la STL:
//! 1. Enfiler la pièce de départ en lui associant une distance du départ de zéro.
//! 2. Faire
//!      1. Défiler une pièce
//!      2. Enfiler toutes les pièces qui sont accessibles à partir de cette pièce à l'aide d'une porte
//!         de la couleur du joueur, et qui n'ont pas été déjà parcourues, en leur associant la distance
//! 		du départ de la pièce défilée plus un.
//!
//! 		Remarquez qu'il faut faire une vérification double ici. Il faut d'abord chercher les portes dans la liste
//! 		de portes de la pièce défilée, puis il faut ensuite aussi chercher les portes dans les listes de portes de
//! 		toutes les pièces pour voir s'il y en aurait qui mènent à la pièce défilée. Ceci est nécessaire car les portes
//! 		ne sont pas à sens unique, mais la méthode qui charge un labyrinthe fournie ne les ajoute qu'une seule fois
//!			dans le modèle d'implantation. Afin de savoir si une pièce a déjà été parcourue ou non, employez le champ
//!			booléen parcourue. N'enfilez que des pièces pour lesquelles ce champ a false comme valeur, puis au moment
//!			où vous l'enfilez, appliquez-lui la valeur true. Aussi, n'oubliez pas, avant de commencer l'algorithme, de
//!			mettre ce champ à false pour toutes les pièces du labyrinthe.
//!
//!	Tant qu'il reste des pièces dans la file et que la pièce d'arrivée n'a pas encore été atteinte (défilée).


    /**
     * \brief Nombre d'étape minimum pour solutionner le labyrinthe pour le joueur en ne passant que par les portes qui correspondent à sa couleur
     * \param[in] Couleur joueur
     * \return int représantant le nombre d'étape minimum
     */
    int Labyrinthe::solutionner(Couleur joueur)
    {
        /* PLAN
         * - Faire liste d'adjacence:
         *   - Parcourir toutes les pieces. et créer un map <piece, <portes>.
         *   - Parcourir à nouveau. Pour chaque pièce, ajouter portes présentes.
         *       - Pour chacune de ces portes, aller dans la piece, voir si liste porte contient origine, s'ajouter sinon.
         *
         * - Resoudre:
         *   - Garder un compteur de distance dans la boucle
         *   - Faire une queue de pieces
         *   - Push le départ, marquer visité = true et distance = 0
         *   - Par la liste d'adjacence, aller dans une pièce adjacente pas déjà visitée.
         *       - Marquer la distance = current + 1
         *       - Répéter pour toutes les pièces touchant à l'origine
         */

        NoeudListePieces* noeudCourant = trouvePiece(getDepart()->getNom());
        NoeudListePieces* noeudDepart = noeudCourant;

        // Création d'une liste d'adjacence, premier parcours crée toutes les pieces et leur liste de portes
        std::map<std::string, std::vector<Porte>> listeAdjacence;
        do
        {
            
            // Enlever portes mauvaise couleur avant de push la liste
            if (noeudCourant == nullptr)
            {
                break;
            }
            if (noeudCourant->piece.getNom() != "")
            {
                Piece pieceCourante = noeudCourant->piece;
                Piece* pieceCourantePtr = &pieceCourante;
                std::list<Porte> portesIci = pieceCourante.getPortes();
                std::list<Porte>::iterator iterPorte;
                std::vector<Porte> vPortes;
                if (!portesIci.empty())
                {
                    for (iterPorte = portesIci.begin(); iterPorte != portesIci.end(); ++iterPorte)
                    {
                        if (iterPorte->getCouleur() == joueur)
                        {
                            Porte cettePorte = *iterPorte;
                            vPortes.push_back(cettePorte);
                        }
                    }
                }
                // Associer liste de porte à une pièce dans le dictionnaire
                string nomIci = pieceCourante.getNom();
                pieceCourante.setParcourue(false);
                pieceCourante.setDistanceDuDebut(INFINI);

                if (pieceCourantePtr != nullptr && !vPortes.empty())
                {
                    listeAdjacence.insert({ nomIci , vPortes });
                }
            }

            noeudCourant = noeudCourant->suivant;
        } while (noeudCourant != noeudDepart && noeudCourant != nullptr);

        // Deuxième parcours de la liste d'adjacence ajoute les portes dans l'autre direction (si affiché dans A, récrire dans B)
        noeudCourant = noeudDepart;

        do
        {
            if (noeudCourant == nullptr)
            {
                break;
            }
            if (noeudCourant->piece.getNom() != "")
            {
                std::list<Porte> portesIci = noeudCourant->piece.getPortes();
                std::list<Porte>::iterator iterPorte;
                std::vector<Porte> vPortes;

                if (!portesIci.empty())
                {
                    for (iterPorte = portesIci.begin(); iterPorte != portesIci.end(); ++iterPorte)
                    {
                        Porte cettePorte = *iterPorte;
                        if (cettePorte.getCouleur() == joueur)
                        {
                            Piece* destinationPtr = cettePorte.getDestination();
                            Piece destination = *destinationPtr;
                            string nomDestination = destination.getNom();
                            vector<Porte>& portesLaBas = listeAdjacence[nomDestination];
                            portesLaBas.push_back(cettePorte);
                        }
                    }
                }
            }
            noeudCourant = noeudCourant->suivant;

        } while (noeudCourant != noeudDepart && noeudCourant != nullptr);


        // Début du parcours en largeur


        // Initialiser avec pièce départ visitée et distance avec elle-même de 0
        depart->setDistanceDuDebut(0);


        // Créer une file réprésentant toutes les pièces qu'on peut atteindre à partir de la pièce courante

        // Compteur de distance, augmente de 1 chaque fois qu'on avance
        noeudCourant = noeudDepart;

        do
        {
            noeudCourant->piece.setDistanceDuDebut(0);
            noeudCourant->piece.setParcourue(false);
            noeudCourant = noeudCourant->suivant;

        } while (noeudCourant != noeudDepart && noeudCourant != nullptr);
        noeudCourant = noeudDepart;
        queue<Piece*> file;
        noeudDepart->piece.setParcourue(true);
        noeudDepart->piece.setDistanceDuDebut(0);
        file.push(&noeudDepart->piece);
        string nomArrivee = arrivee->getNom();
        int compteurDistance = 0;

            while (!file.empty())
            {
                Piece* pieceCourantePtr = file.front();
                Piece pieceCourante = *pieceCourantePtr;
                file.pop();
                string nomIci = pieceCourantePtr->getNom();
                vector<Porte> vPortesIci = listeAdjacence[nomIci];

                if (pieceCourantePtr == arrivee)
                {
                    return (compteurDistance + 1);
                }

                if (!vPortesIci.empty())
                {
                    vector<Porte>::iterator vIterPorte;

                    for (vIterPorte = vPortesIci.begin(); vIterPorte != vPortesIci.end(); ++vIterPorte)
                    {
                        Piece* destinationPtr = vIterPorte->getDestination();
                        Piece destination = *destinationPtr;
                        Piece* vraieDest = &(trouvePiece(destination.getNom())->piece);

                        if (!(destination.getParcourue()))
                        {
                            vraieDest->setDistanceDuDebut(pieceCourantePtr->getDistanceDuDebut() + 1);
                            vraieDest->setParcourue(true);
                            file.push(vraieDest);
                            //cout << "Ajout de : " << vraieDest->getNom() << " À l'adresse: " << vraieDest << endl;
                            if (destination.getDistanceDuDebut() > compteurDistance)
                            {
                                compteurDistance = destination.getDistanceDuDebut();
                            }
                        }
                        if (destinationPtr->getNom() == nomArrivee)
                        {
                            return pieceCourantePtr->getDistanceDuDebut() + 1;
                        }
                    }
                }
            }
            listeAdjacence.clear();
        return -1;
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
