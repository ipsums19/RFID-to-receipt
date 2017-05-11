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
    fstream page;
    page.open("../web/page.html", fstream::trunc | fstream::out);;

    string line;

    while(aux_page.good())
    {
        getline(aux_page, line);
        page << line << endl;
        if(line.find("<tbody>") != -1){
            double total = 0.0;
            map<string,pair<int,double> >::const_iterator it = groceries.begin();
            for (++it; it != groceries.end(); ++it)
            {
                page << "      <tr>" << endl;;
                page << "        <td>" << it->first << "</td> ";
                page << "<td>" << it->second.second << "</td> ";
                page << "<td>" << it->second.first << "</td> ";
                total += it->second.first * it->second.second;
                page << "<td>" << it->second.first * it->second.second << "</td> " << endl;;
                page << "      </tr>" << endl;
            }
            page << "<tr>";
            page << "<td></td>";
            page << "<td></td>";
            page << "<td></td>";
            page << "<td></td>";
            page << "</tr>" << endl;

            page << "      <tr>" << endl;;
            page << "        <td><dt>" << "TOTAL" << "</dt></td> ";
            page << "<td>" <<  "</td> ";
            page << "<td>" <<  "</td> ";
            page << "<td><dt>" << total << " €" << "</dt></td> " << endl;;
            page << "      </tr>" << endl;
        }
    }

}
