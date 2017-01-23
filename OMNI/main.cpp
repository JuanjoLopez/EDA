

#include "omni.h"
//#include <windows.h>
#include <fstream>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "l_distance.h"

#define TOLERANCIA 2
#define MAXPAL 10
#define I 0

typedef unsigned int uint;


template< class T >
struct sort_candidates
{
    bool operator()( const pair<T, distance_type> &p1, const pair<T, distance_type> &p2)
    {
        return p1.second < p2.second;
    }
};


int main()
{


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

    OmniSequential<string> omni( m_espace, &l_distance );

    // Creamos la interfaz

    while(1){
        string q;
        cout << "Ingrese una palabra erronea: ";
        cin >> q;

        vector< pair< string, distance_type > > ret = omni.query( q, TOLERANCIA );

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
    }

    return 0;
}
