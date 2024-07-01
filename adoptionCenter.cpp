#include "adoptionCenter.h"
#include <iostream>
using namespace std;

// AdoptionCenter constructor
// Initialize all data members to represent an empty database.
// The BSTs need to be initialized with their comparison functions:
// - NAME: Sort by species name (including breed), in increasing lexicographic order
// - AGE: Sort by increasing age
// - HEALTH: Sort by increasing health severity
// - VACCINE: Sort by increasing VaccinationStatus total hash value
//
// The comparison functions when comparing the left animal (a1) and right animal (a2) should return:
// - a negative value if a1 < a2
// - 0 if a1 == a2
// - a positive value if a1 > a2

AdoptionCenter::AdoptionCenter() : animals(nullptr), numAnimals(0), sortedAnimals{
                                                                        // NAME (0)
                                                                        BST([](const Animal *a1, const Animal *a2)
                                                                            {
        //sort by species name (including breed)
        //in increasing lexicographic order
        //?should be ok if only use < or > operator
        //check a1 name < a2 name?
        if(a1->getSpecies() < a2->getSpecies())
        {
            //a1 name < a2 name => return -ve value
            return -1;
        }
        //check a1 name > a2 name
        if(a1->getSpecies() > a2->getSpecies())
        {
            //a1 name > a2 name => return +ve value
            return 1;
        }
        //else
        //a1 name = a2 name
        //return 0
        return 0; }),
                                                                        // AGE (1)
                                                                        BST([](const Animal *a1, const Animal *a2)
                                                                            {
        //sort by increasing age
        //check a1 age < a2 age ?
        if(a1->getAge() < a2->getAge())
        {
            //a1 age < a2 age => return -ve value
            return -1;
        }
        //check a1 age > a2 age ?
        if(a1->getAge() > a2->getAge())
        {
            //a1 age > a2 age => return +ve value
            return 1;
        }
        //else
        //a1 age = a2 age
        //return 0
        return 0; }),
                                                                        // HEALTH (2)
                                                                        BST([](const Animal *a1, const Animal *a2)
                                                                            {
        //Sort by increasing health severity
        //small serve < bigger serve < large serve
        //check a1 serve < a2 serve?
        if(a1->getHealthCondition().severity < a2->getHealthCondition().severity)
        {
            //a1 serve < a2 serve => return -ve value
            return -1;
        }
        //check a1 serve > a2 serve?
        if(a1->getHealthCondition().severity > a2->getHealthCondition().severity)
        {
            //a1 serve > a2 serve => return +ve value
            return 1;
        }
        //else
        //a1 serve = a2 serve
        //return 0
        return 0; }),
                                                                        // VACCINE (3)
                                                                        BST([](const Animal *a1, const Animal *a2)
                                                                            {
        //Sort by increasing VaccinationStatus total hash value
        //small total hash value < big total hash value < large total hash value

        //check a1 total hash < a2 total hash?
        if(a1->getVaccinationStatus().getTotalHashValue() < a2->getVaccinationStatus().getTotalHashValue())
        {
            //a1 hash < a2 hash => return -ve value
            return -1;
        }
        //check a1 total hash > a2 total hash?
        if(a1->getVaccinationStatus().getTotalHashValue() > a2->getVaccinationStatus().getTotalHashValue())
        {
            //a1 hash > a2 hash => return +ve value
            return 1;
        }
        //else
        //a1 hash = a2 hash
        //return 0
        return 0; })}

{

    // TODO

    //! ALL done in MIL
    // animals -> nullptr
    // numAnimals -> 0
    // set all 4 BST in the sorted Animals array
}

// TASK 4.2: AdoptionCenter destructor
// Deallocate any dynamic memory in this class.
// Hint: This is where the animals should be deallocated.
AdoptionCenter::~AdoptionCenter()
{

    // TODO

    // BST are not dynamic data members -> no need delete
    // BST node destructor will deallocate all nodes in the linked list
    // not deallocate animals

    // deallocate animals
    for (int i = 0; i < numAnimals; ++i)
    {
        // deallocate animals
        delete animals[i];
    }
    // delete the array
    delete [] animals;
}


