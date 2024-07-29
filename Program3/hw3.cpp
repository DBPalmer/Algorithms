#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/**
 * stores a candidates scores of WPM and IPM
 */
#define scores pair<float, float>

void merge_eligible(vector<pair<int, scores>>& vec, int l, int m, int r) {
    int a1; int a2; int i, j, x;
    a1 = m - l + 1;
    a2 = r - m;
    vector<pair<int, scores>> L, M;
    //populate each vector, splitting at m (which is where firstHalf stops and secondHalf begins)
    for (int i = 0; i < a1; i++) {
        L.push_back(vec[l + i]);
    }
    for (int j = 0; j < a2; j++) {
        M.push_back(vec[m + j + 1]);
    }
    i = 0; j = 0; x = l; int z;
    while (i < a1 && j < a2) {
        if (L[i].second.first < M[j].second.first || (L[i].second.first == M[j].second.first && L[i].second.second <= M[j].second.second)) {//in case WPM == WPM, sorts on IPM
            vec[x] = L[i];//add element to vec
            z = x;
            while (z > l) {//until if statement is false or beginning of vector is reached
                //checks if the element previously inserted into vec is a valid candidate
                if (vec[z - 1].second.second > vec[x].second.second && vec[z - 1].second.first < vec[x].second.first) {
                    vec.erase(vec.begin() + z - 1);//delete invalid candidate
                    //vector size is decreased by one, change x & z
                    x--;
                    z--;
                } else {//if vec[z-1] is a valid candidate, it can be inferred that every other candidate in front of vec[z-1] is also valid since I am sorting on WPM then IPM
                    z=0;//exit while loop, no further checking needed
                }
            }
            i++;
        } else if (L[i].second.first > M[j].second.first || (L[i].second.first == M[j].second.first && L[i].second.second > M[j].second.second)){//in case WPM == WPM, sorts on IPM
            vec[x] = M[j];//add element to vec
            z = x;
            while (z > l) {//until if statement is false or beginning of vector is reached
                //checks if the element previously inserted into vec is a valid candidate
                if (vec[z - 1].second.second > vec[x].second.second && vec[z - 1].second.first < vec[x].second.first) {
                    vec.erase(vec.begin() + z - 1);//delete invalid candidate
                    //vector size is decreased by one, change x & z
                    x--;
                    z--;
                } else {//if vec[z-1] is a valid candidate, it can be inferred that every other candidate in front of vec[z-1] is also valid since I am sorting on WPM then IPM
                    z=0;//exit while loop, no further checking needed
                }
            }
            j++;
        }
        x++;
    }
    while (i < a1) {//copy remaining L[] values into vector
        vec[x] = L[i];//add element to vec
        z = x;
        while (z > l) {//until if statement is false or beginning of vector is reached
            //checks if the element previously inserted into vec is a valid candidate
            if (vec[z - 1].second.second > vec[x].second.second && vec[z - 1].second.first < vec[x].second.first) {
                vec.erase(vec.begin() + z - 1);//delete invalid candidate
                //vector size is decreased by one, change x & z
                x--;
                z--;
            } else {//if vec[z-1] is a valid candidate, it can be inferred that every other candidate in front of vec[z-1] is also valid since I am sorting on WPM then IPM
                z=0;//exit while loop, no further checking needed
            }
        }
        i++;
        x++;
    }
    while (j < a2) {//copy remaining M[] values into vector
        vec[x] = M[j];//add element to vec
        z = x;
        while (z > l) {//until if statement is false or beginning of vector is reached
            //checks if the element previously inserted into vec is a valid candidate
            if (vec[z - 1].second.second > vec[x].second.second && vec[z - 1].second.first < vec[x].second.first) {
                vec.erase(vec.begin() + z - 1);//delete invalid candidate
                //vector size is decreased by one, change x & z
                x--;
                z--;
            } else {//if vec[z-1] is a valid candidate, it can be inferred that every other candidate in front of vec[z-1] is also valid since I am sorting on WPM then IPM
                z=0;//exit while loop, no further checking needed
            }
        }
        j++;
        x++;
    }

}
void recursiveBestApplicant(vector<pair<int, scores>>& vec, int const begin, int const end) {
    if (begin < end) {
        int m = begin+(end-begin)/2;
        //splitting vec into two halves and populating those halves. This makes deleting vector elements possible
        vector<pair<int, scores>> firstHalf;
        vector<pair<int, scores>> secondHalf;
        copy(vec.begin(), vec.begin()+m+1, back_inserter(firstHalf));
        copy(vec.begin()+m+1, vec.end(), back_inserter(secondHalf));
        //make a recursive call for each half
        recursiveBestApplicant(firstHalf, 0, firstHalf.size()-1);
        recursiveBestApplicant(secondHalf, 0, secondHalf.size()-1);
        //m has to split the two halves. m is not always the center, since more elements may be deleted from one half than the other
        m = firstHalf.size()-1;
        //add the secondHalf to the end of the firstHalf to combine the vectors
        firstHalf.insert(firstHalf.end(), secondHalf.begin(), secondHalf.end());
        vec = firstHalf;
        //merge step
        merge_eligible(vec, 0, m, vec.size()-1);
    }
}
vector<int> BestApplicants(const vector<pair<float, float> >& applicants) {
    vector<int> res;
    vector<pair<int, scores>> apps;//scores candidates and their ID
    for (int i=0; i<applicants.size(); i++){//preprocessing to copy applicants to apps so that IDs remain with candidates
        apps.push_back(make_pair(i,scores(applicants[i].first, applicants[i].second)));
    }
    recursiveBestApplicant(apps, 0, apps.size()-1);//first recursive call
    for (int i=0; i<apps.size(); i++){//copies eligible candidate IDs to res
        res.push_back(apps[i].first);
    }
    return res;
}

