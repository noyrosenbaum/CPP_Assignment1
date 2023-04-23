#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int main() {
    pperson p1 = creat_person("Maya", "Levi", 123456789);
    pperson p2 = creat_person("Lia", "Kaplan", 987654321);
    pperson p3 = creat_person("Shoshana", "Srur", 135794680);
    pperson p4 = NULL;
    PAdptArray persons = CreateAdptArray(copy_person, delete_person, print_person);
    
    SetAdptArrayAt(persons, 2, p1);
    SetAdptArrayAt(persons, 8, p2);
    SetAdptArrayAt(persons, 1, p3);
    assert(SetAdptArrayAt(persons, 9, p4) == FAIL);
    assert(GetAdptArrayAt(persons, 10) == NULL);
    printf("the size is %d\n", GetAdptArraySize(persons)); // prints 9
    PrintDB(persons); // prints The DB

    pbook b1 = creat_book("A Court Of Thorns And Roses", 123);
    pbook b2 = creat_book("It Ends With Us", 456);
    pbook b3 = creat_book("The Cruel Prince", 789);
    PAdptArray nullptr = CreateAdptArray(NULL, NULL, NULL);
    assert(nullptr == NULL);

    assert(GetAdptArraySize(nullptr) == -1);

    PAdptArray mybooks = CreateAdptArray(copy_book, delete_book, print_book);

    SetAdptArrayAt(mybooks, 3, b1);
    SetAdptArrayAt(mybooks, 5, b2);

    assert(GetAdptArraySize(mybooks) == 6);

    SetAdptArrayAt(mybooks, 2, b3);
    assert(GetAdptArraySize(mybooks) == 6);
    printf("the size is %d\n", GetAdptArraySize(mybooks));

    PrintDB(mybooks);
    pbook b = GetAdptArrayAt(mybooks, 3);
    printf("the book is %s\n", b->name);
    assert(strcmp(b->name, "A Court Of Thorns And Roses") == 0);
    PrintDB(mybooks);

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