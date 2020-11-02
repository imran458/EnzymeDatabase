//Imran Sabur
//CSCI 335
//This was done for Assigment 2 

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <vector>
#include <fstream>
using namespace std; 

class SequenceMap
{
    public:
    SequenceMap() = default; //default constructor 
    ~SequenceMap() = default; //destructor
    SequenceMap(const SequenceMap &rhs) = default; //copy-constructor
    SequenceMap(SequenceMap &&rhs) = default; //move constructor
    SequenceMap& operator=(SequenceMap &&rhs) = default; //move - assignment
    SequenceMap& operator=(const SequenceMap& rhs) = default;  //copy - assignment 
    //end of big 5

    /*
    that constructs a SequenceMap from two strings (note that now the vector enzyme_acronyms_ 
    will contain just one element, the an_enz_acro).
    */

    SequenceMap(const string &a_rec_seq, const string &an_enz_acro):
        recognition_sequence_(a_rec_seq), enzyme_acronyms_{an_enz_acro}{}
        //initiliazed the recognition sequence and the vector
    /*
    that operates based on the regular string comparison between the recognition_sequence_ strings 
    (this will be a one line function).
    */
    bool operator<(const SequenceMap &rhs) const{
        return recognition_sequence_ < rhs.recognition_sequence_; 
    }

    /*
        function
        assumes that the object’s recognition_sequence_ and other_sequence.recognition_sequence_ are equal to each other. The function Merge() merges the other_sequence.enzyme_acronym_ with the object’s enzyme_acronym_. 
        The other_sequence object will not be affected.
    */
    void Merge(const SequenceMap &other_sequence){
        for(int i = 0;i < other_sequence.enzyme_acronyms_.size();i++){
            enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
        }
    }

    //function that prints the vector of acronyms
    void list_acronyms(){
        for(int i =0;i < enzyme_acronyms_.size();i++){ //for each element in the vector, print it
            cout << enzyme_acronyms_[i] << " ";
        }
        cout << endl;
    }
    //function that prints out the acronyms which corresponds to the given sequence
    friend std::ostream &operator<<(std::ostream &out, const SequenceMap &a_map){
        out << a_map.recognition_sequence_ << " ";
        for(int i =0;i < a_map.enzyme_acronyms_.size();i++){
            //out << a_map.recognition_sequence_ << " " << a_map.enzyme_acronyms_[i] << endl; 
            out << a_map.enzyme_acronyms_[i] << " ";
        } 
        out << endl; 

        return out; 
    }


    //returns the recognition sequenc3e
    string get_sequence() const
    {
        return recognition_sequence_; 
    }



    private:
    string recognition_sequence_; 
    vector<string> enzyme_acronyms_;


};


#endif