#ifndef 7SEGMENTS_H
#define 7SEGMENTS_H

//NE PAS CREER DOBJETS DE TYPE DISPLAY, SEULEMENT APPELLER COMPTEUR EN CAS DE BESSOIN.


using namespace std;

class Display
{
	private:

		int a;
		int b;
		int c;
		int d;
		int e;
		int f;
		int g;
		int dp;
	public:
		Display();
		~Display()
		void Set(int number);
		void SetDP(bool etat);
		void AllOff();
		void SetPins(int a, int b, int c, int d, int e, int f, int g, int dp);
};

class Compteur
{
	private:
		int dizaines;
		int unites
		int increment;
		Display Afficheur1;
		Display Afficheur2;
	public: 
		Compteur();
		~Compteur();
		void Add_1();
		void Remove_1();
		void Reset();
		void Setup(int valeur);

}; 

#endif
