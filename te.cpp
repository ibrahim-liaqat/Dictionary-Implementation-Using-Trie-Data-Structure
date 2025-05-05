#include <iostream>
#include<stack>
#include<fstream>
#include<vector>
using namespace std;
class node {
public:
    char data;
    node* aplha[93];
    bool end;
    string m;
    node(char d) {
        data = d;
        for (int i = 0; i < 93; i++) {
            aplha[i] = nullptr;
        }
        end = false;
    }
};
class tri {
public:
    node* root;
    tri() {
        root = new node('^');
    }
    void insertword(string w, string m) {
        insert(root, w, m);
    }
    void insert(node* root, string d, string m) {
        if (d.length() == 0) {
            root->end = true;
            root->m = m;
            return;
        }
        int i = d[0] - 33;
        node* child;
        if (root->aplha[i] != nullptr) {
            child = root->aplha[i];
        }
        else {
            child = new node(d[0]);
            root->aplha[i] = child;
        }
        insert(child, d.substr(1), m);
    }
    bool search(node* root, string d) {
        if (d.length() == 0) {
            if (root->end == true) {
                cout << "Meaning =" << root->m << endl;
                return true;
            }
            else {
                return false;
            }
        }
        node* child;
        int i = d[0] - 33;
        if (root->aplha[i] != nullptr) {
            child = root->aplha[i];
        }
        else {
            return false;
        }
        return search(child, d.substr(1));
    }
    bool w() {
        string s;
        cout << "Enter Word for search =";
        cin >> s;
        return search(root, s);
    }
    bool deletion(string w) {
        return del(root, w);
    }
    bool del(node* root, string word) {
        node* child = root;
        string w, m;
        for (int i = 0; i < word.length(); i++) {
            int j = word[i] - 33;
            if (child->aplha[j] != nullptr) {
                child = child->aplha[j];
            }
            else {
                cout << "1" << endl;
                return false;
            }

        }
        if (child->end == true) {
            child->end = false;
            ifstream handler;
            handler.open("dsa.txt");
            ofstream handler2;
            handler2.open("t.txt");
            while (!handler.eof()) {
                handler >> m;
                handler >> w;
                if (w != word) {
                    handler2 << m << "\t" << w << endl;
                }
            }
            handler.close();
            handler2.close();
            remove("dsa.txt");
            rename("t.txt", "dsa.txt");
            return true;
        }
        else {
            cout << "2" << endl;
            return false;
        }
    }
    bool upgrade(string word) {
        int choice;
        node* temp = root;
        string w, m, w1, m2;
        for (int i = 0; i < word.length(); i++) {
            int j = word[i] - 33;
            if (temp->aplha[j] != nullptr) {
                temp = temp->aplha[j];
            }
            else {
                cout << "1" << endl;
                return false;
            }
        }
        if (temp->end == true) {
            cout << "Enter 1 for update and 2 for update meaning of word =";
            cin >> choice;
            if (choice == 1) {
                temp->end = false;
                cout << "Enter updated word =";
                cin >> w1;
                insertword(w1, temp->m);
                ifstream handler;
                handler.open("dsa.txt");
                ofstream handler2;
                handler2.open("t.txt");
                while (!handler.eof()) {
                    handler >> m;
                    handler >> w;
                    if (w != word) {
                        handler2 << m << "\t" << w << endl;
                    }
                    else {
                        handler2 << temp->m << "\t" << w1 << endl;
                    }
                }
                handler.close();
                handler2.close();
                remove("dsa.txt");
                rename("t.txt", "dsa.txt");
                return true;
            }
            else {
                cout << "Enter update meaning of word =";
                cin >> m2;
                temp->m = m2;
                ifstream handler;
                handler.open("dsa.txt");
                ofstream handler2;
                handler2.open("t.txt");
                while (!handler.eof()) {
                    handler >> m;
                    handler >> w;
                    if (w != word) {
                        handler2 << m << "\t" << w << endl;
                    }
                    else {
                        handler2 << m2 << "\t" << w << endl;
                    }

                }
                handler.close();
                handler2.close();
                remove("dsa.txt");

                rename("t.txt", "dsa.txt");
                return true;
            }
        }
        else {
            cout << "2" << endl;
            return false;
        }
    }
    bool update(string word) {
        return upgrade(word);
    }
    vector<string> suggest(string word)
    {
        vector<string> s;
        node * temp = root;

        for (int i = 0; i < word.length(); i++)
        {

            int key = word[i] - 33;
            if (!temp->aplha[key])
            {
                return s;
            }
            temp = temp->aplha[key];
        }

        suggest2(temp, word, s);
        return s;
    }

    void suggest2(node* node, string w, vector<string>& s)
    {
        if (node == NULL)
        {
            return;
        }

        if (node->end)
        {
            s.push_back(w);
        }

        for (int i = 0; i < 93; i++)
        {
            if (node->aplha[i] != NULL)
            {
                char ch = i + 33;
                suggest2(node->aplha[i], w + ch, s);
            }
        }
    }

 
};
int main() {
    tri* t = new tri();
    int c = 0;
    string w, m;
    ifstream read("dsa.txt");
    if (!read) {
        cout << "File not Found.";
        return 0;
    }
    else {
        cout << ".......... <<Loading>> .............." << endl;
    }
    while (!read.eof())
    {
        read >> m;
        read >> w;
        t->insertword(w, m);
    }
   
    read.close();
    cout << "<< Dictionary Loaded successfully >>" << endl;
    int f;
    f = 1;
    while (1) {
        
        cout << "Enter 1 for search a word :"<<endl;
        cout << "Enter 2 for insert a new  word: " << endl;
        cout << "Enter 3 for delete a word :" << endl;
        cout<<  "Enter 4  for update a word : "<<endl;
        cout << "Enter 5 for suggestion of word :" << endl;
        cout << "Enter 6 for close dictionary :" << endl;
        cin >> f;
        if (f == 1) {
            if (t->w() == false) {
                cout << "Word not found  " << endl;
            }
          
        }
        else if (f == 2) {
            cout << "Enter new word =";
            cin >> w;
            cout << "Enter meaning =";
            cin >> m;
            t->insertword(w, m);
            ofstream handler;
            handler.open("dsa.txt", ios::app);
            handler << m << "\t" << w << endl;
            handler.close();
        }
        else if (f == 3) {
            cout << "Enter a word for  delete =";
            cin >> w;
            if (t->deletion(w) == true) {
                cout << "Delete successfully " << endl;
            }
            else {
                cout << "Word not found " << endl;
            }
         
        }
        else if (f == 4) {
            cout << "Enter word for update =";
            cin >> w;
            if (t->update(w) == true) {
                cout << "Update successfully " << endl;
            }
            else {
                cout << "Word not found " << endl;
            }

        }
        else if (f == 5) {
            string temp;
            cout << "Enter suggestion letters: ";
            cin >> temp;
            vector<string> s=t->suggest(temp);
            if (s.empty())
            {
                cout << "No suggestions found.\n";
                continue;
            }
            else {
                int size = (s.size());
				int j = min(10, size);
                
                for (int i = 0; i < j; i++) {
                    cout << s[i] << endl;
                }
            }
        }
       
        else {
            break;
        } 

    }
    return 0;
}