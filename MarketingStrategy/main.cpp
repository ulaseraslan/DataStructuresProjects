//
//  main.cpp
//  ulaseraslan_hw3
//
//  Created by Ulaş Eraslan on 13.04.2020.
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.
//

#include <iostream>
#include "LinkedList.h"
#include "SeparateChaining.h"
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

struct item {
    string name;
    float confidence;
};

double trans_count=0;
string dummy = "itemNotFound";
HashTable<string> hashtable(dummy);
vector<string>items;
vector<string> support_items;
vector<string> pairs;
vector<string>support_pairs;
void find_pairs (int i,int &iter);

void file_operations (string filename);
void supportval_calculation (double transcount, double support_value_given,vector<string>&vec,vector<string>main_vec);
void check_pair_occurence (int i,int &iter);
void check_pair_amount (int i,int &iter,int &size,vector<string>&vec);
void check_pair_occurence (string filename);
vector<string> perm_cal ();
void print_confidence (vector<item> last_print, vector<string>perms,double confidence_given);
void confidence_calculation (vector<string> perms, double confidence,string filename);
vector<string> check_confidence (string filename);




int main() {
    
    string filename;
    double support=0,confidence=0;
    
    cout << "Please enter the transaction file name: ";
    cin>>filename;
    
    //File operations
    file_operations(filename);
    
    cout << "Please enter support and confidence values between 0 and 1: ";
    cin >> support >> confidence;
    
    //Calculate support values
    supportval_calculation(trans_count, support,support_items,items);
    
    //Pair Operations
    
    for (int i =0; i<support_items.size();i++) {
        find_pairs(i,i);
    }
    check_pair_occurence (filename); //This function re-read the file and find occurences of the pairs.
    supportval_calculation(trans_count, support,support_pairs,pairs); // Support values of the pairs are calculated.
    
    //Finding all 2 lenght permutations
    vector<string> perms = perm_cal(); // Find length 2 permutations of the Items and pairs which their support values are higher than given support val.
    
    // Confidence Calculation
    confidence_calculation (perms, confidence,filename); // Found perms' confidence values are calculated and higher ones are printed.
        
    return 0;
}

void file_operations (string filename) {
    
    string word,line;
    
    ifstream input;
    input.open(filename);
    
    if (!input) {
        while (!input) {
            cout << "Can not open the file!" <<endl;
            cout << "Please enter the transaction file name: ";
            cin>>filename;
            input.open(filename);
        }
    }
    
    while(!input.eof()) {
        
        getline(input, line);
        trans_count++;                  //For each transaction trans_count is incremented by one.
        istringstream iss(line);
        
        for(std::string word; iss >> word;) {
            
            if (hashtable.find(word)!= dummy) { // If word is in the hashtable just increase its amount.
                
                hashtable.increase_amount(word);
            }
            
            else {                                      //Else insert and increse the amount.
                hashtable.insert(word);
                hashtable.increase_amount(word);
                items.push_back(word);
            }
            
        }
    }
    input.close();
    
}

void supportval_calculation (double transcount, double support_value_given,vector<string>&vec,vector<string>main_vec) {
    
    for (int i =0; i<main_vec.size(); i++) {
        
        double amount = hashtable.get_amount(hashtable.find(main_vec[i]));      //For each item/pair find its amount in the hashtable.
        double supportval = amount / transcount;                                // To calculate the support value. divide amount by transaction count.
        if (supportval >=  support_value_given) {                               // If found support value is greater than the given support value.
            if (vec == support_items) {
                vec.push_back(main_vec[i]);
                hashtable.insert(main_vec[i]);
                hashtable.set_support(main_vec[i], supportval);
            }
            else {
                vec.push_back(main_vec[i]);
                hashtable.insert(main_vec[i]);
                hashtable.set_support(main_vec[i], supportval);
            }
        }
        else {
            hashtable.remove(main_vec[i]);                                      //Else remove the item/pair from the hashtable.
            
        }
    }
}

void find_pairs (int i,int &iter) {         //This function finds item pairs by recursion algorithm.
    
    if (i!= support_items.size()) {
        find_pairs(i+1,iter);
    }
    
    else {
        return;
    }
    
    if (i!=iter) {
        string pair = hashtable.find(support_items[iter]) + " "+ hashtable.find(support_items[i]);
        
        if (hashtable.find(pair) == dummy){
            
            hashtable.insert(pair);
            pairs.push_back(pair);
            
        }
        
        
    }
}
void check_pair_amount (int i,int &iter,int &size,vector<string>&vec) {  //Find all pairs' amounts.
    
    if (i!= size) {
        check_pair_amount(i+1,iter,size,vec);
    }
    
    else {
        return;
    }
    
    if (i!=iter) {
        string pair = hashtable.find(vec[iter]) + " "+ hashtable.find(vec[i]);
        string pair2 = hashtable.find(vec[i]) + " "+ hashtable.find(vec[iter]);
        
        if ((hashtable.find(pair) != dummy ) || (hashtable.find(pair2) != dummy ) ){
            if ((hashtable.find(pair2) != dummy )) {
                hashtable.increase_amount(pair2);
            }
            else if ((hashtable.find(pair) != dummy )) {
                hashtable.increase_amount(pair);
            }
        }
    }
}

