//Imran Sabur
//CSCI 335
//This is header file of avl tree provided to me by Professor Stamos. Functions that were added by me have my name on them.
//For parts 2a, 2b


#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include "SequenceMap.h"
#include <algorithm>
#include <iostream> 
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root{ nullptr }
      { }
    
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Public function which helps in printing the acronym corresponding to the inputted sequence
     */
    void locate(string& y) const {
        locate_helper(y,root);
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }
    
    /**
     * Public function which calls sequence_deleter. 
     * Takes in a sequence to delete and counter is intialized to 0.
     */
    bool seq_delete(const string& a, int& recur_counter){
        recur_counter = 0;
        return seq_deleter(a, root,recur_counter);
    }

    /**
     * Public function which returns the total number of nodes
     */
    int get_node_count() const{
        return get_node_count_helper(root);
    }

    /**
     * Public function which finds the string to be removed from sequences.txt
     */
    bool find(string& a, int& recur_counter){
        recur_counter = 0;
        return find_helper(a,root,recur_counter);
    }

    /**
     * Public function which calls the helper function made in the private 
     * simply returns the depth of a tree and is a type float
     */
    float get_depth() const{
        return depth_helper(root,0);
    }

  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
        {
            t->element.Merge(x); //merge the acronyms
        }
        balance( t );
    }



  
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        
        balance( t );
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
        
        balance( t );
    }

    /**
     * Internal method to counts the total number of recursion calls for all executions of remove().
     * w is the string of sequence.txt which is to be deleted
     * t is the node which roots the tree
     * recur_calls is the counter which allows to keep track of amount of recursive calls
     * Majority of the function was templated from the remove function, modified it to fit my code
     * added by Imran Sabur
     */

    bool seq_deleter(const string& w,AvlNode *& t, int& recur_calls){
        recur_calls++;
        if( t == nullptr )
            return false;   // Item not found; do nothing
        
        if( w < t->element.get_sequence() )
            seq_deleter( w, t->left,recur_calls );
        else if( t->element.get_sequence() < w ) //if that is not the sequence to be deleted, traverse left
            seq_deleter( w, t->right,recur_calls ); //update the number of recursive calls
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            return seq_deleter( t->element.get_sequence(), t->right, recur_calls );
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            return true; 
        }
        return false;
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        } else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
	}
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }

     /**
     * Internal method to match and print the corresponding acronym to the inputted enzyme
     * a is the string, or input that will be given to query the tree and find a macth
     * t is the node that roots the tree.
     */
    void locate_helper(string& a, AvlNode* t) const{
    if( t == nullptr )
            cout << "Not Found " << endl; //base condition if input is not present in tree
        else if( a < t->element.get_sequence() ) //if that acronym is not found, traverse left
            return locate_helper( a, t->left ); //recursively move left
        else if( t->element.get_sequence() < a ) //if not in the left, then traverse right
            return locate_helper( a, t->right );
        else{
             t->element.list_acronyms(); //indicates that we have found that acronym and calls acronym corresponding to the given sequence
        }
             
    }

     /**
     * Internal method to (find()) the tree for each string in the sequences.txt file
     * Also keeps track of how many recursive calls have been made for find()
     * y is the string gathered from the parsing of sequences file
     * recur_counter is the variable used to track the number of recursive calls 
     * t is the node that roots the tree.
     * added by Imran Sabur
     */
    bool find_helper(string &y,AvlNode* t, int& recur_counter){
        recur_counter++;  //starting function increment counter
        if( t == nullptr )
            return false;  //edge case for if t hits nullptr
        else if( y < t->element.get_sequence() )
            return find_helper( y, t->left,recur_counter ); //uses operator to find the sequence, traverse left while updating counter
        else if( t->element.get_sequence() < y )
            return find_helper( y, t->right,recur_counter ); //uses operator to find the sequence, traverse left while updating counter
        else{
             return false;  //end 
        }
    }

     /**
     * Internal helper method to count number of nodes in a tree
     * t is the node that roots the tree.
     * Added by Imran Sabur 
     */
    int get_node_count_helper(AvlNode *x) const{
       
    if (x == nullptr)  
        return 0;  
    else
        return(get_node_count_helper(x->left) + 1 + get_node_count_helper(x->right));
        //recursively travel left, and right. Add one for the root itself.
    }

     /**
     * Internal method to determine the depth of the tree
     * depth is value which is updated as node is visited
     * t is the node that roots the tree.
     * added by Imran Sabur
     */
    float depth_helper(AvlNode *t, float depth) const {
       
    if (t == nullptr) {
        return 0;
    }
    return depth  + depth_helper(t->left, depth + 1) + depth_helper(t->right, depth + 1);
        //similar to counting the number of nodes, we travel left and right and add 1 for each recurive call
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        /*
        AvlNode *k2 = k3->left->right;
        // cout << "here" << endl;
        k3->right = k2->left;
        k2->left = k3;
      //  cout << "here" << endl; 
        k3->height = max( height( k3->left ), height( k3->right ) ) + 1;
        k2->height = max( height( k2->right ), k3->height ) + 1;
        k3 = k2;

        AvlNode *k1 = k3->left;
        // cout << "k1" << k1 << " r " << k1->right << " l " << k1->left << endl;
        // cout << "k2" << k2 << " r " << k2->right << " l " << k2->left << endl;
        k3->left = k1->right;
        k1->right = k3;
        k3->height = max( height( k3->left ), height( k3->right ) ) + 1;
        k1->height = max( height( k1->left ), k3->height ) + 1;
        k3 = k1;
    //    cout << "here" << endl; 
        
        */
        rotateWithRightChild( k3->left );
       rotateWithLeftChild( k3 );
    }

        

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        /*   
        AvlNode *k2 = k1->right->right;
        //    cout << "here" << endl;
        k1->left = k2->right;
       // cout << "here" << endl;
        k2->right = k1;
       // cout << "here" << endl;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
       // cout << "here" << endl;
        k2->height = max( height( k2->left ), k1->height ) + 1;
       // cout << "here" << endl;
        k1 = k2;
      //  cout << "here" << endl;

        
        AvlNode *k4 = k1->right;
      //  cout << "here" << endl;
        k1->right = k4->left;
      //  cout << "here" << endl;
        k4->left = k1;
     //   cout << "here" << endl;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
      //  cout << "here" << endl;
        k4->height = max( height( k4->right ), k1->height ) + 1;
      //  cout << "here" << endl;
        k1 = k4;
     //   cout << "here" << endl;
        
        */

        rotateWithLeftChild( k1->right );
      rotateWithRightChild( k1 );
    }
};

#endif
