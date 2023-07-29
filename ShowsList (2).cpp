/*************************************************************/
/*                   ShowsList Definition                    */
/*************************************************************/
/* TODO: Implement the member functions of class ShowsList   */
/*     This class uses a linked-list of Show structs to      */
/*     represent the schedule of shows                       */
/*************************************************************/

#include "ShowsList.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
ShowsList::ShowsList() {
    /*
    DO NOT MODIFY THIS
    This constructor is already complete. 
    */
    head = nullptr;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool ShowsList::isEmpty() {
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: prints the current list of shows nicely
 * @param none
 * @return none
 */
void ShowsList::displayShows() {
    // TODO: Copy-paste your solution from Assignment 3

    if(head == NULL){
        cout << "nothing in path" << endl;
        return;
    }
        
    
    cout << "== CURRENT SHOWS LIST ==" << endl;
    Show* temp = head;
    while(temp != NULL){
      cout << temp->name << "-> ";
      temp = temp->next;
    }
    cout << "NULL" << endl << "===" << endl;
}

/*
 * Purpose: Add a new show to the shows linked list
 *   between the previous and the show that follows it in the list.
 * @param previousShow the show that comes before the new show
 * @param showName name of the new Show
 * @return none
 */
void ShowsList::addShow(Show* previousShow, string showName) {
    // TODO: Copy-paste your solution from Assignment 3


    Show* temp = new Show;

    temp->name=showName;
    temp->numberRatings = 0;
    temp->rating=0;



    if(isEmpty() || previousShow == NULL){
        temp->next = head;
        head = temp;
        cout << "adding: " << head->name << " (HEAD)" << endl;
        return;
    }

    temp->next = previousShow->next;
    previousShow->next = temp;
    cout << "adding: " << temp->name << " (prev: " << previousShow->name << ")" << endl;




}

/*
 * Purpose: populates the ShowsList with the predetermined shows
 * @param none
 * @return none
 */
void ShowsList::buildShowsList() {
    // TODO: Copy-paste your solution from Assignment 3


    head = NULL;
    addShow(NULL, "Friends");
    addShow(searchShow("Friends"), "Ozark");
    addShow(searchShow("Ozark"), "Stranger Things");
    addShow(searchShow("Stranger Things"), "The Boys");
    addShow(searchShow("The Boys"), "Better Call Saul");


}

/*
 * Purpose: Search the ShowsList for the specified show and return a pointer to that node
 * @param showName - name of the show to look for in list
 * @return pointer to node of show, or NULL if not found
 *
 */
Show* ShowsList::searchShow(string showName) {
    // TODO: Copy-paste your solution from Assignment 3

    Show* temp = head;

    while(temp != NULL){
        if(temp->name == showName)
            return temp;

        temp = temp->next;
    }
    

    return nullptr;
}

/*
 * Purpose: Give a new rating to a show
 * @param receiver - name of the show that is receiving the rating
 * @param rating - the rating that is being given to a show
 * @return none
 */
void ShowsList::addRating(string receiver, double rating) {
    // TODO: Copy-paste your solution from Assignment 3


    if(head == NULL){

        cout << "Empty list" << endl;
        return;
    }

    Show* temp = head;

    while(temp->name != receiver && temp->next != NULL){
        temp = temp->next;
    }
    if(temp->name == receiver){
        temp->rating = (temp->rating*(temp->numberRatings) + rating)/(temp->numberRatings+1);
        temp->numberRatings++;
        cout << "The rating has been updated: " << temp->rating << endl; 
        return;
    }
    else if(temp->next == NULL){

        cout << "Show not found" << endl;
        return;
    }
}


/****************************************************/
/*  ASSIGNMENT 4: Functions to be completed below.  */
/****************************************************/


/*
 * Purpose: Delete the Show in the list with the specified name.
 * @param showName - name of the Show to delete in the list.
 * @return none
 */
void ShowsList::removeShows(string showName)
{
    bool isFound = false;
    //TODO: Complete this function

    if(isEmpty()){
        cout << "Show does not exist." << endl;
        return;
    }

    if(head->name == showName){
        Show* prev = head;
        head = head->next;
        delete prev;
        isFound = true;
        return;
    }
    
        Show* prev = head;

       Show* temp = head->next;




    while(temp != NULL && isFound == false){
        if(temp->name == showName){

            prev->next = temp->next;
            delete temp;
            isFound = true;
            return;

        }
        else{
            prev = temp;
            temp = temp->next;
        }

    }
    if(isFound == false){
        cout << "Show does not exist." << endl;
    }

    
}

/*
 * Purpose: deletes all Shows in the list starting from the head of the linked list.

 * @param: none
 * @return: none
 */
void ShowsList::purgeCompleteShowList()
{
    // TODO: Complete this function

    if(isEmpty() == true){
        return;
    }

    Show* next;
    while(head!=NULL){
        next = head->next;
        cout << "deleting: " << head->name << endl;
        delete head;
        head = next;
    }

   cout << "Deleted show list" << endl;

    
}

/*
* Purpose: Creates a loop from last node to the show name specified.
* @param showName - name of the show to loop back to
* returns the last node before loop creation (to break the loop)
*/
Show* ShowsList::produceGlitch(string showName) 
{
    /*
    DO NOT MODIFY THIS
    This function is already complete. 
    */
    Show* ptr = searchShow(showName);
    Show* temp = head;
    while(temp && temp->next!=NULL){
        temp=temp->next;
    }
    if(ptr && temp)
        temp->next=ptr;
    return temp;
}

/*
 * Purpose: to detect loop in the linked list
 * @return: true if loop is detected, else false
 */
bool ShowsList::findGlitch() 
{
    // TODO: Complete this function
    if(isEmpty()){
        return false;
    }

    Show* first = head;
    Show* second = head;

    while(second!=NULL && second->next != NULL){
        if(second->next->next == NULL){
            return false;
        }
        first = first->next;
        second = second->next->next;
        if(first == second){
            return true;
        }
    }
    
    return false;
}

void ShowsList::rearrangeShowList(int start, int end)
{
    // TODO: Complete this function

    if(isEmpty()){
        cout << "Linked List is Empty" << endl;
        return;
    }

    if(start < 0){
        cout << "Invalid start index" << endl;
        return;
    }
    if(end < 0){
        cout << "Invalid end index" << endl;
        return;
    }
    if(start>end){
        cout << "Invalid indeces" << endl;
        return;
    }
    int numElements = 1;
    Show* test = head;
    while(test->next != NULL){
        test = test->next;
        numElements++;
    }

    if(start > numElements){
        cout << "Invalid start index" << endl;
    }

    if(end > numElements){
        cout << "Invalid end index" << endl;
    }


    Show* one = head;
    Show* three = head;
    Show* four = head->next;
    if(start == 0){
        for(int i = 0; i < end; i++){
            three = three->next;
            four = four->next;
        }

        three->next = NULL;
        one->next = three;

        

        head = four;

        return;
    }


    Show* two = head->next;

    for(int j = 0; j < start - 1; j++){
        one = one->next;
        two = two->next;
    }
    
    for(int i = 0; i < end; i++){
        three = three->next;
        four = four->next;
    }

    three->next=NULL;
    four->next= two;
    one->next = four;



    


}



