#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int main() {
    // Create 3 person objects and set 1 to null
    pperson p1 = creat_person("Shir", "Cohen", 123456789);
    pperson p2 = creat_person("Ofer", "Kaplan", 987654321);
    pperson p3 = creat_person("Shira", "Srur", 135794680);
    pperson p4 = NULL;
    // Create an adaptive array object for persons with specified copy, delete, and print functions
    PAdptArray persons = CreateAdptArray(copy_person, delete_person, print_person);
    
    SetAdptArrayAt(persons, 2, p1);
    SetAdptArrayAt(persons, 8, p2);
    SetAdptArrayAt(persons, 1, p3);
    assert(SetAdptArrayAt(persons, 9, p4) == FAIL);
    // Assert that getting an object at an invalid index returns null and print the size of the array
    assert(GetAdptArrayAt(persons, 10) == NULL);
    printf("the size is %d\n", GetAdptArraySize(persons)); // prints 9
    // Print the contents of the persons array
    PrintDB(persons); 

    // Create 3 book objects and an empty adaptive array object for books, assert the null array equals null, and check size of array
    pbook b1 = creat_book("A Court Of Thorns And Roses", 123);
    pbook b2 = creat_book("It Ends With Us", 456);
    pbook b3 = creat_book("The Cruel Prince", 789);
    PAdptArray nullptr = CreateAdptArray(NULL, NULL, NULL);
    assert(nullptr == NULL);

    assert(GetAdptArraySize(nullptr) == -1);

    PAdptArray mybooks = CreateAdptArray(copy_book, delete_book, print_book);

    // Set the 3 book objects at specified indices in the adaptive array and assert that the size is correct
    SetAdptArrayAt(mybooks, 3, b1);
    SetAdptArrayAt(mybooks, 5, b2);

    assert(GetAdptArraySize(mybooks) == 6);
    // Set another book object at a specified index and assert that the size is still correct
    SetAdptArrayAt(mybooks, 2, b3);
    assert(GetAdptArraySize(mybooks) == 6);
    printf("the size is %d\n", GetAdptArraySize(mybooks));
    // Print the contents of the mybooks array, get an object at a specified index, and print the name of the book
    PrintDB(mybooks);
    pbook b = GetAdptArrayAt(mybooks, 3);
    printf("the book is %s\n", b->name);
    assert(strcmp(b->name, "A Court Of Thorns And Roses") == 0);
    PrintDB(mybooks);
    // Delete both adaptive array objects and all allocated objects
    DeleteAdptArray(mybooks);
    DeleteAdptArray(persons);
    delete_book(b1);
    delete_book(b2);
    delete_book(b);
    delete_person(p1);
    delete_person(p2);
    delete_person(p3);
    delete_book(b3);

    return 0;
}