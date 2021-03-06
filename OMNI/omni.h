#include <vector>
#include <fstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
#define K 3                     // K >= 1
#define I 0

typedef int distance_type;
typedef unsigned int uint;

#include "l_distance.h"

#define TOLERANCIA 2
#define MAXPAL 10
#define I 0

template< class T >
struct sort_candidates
{
    bool operator()( const pair<T, distance_type> &p1, const pair<T, distance_type> &p2)
    {
        return p1.second < p2.second;
    }
};



template <class m_object_type>
class OmniSequential{
    typedef unsigned int uint;
    typedef distance_type (*distance_function)( const m_object_type&, const m_object_type& );

public:
    OmniSequential(){
        vector<string> m_espace;

    // Levantamos las palabras en m_espace

    ifstream ifile("dict.txt");
    string buffer;
    while( !ifile.eof() ){
        ifile >> buffer;
        m_espace.push_back(buffer);
    }
    ifile.close();

    /*
        m_espace.push_back("hola");
        m_espace.push_back("chola");
        m_espace.push_back("bola");
        m_espace.push_back("joya");
    */

    // Creamos la estructura de datos
    // El tiempo de creacion es n^2, así que puede demorar varios minutos
    // En mi caso tardó 30 minutos

    OmniSequential_init( m_espace, &l_distance );

    }

    void OmniSequential_init( const vector<m_object_type> &_space, distance_function _distance )
    {
        space = _space;
        distance = _distance;
        create_matrix();
    }

    vector< pair< m_object_type, distance_type > > query( const m_object_type& q, distance_type r ){//FUNCION DE CONSULTA PRINCIPAL
        vector< pair< m_object_type, distance_type > > candidates;
        get_candidates( q, r, candidates );
        return candidates;
    }

    void OmniSequential_query_error_word(const m_object_type& q , distance_type r)
    {
        //while(1){
        //string q;
        //cout << "Ingrese una palabra erronea: ";
        //cin >> q;

        vector< pair< string, distance_type > > ret = query( q, r );

        if( !ret.empty() ){
            sort( ret.begin(), ret.end(), sort_candidates<string>() );

            if( ret[I].second == I ){
                cout << "La palabra es correcta!" << endl;
            }else{
                cout << "Quiza quizo decir: " << endl;
                for( uint i = I; i < ret.size() && i < MAXPAL; ++i ){
                    cout << "Distancia: " << (uint)ret[i].second << "\tPalabra: " << ret[i].first << endl;
                }
            }
        }
        else{
            cout << "No hay sugerencias" << endl;
        }

        /*system("pause"); Windows
        system("cls");*/
        //}

    }

    ~OmniSequential(){
        delete_matrix();
    }


private:
    vector<m_object_type> space;
    distance_function distance;

    m_object_type focuses[K];
    distance_type* matrix[K];


    void create_matrix(){
       get_focuses();
       for( uint i = I; i < K; ++i )
       {
           matrix[i] = new distance_type[space.size()];
           for( uint j = I; j < space.size(); ++j )
               matrix[i][j] = distance( focuses[i], space[j] );
       }
    }

    void delete_matrix(){
        for( uint i = I; i < K; ++i )
            delete[] matrix[i];
    }

    void get_focuses(){
        focuses[I] = space[I];                                          // Usa como temporal
        uint total_focuses = I;
        for( uint i = I; i < K; ++i ){
            size_t focus_pos = I;
            distance_type max_distance = I;
            for( size_t it = I; it < space.size(); ++it ){
                distance_type current_distance;
                for( uint j = I; j < total_focuses || j == I; ++j )                 // Recorre focos existentes
                    current_distance += distance( focuses[j], space[it] );
                if( current_distance > max_distance ){
                    focus_pos = it;
                    max_distance = current_distance;
                }
            }
            focuses[i] = space[focus_pos];
            space.erase( space.begin() + focus_pos );
            ++total_focuses;
        }
    }

    void get_candidates( const m_object_type& q, distance_type r, vector< pair< m_object_type, distance_type > > &candidates ){
        bool eliminated[space.size()];
        for( uint i = I; i < space.size(); ++i )
            eliminated[i] = 0;

        for( uint i = I; i < K; ++i ){
            distance_type rp = distance( q, focuses[i] );

            if( rp <= r )
                candidates.push_back( pair< m_object_type, distance_type >( focuses[i], rp ) );

            for( size_t j = I; j < space.size(); ++j )
                if( !eliminated[j] )
                    if( rp - r > matrix[i][j] || matrix[i][j] > rp + r )
                        eliminated[j] = 1;
        }

        for( size_t i = I; i < space.size(); ++i ){
            if( !eliminated[i] ){
                distance_type rp = distance( q, space[i] );
                if( rp <= r )
                    candidates.push_back( pair< m_object_type, distance_type >( space[i], rp ) );
            }
        }
    }

};
