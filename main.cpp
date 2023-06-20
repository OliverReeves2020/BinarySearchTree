//
// Created by Oliver Reeves on 06/10/2022.
//
#include <iostream>
#include "dictionary.h"

bool lessthan(int a,int b) {
    return a > b;
}
bool greaterthan(int a,int b) {
    return a < b;
}

int main(){
    Dictionary dict;



    dict.insert(25,"Jane");
    dict.insert(15,"Dave");
    dict.insert(10,"Neil");
    dict.insert(8,"Mary");
    dict.insert(50,"Ed");
    dict.insert(35,"Eddie");
    dict.insert(70,"E");
    dict.insert(60,"E2");
    dict.insert(65,"E3");



    std::cout<<"--------\ncopy start\n----------\n";
    //dict.displayTree();

    //dict.tempRotation(25);
    //Dictionary dict2(dict);
    std::cout<<"--------\nend\n----------\n";

    dict.removeIf(15,lessthan);
   dict.displayTree();

    //Dictionary dict3;
    //dict3=std::move(dict);


    //dict3.displayEntries();

    std::cout<<"--------\nend\n----------\n";














}