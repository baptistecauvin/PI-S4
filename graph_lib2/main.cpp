#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    int choix;

    std::cout<<"que voulez vous faire" <<std::endl;

    std::cin>>choix;

    switch(choix)
    {
    case 1 :

            std::cout<<"1: ajouter sommet "<< std::endl;
            g.make_example();
            g.ajouter_sommet();
            g.sauvegarder();
            break;

    case 2 :
        {
            std::cout<<"2: ajouter arrete "<<std::endl;
            break;
        }
    case 3 :
        {
            std::cout <<"3: supprimer sommet "<< std::endl;
            break;
        }
    case 4 :
        {
            std::cout <<" 4: supprmier arrete" <<std::endl;
            break;
        }
    }




    //g.make_example();


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }


    g.sauvegarder();
    grman::fermer_allegro();


    return 0;
}
END_OF_MAIN();


