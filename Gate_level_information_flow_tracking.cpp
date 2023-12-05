/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include<algorithm>
#include <bits/stdc++.h>

using namespace std;
///////////////////////////////
int f(int n);
int f(int n) {
  if(n > 1)
    return n * f(n - 1);
  else
    return 1;
}
////////////////////////
int and_gate(int a, int b){
    int o = a && b;
    return o;
}

int or_gate(int a, int b){
    int o = a || b;
    return o;
}

int nand_gate(int a, int b){
    int o = !(a && b);
    return o;
}

int nor_gate(int a, int b){
    int o = !(a || b);
    return o;
}
int not_gate(int a){
    int o = !a;
    return o;
}

int xor_gate(int a, int b){
    int o = a^b;
    return o;
}

int shadowlogic_andgate(int a, int b, int at, int bt){
    int p = at && bt;
    int q = at && b;
    int r = a && bt;
    int s = (p || q || r);
    return s;
}

int shadowlogic_nandgate(int a, int b, int at, int bt){
    int p = at && bt;
    int q = at && b;
    int r = a && bt;
    int s = (p || q || r);
    return s;
}

int shadowlogic_orgate(int a, int b, int at, int bt)
{
    int not_b = !b;
    int not_a = !a;
    int p = at && bt;
    int q = at && not_b;
    int r = not_a && bt;
    int s = (p|| q || r);
    return s;
}
int shadowlogic_norgate(int a, int b, int at, int bt)
{
    int not_b = !b;
    int not_a = !a;
    int p = at && bt;
    int q = at && not_b;
    int r = not_a && bt;
    int s = (p || q || r);
    return s;
}

int shadowlogic_notgate(int at)
{
    int s = at;
    return s;
}

int shadowlogic_xorgate(int at, int bt)
{
    int s = at || bt;
    return s;
}
////////////////////////////

int output_value(string s, int a, int b){
    int o;
    if(s == "NOT"){
        o = not_gate(a);
    }
    else if(s == "AND"){
        o = and_gate(a, b);
    }
    else if(s == "NAND"){
        o = nand_gate(a, b);
    }
    else if(s == "OR"){
        o = or_gate(a, b);
    }
    else if(s == "NOR"){
        o = nor_gate(a, b);
    }
    else if(s == "XOR"){
        o = xor_gate(a, b);
    }
    return o;
}

int tainted_output_value(string s, int a, int b, int at, int bt){
    int o;
    if(s == "NOT"){
        o = shadowlogic_notgate(at);
    }
    else if(s == "AND"){
        o = shadowlogic_andgate(a, b, at, bt);
    }
    else if(s == "NAND"){
        o = shadowlogic_nandgate(a, b, at, bt);
    }
    else if(s == "OR"){
        o = shadowlogic_orgate(a, b, at, bt);
    }
    else if(s == "NOR"){
        o = shadowlogic_norgate(a, b, at, bt);
    }
    else if(s == "XOR"){
        o = shadowlogic_xorgate(at, bt);
    }
    return o;
}

/////////////////////////////////////////
string get_input_variable(string s){
    int i = s.find('(');
    int j = s.find(')');
    string a = s.substr((i + 1), (j - i - 1));
    return a;
}

string gate_out(string s){
    int i = s.find(' ');
    string output_of_gate = s.substr(0, i);
    return output_of_gate;
}

string gate_name(string s){
    int i = s.find(' ');
    int j = s.find('(');
    string gate = s.substr((i + 3), (j - i - 3));
    return gate;
}

string gate_input1(string s){
    string input1_of_gate;
    int j = s.find('(');
    int k = s.find(')');
    int l;
    string gate1 = gate_name(s);
    if(gate1 == "NOT"){
        input1_of_gate = s.substr((j + 1), (k - j - 1));
    }
    else{
        l = s.find(',');
        input1_of_gate = s.substr((j + 1), (l - j - 1));
    }
    return input1_of_gate;
}

string gate_input2(string s){
    string input2_of_gate;
    int j = s.find('(');
    int k = s.find(')');
    int l;
    string gate2 = gate_name(s);
    if(gate2 == "NOT"){
        input2_of_gate = "";
    }
    else{
        l = s.find(',');
        input2_of_gate = s.substr((l + 2), (k - l - 2));
    }
    return input2_of_gate;
}

