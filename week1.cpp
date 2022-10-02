#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
        string s1="abcdasd";
       ofstream fout("1.txt");
      fout.write(s1.c_str(),s1.length());
      fout.close();
       ifstream fin("1.txt",ios::in);
      char x[1024];
     fin>>x;
     cout<<x;
      fin.close();
      return 0;
}
;