void check_pair_occurence (string filename) { //This function re-reads the file and find the occurences of the pairs.
    
    string word,line;
    
    ifstream input;
    input.open(filename);
    vector <string>pairs_temp;
    
    while(!input.eof()) {
        
        getline(input, line);
        istringstream iss(line);
        
        for(std::string word; iss >> word;) {
            pairs_temp.push_back(word);
        }
        int size = pairs_temp.size();
        int i=0;
        for (int j=0;j<pairs_temp.size();j++) {
            check_pair_amount(j,i,size,pairs_temp);
            i++;
        }
        pairs_temp.clear();
    }
}


void confidence_calculation (vector<string> perms, double confidence,string filename) { //This function finds the confidence values of the found 2 lenght permutations.
    
    vector <item> last_to_print;
    vector<string> confidence_cal;
    vector <string> check_vec = check_confidence(filename);
    
    for (int i =0;i<perms.size(); i++) {
        
        bool sub1_check = false,sub2_check = false;
        
        string word = perms[i];                             //At this point each permutation is seperated.
        string sub1 = word.substr(0,word.find(","));
        string sub2 = word.substr(word.find(",")+1);
        
        string sub1_1="",sub1_2="";
        
        if (sub1.find(" ")!= string::npos) {                //If first sub-string is pairs related operations are hold.
            sub1_1 = sub1.substr(0,sub1.find(" "));
            sub1_2 = sub1.substr(sub1.find(" ")+1);
            sub1_check =true;
        }
        
        string sub2_1="",sub2_2="";
        
        if (sub2.find(" ") != string::npos) {               //If second sub-string is pairs related operations are hold.
            sub2_1 = sub2.substr(0,sub2.find(" "));
            sub2_2 = sub2.substr(sub2.find(" ")+1);
            sub2_check =true;
        }
        
        if (sub1_check == false && sub2_check == false) { // a->b condition
            string total_word = sub1 + " " + sub2;
            string total_word2 = sub2 + " " + sub1;
            if (hashtable.find(total_word)!= dummy) {
                float confidence_val = (roundf(((hashtable.get_amount(total_word))/trans_count) / (hashtable.get_support(sub1))*100) / 100);
                
                if (confidence_val >= confidence) {
                    string pair = sub1 + ";" + sub2 + ";";
                    item product;
                    product.name = pair;
                    product.confidence= confidence_val;
                    last_to_print.push_back(product);
                }
                
            }
            else if (hashtable.find(total_word2)!= dummy) {
                float confidence_val = (roundf(((hashtable.get_amount(total_word2))/trans_count) / (hashtable.get_support(sub1))*100) / 100);
                string confval= to_string(confidence_val);
                
                if (confidence_val >= confidence) {
                    string pair2 = sub1 + ";" + sub2 + ";";
                    item product;
                    product.name = pair2;
                    product.confidence= confidence_val;
                    last_to_print.push_back(product);
                }
            }
        }
        
        else {
            for (int j=0; j<check_vec.size(); j++) {
                
                string check_word= check_vec[j];
                
                if (sub1_check == true && sub2_check == false) { // a,b -> c condition
                    
                    if (check_word.size() >= 3) {
                        
                        if (check_word.find(sub1_1) != string::npos && check_word.find(sub1_2) != string::npos && check_word.find(sub2) != string::npos ) {
                            
                            string word = sub1_1 + "," + sub1_2 + ";" + sub2;
                            if (hashtable.find(word)!= dummy) {
                                hashtable.increase_amount(word);
                            }
                            
                            else if (hashtable.find(word) == dummy ) {
                                hashtable.insert(word);
                                hashtable.increase_amount(word);
                                confidence_cal.push_back(word);
                            }
                            
                        }
                    }
                    
                }
                
                else if (sub1_check == false && sub2_check == true) { // a -> b,c condition
                    
                    if (check_word.size() >= 3) {
                        
                        if (check_word.find(sub2_1) != string::npos && check_word.find(sub2_2) != string::npos && check_word.find(sub1) != string::npos ) {
                            
                            string word = sub1 + ";" + sub2_1 + "," + sub2_2;
                            
                            if (hashtable.find(word)!= dummy ) {
                                hashtable.increase_amount(word);
                            }
                            else if (hashtable.find(word) == dummy) {
                                hashtable.insert(word);
                                hashtable.increase_amount(word);
                                confidence_cal.push_back(word);
                            }
                            
                        }
                    }
                    
                }
                
                else if (sub1_check == true && sub2_check == true) { // a,b -> c,d condition
                    
                    if (check_word.size() >= 4) {
                        
                        if (check_word.find(sub1_1) != string::npos && check_word.find(sub1_2) != string::npos && check_word.find(sub2_1) != string::npos && check_word.find(sub2_2) != string::npos) {
                            
                            string word = sub1_1 + "," + sub1_2 + ";" + sub2_1 + "," + sub2_2;
                            
                            if (hashtable.find(word)!= dummy) {
                                hashtable.increase_amount(word);
                            }
                            else if (hashtable.find(word) == dummy ) {
                                hashtable.insert(word);
                                hashtable.increase_amount(word);
                                confidence_cal.push_back(word);
                            }
                            
                        }
                    }
                    
                }
                
            }
        }
    }
    
    print_confidence (last_to_print, confidence_cal,confidence);
    
}
vector<string> check_confidence (string filename) {
    
    string word,line;
    vector <string> read_words;
    
    ifstream input;
    input.open(filename);
    
    while(!input.eof()) {
        
        getline(input, line);
        
        read_words.push_back(line);
        
    }
    
    return read_words;
}

