#include "bst.h"
using namespace std;

/**
 * Returns true if "src" contains *any* words in "filterWords" (case-insensitive).
 * e.g.:
 *   containAnyWords("Example string", "example") == true
 *   containAnyWords("Example string", "amp") == true
 *   containAnyWords("Example string", "this is a long sentence") == true  [contains 'a']
 *   containAnyWords("Example string", "no occurence") == false
 */
bool containAnyWords(string src, string filterWords)
{
    auto strToLower = [](string &str)
    {
        for (char &c : str)
            c = tolower(c);
    };
    strToLower(src);
    strToLower(filterWords);
    size_t found = filterWords.find(' ');
    while (found != string::npos)
    {
        if (src.find(filterWords.substr(0, found)) != string::npos)
            return true;
        filterWords = filterWords.substr(found + 1);
        found = filterWords.find(' ');
    }
    return src.find(filterWords) != string::npos;
}

// TASK 2.1: Filter::match(const Animal&) const
// Returns true if the animal satisfies ALL 3 conditions:
// - species (including breed) contains *any* of the words in speciesMatch
// - health description contains *any* of the words in healthMatch
// - vaccine status contains *all* of the non-empty strings in vaccineMatch
bool Filter::match(const Animal &a) const
{

    // TODO

    // filter species
    if (containAnyWords(a.getSpecies(), this->speciesFilter) == true)
    {
        // filter health
        if (containAnyWords(a.getHealthCondition().description, this->healthFilter) == true)
        {
            // filter vaccine status
            // loop through
            for (int i = 0; i < VACCINE_TABLE_SIZE; ++i)
            {
                // check have vaccine
                if (a.getVaccinationStatus().hasVaccine(this->vaccineFilter[i]) == false)
                {
                    // animal a dont have a vaccine in vaccineFilter
                    // return false
                    return false;
                }
                // have that vaccine
                // next vaccine
            }

            // passed filter vaccine status
            return true;
        }
    }

    // one of the test failed -> return false
    return false;
    // return true;
}

// TASK 2.2: AnimalLLnode::print(unsigned int&, unsigned int&, const Filter&) const
// Print the animals in this linked list if it matches with the filter.
// The linked list should be maintained such that it is in decreasing ID order.
//
// E.g. (each node is shown as ID[Name]):
//      7[Cat] -> 6[Cat] -> 5[Dog] -> 3[Cat] -> 1[Bird] -> 0[Cat]
// should be printed in the following order using Filter{Name = "Cat"}:
//      0[Cat]
//      3[Cat]
//      6[Cat]
//      7[Cat]
//
// The parameters ignoreCount and displayCount should be passed to the animal's display() function
void AnimalLLnode::print(unsigned int &ignoreCount, unsigned int &displayCount, const Filter &filter) const
{

    // TODO
    // if not last node -> print from next node
    if (this->next != nullptr)
    {
        // print start from next node
        this->next->print(ignoreCount, displayCount, filter);
    }

    // last node
    if (filter.match(*this->animal) == true) // if filter is match with the animal of this node
    {
        // print this animal
        this->animal->display(ignoreCount, displayCount);
        // cout << this->animal->getVaccinationStatus().numVaccines <<endl; //!test
        // cout << this->animal->getVaccinationStatus().getTotalHashValue() <<endl; //!test
    }
}

// TASK 2.3: BSTnode destructor
BSTnode::~BSTnode()
{

    // TODO
    // delete animal linklist
    AnimalLLnode *cur = head;
    // loop through the whole linked list
    while (cur != nullptr)
    {
        AnimalLLnode *temp = cur; // set temp to target node
        cur = cur->next;          // update cur
        //! SUS, but should be no need to deallocate the animal here
        temp->animal = nullptr; // only set to nullptr
        // delete temp->animal;      // delete data in temp
        delete temp; // delete old cur node
    }

    // BST left
    // BST right
    // no need delete -> cuz not ptr, is data member will auto killed
}

// TASK 2.4: BSTnode::addAnimal(const Animal* a)
// Add an animal to the linked list.
// Ensure the order is *decreasing ID*, e.g.: 7[Cat] -> 6[Cat] -> 5[Dog] -> 3[Cat] -> 1[Bird] -> 0[Cat]
// You may assume no two animals with the same ID will be added to a node
// (this also means you should not add the same animal to a node twice!)
void BSTnode::addAnimal(const Animal *a)
{

    // TODO
    // empty list
    if (head == nullptr) // head is nullptr (empty list)
    {
        // add animal to empty list
        head = new AnimalLLnode(a, nullptr); // create a head animal with null next
        // return
        return;
    }
    //----not empty list-----

    // insert to first node (largest)
    if (a->getID() > head->animal->getID()) // animal a's ID > head's ID
    {
        // add animal to head
        // make a new node contains animal a and set next node to old head
        // assign it to head
        head = new AnimalLLnode(a, head);
        // return
        return;
    }

    // insert to end node(smallest)
    // cur ptr defualt point to head node
    AnimalLLnode *cur = head;
    // find last node
    for (; cur->next != nullptr; cur = cur->next)
        ;
    // check is the smallest node
    if (a->getID() < cur->animal->getID())
    {
        // new node a, set next to null
        // set last node next or new node a
        cur->next = new AnimalLLnode(a, nullptr);
    }

    // insert middle
    cur = head; // reset cur = head
    for (; cur->next != nullptr; cur = cur->next)
    {
        // if cur > new > cur->next
        if (a->getID() < cur->animal->getID() && a->getID() > cur->next->animal->getID())
        {
            //(cur)->(new)->(cur->next)
            // new node a , set next to cur->next (old)
            // assign cur->next to new node a which next is old cur->next
            cur->next = new AnimalLLnode(a, cur->next);
            // return
            return;
        }
    }

    // same ID -> havent insert
    return;
}

