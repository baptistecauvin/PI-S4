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

    Graph g1;
    Graph g2;
    Graph g3;

    while(y!=1)
    {
        blit(menu_principal,screen,0,0,0,0,800,600);
        while (x!=1)
        {
            if(mouse_y>130 && mouse_x<400 && mouse_x>290 && mouse_y<160 && mouse_b&1)
            {
                //namefile = "Graphe-1.txt";
                g1.make_example();
                x=1;
            }

            if(mouse_y>215 && mouse_x<400 && mouse_x>290 && mouse_y<250 && mouse_b&1)
            {
                //namefile = "Graphe-2.txt";
                g2.make_example();
                x=1;
            }

            if(mouse_y>300 && mouse_x<400 && mouse_x>290 && mouse_y<335 && mouse_b&1)
            {
                //namefile = "Graphe-3.txt";
                g3.make_example();
                x=1;
            }

            if(key[KEY_SPACE])
            {
                grman::fermer_allegro();
                return 0;

            }

        }
        /// Vous gardez la main sur la "boucle de jeu"
        /// ( contrairement à des frameworks plus avancés )
        std::cout<<"3"<<std::endl;
        while ( !key[KEY_ESC] )
        {
            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g1.update();

            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();

            x=0;

            if(key[KEY_S])
            {
                g1.sauvegarder();
            }
        }

        //g1.sauvegarder();
        //grman::fermer_allegro();
    }

    grman::fermer_allegro();
    return 0;
}
END_OF_MAIN();


