//TP PAR LILY AMSELLEM

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <map>
#include <set>

#include "point2d.h"
#include "town.h"

using namespace std;


#ifndef srcPath
#define srcPath "."
#endif
// The path and name of the town file
string townFile = srcPath "/villes.txt";

//QUESTION 1: BUILD THE HISTOGRAM OF TOWN NAME REPETITIONS

//Function which returns a map whose Keys are town names, and whose data are the number of towns with that name
map<string,int> name_rep1(vector<Town> towns){
    //Use of an associative tab
    map<string,int> nb_repetition;
    //Go through the vector of Towns
    for (vector<Town>::iterator it=towns.begin();it!=towns.end();++it){
        string name=it->name();
        //If the association (name,int) exists, we increment the data
        //Otherwise, the association is automatically created
        nb_repetition[name]+=1;
    }

    return nb_repetition;
}

//Function which returns the histogram wanted
map<int,int> name_rep2(vector<Town> towns){
    //Construction of the histogram using another map
    map<string,int> nb_repetition=name_rep1(towns);
    map<int,int> histogram;
    for(map<string,int>:: iterator it1=nb_repetition.begin();it1!=nb_repetition.end();++it1)
        histogram[it1->second]+=1;
    return histogram;
}

//Display function
template <typename T,typename S>
void display_1(map<T,S> tab){
    for (typename map<T,S>:: iterator it=tab.begin();it!=tab.end();++it)
        cout<< it->second <<" towns have a name which is used " << it->first <<" times"<< endl;
}

//QUESTION 3 : TOWNS WHICH HAVE THE SAME COORDINATES

map<Point2D,int> coords_rep(vector<Town> towns){

    map<Point2D,int> nb_repetition;
    //Go through the vector of Towns
    for (vector<Town>::iterator it=towns.begin();it!=towns.end();++it){
        Point2D coords=it->point();
        //If the association (name,int) exists, we increment the data
        //Otherwise, the association is automatically created
        nb_repetition[coords]+=1;
    }

    return nb_repetition;
}

//Display function
template <typename T,typename S>
void display_2(map<T,S> tab){
    for (typename map<T,S>:: iterator it=tab.begin();it!=tab.end();++it)
        cout<< it->second <<" towns have the coordinates " << it->first<< endl;
}

//QUESTION 4: TOWNS WITH COORDINATES/NAME IN COMMON WITH AT LEAST ANOTHER TOWN
set<Town> same_name_and_coords(vector<Town> towns){
    set<Town> N;
    set<Town> C;
    map<string,int> same_names=name_rep1(towns);
    map<Point2D,int> same_coords=coords_rep(towns);

    for(vector<Town>:: iterator it=towns.begin();it!=towns.end();++it){
        if(same_coords[it->point()]>1)
            C.insert(*it);
        if(same_names[it->name()]>1)
            N.insert(*it);
    }

    cout<< C.size()<< " towns have the same coordinates than at least one other town"<< endl;
    cout<< N.size()<< " towns have the same name than at least another town"<< endl;

    //To get the intersection of both sets
    vector<Town> intersection_vector(min(N.size(),C.size()));
    vector<Town>:: iterator end=set_intersection(N.begin(),N.end(),C.begin(),C.end(),intersection_vector.begin());
    intersection_vector.resize(end-intersection_vector.begin());
    set<Town> intersection(intersection_vector.begin(),intersection_vector.end());
    return intersection;
}

//Display function
void display_3(set<Town> intersection){
    for (set<Town>::iterator it1=intersection.begin();it1!=intersection.end();++it1)
        cout<<*it1<< endl;
    cout<< "Il y a "<< intersection.size()<<" towns have at least another town with same name and at least another town with same coordinates"<<endl;
}

//QUESTION 5