// TASK 2.5: BSTnode::addAnimal(const Animal* a)
// Remove an animal from the linked list.
// Ensure the order of the other animals are kept.
// If the animal does not exist, do nothing.
// If there are no animals left after removing, set head to nullptr.
void BSTnode::removeAnimal(const Animal *a)
{

    // TODO
    //cout << "proceed REMOVE ANIMAL IN LINKED LIST "<<endl; //!test

    // empty list
    if (head == nullptr) // nth to remove
    {
        return;
    }

    // remove first
    if (a->getID() == head->animal->getID()) // head is target
    {
        // if only one node
        if (head->next == nullptr)
        {
            // unbind head's animal
            head->animal = nullptr;
            // delete head
            delete head;
            head = nullptr;
            return;
        }

        // not only one node -> delete head node
        //  set temp defualt as head
        AnimalLLnode *temp = head;
        head = head->next; // update head to next node
        // the target node's animal make to nullptr
        temp->animal = nullptr;
        // remove node
        delete temp;

        // return
        return;
    }

    // locate node
    AnimalLLnode *prev = head; // prev node
    AnimalLLnode *cur = head;  // cur node

    // loop through linked list and setup prev and cur
    while (cur != nullptr)
    {
        // found node
        if (cur->animal->getID() == a->getID())
        {
            // check its last node or middle node
            // check last node?
            if (cur->next == nullptr) // last node
            {
                // update prev node
                prev->next = nullptr;
                // unbind the animal of the cur node
                cur->animal = nullptr;
                // delete node
                delete cur;

                // return
                return;
            }

            // middle node
            prev->next = cur->next; // prev node points to the next next node

            // update cur next
            cur->next = nullptr;
            // unbind the animal of the cur node
            cur->animal = nullptr;
            // delete middle node
            delete cur;
            // return
            return;
        }

        // update prev -> old cur
        prev = cur;
        // update cur
        cur = cur->next;
    }

    // sth error
    return;
}

// TASK 3.1: BST destructor
BST::~BST()
{

    // TODO
    // just delete root
    delete root;
}

// TASK 3.2: BST::findMinNode()
// Optional task, but may be needed for BST::remove().
// Return a reference to the BSTnode* of the min node in this BST.
BSTnode *&BST::findMinNode()
{
    // TODO
    // leftest node is min
    // if left node is empty -> return node
    if (this->root->left.isEmpty())
    {
        // retrun this->root (no left node)
        return this->root;
    }

    // recursive case
    // return the left node -> findMinNode() -> continue search left unitl encounter its left node is empty
    return this->root->left.findMinNode();
}

// TASK 3.3: BST::insert(const Animal* a)
// Insert an animal 'a' to the BST.
// Use the comparator "data member function" to compare the animal with the current node:
// - If 'a' is "less than" the current node, insert it to the left subtree.
// - If 'a' is "more than" the current node, insert it to the right subtree.
// - If 'a' "equals" the current node, insert it into this node's linked list.
// - Otherwise, if the node is empty, create a new node using 'a'.
void BST::insert(const Animal *a)
{

    // TODO
    //cout << "insert animal : " << a->getSpecies() << endl; //!test

    // base case: empty node
    if (this->isEmpty()) // root is nullptr
    {
        // create new node on the root
        //cout << "new node for : "<< a->getSpecies()<<endl; //!test
        this->root = new BSTnode(a, comparator);
        return;
    }

    //----not empty tree

    // recursive case: a < node (-ve)
    if (comparator(a, this->root->head->animal) < 0)
    {
        // left node -> insert
        //cout << "go left" <<endl; //!test
        this->root->left.insert(a);
        return;
    }

    // recursive case: a > node (+ve)
    if (comparator(a, this->root->head->animal) > 0)
    {
        // right node -> insert
        //cout << "go right" <<endl; //!test
        this->root->right.insert(a);
        return;
    }

    // found node
    //cout << "add to cur node : " << a->getSpecies() <<endl; //!test
    this->root->addAnimal(a);

    return;
}

