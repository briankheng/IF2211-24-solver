#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

const double EPS = 1e-7;
bool valid;
set<string> solutions;
vector<string> cards;
string ops[4] = {"+", "-", "*", "/"}, validCards[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"}, choice, inp;

void output()
{
    if (solutions.empty())
    {
        cout << "Tidak ada solusi!"
             << "\n";
    }
    else
    {
        cout << solutions.size() << ' ' << "solusi ditemukan!"
             << "\n"
             << "\n";
        for (auto it : solutions)
            cout << it << "\n";
    }
}

double operation(double c1, double c2, string op)
{
    if (op == "+")
        return c1 + c2;
    else if (op == "-")
        return c1 - c2;
    else if (op == "*")
        return c1 * c2;
    else if (op == "/")
        return c1 / c2;
}

void solveEquation(vector<string> eq)
{
    // Case 1: ((1 op 2) op 3) op 4
    if (abs(operation(operation(operation(stod(eq[0]), stod(eq[2]), eq[1]), stod(eq[4]), eq[3]), stod(eq[6]), eq[5]) - 24) <= EPS)
    {
        solutions.insert("((" + eq[0] + " " + eq[1] + " " + eq[2] + ") " + eq[3] + " " + eq[4] + ") " + eq[5] + " " + eq[6]);
    }
    // Case 2: (1 op 2) op (3 op 4)
    if (abs(operation(operation(stod(eq[0]), stod(eq[2]), eq[1]), operation(stod(eq[4]), stod(eq[6]), eq[5]), eq[3]) - 24) <= EPS)
    {
        solutions.insert("(" + eq[0] + " " + eq[1] + " " + eq[2] + ") " + eq[3] + " (" + eq[4] + " " + eq[5] + " " + eq[6] + ")");
    }
    // Case 3: (1 op (2 op 3)) op 4
    if (abs(operation(operation(stod(eq[0]), operation(stod(eq[2]), stod(eq[4]), eq[3]), eq[1]), stod(eq[6]), eq[5]) - 24) <= EPS)
    {
        solutions.insert("(" + eq[0] + " " + eq[1] + " (" + eq[2] + " " + eq[3] + " " + eq[4] + ")) " + eq[5] + " " + eq[6]);
    }
    // Case 4: 1 op ((2 op 3) op 4)
    if (abs(operation(stod(eq[0]), operation(operation(stod(eq[2]), stod(eq[4]), eq[3]), stod(eq[6]), eq[5]), eq[1]) - 24) <= EPS)
    {
        solutions.insert(eq[0] + " " + eq[1] + " ((" + eq[2] + " " + eq[3] + " " + eq[4] + ") " + eq[5] + " " + eq[6] + ")");
    }
}

void findEquation(vector<string> eq, int idx)
{
    if (idx == 4)
    {
        solveEquation(eq);
        return;
    }
    for (auto op : ops)
    {
        eq.push_back(op);
        eq.push_back(cards[idx]);
        findEquation(eq, idx + 1);
        eq.pop_back();
        eq.pop_back();
    }
}

void tukar(string &s1, string &s2)
{
    string temp = s1;
    s1 = s2;
    s2 = temp;
}

void permutation(int l, int r)
{
    if (l == r)
    {
        findEquation({cards[0]}, 1);
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            tukar(*(cards.begin() + l), *(cards.begin() + i));
            permutation(l + 1, r);
            tukar(*(cards.begin() + l), *(cards.begin() + i));
        }
    }
}

vector<string> tokenize(string s)
{
    vector<string> tokens;
    string cur = "";
    for (auto it : s)
    {
        if (it == ' ')
        {
            tokens.push_back(cur);
            cur = "";
        }
        else
            cur += it;
    }
    tokens.push_back(cur);
    return tokens;
}

int main()
{
    // INPUT
    cout << "~~~ Selamat Datang Di Permainan Kartu 24! ~~~\n\n";

    cout << "1. Input dari pengguna\n2. Input auto-generate\n\nMasukan pilihan: ";
    getline(cin, choice);

    while (choice != "1" && choice != "2")
    {
        cout << "\nMasukan tidak sesuai!\nMasukan pilihan: ";
        getline(cin, choice);
    }

    // TAKE CARD
    if (choice == "1")
    {
        do
        {
            valid = true;
            cout << "\nPilihan kartu:\n";
            getline(cin, inp);
            cards = tokenize(inp);
            if (cards.size() == 4)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (cards[i] == "2" || cards[i] == "3" || cards[i] == "4" || cards[i] == "5" || cards[i] == "6" ||
                        cards[i] == "7" || cards[i] == "8" || cards[i] == "9" || cards[i] == "10")
                        continue;
                    else if (cards[i] == "A")
                        cards[i] = "1";
                    else if (cards[i] == "J")
                        cards[i] = "11";
                    else if (cards[i] == "Q")
                        cards[i] = "12";
                    else if (cards[i] == "K")
                        cards[i] = "13";
                    else
                        valid = false;
                }
            }
            else
                valid = false;
            if (!valid)
            {
                cout << "\nMasukan tidak sesuai!"
                     << "\n";
            }
            if (valid)
                cout << "\n";
        } while (!valid);
    }
    else
    {
        cout << "\nPilihan kartu:\n";
        for (int i = 0; i < 4; i++)
        {
            cards.push_back(validCards[rnd() % 13]);
            cout << cards[i] << ' ';
            if (cards[i] == "A")
                cards[i] = "1";
            else if (cards[i] == "J")
                cards[i] = "11";
            else if (cards[i] == "Q")
                cards[i] = "12";
            else if (cards[i] == "K")
                cards[i] = "13";
        }
        cout << "\n\n";
    }

    // FIND SOLUTION
    auto start = chrono::high_resolution_clock::now();
    permutation(0, 3);
    auto stop = chrono::high_resolution_clock::now();

    // OUTPUT
    output();

    cout << "\nApakah ingin menyimpan solusi? (Y/N)\nMasukan pilihan: ";
    getline(cin, choice);
    while (choice != "Y" && choice != "N" && choice != "y" && choice != "n")
    {
        cout << "\nMasukan tidak sesuai!\nMasukan pilihan: ";
        getline(cin, choice);
    }

    if (choice == "Y" || choice == "y")
    {
        string fileName;
        cout << "\nMasukan nama file keluaran: ";
        getline(cin, fileName);
        fileName = "../test/" + fileName + ".txt";
        freopen(fileName.c_str(), "w", stdout);
        output();
        freopen("CON", "w", stdout);
    }

    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "\nWaktu eksekusi program: "
         << duration.count() << " ms\n";

    cout << "\n\n~~~ Terima kasih telah menggunakan program ini! ~~~\n\n";

    return 0;
}