// Add an animal to the dynamic-length array data member,
// by increasing its size by 1 and increment numAnimals accordingly.
// Add the animal to the end of the array,
// such that the array is sorted by increasing ID (assume we only add increasing IDs)
// The animal should also be added to the 4 BSTs.
void AdoptionCenter::addAnimal(Animal *a)
{

    // TODO
    //cout << "add animal : " <<a->getSpecies()<<endl; //!test

    //increase array size by 1
    Animal** newAnimal = new Animal*[numAnimals + 1];

    //move old array animals to new animals
    for(int i = 0; i < numAnimals; ++i)
    {
        //move
        newAnimal[i] = animals[i];

        //unbind old animals
        animals[i] = nullptr;
    }

    //Add animals

    // add animal to the BST
    
    // insert to NAME BST
    sortedAnimals[NAME].insert(a);
    // cout << "inserted to name BST" <<endl; //!test
    // insert to AGE BST
    sortedAnimals[AGE].insert(a);
    // cout << "inserted to age BST" <<endl; //!test
    // insert to HEALTH BST
    sortedAnimals[HEALTH].insert(a);
    // cout << "inserted to health BST" <<endl; //!test
    // insert to VACCINE BST
    sortedAnimals[VACCINE].insert(a);
    // cout << "inserted to vaccine BST" <<endl; //!test

    //add animals to newAnimals
    newAnimal[numAnimals] = a;

    //update numAnimals
    numAnimals++;

    //delocate old animals
    delete [] animals;

    //update animals
    animals = newAnimal;

    //done
    return;
}


// Remove an animal from the database by ID.
// If the ID does not exist, do nothing.
// Otherwise, resize the array to decrease its size by 1,
// copy the non-deleted animals over and decrement numAnimals accordingly.
// The animal should also be removed from the 4 BSTs.
// Finally, return true if the animal was successfully removed.
bool AdoptionCenter::removeAnimal(unsigned int id)
{
    // TODO
    
    //defualt targeti is -1 (represent to animal not find)
    int Targeti = -1;

    //search for the animal
    for(int i = 0; i < numAnimals; ++i)
    {
        if(animals[i]->getID() == id)
        {
            //found target
            //save down the target id
            Targeti = i;
            break;
        }
    }

    //do nth if target not find
    if(Targeti == -1)
    {
        return false;
    }

    //-------------Target Found-------------
    //pointer to the target animal
    Animal* target = animals[Targeti];

    //new array with decrease arraySuze by 1
    Animal** newAnimal = new Animal*[numAnimals - 1];

    //move all arrays item front by 1 to "remove the animal from animals"
    for(int i = Targeti; i < numAnimals - 1; ++i)
    {
        animals[i] = animals[i+1];
    }

    //update numAnimals
    --numAnimals;

    //move all animals to the new array
    for(int i = 0; i < numAnimals; ++i)
    {
        //move
        newAnimal[i] = animals[i];
        //remove old animals array
        animals[i] = nullptr;
    }

    //deallocate old animals array
    delete [] animals;

    //remove target
    //remove from 4 bst

    // remove in NAME BST
    sortedAnimals[NAME].remove(target);
    // cout << "removed to name BST" <<endl; //!test
    // remove in AGE BST
    sortedAnimals[AGE].remove(target);
    // cout << "removed to age BST" <<endl; //!test
    // remove in HEALTH BST
    sortedAnimals[HEALTH].remove(target);
    // cout << "removed to health BST" <<endl; //!test
    // remove in VACCINE BST
    sortedAnimals[VACCINE].remove(target);
    // cout << "removed to vaccine BST" <<endl; //!test

    //deallocate target Animals
    delete target;

    animals = newAnimal;


    //remove success
    return true;

    return false;
}


// Increment the age of all animals by 1.
void AdoptionCenter::incrementAge()
{

    // TODO
    // loop through all the animals
    for (int i = 0; i < numAnimals; ++i)
    {
        // add 1 to all animals
        animals[i]->incrementAge();
    }

    //? need to adjust the age of the BST?

    return;
}


