#include "graph.h"
#include <fstream>
#include <iostream>

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);


    m_tool_box.add_child(m_save);
    m_save.add_child(m_text_save);
    m_save.set_dim(75,40);
    m_save.set_posx(0);
    m_save.set_posy(0);
    m_save.set_bg_color(ORANGE);
    m_text_save.set_message(" SAVE ");

    m_tool_box.add_child(m_add_sommet);
    m_add_sommet.add_child(m_text_adds);
    m_add_sommet.set_dim(75,40);
    m_add_sommet.set_posx(0);
    m_add_sommet.set_posy(40);
    m_add_sommet.set_bg_color(VERT);
    m_text_adds.set_message(" AJOUTER S ");

    m_tool_box.add_child(m_add_arrete);
    m_add_arrete.add_child(m_text_adda);
    m_add_arrete.set_dim(75,40);
    m_add_arrete.set_posx(0);
    m_add_arrete.set_posy(80);
    m_add_arrete.set_bg_color(BLEU);
    m_text_adda.set_message(" AJOUTER A ");

    m_tool_box.add_child(m_sup);
    m_sup.add_child(m_text_sup);
    m_sup.set_dim(75,40);
    m_sup.set_posx(0);
    m_sup.set_posy(120);
    m_sup.set_bg_color(ROUGE);
    m_text_sup.set_message(" SUPPRIMER S ");

    m_tool_box.add_child(m_supa);
    m_supa.add_child(m_text_supa);
    m_supa.set_dim(75,40);
    m_supa.set_posx(0);
    m_supa.set_posy(160);
    m_supa.set_bg_color(KAKI);
    m_text_supa.set_message(" SUPPRIMER A ");

    m_tool_box.add_child(m_back);
    m_back.add_child(m_text_back);
    m_back.set_dim(75,40);
    m_back.set_posx(0);
    m_back.set_posy(200);
    m_back.set_bg_color(BLANC);
    m_text_back.set_message(" RETOUR ");

    m_tool_box.add_child(m_q);
    m_q.add_child(m_text_q);
    m_q.set_dim(75,40);
    m_q.set_posx(0);
    m_q.set_posy(240);
    m_q.set_bg_color(VIOLET);
    m_text_q.set_message(" QUITTER ");
}

Graph::Graph(int x,int t,unsigned int nb,int p,int val,int vx,int vy)
{
    x=id;
    nb=nb_sommet;
    p=poids;
    val=value;
    vx=verx;
    vy=very;
    t=tmp;
}


