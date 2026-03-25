#ifndef EVALUAR_HPP
#define EVALUAR_HPP
#include <string>
#include <map>
#include <list>
#include <vector>
#include <sstream>

#include "tree.h"

using namespace std;
using namespace aed;

namespace aed {
class Evaluar
{
	void printmap(map<int, list<bool> >& M) {
		cout << "M = {";
		map<int, list<bool> >::iterator p = M.begin();
		while (p!=M.end()) {
			cout << p->first << "->[";
			list<bool> &L = p->second;
			list<bool>::iterator q = L.begin();
			while (q!=L.end()) {
				cout << (*q ? "true" : "false");
				q++;
				if (q!=L.end()) cout << ", ";
			}
			cout << "]";
			p++;
			if (p!=M.end()) cout << ", ";
		}
		cout << "}" << endl;
	}

	list< list<int> > colas(list<int> &L)
	{
		list< list<int> > R;
		if (L.empty()) return R;
		list<int>::iterator it = L.begin();
		while (it != L.end())
		{
			R.push_back(list<int>(it, L.end()));
			++ it;
		}

		return R;
	}

	void s2l(string s, list<int> &L)
	{
		istringstream is(s);
		int n;
		while (is >> n)
			L.push_back(n);
	}

	void prl(list<int> &L)
	{
		if (L.empty()) return;
		list<int>::iterator il = L.begin();
		for (; &*il != &*L.rbegin(); il ++)
			cout << *il << " ";
		cout << *il;
	}

	void s2m(string s, map<int, list<bool> > &M)
	{
		M.clear();
		istringstream is(s);

		int k, n, v;
		while (is >> k >> n)
		{
			list<bool> L;

			for (int i = 0 ; i < n ; i ++)
			{
				is >> v;
				L.push_back(v);
			}
			M[k] = L;
		}
	}

	void s2m(string s, map<int, list<int> > &M)
	{
		M.clear();
		istringstream is(s);

		int k, n, v;
		while (is >> k >> n)
		{
			list<int> L;

			for (int i = 0 ; i < n ; i ++)
			{
				is >> v;
				L.push_back(v);
			}
			M[k] = L;
		}
	}

	void acum_hasta(list<int> &L, int n)
	{
		int acum = 0;
		list<int>::iterator it = L.begin();
		while (it != L.end())
		{
			acum += *it;
			it = L.erase(it);
			if (acum >= n)
			{
				L.insert(it, acum);
				acum = 0;
			}
		}
		if (acum > 0)
			L.push_back(acum);
	}

	int readnum(string &s, unsigned int &n)
	{
		int k = 0;
		bool negativo = false;
		if (s[n] == '-')
		{
			negativo = true;
			n ++;
		}

		while (s[n] >= '0' && s[n] <= '9')
		{
			k *= 10;
			k += s[n] - '0';
			++ n;
		}

		if (negativo) k *= -1;

		return k;
	}

	void lisp2tree(string s, tree<int> &T, unsigned int &i, tree<int>::iterator it)
	{
		while (i < s.size())
		{
			while (s[i] == ' ') ++ i;

			if (s[i] == '(')
			{
				++ i;
				while (s[i] == ' ') ++ i;
				it = T.insert(it, readnum(s, i));
				lisp2tree(s, T, i, it.lchild());
				++ it;
			}
			else if (s[i] == ')')
			{
				++ i;
				return;
			}
			else
			{
				it = T.insert(it, readnum(s, i));
				++ it;
			}
		}
	}

	void lisp2tree(string s, tree<int> &T)
	{
		unsigned int i = 0;
		lisp2tree(s, T, i, T.begin());
	}

	public:

	void evaluar1(int (*F) (tree<int>&, int))
	{
		cout << "Evaluando ejercicio 1" << endl;
		verificar1(F, "(1 (2 3 4 5) (6 (7 8 9)))", 0, 1);
		verificar1(F, "(1 (2 3 4 5) (6 (7 8 9)))", 1, 2);
		verificar1(F, "(1 (2 3 4 5) (6 (7 8 9)))", 2, 4);
		verificar1(F, "(1 (2 3 4 5) (6 (7 8 9)))", 3, 2);
		
		verificar1(F, "(1 (2 3 4 5) (6 (7 8 9) 0))", 2, 5);
		verificar1(F, "(1 (2 (3 (4 (5)))))", 1, 1);
		verificar1(F, "(1 (2 (3 (4 (5)))))", 2, 1);
		verificar1(F, "(1 (2 (3 (4 (5)))))", 3, 1);
		verificar1(F, "(1 (2 (3 (4 (5)))))", 4, 1);
		verificar1(F, "(1 (2 (3 (4 (5 6 7 8 9 0)))))", 5, 5);
		cout << "Fin de evaluar ejercicio 1" << endl << endl;
	}

	void verificar1(int (*F) (tree<int>&, int), string t, int l, int r)
	{
	
		tree<int> T;
		lisp2tree(t, T);
		if (F(T, l) == r)
			cout << "BIEN\n";
		else
			cout << "NO\n";
	}

	void evaluar2(bool (*F) (map<int, list<int> >&, map<int, list<int> >&, int))
	{
		cout << "Evaluando ejercicio 2" << endl;
		verificar2(F, "1 2 2 4 2 3 1 3 4 3 2 2 4 4 3 1 2 3", "4 2 5 7 5 3 4 6 7 6 2 5 7 7 3 4 5 6", 3, true);
		verificar2(F, "1 2 2 4 2 3 1 3 4 3 2 2 4 4 3 1 2 3", "4 2 5 7 5 3 4 6 7 6 2 5 7 7 3 4 5 6", 1, false);
		verificar2(F, "1 2 2 4 2 3 1 3 4 3 2 2 4 4 3 1 2 3", "4 2 5 7 5 3 4 6 7 6 2 5 7 7 3 4 5 6", 2, false);
		verificar2(F, "1 2 2 4 2 3 1 3 4 3 2 2 4 4 3 1 2 3", "1 2 2 4 2 3 1 3 4 3 2 2 4 4 3 1 2 3", 0, true);
		verificar2(F, "1 2 2 4 2 3 1 3 4 3 2 2 4 4 3 1 2 3", "1 2 2 4 2 3 1 3 4 3 2 2 4 4 3 1 2 3", 1, false);
		
		verificar2(F, "1 2 2 4 2 3 1 3 4 3 2 2 4 4 3 1 2 3", "4 2 5 7 5 3 4 6 7 6 2 5 7", 3, false);
		verificar2(F, "1 2 2 4 2 3 1 3 4 3 2 2 4", "4 2 5 7 5 3 4 6 7 6 2 5 7 7 3 4 5 6", 3, false);
		cout << "Fin de evaluar ejercicio 2" << endl << endl;
	}

	void verificar2(bool (*F) (map<int, list<int> >&, map<int, list<int> >&, int), string m1, string m2, int o, bool r) 
	{
		map<int, list<int> > M1, M2;
		s2m(m1, M1);
		s2m(m2, M2);
		if (F(M1, M2, o) == r)
			cout << "BIEN\n";
		else
			cout << "NO\n";
	}

	void evaluar3(void (*F) (list<int>&, map<int, list<int> >&))
	{
		cout << "Evaluando ejercicio 3" << endl;
		verificar3(F, "1 2 4 3 2 5 2 7 1 6 9 2 14", "1 3 2 4 6 3 1 2 5 1 2 7 0 9 2 2 14");
		verificar3(F, "1 2 1 2 1 2 1 2", "1 4 2");
		verificar3(F, "1 1 1 1 1 1 1 1", "1 0");
		verificar3(F, "1 1 1 1 1 1 1 2", "1 1 2");
		verificar3(F, "2 1 3 2 3 2 5 2 5", "1 0 3 2 2 2 5 1 2");
		
		cout << "Fin de evaluar ejercicio 3" << endl << endl;
	}
	
	void verificar3(void (*F) (list<int>&, map<int, list<int> >&), string l, string m)
	{
		list<int> L;
		s2l(l, L);
		map<int, list<int> > M, R;
		s2m(m, M);
		F(L, R);
		if (R == M)
			cout << "BIEN\n";
		else
			cout << "NO\n";
	}

	

};

}

#endif