// Modify the animal with the specified ID's health condition to the provided parameter.
// If the animal does not exist, do nothing.
// Else, ensure the BST for health condition is sorted after the modification.
void AdoptionCenter::setAnimalHealthCondition(unsigned int id, const HealthCondition &h)
{

    // TODO
    // set health condition
    // check animal exist
    // defualt animal not exists
    bool animalExists = false;
    Animal *a = nullptr;
    // loop through animals
    for (int i = 0; i < numAnimals; ++i)
    {
        // found animal with targeted id
        if (animals[i]->getID() == id)
        {
            // animal exists
            animalExists = true;
            // set the new health condition
            //!we dont set here -> cuz the updated bst will let remove cant find the animals
            //animals[i]->setHealthCondition(h);
            // pointer point to the animal
            a = animals[i];
            // break out loop
            break;
        }
    }

    // do nothing if animal not exists
    if (animalExists == false)
    {
        // return
        return;
    }

    //----animal Exists----
    // modify the target animal's health condition
    // make sure the BST condition is sorted

    //?make a new BST?
    //!SUS

    //---check BST needs to sort?---

    //cout << "SORT : " << a->getSpecies() <<endl; //!test

    //need to sort again
    //cout << a->getID() <<endl; //!test

    // remove target animal?
    sortedAnimals[HEALTH].remove(a);

    //set health condition
    a->setHealthCondition(h);

    // insert target animal?
    sortedAnimals[HEALTH].insert(a);
}


// Add the provided vaccine to the animal specified by ID.
// If the animal does not exist, do nothing.
// Else, ensure the BST for vaccine status is sorted after the modification.
void AdoptionCenter::addAnimalVaccine(unsigned int id, const string &v)
{

    // TODO
    // defualt not animal not exists
    //cout << "add vaccine"<<endl; //!test
    bool animalExists = false;
    // pointer point to the target animal
    Animal *a = nullptr;

    // search the animal
    for (int i = 0; i < numAnimals; ++i)
    {
        // found target animal
        if (animals[i]->getID() == id)
        {
            //cout << id<< endl; //!test
            //cout << animals[i]->getSpecies()<<endl; //!test
            // animal exists
            animalExists = true;
            // add vaccine
            //!same here
            //animals[i]->addVaccine(v);
            // set pointer point to the taget
            a = animals[i];
            // break out loop
            break;
        }
    }

    // check animal exist or not
    if (animalExists == false)
    {
        // not exists
        // do nth
        return;
    }

    //!BUG

    // update bst
    // remove target
    sortedAnimals[VACCINE].remove(a);
    //add vaccine
    a->addVaccine(v);
    // insert target again
    sortedAnimals[VACCINE].insert(a);
}

// Modify the animal with the specified ID's special needs to the provided parameter.
// If the animal does not exist, do nothing.
void AdoptionCenter::setAnimalSpecialNeeds(unsigned int id, const std::string &n)
{

    // TODO
    for (int i = 0; i < numAnimals; ++i)
    {
        // found animal with targeted id
        if (animals[i]->getID() == id)
        {
            // change setAnimalSpecialNeeds of that animal
            animals[i]->setSpecialNeeds(n);
            // return
            return;
        }
    }
    // if cant find -> wont do anything

    // return
    return;
}

/**
 * Provided function to display the animals in the database.
 * @param start: Starting index to print (e.g. start == 5: ignore the first 5 animals that matches the filter)
 * @param stop: Index to stop printing (e.g. stop == 10: print until the 10th animal [exclusive] that matches the filter)
 * @param filter: Only print animals that match this filter.
 * @param criteria: Sorting criteria. By default sort by ID (assuming animals are added in increasing ID)
 */
void AdoptionCenter::display(unsigned int start, unsigned int stop, const Filter &filter, SortCriteria criteria) const
{
    unsigned int displayCount = stop - start;
    if (criteria == ID)
    {
        for (unsigned int i = 0; i < numAnimals; ++i)
        {
            if (filter.match(*animals[i]))
            {
                animals[i]->display(start, displayCount);
            }
        }
    }
    else
    {
        sortedAnimals[criteria].print(start, displayCount, filter);
    }
}

/**
 * Provided function to print the vaccines an animal, specified by ID, has taken.
 */
void AdoptionCenter::displayPetVaccines(unsigned int id) const
{
    unsigned int i = 0;
    for (; i < numAnimals; ++i)
    {
        if (animals[i]->getID() == id)
        {
            VaccinationStatus v = animals[i]->getVaccinationStatus();
            if (v.numVaccines == 0)
                cout << "No vaccines found." << endl;
            else
                for (unsigned int j = 0; j < VACCINE_TABLE_SIZE; ++j)
                {
                    if (v.vaccineHashTable[j].length() > 0)
                        cout << v.vaccineHashTable[j] << endl;
                }
            return;
        }
    }
    if (i == numAnimals)
        cout << "ID not found in database." << endl;
}
