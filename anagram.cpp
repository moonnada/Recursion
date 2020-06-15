
#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

int loadDictionary(istream &dicfile, string dict[]);
int permuteRecur(string word, const string dict[], int size, string results[]);
void printRecur(const string results[], int size);
bool checkword(string word, string dict, int size);
void StringChar(string word, string dict, char cword[], char cdict[]);
bool checkWordHelper(char word[], char dict[], int size);

int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    nwords = loadDictionary(dictfile, dict);
    
    cout << "Please enter a string for an anagram: ";
    cin >> word;
    
    int numMatches = permuteRecur(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        printRecur(results, numMatches);
}

int loadDictionary(istream &dicfile, string dict[]) {
    getline(dicfile, dict[0]);
    if (! dicfile)
        return 0;
    else
        return loadDictionary(dicfile, dict+1) + 1;
}


int permuteRecur(string word, const string dict[], int size, string results[]) {
    if (word[0] == '\0')
        return 0;
    else if (size == 0)
        return 0;
    
    unsigned long int wlength = word.size();
    if (dict[0].size() == wlength){
        if (checkword(word, dict[0], wlength)){
            results[0] = dict[0];
            return permuteRecur(word, dict+1, size-1, results+1)+1;
        }
        else
            return permuteRecur(word, dict+1, size-1, results);
    }
    else
        return permuteRecur(word, dict+1, size-1, results);
    return 0;
}

bool checkword(string word, string dict, int size) {
    char a[size], b[size];
    StringChar(word, dict, a, b);
    
    if(checkWordHelper(a, b, size))
        return true;
    else
        return false;
}

void StringChar(string word, string dict, char cword[], char cdict[]){
    if (word[0] == '\0')
    return;
    
            cword[0] = tolower(word[0]);
            cdict[0] = tolower(dict[0]);
                                                                    
StringChar(word.substr(1,word.size()-1), dict.substr(1,dict.size()-1), cword+1,cdict+1);

    unsigned long int size = word.size();           //sorts both arrays into alphabetical order
    sort(cword, cword+size);
    sort(cdict, cdict+size);

}
           
bool checkWordHelper(char word[], char dict[], int size){
               if (size == 0)
                   return true;
               if (word[0] == '\0' && dict[0] == '\0')
                   return true;
               if ((word[0] != '\0' && dict[0] == '\0') || (word[0] != '\0' && dict[0] != '\0'))
                   return false;
               
               if (word[0] == dict[0]) {
                   if (checkWordHelper(word+1, dict+1, size-1)) {
                       return true;
                   }
               }
               return false;
           }

void printRecur(const string result[], int size) {
    if (size == 0)
        return;
    if (result [0] == "")
        return;
    
    cout<<result[0]<<endl;
    printRecur(result+1, size-1);
}
