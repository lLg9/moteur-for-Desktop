#ifndef MOTEUR_CONTENT_BASE
#define MOTEUR_CONTENT_BASE

class moteur_content_base{
public:
	virtual void import_data() = 0;
	virtual void q_n_a() = 0;
	virtual void export_data() = 0;
protected: 
	moteur_content_base() {}
};


#endif