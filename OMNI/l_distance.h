#include <iostream>
using namespace std;
#define init 0
#define next 1
typedef const string static_str;
typedef unsigned int uint;

distance_type l_distance(static_str &str1, static_str &str2)
{
   
    size_t len_str1 = str1.size();
    size_t len_str2 = str2.size();

    distance_type dist[len_str1+next][len_str2+next];

    for(uint i=init; i<=len_str1; ++i)
        dist[i][init] = i;
    for(uint j=init; j<=len_str2; ++j)
        dist[init][j] = j;

    distance_type cost;
    for(uint i=next; i<=len_str1; ++i)
    {
        for(uint j=next; j<=len_str2; ++j)
        {
            cost = ( str1[i-next] == str2[j-next] )?  0 : 1 ;
            dist[i][j] = min( min ( dist[i-next][j] + next ,              // deletion
                                    dist[i][j-next] + next ),             // insertion
                              dist[i-next][j-next] + cost );        // substitution
        }
    }

    return dist[len_str1][len_str2];
}
