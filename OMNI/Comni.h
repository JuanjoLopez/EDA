

typedef void Comni;

#ifdef __cplusplus
extern "C" {
	#endif
	Comni * omnisequential_new(const vector<string> &space);
	vector<pair<string,distance_type> > omni_query(Comni * t,const string &q,int distance);
	void omni_delete(Comni * t);
	#ifdef __cplusplus
}
#endif