void Graph::menu()
{
    BITMAP* menu_principal, *menu, *page;

    menu_principal=load_bitmap("menu_principal.bmp",NULL);
    if (!menu_principal)
    {
        allegro_message("pas pu trouver/charger menu_principal.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    page=load_bitmap("page.bmp",NULL);
    if (!page)
    {
        allegro_message("pas pu trouver/charger page.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    menu=create_bitmap(SCREEN_W,SCREEN_H);

    blit(menu_principal,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    int choix=0;

    while(choix!=4)
    {

        if(mouse_y>130 && mouse_x<400 && mouse_x>290 && mouse_y<160 && mouse_b&1)
        {
            choix=1;
            draw_sprite(menu, page,0,0);
        }

        if(mouse_y>215 && mouse_x<400 && mouse_x>290 && mouse_y<250 && mouse_b&1)
        {
            choix=2;
            draw_sprite(menu, page,0,0);

        }

        if(mouse_y>300 && mouse_x<400 && mouse_x>290 && mouse_y<335 && mouse_b&1)
        {
            choix=3;
            draw_sprite(menu, page,0,0);
        }

        rest(20);


        if(mouse_b&1 && choix<=4 && choix>=1)
        {
            switch(choix)
            {
            case 1:
            {
                choix=4;
                fichier="Graphe-1.txt";
                make_example(fichier);
                break;
            }
            case 2:
            {
                choix=4;
                fichier="Graphe-2.txt";
                make_example(fichier);
                break;
            }
            case 3:
            {
                choix=4;
                fichier="Graphe-3.txt";
                make_example(fichier);
                break;
            }
            case 4:
            {
                exit(1);
            }

            }
        }
    }

}
/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example(std::string filename)
{
    //Ouverture du fichier en mode lecture
    std::ifstream fichier(filename,std::ios::in);

    if(fichier)
    {
        m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
        fichier>> nb_sommet;
        fichier>> nb_arrete;

        for (int i=0 ; i<nb_sommet; i++ )
        {
            fichier >>tmp;
            fichier >>value;
            fichier >>verx;
            fichier>>very;
            fichier>>name;
            add_interfaced_vertex(i,value,verx,very, name);
        }

        for(int j=0; j<nb_arrete; j++)
        {
            fichier >>tmp;
            fichier >> s1;
            fichier >> s2;
            fichier >> poids;
            add_interfaced_edge(j,s1,s2,poids);
        }
        fichier.close();
    }

    else
        std::cout<< "impossible d'ouvrir le fichier" ;

}


void Graph::sauvegarder(std::string filename)
{

    if(m_interface->m_save.clicked())
    {


        std::ofstream fichier(filename,std::ios::out);
        fichier << m_vertices.size()<<std::endl;
        fichier << m_edges.size()<<std::endl;
        for(auto it=m_vertices.begin(); it!=m_vertices.end(); ++it)
        {
            fichier << it->first<< " " ;

            fichier << it->second.m_value<<" ";
            fichier << it->second.m_interface->m_top_box.get_posx()<<" ";
            fichier << it->second.m_interface->m_top_box.get_posy()<<" ";
            fichier << it->second.m_interface->m_img.get_pic_name()<<std::endl;


        }

        int i=0;
        for(const auto & it:m_edges)
        {
            fichier<<i; //id
            fichier<<" "<<it.second.m_from; //S1
            fichier<<" "<<it.second.m_to; //S2
            fichier<<" "<<it.second.m_weight<<"\n"; //poid
            i++;
        }

        fichier.close();
    }
}
void Graph::ajouter_sommet()
{
    if(m_interface->m_add_sommet.clicked())
    {

        int choix2;
        std::cout <<"que voulez vous ajouter"<<std::endl;
        std::cout<<" 1-dino1 2-dino2 3_dino3"<<std::endl;
        std::cin >> choix2;

        if(choix2==1)
        {
            add_interfaced_vertex(m_vertices.size(),50,300,400,"pteranodon.png");
        }
        if(choix2==2)
        {
            add_interfaced_vertex(m_vertices.size(),50,500,600,"herbe.png");
        }

    }
}
void Graph::ajouter_arrete()
{
    if(m_interface->m_add_arrete.clicked())
    {
        int S1,S2;
        int poid;

        std::cout<< "choissisez le sommet de depart" <<std::endl;
        std::cin>>S1;
        std::cout<<"choisissez le sommet d'arrive" <<std::endl;
        std::cin>>S2;
        std::cout<<"quelle poid pour votre arrete"<<std::endl;
        std::cin>>poid;

        add_interfaced_edge(m_edges.size(),S1,S2,poid);
    }
}

void Graph::supprimer_arrete()
{
    if(m_interface->m_supa.clicked())
    {

        int eidx=4; /// référence vers le Edge à enlever
        Edge &remed=m_edges.at(eidx);

        std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

/// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
        std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
        std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
        std::cout << m_edges.size() << std::endl;

/// test : on a bien des éléments interfacés
        if (m_interface && remed.m_interface)
        {
/// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
            /* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
            /* m_interface->m_main_box.add_child(ei->m_top_edge); */
            /* m_edges[idx] = Edge(weight, ei); */
/// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
/// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
/// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
            m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
        }

/// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
/// References sur les listes de edges des sommets from et to
        std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
        std::vector<int> &veto = m_vertices[remed.m_to].m_in;
        vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
        veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

/// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
/// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
/// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
        m_edges.erase( eidx );

/// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
        std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
        std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
        std::cout << m_edges.size() << std::endl;

    }
}

void Graph::supprimer_sommet(int eidx)
{
    if(m_interface->m_sup.clicked())
    {

        Vertex &remed=m_vertices.at(eidx);
        if (m_interface && remed.m_interface)
        {
            if(remed.m_in.empty() == false || remed.m_out.empty() == false)
            {
                for(auto it=m_edges.begin(); it!=m_edges.end(); ++it)
                {
                    if(it->second.m_from == eidx || it->second.m_to ==eidx)
                    {
                        Edge &remed=m_edges.at(it->first);
                        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
                        m_edges.erase(it->first);


                    }
                }
            }



        }
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_box );
        m_vertices.erase( eidx );
    }
}


void Graph::retour()
{
    Graph g;
    g.menu();
    while(!m_interface->m_back.clicked())
    {
        g.update();
        grman::mettre_a_jour();

    }
}

void Graph::quitter()
{
    if(m_interface->m_q.clicked())
    {
        grman::fermer_allegro();
        exit(1);
    }

}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    sauvegarder(fichier);
    ajouter_arrete();
    ajouter_sommet();
    supprimer_arrete();
    g.supprimer_sommet();
    quitter();

    int a=m_interface->t();
    if(a==1)
    {
        retour();
    }

}

int GraphInterface::t()
{
    if(m_back.clicked())
    {
        return 1;
    }
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);

    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;

    m_vertices[id_vert1].m_out.push_back(id_vert2);
    m_vertices[id_vert2].m_in.push_back(id_vert1);
}

