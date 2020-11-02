//Imran Sabur
// Main file for Part2(b) of Homework 2.
//I completed the TestTree function

#include "avl_tree.h"
#include "SequenceMap.h"
// You will have to add #include "sequence_map.h"

#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <cmath>
using namespace std;

namespace {






// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {

    ifstream inFile(db_filename); //open the database
    SequenceMap new_sequence_map;  //declare a new map 
    string db_line, skipped_lines,acro,rec_seq;
  
    for(int i =0; i < 10;i++){
    getline(inFile,skipped_lines); //skips first 10 lines
    //test case
    } 
    while(getline(inFile,db_line)) //for each line of the file 
    {
      
      stringstream ss(db_line); //stringstream object to parse the 22
      
      getline(ss,acro,'/'); //reads file and stops at the first / and stores that in the acronym variables
    
      
       while(getline(ss,rec_seq,'/')) //stops at the / or // to parse in the sequence
       {
          if(rec_seq.length() > 0) //edge case for empty string that was giving me an extra node
          {
            SequenceMap new_sequence_map(rec_seq,acro); // create a new map and put the sequence and acronym
            a_tree.insert(new_sequence_map);  //insert in the tree
          }  
       }//end second while

    }//end second while

    float full_node = a_tree.get_node_count(); //gets the total number of nodes of a_tree
    float max_depth = a_tree.get_depth(); //gets the full depth of a_tree
    float average_depth = max_depth/full_node; //gets the average depth of a_tree

  
   

  //2a
   cout << full_node << endl; 

   //3a
   cout << average_depth << endl; 

   float result = log2(full_node);

   float ratio = average_depth/result;  //prints the  ratio of the average depth to log base 2 of n

   //3b
   cout << ratio << endl; 

    int counter = 0 , recur_count = 0, recur_calls; 
    string txtline; //total 
    ifstream my_file(seq_filename); //read in sequences.txt
    while(getline(my_file,txtline)){ //begin parsing, read each line in the file
        counter++; //total number of lines in file, or strings
        if(a_tree.find(txtline,recur_calls)){ //if i found that line, update the recursion counter
           recur_count++; 

        }
        recur_count += recur_calls; //counter is equal to the number of calls made

    }

    float average = (float)recur_count/counter;
    
    //4a
    cout << counter << endl; 
    //4b
    cout << average << endl; 



  ////Begin the removing procedure
    ifstream myfile(seq_filename); //read sequence again
    string line; 
    int rem_string = 0;
    int rem_line = 0;
    
    while(getline(myfile,line)){ //for each line in the file
      

      if(rem_line % 2 == 0){ //if the line is even
        SequenceMap navigate(line, ""); //look through the sequence map
        if(a_tree.contains(navigate)){ //if it contains it remove it
          a_tree.remove(navigate);
          if(!a_tree.contains(navigate)){
              rem_string++;
          }

        }
        
        
      }
    rem_line++; 
    


  }
 // 5a
 cout << rem_string << endl;

  ifstream m_file(seq_filename);
  string sequence;
    int even = 0, amount_del = 0, recursion_calls = 0, total_recur = 0, total = 0;   
    while (getline(m_file, sequence)) { //for each line in the fiel
        
        if (even % 2 == 0) {        //if the line is even remove   
            total++;                              
            if (a_tree.seq_delete(sequence, recursion_calls))             
                amount_del++; 
            total_recur += recursion_calls;     //get the amount of recursion calls
        } 
        even++;                                      
    }
    float avg_calls = (float)total_recur / total;
    //5b
    cout << avg_calls << endl; //report the average calls 
    int new_total = a_tree.get_node_count(); //get the amount of nodes after deletion
    //6a
    cout <<  new_total << endl; //report

    float new_depth = a_tree.get_depth();
    float new_depth_final = new_depth/new_total;
    //6b
    cout << new_depth_final << endl; //get the new depth after removal

    float log_result = log2(new_total);
    float final_result = new_depth_final/log_result;

    //6c
    cout << final_result << endl; //print average depth to logn after removal
  }//end test tree
}  // namespace


int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);
 

  /*
  float full_node = a_tree.get_node_count();
  float max_depth = a_tree.get_depth();
  float average_depth = max_depth/full_node;

  
   


   cout << full_node << endl; 
   cout << average_depth << endl; 

   float result = log2(full_node);

   float ratio = average_depth/result; 
   cout << ratio << endl; 
  */

  return 0;
}
  

