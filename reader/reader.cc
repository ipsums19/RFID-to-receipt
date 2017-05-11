#include<iostream>
#include<fstream>
#include<map>
#include<string>

using namespace std;

int main()
{
    ifstream dummy ("../data/tags.csv", ifstream::in);

    string product, price;

    //wait till there's something into the file
    getline(dummy, product, ',');
    while(!dummy.good()){}

    ifstream file ("../data/tags.csv", ifstream::in);

    map<string,pair<int,double> > groceries;

    while(file.good())
    {
        getline(file, product, ',');
        getline(file, price);
        if(groceries.find(product) == groceries.end()){
            groceries[product] = make_pair(1, stod(price));
        } else{
            groceries[product].first++;
        }
    }
    map<string,pair<int,double> >::const_iterator it = groceries.begin();
    for (++it; it != groceries.end(); ++it)
    {
        cout << "NAME = " << it->first << "   ";
        cout << "NUMBER = " << it->second.first << "   ";
        cout << "COST = " << it->second.second << endl;
    }

    ifstream aux_page("../web/aux_page.html");
    ifstream page("../web/page.html");

}