string get_output_variable(string s){
    int i = s.find('(');
    int j = s.find(')');
    string a = s.substr((i + 1), (j - i - 1));
    return a;
}
/////////////////////////////
bool sortFunc( const vector<string>& v1,
           const vector<string>& v2 ) {
 return v1[4] < v2[4];
 }
 /////////////
void create(multimap <string, int> &m, int a){
    int c = 0;
    multimap <string, int> :: iterator p;
    p = m.begin();
    while((c < a) && (p != m.end())){
        c++;
        p++;
    }
    p->second = 1;
    if(p != m.begin()){
        p--;
        p->second = 0;
        p++;
    }
}
//////////////
void com(multimap <string, int> &m, int *arr, int n1){
    int n2 = 0;
    multimap <string, int> :: iterator p1;
    for(p1 = m.begin(); p1 != m.end(); p1++){
        p1->second = arr[n2];
        n2++;
    }
}
/////////////

int main()
{
    /////// Input and Output variables ////////
    multimap <string, int> input_variables;
    multimap <string, int> output_variables;
    multimap <string, int> variables_level;
    multimap <string, int> variables;
    multimap <string, int> taint_variables;
    multimap <string, int> input_taint_variables;
    vector<vector<string>> gate_information;
    ifstream inFile;
    inFile.open("abcd.txt");
    string line;
    while(!inFile.eof()){
        getline(inFile, line);
        if(inFile.good()){
            string s1 = line.substr(0, 5);
            string s2 = line.substr(0, 6);
            if(s1 == "INPUT"){
                string input = get_input_variable(line);
                input_variables.insert(pair <string, int> (input, 0));
                variables.insert(pair <string, int> (input, 1));
                taint_variables.insert(pair <string, int> (input, 0));
                input_taint_variables.insert(pair <string, int> (input, 0));
            }
            else if(s2 == "OUTPUT"){
                string output = get_output_variable(line);
                output_variables.insert(pair <string, int> (output, 0));
            }
            else{
                string out = gate_out(line);
                string gate = gate_name(line);
                string input1 = gate_input1(line); 
                string input2 = gate_input2(line);
                vector<string> v1{out, gate, input1, input2};
                gate_information.push_back(v1);
                if(!variables_level.count(out)){
                    variables_level.insert(pair <string, int> (out, -1));
                }
                if(!variables_level.count(input1)){
                    variables_level.insert(pair <string, int> (input1, -1));
                }
                if((!variables_level.count(input2)) && (input2 != "")){
                    variables_level.insert(pair <string, int> (input2, -1));
                }
            }
        }
    }
    
    
    //LEVELIZATION//
    int n = gate_information.size();
    //
    multimap <string, int> :: iterator itr;
    for (itr = input_variables.begin(); itr != input_variables.end(); ++itr)
    {
        multimap <string, int> :: iterator itr1;
        itr1 = variables_level.find(itr->first);
        itr1->second = 0;
    }
    //
    int k = 0;
    while(k < n){
        for(int x = 0; x<n; x++){
            if(gate_information[x][1] == "NOT"){
                multimap <string, int> :: iterator itr1;
                itr1 = variables_level.find(gate_information[x][2]);
                if((itr1->second != -1) && (gate_information[x].size() < 5)){
                    int c = itr1->second + 1;
                    multimap <string, int> :: iterator itr2;
                    itr2 = variables_level.find(gate_information[x][0]);
                    itr2->second = c;
                    gate_information[x].push_back(to_string(c));
                }
            }
            else{
                multimap <string, int> :: iterator itr1;
                itr1 = variables_level.find(gate_information[x][2]);
                multimap <string, int> :: iterator itr2;
                itr2 = variables_level.find(gate_information[x][3]);
                if((itr1->second != -1) && (itr2->second != -1) && (gate_information[x].size() < 5)){
                    int m;
                    if(itr1->second >= itr2->second){
                        m = itr1->second;
                    }
                    else{
                        m = itr2->second;
                    }
                    int c = m + 1;
                    multimap <string, int> :: iterator itr3;
                    itr3 = variables_level.find(gate_information[x][0]);
                    itr3->second = c;
                    gate_information[x].push_back(to_string(c));
                }
            }
        }
        k++;
    }
    sort(gate_information.begin(), gate_information.end(), sortFunc);
    
    ///////////////
    int noi = input_variables.size();
    int *input_array = new int[noi]{0};
    
    //////////////Evaluation////////////
    int limit = 0;
    int q = 0;
    int limit1 = 100;
    while((q <= noi) && (limit < limit1))
    {
        if(q != 0){
            input_array[q - 1] = 1;
        }
        int nop = f(noi)/(f(q)*f(noi - q));
        int z = 0;
        while((z<nop) && (limit < limit1))
        {
            com(input_variables, input_array, noi);
            multimap <string, int> :: iterator y1;
            multimap <string, int> :: iterator y2;
            for(y1 = input_variables.begin(); y1 != input_variables.end(); ++y1){
                y2 = variables.find(y1->first);
                y2->second = y1->second;
            }
            int *taint_input_array = new int[noi]{0};
            int qt = 0;
            while((qt <= noi) && (limit < limit1))
            {
                if(qt != 0){
                    taint_input_array[qt - 1] = 1;
                }
                int nopt = f(noi)/(f(qt)*f(noi - qt));
                int zt = 0;
                while((zt < nopt) && limit < limit1)
                {
                    com(input_taint_variables, taint_input_array, noi);
                    multimap <string, int> :: iterator y3;
                    multimap <string, int> :: iterator y4;
                    for(y3 = input_taint_variables.begin(); y3 != input_taint_variables.end(); ++y3){
                        y4 = taint_variables.find(y3->first);
                        y4->second = y3->second;
                    }
                    for(int i=0; i<gate_information.size(); i++){
                        if(gate_information[i][1] == "NOT"){
                            multimap <string, int> :: iterator it1;
                            multimap <string, int> :: iterator it2;
                            it1 = variables.find(gate_information[i][2]);
                            it2 = taint_variables.find(gate_information[i][2]);
                            int b = 0;
                            int bt = 0;
                            int a = it1->second;
                            int at = it2->second;
                            int o1 = output_value(gate_information[i][1], a, b);
                            int ot = tainted_output_value(gate_information[i][1], a, b, at, bt);
                            variables.insert(pair <string, int> (gate_information[i][0], o1));
                            taint_variables.insert(pair <string, int> (gate_information[i][0], ot));
                        }
                        else{
                            multimap <string, int> :: iterator it1;
                            multimap <string, int> :: iterator it2;
                            multimap <string, int> :: iterator it3;
                            multimap <string, int> :: iterator it4;
                            it1 = variables.find(gate_information[i][2]);
                            it2 = taint_variables.find(gate_information[i][2]);
                            it3 = variables.find(gate_information[i][3]);
                            it4 = taint_variables.find(gate_information[i][3]);
                            int a = it1->second;
                            int b = it3->second;
                            int at = it2->second;
                            int bt = it4->second;
                            int o1 = output_value(gate_information[i][1], a, b);
                            int ot = tainted_output_value(gate_information[i][1], a, b, at, bt);
                            variables.insert(pair <string, int> (gate_information[i][0], o1));
                            taint_variables.insert(pair <string, int> (gate_information[i][0], ot));
                        }
                    }
                    multimap <string, int> :: iterator i1;
                    multimap <string, int> :: iterator i2;
                    for(i1 = input_variables.begin(); i1 != input_variables.end(); ++i1){
                        i2 = variables.find(i1->first);
                        cout << i2->first << ':' << i2->second << " ";
                    }
                    cout <<  "| ";
                    multimap <string, int> :: iterator i3;
                    multimap <string, int> :: iterator i4;
                    for(i3 = input_variables.begin(); i3 != input_variables.end(); ++i3){
                        i4 = taint_variables.find(i3->first);
                        cout << i4->first << ':' << i4->second << " ";
                    }
                    cout << "| ";
                    multimap <string, int> :: iterator i5;
                    multimap <string, int> :: iterator i6;
                    for(i5 = output_variables.begin(); i5 != output_variables.end(); ++i5){
                        i6 = variables.find(i5->first);
                        cout << i6->first << ':' << i6->second << " ";
                    }
                    cout << "| ";
                    multimap <string, int> :: iterator i7;
                    multimap <string, int> :: iterator i8;
                    for(i7 = output_variables.begin(); i7 != output_variables.end(); ++i7){
                        i8 = taint_variables.find(i7->first);
                        cout << i8->first << ':' << i8->second << " ";
                    }
                    cout << endl;
                    next_permutation(taint_input_array, taint_input_array + noi);
                    zt++;
                    limit++;
                }
                qt++;
            }
            next_permutation(input_array, input_array + noi);
            z++;
        }
        q++;
    }
    return 0;
}