void mistake_1(vector<Town> towns){

    //Computation of the set of towns which have the same name that another town
    //and the same coordinates that another town
    set<Town> intersection=same_name_and_coords(towns);
    int mistaken_towns=0;

    clock_t t1 = clock();
    for (set<Town>::iterator it1=intersection.begin();it1!=intersection.end();++it1){
        for(set<Town>::iterator it2=intersection.begin();it2!=intersection.end() && it2!=it1;++it2){
            for (set<Town>::iterator it3=intersection.begin();it3!=intersection.end() && it3!=it1 && it3!=it2;++it3){
                for(set<Town>::iterator it4=intersection.begin();it4!=intersection.end() && (it4!=it1) && (it4!=it2) && (it4!=it3);++it4){
                    if(it2->point()==it1->point() && it3->name()==it1->name() && it4->name()==it2->name() && it4->point()==it3->point())
                        mistaken_towns++;

                }

            }

        }
    }
    clock_t t2 = clock();
    double Time=(t2-t1)/(double)CLOCKS_PER_SEC;
    cout<<"temps de calcul: "<< Time<<endl;

    cout<<mistaken_towns<<" towns can be mistaken for another"<<endl;

}


void mistake_2(vector<Town> towns){

    //Computation of the set of towns which have the same name that another town
    //and the same coordinates that another town
    set<Town> intersection=same_name_and_coords(towns);
    vector<Town> v;
    int mistaken_towns=0;

    //We put the towns in a vector to use the methods of the Town Class
    for(set<Town> :: iterator it=intersection.begin();it!=intersection.end();++it)
        v.push_back(*it);

     //OTHER VERSION
     clock_t t1 = clock();
     for (vector<Town>::iterator it1=v.begin();it1!=v.end();++it1){
         vector<Town> same_coords=it1->towns_with_x_y(v,it1->x(),it1->y());
         vector<Town> same_name=it1->towns_with_name(v,it1->name());
         for(vector<Town>::iterator it2=same_coords.begin();it2!=same_coords.end() && *it2!=*it1;++it2){
             for (vector<Town>::iterator it3=same_name.begin();it3!=same_name.end() && *it3!=*it1 &&*it3!=*it2;++it3){
                 for(vector<Town>::iterator it4=v.begin();it4!=v.end() && ( *it4!=*it1) && ( *it4!=*it2) && ( *it4!=*it3);++it4){
                     if(it2->point()==it1->point() && it3->name()==it1->name() && it4->name()==it2->name() && it4->point()==it3->point())
                         mistaken_towns++;

                 }

             }

         }
     }

     clock_t t2 = clock();
     double Time=(t2-t1)/(double)CLOCKS_PER_SEC;
     cout<<"temps de calcul: "<< Time<<endl;

    cout<<mistaken_towns<<" towns can be mistaken for another"<<endl;

}



/*
 * Study French isotoponyms
 */
int main()
{
    /////
    ///// Read town file
    /////
    // Create an empty list of towns
    vector<Town> towns;
    // Read file
    cout << "Reading town file: " << townFile << endl;
    clock_t time1 = clock();
    int nb_towns = Town::read_file(townFile, towns);
    clock_t time2 = clock();
    // Sanity check
    if (nb_towns < 0) {
	cout << "Error while reading file" << endl;
	return 2;
    }
    if (nb_towns == 0) {
	cout << "No town found" << endl;
	return 1;
    }
    // Initialize random seed
    srand(time(NULL));
    // Say how many towns have been read
    cout << "File read in: "
	 << ((float)(time2-time1)/CLOCKS_PER_SEC) << " s" << endl;
    cout << "Number of towns in file: "
	 << towns.size() /* same as nb_towns */ << endl;
    //cout << "A random town, using format \"name[lat,lon](x,y)\": "
    //<< towns[rand() % towns.size()] << endl;

    //********QU 1: TOWNS WITH SAME NAME********
    //map<int,int> histogram=name_rep2(towns);
    //display_1(histogram);

    //********* QU 2: TOWNS WITH SAME COORDINATES********
    //map<Point2D,int> histogram=coords_rep(towns);
    //display_2(histogram);

    //*********QU 3: TOWNS WHO HAVE ANOTHER TOWN WITH SAME NAME AND ANOTHER TOWN WITH  SAME COORDINATES
    //set<Town> intersection=same_name_and_coords(towns);
    //display_3(intersection);

    //********QU 4: TOWNS WHICH CAN BE MISTAKEN ***********
    //mistake_1(towns);
    mistake_2(towns); //More efficient version

    // That's all folks
    return 0;
}
