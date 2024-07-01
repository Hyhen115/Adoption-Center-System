#include "datatypes.h"
#include <iostream>
using namespace std;

/**
 * Returns the ASCII sum of all characters in a string
 * To be used as the indexing key of a string into the hash table,
 * e.g. k = sumStringChars(str)
 */
unsigned int sumStringChars(const string &str)
{
    unsigned int sum = 0;
    for (unsigned int i = 0; i < str.length(); ++i)
        sum += static_cast<unsigned int>(str[i]);
    return sum;
}

// TASK 1.1: VaccinationStatus default constructor
VaccinationStatus::VaccinationStatus() : numVaccines(0)
{

    // TODO
    // Defualt VaccinationStatus constructir
    // numVaccines set to 0
    // initialize vaccineHashTable array to all empty strings
    for (int i = 0; i < VACCINE_TABLE_SIZE; ++i)
    {
        // set to empty string
        vaccineHashTable[i] = "";
    }
}

// TASK 1.2: VaccinationStatus::addVaccine(const string&)
// - If the table is not at least half empty, output the first error message and return.
// - Else, calculate k = sumStringChars(v) and hash(k) = k % VACCINE_TABLE_SIZE
//   Follow the quadratic probing formula: h(i) = [hash(k) + i^2] % VACCINE_TABLE_SIZE
//   to add the vaccine to the table.
//   If the vaccine already exists, output the second error message and return.
void VaccinationStatus::addVaccine(const string &v)
{

    // check is half empty?
    // half : vaccine_table_size / 2
    // if num > size/2 -> not half empty
    if (numVaccines > VACCINE_TABLE_SIZE / 2 /* TODO: Table is not half-empty */)
    {
        cout << "This system does not support having taken more than " << numVaccines << " vaccines." << endl;
        return;
    }

    // TODO: Quadratic probing

    // calculate k = sumStringChars(v)
    int k = sumStringChars(v);

    // probe into the hash table using k, hash(k) = k % VACCINE_TABLE_SIZE
    int hashk = k % VACCINE_TABLE_SIZE;

    // quadratic probing formula: h(i) = [hash(k) + i^2] % VACCINE_TABLE_SIZE

    if (hasVaccine(v) /* TODO: Vaccine exists */)
    {
        cout << "This animal has already taken " << v << "." << endl;
        return;
    }

    // TODO: Quadratic probing
    // vaccine not exists && table is half empty
    // insert vaccine

    // check no collision here?
    if (vaccineHashTable[hashk] == "")
    {
        //no collision here
        // insert vaccine
        vaccineHashTable[hashk] = v;
        //update numVaccines
        ++numVaccines;
        return;
    }
    //there are collision
    int hashi = hashk; //hashi = hashk
    int i = 1;                     //defualt 1 st collision occurs
    while (i < VACCINE_TABLE_SIZE) //! sus
    {
        // if find empty (empty string)
        if (vaccineHashTable[hashi] == "")
        {
            // insert vaccine
            vaccineHashTable[hashi] = v;
            //update numVaccines
            ++numVaccines;
            return;
        }

        // cant not empty -> collision
        // update hashk
        hashi = (hashk + i * i) % VACCINE_TABLE_SIZE; //! changed
        // update i -> next collision
        ++i;
    }
}

// TASK 1.3: VaccinationStatus::hasVaccine(const string&) const
// Returns true if the vaccine exists in the table, false otherwise
bool VaccinationStatus::hasVaccine(const string &v) const
{

    // TODO
    // find if the vaccine exists in the hash table
    // calculate k = sumStringChars(v)
    int k = sumStringChars(v);

    // probe into the hash table using k, hash(k) = k % VACCINE_TABLE_SIZE
    int hash = k % VACCINE_TABLE_SIZE;
    int hashi = hash; //for the modify variable

    // loop through the hash map
    int i = 1;                     // ?defualt the collision as 1st
    while (i < VACCINE_TABLE_SIZE) //! sus
    {
        // find the vaccine
        if (vaccineHashTable[hashi] == v)
        {
            // found the vaccine
            return true;
        }

        // not target
        //  update hash
        hashi = (hash + i * i) % VACCINE_TABLE_SIZE; //! changed
        // update i -> next collision
        ++i;
    }

    return false;
}

/**
 * Returns a value representing the current hash table
 * Used for comparing 2 animals with different vaccination status
 */
unsigned int VaccinationStatus::getTotalHashValue() const
{
    unsigned int hash = 0;
    for (unsigned int i = 0; i < VACCINE_TABLE_SIZE; ++i)
        hash += sumStringChars(vaccineHashTable[i]);
    return hash * numVaccines;
}
