
typedef void Comni;

#ifdef __cplusplus
extern "C" {
	#endif
	Comni * omnisequential_new();
	void omni_query(Comni * t, const char * q, int distance);
	void omni_delete(Comni * t);
	#ifdef __cplusplus
}
#endif