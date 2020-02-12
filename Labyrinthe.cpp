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
        NoeudListePieces noeud;
        NoeudListePieces* ptrNoeud = &noeud;
        ptrNoeud->piece = p;

        if (dernier == nullptr)
        {
            ptrNoeud->suivant = ptrNoeud;
            dernier = ptrNoeud;
        }
        else if (!appartient(p)) {
            ptrNoeud->suivant = dernier->suivant;
            dernier->suivant = ptrNoeud;
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
        std::vector<std::vector<std::pair<int, int>>> adjListe;

        NoeudListePieces* noeudDepart  = trouvePiece(getDepart()->getNom());
        NoeudListePieces* noeudArrivee = trouvePiece(getArrivee()->getNom());
        NoeudListePieces* noeudCourant = noeudDepart;

        // Ajouter un vector pour chaque piece
        int compteur = 0;

        do {
            std::vector<std::pair<int, int>> piecePesee;
            adjListe.push_back(piecePesee);
            std::list<Porte> portesIci = noeudCourant->piece.getPortes();
            std::list<Porte>::const_iterator iterPortes = portesIci.begin();

            for (iterPortes = portesIci.begin(); iterPortes != portesIci.end(); ++iterPortes)
            {
                if (iterPortes->getCouleur() == joueur)
                    adjListe[compteur].push_back(std::make_pair(compteur, 1));
            }

            noeudCourant = noeudCourant->suivant;
            if (noeudCourant == noeudArrivee)
                indexArrivee = compteur; // Le noeud contenant la pice <arrivee> peut être n'importe où

        } while (noeudCourant != noeudDepart);

        // Calcul du plus court chemin entre depart et chacune des autres pieces
        std::vector<int> distance = calcCheminPlusCourt(adjListe, compteur);

        return indexArrivee == -1 ? -1 : distance[indexArrivee];
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
        file.push(make_pair(0, 0));
        distance[0] = 0;

        while (!file.empty())
        {
            int minPiece = file.top().first;
            file.pop();

            // Parcourir les pieces adjacentes à 
            for (int i = 0; i < adjListe[minPiece].size(); i++)
            {
                int connectee = adjListe[minPiece][i].first;
                int poids     = adjListe[minPiece][i].second;

                if (distance[connectee] < distance[minPiece] + poids)
                {
                    distance[connectee] = distance[minPiece] + poids;
                    file.push(make_pair(connectee, distance[minPiece]));
                }
            }
        }

        return distance;
    }



    /**
     * \brief Trouve le joueur qui peut solutionner le labyrinthe en le moins de déplacements. Si égalité,
     *	priorité au joueur rouge, vert, bleu, puis au jaune
     * \return Couleur du gagnant
     */
    Couleur Labyrinthe::trouveGagnant()
    {
        int rouge = solutionner(Couleur::Rouge);
        int vert = solutionner(Couleur::Vert);
        int bleu = solutionner(Couleur::Bleu);
        int jaune = solutionner(Couleur::Jaune);

        if (rouge == -1 && vert == -1 && bleu == -1 && jaune == -1)
        {
            return Couleur::Aucun;
        }

        if (rouge >= vert && rouge > bleu&& rouge > jaune)
        {
            return Couleur::Rouge;
        }

        if (vert > rouge&& vert >= bleu && vert > jaune)
        {
            return Couleur::Vert;
        }

        if (bleu > rouge&& bleu > vert&& bleu >= jaune)
        {
            return Couleur::Bleu;
        }

        if (jaune > rouge&& jaune > vert&& jaune > bleu)
        {
            return Couleur::Jaune;
        }
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
        catch (logic_error e1)
        {
            return false;
        }
        catch (invalid_argument e2)
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
        catch (logic_error e1)
        {
            throw logic_error("La piece n'existe pas dans le labyrinthe");
        }
        catch (invalid_argument e2)
        {
            throw logic_error("Le nom de la piece demandee est vide ou invalide");
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
        catch (logic_error e1)
        {
            throw logic_error("La piece n'existe pas dans le labyrinthe");
        }
        catch (invalid_argument e2)
        {
            throw logic_error("Le nom de la piece demandee est vide ou invalide");
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

        // TODO PROBLÈME ICI, NE PEUT PAS LIRE DERNIER AVANT QU'IL SOIT INITIALISÉ LORS DU CHARGEMENT PREMIÈRE PIÈCE
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

        throw logic_error("Pièce introuvable");

    }

    Labyrinthe::NoeudListePieces::NoeudListePieces(const NoeudListePieces& source)
    {
        *this = source;
    }



    //=====///
    //std::vector<int> Labyrinthe::TESTcalcCheminPlusCourt(std::vector<std::vector<std::pair<int, int>>>& adjListe,
    //    int& debut)
    //{

    //}

    //int Labyrinthe::TESTsolutionner(Couleur joueur)
    //{
    //    // COMMENCER À CREER NOEUDS AVEC DEPART, PAS OBLIGÉ DE FINIR À ARRIVÉE
    //    // CRÉER COMPTER QUI SERA INDEX "DEST" DANS LA STRUCT. AVANT, VERIFIER SI NOEUD = A ARRIVEE POUR SAVE SON INDEX



    //    int indexArrivee = 99; // PLACEHOLDER
    //    return -1;
    //}

    //struct Labyrinthe::NoeudListeAdj* Labyrinthe::creerNoeudAdj(int dest, int poids)
    //{
    //    struct NoeudListeAdj* leNoeud = (struct NoeudListeAdj*) malloc(sizeof(struct NoeudListeAdj));
    //    leNoeud->dest = dest;
    //    leNoeud->poids = poids;
    //    leNoeud->suivant = NULL;

    //    return leNoeud;
    //}

    //Labyrinthe::Graphe* Labyrinthe::initGraphe(int nbPieces)
    //{
    //    struct Graphe* graphe = (struct Graphe*) malloc(sizeof(struct Graphe));
    //    graphe->nbPieces = nbPieces;
    //    graphe->tableauListesAdj = (struct ListeAdj*) malloc(nbPieces);

    //    for (int i = 0; i < nbPieces; ++i)
    //    {
    //        graphe->tableauListesAdj[i].tete = NULL;
    //    }

    //    return graphe;
    //}

    //void Labyrinthe::ajouterCheminDansGraphe(Graphe* graphe, int origine, int dest, int poids)
    //{
    //    // Ajouter chemin de origine vers destination (au début)
    //    struct NoeudListeAdj* leNoeud = creerNoeudAdj(dest, poids);
    //    leNoeud->suivant = graphe->tableauListesAdj[origine].tete;
    //    graphe->tableauListesAdj[origine].tete = leNoeud;

    //    // Ajouter chemin de destination vers origine aussi
    //    leNoeud = creerNoeudAdj(origine, poids);
    //    leNoeud->suivant = graphe->tableauListesAdj[dest].tete;
    //    graphe->tableauListesAdj[dest].tete = leNoeud;
    //}


    //Labyrinthe::NoeudMinMonceau* Labyrinthe::creerNoeudMinMonceau(int nbPieces, int distance)
    //{
    //    struct NoeudMinMonceau* noeudMinMonceau = (struct NoeudMinMonceau*) malloc(sizeof(struct NoeudMinMonceau));
    //    noeudMinMonceau->nbPieces = nbPieces;
    //    noeudMinMonceau->distance = distance;
    //    return noeudMinMonceau;
    //}

    //Labyrinthe::MinMonceau* Labyrinthe::creerMinMonceau(int capacite)
    //{
    //    struct MinMonceau* minMonceau = (struct MinMonceau*) malloc(sizeof(struct MinMonceau));
    //    minMonceau->position = (int*)malloc(capacite * sizeof(int));
    //    minMonceau->taille = 0;
    //    minMonceau->capacite = capacite;
    //    minMonceau->tableauMonceau = (struct NoeudMinMonceau**) malloc(capacite * sizeof(struct NoeudMinMonceau*));

    //    return minMonceau;
    //}

    //void Labyrinthe::swapNoeudMinMonceau(NoeudMinMonceau** a, NoeudMinMonceau** b)
    //{
    //    struct NoeudMinMonceau* temp = *a;
    //    *a = *b;
    //    *b = temp;
    //}

    //void Labyrinthe::gererMonceau(MinMonceau* minMonceau, int idx)
    //{
    //    int plusPetit = idx;
    //    int gauche = 2 * idx + 1;
    //    int droite = 2 * idx + 2;

    //    if (gauche < minMonceau->taille && minMonceau->tableauMonceau[gauche]->distance minMonceau->tableauMonceau[plusPetit]->distance)
    //    {
    //        plusPetit = gauche;
    //    }

    //    if (droite < minMonceau->taille && minMonceau->tableauMonceau[droite]->distance minMonceau->tableauMonceau[plusPetit]->distance)
    //    {
    //        plusPetit = droite;
    //    }

    //    if (plusPetit != idx)
    //    {
    //        // Les Noeuds à échanger

    //    }
    //}
}
