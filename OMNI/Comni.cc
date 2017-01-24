#include "Comni.h"
#include "omni.h"

//#include "l_distance.h"

extern "C" {
	
	#include <string>
	Comni * omnisequential_new()
	{

		OmniSequential<string> *t = new OmniSequential<string>();

		return (Comni *) t;	
	}

	void omni_query(Comni * t, const char * q,int distance)
	{
		OmniSequential<string> *t2 = (OmniSequential <string> *) t;

		t2->OmniSequential_query_error_word(q,distance);


	}

	void omni_delete(Comni * t)
	{

	}
	
}//extern