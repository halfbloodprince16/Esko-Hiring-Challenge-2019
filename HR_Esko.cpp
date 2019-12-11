#include"bits/stdc++.h"
#include <sstream> 
using namespace std;
/*
i/p format:
housingcomplex,sector,block,tower,apartment
sector = 10 block
block = 3 tower
tower = 300 apartment
housingcomplex = 8 sector

o/p format :
1housingcomplex = 8sector = 80block = 240tower = 72000apartment

i/p format : 
university,college,class,student
university = 6000 student
college = 600 student
class = 50 student

o/p format : 
1university = 10college = 120class = 6000student

*/

struct Query
{
	string a,b;
	int val=1;
};

std::map<string,bool>m;
std::map<string,bool>::iterator itr;

string get_last_node(struct Query q[],int n)
{
	for(int i=0;i<n;i++)
	{
		m[q[i].a] = true;
	}

	for(itr=m.begin();itr!=m.end();itr++)
	{
		if(itr->second == 0)
		{
			return itr->first;
		}
	}
}

bool cond(struct Query q[],int n,string last)
{
	for(int i=0;i<n;i++)
	{
		if(q[i].b != last)
		{
			return false;
		}
	}
	return true;
}

bool compare(Query a, Query b)
{
	//for descending order replace with a.roll >b.roll
	if(a.val > b.val)		
		return 1;
	else
		return 0;
}

string prepare_query(Query q[],int n)
{
	string result;
	result += to_string(1) + q[0].a;

	for(int i=1;i<n;i++)
	{
		result += " = ";
		int val = q[0].val/q[i].val;
		result += to_string(val);
		result += q[i].a;
	}

	result += " = ";
	result += to_string(q[0].val);
	result += q[0].b;

	return result;
}

int main(int argc, char const *argv[])
{
	string str;
	getline(cin,str);

	int cnt=0;
	string temp;
	for(int i=0;str[i]!='\0';i++)
	{
		if(str[i] == ',')
		{
			m.insert({temp,false});
			temp="";
			cnt++;
		}
		else
		{
			temp += str[i];
		}
	}
	m.insert({temp,false});
	//cout<<cnt;

	Query q[cnt];

	for(int i=0;i<cnt;i++)
	{
		getline(cin,str);
		string a,b,c;
		int j=0;
		for(j=0;str[j]!=' ';++j)
		{
			a += str[j];
		}

		for(j = j+3;str[j]!=' ';j++)
		{
			b += str[j];
		}

		for(j = j+1;str[j]!='\0';j++)
		{
			c += str[j];
		}
		stringstream geek(b); 
	    int x = 0; 
	    geek >> x;

	    //m[{a,c}] = x;

	    q[i].a = a;
	    q[i].b = c;
	    q[i].val = x; 
	}

	string last = get_last_node(q,cnt);

	while(cond(q,cnt,last) != true)
	{
		for(int i=0;i<cnt;i++)
		{
			if(q[i].b == last)
			{
				for(int j=0;j<cnt;j++)
				{
					if(q[i].a == q[j].b)
					{
						q[j].b = q[i].b;
						q[j].val = q[j].val*q[i].val;
					}
				}
			}
		}
	}

	//till here we have converted our queries into one single format.
	//now we'll sort them

	sort(q,q+cnt,compare);

	string final_query = prepare_query(q,cnt);
	cout<<final_query<<endl;
	/*
	for(int i=0;i<cnt;i++)
	{
		cout<<q[i].a<<" "<<q[i].b<<" "<<q[i].val<<endl;
	}*/

	return 0;
}