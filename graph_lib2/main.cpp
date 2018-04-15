#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.make_example();
   // g.get_vertices();
   //g.ajouter_sommet();
 //g.ajouter_arrete();
 /*  std::cout<<"choisir l'indice de l'arete a enlever"<<std::endl;

  for( const auto& it : m_edges )
    {
        std::cout << "numero: " << it.first << ", sommet de depart: " << it.second.m_from << ", sommet d'arrivee: " << it.second.m_to << std::endl;
    }
    std::cin>> eidx; */
 // g.supprimer_arrete();
 //g.supprimer_sommet(4);


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }


    g.sauvegarder();
    grman::fermer_allegro();


    return 0;
}
END_OF_MAIN();


