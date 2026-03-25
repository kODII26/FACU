#ifndef EVALUAR_HPP
#define EVALUAR_HPP

#include <string>
#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

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

	void s2vl(string s, vector< list<int> > &v)
	{
		istringstream is(s);
		int n1, n2;
		while (is >> n1)
		{
			v.push_back(list<int>());
			for (int i = 0 ; i < n1 ; i ++)
			{
				is >> n2;
				v.back().push_back(n2);
			}
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

	public:

	void evaluar1(void (*F) (list<int>&, int, vector< list<int> >&))
	{
		cout << "Evaluando ejercicio 1" << endl;
		verificar1(F, "1 2 3 4 5 6 7 8 9 0", 2, "5 2 4 6 8 0 5 1 3 5 7 9");
		verificar1(F, "1 2 3 4 5 6 7 8 9 0", 3, "4 3 6 9 0 3 1 4 7 3 2 5 8");
		verificar1(F, "1 2 3 4 5 6 7 8 9 0", 4, "3 4 8 0 3 1 5 9 2 2 6 2 3 7");
		verificar1(F, "1 2 3 4 5 6 11 12 13 14 15 16 21 22 23 24 25", 2, "8 2 4 6 12 14 16 22 24 9 1 3 5 11 13 15 21 23 25");
		verificar1(F, "1 2 3 4 5 6 11 12 13 14 15 16 21 22 23 24 25", 3, "6 3 6 12 15 21 24 6 1 4 13 16 22 25 5 2 5 11 14 23");
		verificar1(F, "1 2 3 4 5 6 11 12 13 14 15 16 21 22 23 24 25", 4, "4 4 12 16 24 5 1 5 13 21 25 4 2 6 14 22 4 3 11 15 23");
		verificar1(F, "1 2 3 4 5 6 11 12 13 14 15 16 21 22 23 24 25", 5, "3 5 15 25 5 1 6 11 16 21 3 2 12 22 3 3 13 23 3 4 14 24");
		verificar1(F, "5 10 15 20 25 30 35 40 45 50", 5, "10 5 10 15 20 25 30 35 40 45 50 0  0  0  0");
		verificar1(F, "5 10 15 20 25 30 35 40 45 50", 3, "3 15 30 45 3 10 25 40 4 5 20 35 50");
		verificar1(F, "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25", 1, "25 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25");
		verificar1(F, "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25", 2, "12 2 4 6 8 10 12 14 16 18 20 22 24 13 1 3 5 7 9 11 13 15 17 19 21 23 25");
		verificar1(F, "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25", 3, "8 3 6 9 12 15 18 21 24 9 1 4 7 10 13 16 19 22 25 8 2 5 8 11 14 17 20 23");
		verificar1(F, "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25", 4, "6 4 8 12 16 20 24 7 1 5 9 13 17 21 25 6 2 6 10 14 18 22 6 3 7 11 15 19 23");
		verificar1(F, "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25", 5, "5 5 10 15 20 25 5 1 6 11 16 21 5 2 7 12 17 22 5 3 8 13 18 23 5 4 9 14 19 24");
	}

	void verificar1(void (*F) (list<int>&, int, vector< list<int> >&), string s1, int m, string s2)
	{
		vector< list<int> > v1, v2;
		list<int> L;
		s2l(s1, L);
		F(L, m, v1);
		/*
		for (int i = 0 ; i < v.size() ; i ++)
		{
			//cout << "v[" << i << "] = ";

			cout << v[i].size() << " ";
			prl(v[i]);
			cout << " ";
		}
		cout << endl;
		cout << endl;
		*/

		s2vl(s2, v2);
		if (v1 == v2)
			cout << "BIEN" << endl;
		else
			cout << "NO" << endl;
	}

	void evaluar2(bool (*F) (list<int>&, list<int>&))
	{
		cout << "Evaluando ejercicio 2" << endl;
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "1", true);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "1 2", true);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "1 3", true);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "1 4", true);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "1 0", true);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "1 1", false);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "2 1", false);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "2 2", false);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "2 3", true);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "2 9", true);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "1 2 3 4 5 6 7 8 9 0", true);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "1 3 4 5 6 7 8 9 0", true);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "1 3 4 6 7 8 9 0", true);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "1 3 4 6 7 8 9", true);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "1 3 6 7 8 9", true);
		verificar2(F,"1 2 3 4 5 6 7 8 9 0", "1 6 5 7 8 9", false);
	}

	void verificar2(bool (*F) (list<int>&, list<int>&), string s1, string s2, bool b)
	{
		list<int> L1, L2;
		s2l(s1, L1);
		s2l(s2, L2);
		if (b == F(L1, L2))
			cout << "BIEN" << endl;
		else
			cout << "NO" << endl;
	}

	void evaluar3(void (*F) (list<int>&, list<int>&))
	{
		cout << "Evaluando ejercicio 3" << endl;
		verificar3(F, "1 2 2 3 4 5", "2 2");
		verificar3(F, "1 2 2 0 4 5", "2 2 0 4");
		verificar3(F, "1 3 5", "");
		verificar3(F, "1 3 4 5 6", "4");
		verificar3(F, "1 3 5 2 4 6", "2 4 6");
		verificar3(F, "1 0 2 1 4 5 3 5 2 4 6", "2 4 6");
	}

	void verificar3(void (*F) (list<int>&, list<int>&), string s1, string s2)
	{
		list<int> L1, L2, R;
		s2l(s1, L1);
		s2l(s2, L2);
		F(L1, R);
		if (R == L2)
			cout << "BIEN" << endl;
		else
			cout << "NO" << endl;
	}
};

}

#endif


