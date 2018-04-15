#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    BITMAP* menu_principal;
    int x=0;
    int y=0;

    menu_principal=load_bitmap("menu_principal.bmp",NULL);
    if (!menu_principal)
    {
        allegro_message("pas pu trouver/charger menu_principal.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    /// Un exemple de graphe
    Graph g1;
    Graph g2;
    Graph g3;
    Graph g;

    blit(menu_principal,screen,0,0,0,0,800,600);
    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    std::cout<<"3"<<std::endl;
    while ( !key[KEY_ESC] )
    {
        while(y!=1)
        {

            while(x!=1)
            {

                if(mouse_y>130 && mouse_x<400 && mouse_x>290 && mouse_y<160 && mouse_b&1)
                {
                    //namefile = "Graphe-1.txt";
                    g=g1;
                    g.make_example("Graphe-1.txt");
                    x=1;
                }

                if(mouse_y>215 && mouse_x<400 && mouse_x>290 && mouse_y<250 && mouse_b&1)
                {
                    g=g2;
                    //namefile = "Graphe-2.txt";
                    g.make_example("Graphe-2.txt");
                    x=1;
                }

                if(mouse_y>300 && mouse_x<400 && mouse_x>290 && mouse_y<335 && mouse_b&1)
                {
                    g=g3;
                    //namefile = "Graphe-3.txt";
                    g.make_example("Graphe-3.txt");
                    x=1;
                }

                if(key[KEY_SPACE])
                {
                    grman::fermer_allegro();
                    return 0;
                }
            }
            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g.update();

            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();


            x=0;

            g.sauvegarder();
            g.ajouter_arrete();
            g.ajouter_sommet();
            g.supprimer_arrete();
            //g.supprimer_sommet(6);


        }
    }
    //g.make_example();
    // g.get_vertices();
    //g.ajouter_sommet();
//g.ajouter_arrete();

// g.supprimer_arrete();
//g.supprimer_sommet(4);



    grman::fermer_allegro();


    return 0;
}

END_OF_MAIN();