// TASK 3.4: BST::remove(const Animal* a)
// Remove an animal 'a' from the BST
// Follow the same steps in BST::insert() to locate the node to remove.
// Removal strategy is similar to lecture notes example with a few differences:
// - If the node is not found, do nothing.
// - If the node is found, remove the animal from its linked list. If it makes the linked list become empty,
//   remove the node:
//   + If the node contains 0 or 1 child, move the children node to current root, and deallocate the old root.
//   + Else, *move* the linked list from the right subtree's min node to current root, and deallocate right subtree's min node.
void BST::remove(const Animal *a)
{
    // TODO
    //cout << "remove Animal" << a->getSpecies() <<endl; //!test

    // check have node?
    if (this->isEmpty())
    {
        //cout << "no node" << endl; //!test
        // no node do nothing
        return;
    }
    //-------------------have node-------------------
    // check linked list have animal?
    if (this->root->head == nullptr)
    {
        // dont have animal in the node
        //->remove node

        // check how many children?

        // 2 children
        if (this->root->left.root != nullptr && this->root->right.root != nullptr)
        {
            // move right tree min linked list
            this->root->head = this->root->right.findMinNode()->head;
            // unbound right tree min node's linked list
            this->root->right.findMinNode()->head = nullptr;

            // recursive delete the right min node
            // find node using its old linked list
            this->root->right.remove(this->root->head->animal);

            // return
            return;
        }

        // 0 or 1 children
        // delete node
        // save teh root to delete
        BSTnode *deleting_node = this->root;
        // find which child is not empty
        if (this->root->left.root == nullptr) // left is empty
        {
            // child is on right root
            // point to right root
            this->root = this->root->right.root;
        }
        else // this->root->left.root != nullptr
        {
            // child is on left root
            // point to left root
            this->root = this->root->left.root;
        }
        // set subtrees to nullptr before removal
        deleting_node->left.root = nullptr;
        deleting_node->right.root = nullptr;
        // delete node
        delete deleting_node;
        // return
        return;
    }
    //-------------------have animal in linked list-------------------
    //cout << comparator(a, this->root->head->animal) << endl; //!test

    if (comparator(a, this->root->head->animal) < 0)
    {
        // remove from left subtree
        //cout <<"move left"<<endl; //!test
        this->root->left.remove(a);
        return;
    }

    if (comparator(a, this->root->head->animal) > 0)
    {
        // remove from right subtree
        //cout <<"move right"<<endl; //!test
        this->root->right.remove(a);
        return;
    }
    //-------------------found node-------------------
    // remove animal
    //cout << "remove animal"<<endl; //!test
    this->root->removeAnimal(a);
    //-------------------target removed-------------------
    // check need delete node?
    // check linked list have animal?
    if (this->root->head == nullptr)
    {
        // dont have animal in the node
        //->remove node

        // check how many children?

        // 2 children
        if (this->root->left.root != nullptr && this->root->right.root != nullptr)
        {
            // move right tree min linked list
            this->root->head = this->root->right.findMinNode()->head;
            // unbound right tree min node's linked list
            this->root->right.findMinNode()->head = nullptr;

            // recursive delete the right min node
            // find node using its old linked list
            this->root->right.remove(this->root->head->animal);

            // return
            return;
        }

        // 0 or 1 children
        // delete node
        // save teh root to delete
        BSTnode *deleting_node = this->root;
        // find which child is not empty
        if (this->root->left.root == nullptr) // left is empty
        {
            // child is on right root
            // point to right root
            this->root = this->root->right.root;
        }
        else // this->root->left.root != nullptr
        {
            // child is on left root
            // point to left root
            this->root = this->root->left.root;
        }
        // set subtrees to nullptr before removal
        deleting_node->left.root = nullptr;
        deleting_node->right.root = nullptr;
        // delete node
        delete deleting_node;
        // return
        return;
    }
    //-------------------linked list still have animal-------------------
    // no need delete node
    return;
}

// TASK 3.5: BST::print(unsigned int&, unsigned int&, const Filter&) const
// Print the BST using in-order traversal.
//
// E.g.: Consider a BST containing animals sorted by species name:
//                      8[Reptile, Healthy] -> 6[Reptile, Bad]
//              5[Rabbit, Critical]
// 7[Dog, Healthy] -> 3[Dog, Healthy]
//                      9[Cat, Bad] -> 4[Cat, Healthy] -> 2[Cat, Very poor]
//              1[Bird, Healthy]
//
// should print in the following order using Filter{Health = "Healthy"}:
//      1[Bird, Healthy]
//      4[Cat, Healthy]
//      3[Dog, Healthy]
//      7[Dog, Healthy]
//      8[Reptile, Healthy]
void BST::print(unsigned int &ignoreCount, unsigned int &displayCount, const Filter &filter) const
{

    // TODO
    // Inorder traversal -> LCR
    // in linked list, -> tail first to head
    //?should be fine to use the linked list print function

    // base case: empty
    if (this->isEmpty())
    {
        // return
        return;
    }

    //---- not empty ----

    // LCR
    // recursion case: left
    this->root->left.print(ignoreCount, displayCount, filter);

    //!===SUS===
    //?should be fine to use the linked list print function
    // print the node value -> use the print func in the linked list node
    this->root->head->print(ignoreCount, displayCount, filter);

    // recursion case: right
    this->root->right.print(ignoreCount, displayCount, filter);
}
