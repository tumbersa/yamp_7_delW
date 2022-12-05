#include <iostream>
#include <set>
using namespace std;
const int ALPHABET_SIZE = 26;
struct TrieTree {
    TrieTree* alphabet[ALPHABET_SIZE];
    bool isEndOfWord;
};
struct TrieTree* getNode()
{
    struct TrieTree* pNode = new TrieTree;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->alphabet[i] = NULL;

    return pNode;
}

void insert(struct TrieTree* root, string key)
{
    struct TrieTree* pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->alphabet[index])
            pCrawl->alphabet[index] = getNode();

        pCrawl = pCrawl->alphabet[index];
    }


    pCrawl->isEndOfWord = true;
}
void printTree(TrieTree* t, string word = "")
{
    if (t->isEndOfWord)
        cout << word << endl;
    for (int i = 0; i < 26; ++i)
        if (t->alphabet[i])
            printTree(t->alphabet[i], word + char(i + 'a'));
}
bool allPtrsEmpty(TrieTree* t)
{
    bool result = true;
    int i = 0;
    while (i < 26 && result)
        if (t->alphabet[i])
            result = false;
        else
            ++i;
    return result;
}

void deleteWord(TrieTree*& t, const string word,bool& f, short i=0)
{
    if (t)
    {
        if (i <= (word.length() - 1))
        {
            deleteWord(t->alphabet[word[i] - 'a'], word,f, i + 1);
        }
        else
        {
            t->isEndOfWord = false;
            if (allPtrsEmpty(t))
            {
                delete t;
                t = nullptr;
            }
            
        }
        if (t) {
            if (t->isEndOfWord) f = 1;
            if (!f) {
                if (allPtrsEmpty(t))
                {
                    delete t;
                    t = nullptr;
                }
            }
        }
    }
}

void delW(TrieTree* root, TrieTree* t2 , char c,string& word2) {
    if (word2[0] == '0')return;
    if (!word2.empty() && t2) {
        if (t2->isEndOfWord && c == word2[word2.length() - 1]) {
            bool f = 0;
            deleteWord(root, word2, f);
            t2 = root;
            word2 = "";
            printTree(root);
            cout << endl;
        }
    }
    
        for (int i = 0; i < 26; ++i)
            if (t2->alphabet[i]) {
                word2 += char(i + 'a');
                delW(root, t2->alphabet[i], c, word2);
            }
        if (!word2.empty()) word2.erase(word2.end() - 1);
        else {
            /*printTree(root);
            exit(1);*/
            word2 += '0';
        }
   
}
int main() {
    string keys[] = { "the", "a", "there",
                   "answer", "any", "by",
                    "bye", "their","sdasd" };
    int n = sizeof(keys) / sizeof(keys[0]);

    struct TrieTree* root = getNode();

    for (int i = 0; i < n; i++)
        insert(root, keys[i]);

    char c = 'r';
    //cin >> c;
    bool f = 0;
    printTree(root);
    cout << endl;
    string word = "";
    delW(root, root, c, word);

    printTree(root);
}