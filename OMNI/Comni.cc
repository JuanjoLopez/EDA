#include "omni.h"
#include "Comni.h"

#include "l_distance.h"

extern "C" {
	
	Comni * omnisequential_new(const vector<string> &space)
	{
		OmniSequential<string> *t = new OmniSequential(space, &l_distance);
		return (Comni *) t;	
	}

	vector<pair<string,distance_type> > omni_query(Comni *t,const string &q,distance_type r)
	{
		OmniSequential<string> *t2 = (OmniSequential *) t;
		vector<pair< string,distance_type> > ret = t2->query(q,r);
		return ret;
	}

	void omni_delete(Comni * t)
	{
		
	}
	
}//extern