void print_confidence (vector<item> last_print, vector<string>perms,double confidence_given) {  //This function calculate the confidence values and print them.
    for (int i=0; i<perms.size(); i++) {
        
        string word = perms[i];
        string total="";
        string sub1= word.substr(0, word.find(";"));
        string sub2= word.substr(word.find(";")+1);
        string sub_total = sub1 + ";" + sub2;
        
        if (sub1.find(",") != string::npos && sub2.find(",") == string::npos) { //Case a,b;c
            
            string sub1_1 = sub1.substr(0,sub1.find(","));
            string sub1_2 = sub1.substr(sub1.find(",")+1);
            
            total = sub1_1 + "," + sub1_2 + ";" + sub2;
            
        }
        
        else if (sub1.find(",") == string::npos && sub2.find(",") != string::npos) { // case a;b,c
            
            string sub2_1 = sub2.substr(0,sub2.find(","));
            string sub2_2 = sub2.substr(sub2.find(",")+1);
            
            total =  sub1+ ";" + sub2_1 + "," + sub2_2 ;
            
        }
        
        else if (sub1.find(",") != string::npos && sub2.find(",") != string::npos) { //case a,b;c,d
            
            string sub1_1 = sub1.substr(0,sub1.find(","));
            string sub1_2 = sub1.substr(sub1.find(",")+1);
            string sub2_1 = sub2.substr(0,sub2.find(","));
            string sub2_2 = sub2.substr(sub2.find(",")+1);
            
            total = sub1_1 + "," + sub1_2 + ";" + sub2_1 + "," + sub2_2;
            
        }
        
        if (sub1.find(",") != string::npos) {
            string first = sub1.substr(0,sub1.find(","));
            string second = sub1.substr(sub1.find(",")+1);
            sub1= first + " " + second;
            
        }
        
        float confidence = (roundf((hashtable.get_amount(sub_total)/trans_count) / hashtable.get_support(sub1) * 100) / 100);
        
        if  (confidence >= confidence_given){
            
            string total_word= total + ";";
            item product;
            product.name = total_word;
            product.confidence= confidence;
            last_print.push_back(product);
            
        }
    }
    
    ofstream file;
    string file_name = "results.txt";
    
    file.open(file_name);
    
    if (last_print.size()==0) {
        cout << "There is no rule for the given support and confidence values."<< endl;
    }
    else {
    cout << last_print.size() << " rules are written to " << file_name << endl;
    
    for (int k=0; k<last_print.size(); k++) {
        file << last_print[k].name << setprecision(2)<< last_print[k].confidence << endl;
        }
    }
    file.close();
    
}

vector<string> perm_cal () {        //This function finds all 2 lenght permutations of the pairs and items which their support values are higher than the given support val.
    
    vector <string> perms;
    support_items.insert(support_items.end(), support_pairs.begin(),support_pairs.end());
    
    string word1="",word2="";
    
    for (int i =0; i<support_items.size(); i++) {
        
        bool check = false;
        
        word1 = support_items[i];
        
        string sub1="",sub2="";
        
        if (word1.find(" ") != string::npos) {
            sub1= word1.substr(0,word1.find(" "));
            sub2 = word1.substr(word1.find(" ")+1);
            check= true;
        }
        
        for (int k=0; k<support_items.size(); k++) {
            
            word2 = support_items[k];
            
            if (!check) {
                if (word2.find(word1) == string::npos && word1.find(word2) == string::npos) {
                    
                    string word = word1 + "," + word2;
                    
                    perms.push_back(word);
                    
                }
            }
            
            else {
                if (word2.find(sub1) == string::npos && word2.find(sub2) == string::npos) {
                    string word = word1 + "," + word2;
                    perms.push_back(word);
                }
            }
            
        }
        
    }
    return perms;
}
