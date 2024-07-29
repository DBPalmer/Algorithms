#include <vector>

using namespace std;

pair< vector<float>, vector<int> >  WWWWW(vector<float> w, vector<float> p, int s, int t)
{
    vector<float> prize; vector<int> choice; //create vectors
    prize.resize(p.size()); choice.resize(p.size()-1); //resize allows for index assignment
    for (int i=p.size()-1; i>=1; i--){//loop through questions, starting at the last question and working backwards
        float checkpoint; float val;
        //finds and assigns proper checkpoint
        if (i > t) {checkpoint = w[t];}
        else if (s < i && i <=t) {checkpoint = w[s];}
        else if (i <= s){checkpoint = 0;}
        if (i != p.size()-1){
            if (choice[i] == 1){//if the choice was to not quit i+1, then assign val that question's prize
                val = prize[i];
            } else { val = w[i];}//if the choice was to quit i+1, val is i's weight
        } else { val = w[i];} //if question is the last, then val is automatically i's weight
        if (w[i-1] >= p[i] * val + (1-p[i]) * checkpoint){//decision to quit
            prize[i-1] = w[i-1];
            choice[i-1] = 0;
        } else {//decision to not quit
            prize[i-1] = p[i] * val + (1 - p[i]) * checkpoint;
            choice[i-1] = 1;
        }
    }
    prize[p.size()-1] = w[p.size()-1];//user won, gets all the money
    return make_pair(prize, choice);
}

pair<vector<vector<float>>, vector<vector<int>>>  WWWWW_1(vector<float> w, vector<float> p, int s, int t)
{
    vector<vector<float>> prize; vector<vector<int>> choice; //create vectors
    //resize allows for index assignment
    prize.resize(2); choice.resize(2);
    prize[0].resize(p.size());
    prize[1].resize(p.size());
    choice[0].resize(p.size()-1);
    choice[1].resize(p.size()-1);
    for (int i=p.size()-1; i>=1; i--){//loop through questions, starting at the last question and working backwards
        float checkpoint; float val;
        //finds and assigns proper checkpoint
        if (i > t) {checkpoint = w[t];}
        else if (s < i && i <=t) {checkpoint = w[s];}
        else if (i <= s){checkpoint = 0;}
        if (i != p.size()-1){
            if (choice[0][i] == 1){//if the choice was to not quit i+1, then assign val that question's prize
                val = prize[0][i];
            } else { val = w[i];}//if the choice was to quit i+1, val is i's weight
        } else { val = w[i];}//if question is the last, then val is automatically i's weight
        if (w[i-1] >= p[i] * val + (1-p[i]) * checkpoint){//decision to quit
            prize[0][i-1] = w[i-1];
            choice[0][i-1] = 0;
        } else {//decision to not quit
            prize[0][i-1] = p[i] * val + (1 - p[i]) * checkpoint;
            choice[0][i-1] = 1;
        }
    }
    prize[0][p.size()-1] = w[p.size()-1];//user won, gets all the money
    //choice[0] and prize[0] are complete, now its time to evaluate the lifeline
    for (int i=p.size()-1; i>=1; i--) {//loop through questions, starting at the last question and working backwards
        float checkpoint; float val;
        float val2; //stores prize value used in lifeline calculation
        float lifeProb; //stores probability if lifeline is used
        //finds and assigns proper checkpoint
        if (i > t) {checkpoint = w[t];}
        else if (s < i && i <=t) {checkpoint = w[s];}
        else if (i <= s){checkpoint = 0;}
        if (i != p.size()-1){
            if (choice[1][i] == 1 || choice[1][i] == 2){//if the choice was to not quit i+1, then assign val that question's prize
                val = prize[1][i];
            } else { val = w[i];}//if the choice was to quit i+1, val is i's weight
            val2 = prize[0][i];//as long as i is not the last question, val2 is the prize[0] of the next question
        } else {//if question is the last, then val & val2 are automatically i's weight
            val = w[i];
            val2 = w[i];
        }
        lifeProb = 0.5 + p[i] / 2.0;
        if (lifeProb > 0.999) { lifeProb = 0.999; }
        float max1 = max(w[i - 1], p[i] * val + (1 - p[i]) * checkpoint);
        float max2 = max(max1, lifeProb * val2 + (1-lifeProb) * checkpoint);
        prize[1][i-1] = max2;//assings max of quit, not quit, and lifeline to prize[1][i]
        if (max2 == w[i - 1]){//choice to quit
            choice[1][i-1] = 0;
        } else if (max2 == p[i] * val + (1 - p[i]) * checkpoint) {//choice to not quit
            choice[1][i-1] = 1;
        } else {//choice to use lifeline
            choice[1][i-1] = 2;
        }
    }
    prize[1][p.size()-1] = w[p.size()-1];//user won, gets all the money
    return make_pair(prize, choice);
}

pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_2(vector<float> w, vector<float> p, int s, int t)
{
    vector < vector<float> > fres;
    vector < vector<int> > fres2;

    vector <float> res0;
    vector <int> res1;

    res0.push_back(1.0);
    res0.push_back(2.0);
    res1.push_back(1);

    fres.push_back(res0);
    fres.push_back(res0);
    fres.push_back(res0);
    fres.push_back(res0);
    fres2.push_back(res1);
    fres2.push_back(res1);
    fres2.push_back(res1);
    fres2.push_back(res1);

    return make_pair(fres, fres2);
}

 
