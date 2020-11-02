// <Your name>
// Main file for Part2(a) of Homework 2.

#include "avl_tree.h"
#include "SequenceMap.h"

#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>
#include <string>
using namespace std;

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {


  ifstream inFile(db_filename);
  SequenceMap new_sequence_map; 
  string db_line, skipped_lines,acro,rec_seq;
  
   

  for(int i =0; i < 10;i++){
    getline(inFile,skipped_lines); //skips first 10 lines
    //test case
  } 
  while(getline(inFile,db_line)){
    stringstream ss(db_line);
    getline(ss,acro,'/'); //reads file and stops at the first /
    
    
  //stops at the second /
    while(getline(ss,rec_seq,'/')){
      if(db_line.empty()){
      db_line.erase(); 
    }
      SequenceMap new_sequence_map(rec_seq,acro); //adds it into the map
      a_tree.insert(new_sequence_map);  //adds into the tree
    }
  
  }//end first while loop

  

}




}  // namespace

int main(int argc, char **argv) {


   
  
  string seq1,seq2,seq3; 
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  cout << "Input filename is " << db_filename << endl;
  
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);

    //three inputs as designated by file
    cin >> seq1;
    cin >> seq2;
    cin >> seq3; 

    a_tree.locate(seq1); //call to the locate helper function made in avl.h
    a_tree.locate(seq2);
    a_tree.locate(seq3);
  //}

  

  

   
  
   

   

    

     
  
  return 0;
}
