#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class U {
public:
    bool login() {
        string usr, pwd;
        cout << "Usr: ";
        cin >> usr;
        cout << "Pwd: ";
        cin >> pwd;
        if (usr == "admin" && pwd == "1234") {
            cout << "Logged in!\n";
            return true;
        } else {
            cout << "Wrong creds!\n";
            return false;
        }
    }
};

class Inc {
private:
    vector<pair<string, double>> in;

public:
    void add() {
        string src;
        double amt;
        cout << "Income Src: ";
        cin >> src;
        cout << "Amt: ";
        cin >> amt;
        in.push_back({src, amt});
        saveToFile();
        cout << "Added!\n";
    }

    double total() {
        double t = 0;
        for (const auto& i : in) {
            t += i.second;
        }
        return t;
    }

    void show() {
        cout << "--- Incomes ---\n";
        for (const auto& i : in) {
            cout << "Src: " << i.first << ", Amt: " << i.second << "\n";
        }
        cout << "Total Inc: " << total() << "\n";
    }

    void saveToFile() {
        ofstream file("income.txt", ios::app);
        if (file.is_open()) {
            for (const auto& i : in) {
                file << i.first << " " << i.second << "\n";
            }
            file.close();
        }
    }

    void loadFromFile() {
        ifstream file("income.txt");
        if (file.is_open()) {
            string src;
            double amt;
            while (file >> src >> amt) {
                in.push_back({src, amt});
            }
            file.close();
        }
    }
};

class Exp {
private:
    vector<pair<string, double>> ex;

public:
    void add() {
        string cat;
        double amt;
        cout << "Exp Cat: ";
        cin >> cat;
        cout << "Amt: ";
        cin >> amt;
        ex.push_back({cat, amt});
        saveToFile();
        cout << "Added!\n";
    }

    double total() {
        double t = 0;
        for (const auto& e : ex) {
            t += e.second;
        }
        return t;
    }

    void show() {
        cout << "--- Expenses ---\n";
        for (const auto& e : ex) {
            cout << "Cat: " << e.first << ", Amt: " << e.second << "\n";
        }
        cout << "Total Exp: " << total() << "\n";
    }

    void saveToFile() {
        ofstream file("expense.txt", ios::app);
        if (file.is_open()) {
            for (const auto& e : ex) {
                file << e.first << " " << e.second << "\n";
            }
            file.close();
        }
    }

    void loadFromFile() {
        ifstream file("expense.txt");
        if (file.is_open()) {
            string cat;
            double amt;
            while (file >> cat >> amt) {
                ex.push_back({cat, amt});
            }
            file.close();
        }
    }
};

class Bud {
private:
    double bud;

public:
    Bud() : bud(0) {}

    void set() {
        cout << "Set Bud: ";
        cin >> bud;
        saveToFile();
        cout << "Bud: " << bud << "\n";
    }

    double get() const {
        return bud;
    }

    void show() const {
        cout << "Bud: " << bud << "\n";
    }

    void saveToFile() {
        ofstream file("budget.txt");
        if (file.is_open()) {
            file << bud << "\n";
            file.close();
        }
    }

    void loadFromFile() {
        ifstream file("budget.txt");
        if (file.is_open()) {
            file >> bud;
            file.close();
        }
    }
};

class Rep {
public:
    void gen(Inc& inc, Exp& exp, Bud& bud) {
        double tInc = inc.total();
        double tExp = exp.total();
        double netSav = tInc - tExp;
        double budStat = bud.get() - tExp;

        cout << "\n--- Report ---\n";
        cout << "Total Inc: " << tInc << "\n";
        cout << "Total Exp: " << tExp << "\n";
        cout << "Net Sav: " << netSav << "\n";
        if (budStat >= 0) {
            cout << "Under Bud by: " << budStat << "\n";
        } else {
            cout << "Over Bud by: " << -budStat << "\n";
        }
    }
};

void menu() {
    cout << "\n--- Finance Mngmnt ---\n";
    cout << "1. Add Inc\n";
    cout << "2. Add Exp\n";
    cout << "3. Set Bud\n";
    cout << "4. Show Rep\n";
    cout << "5. Exit\n";
    cout << "Choice: ";
}

int main() {
    U u;
    if (!u.login()) {
        cout << "Exit.\n";
        return 0;
    }

    Inc incMng;
    Exp expMng;
    Bud budMng;
    Rep repMng;

    incMng.loadFromFile();
    expMng.loadFromFile();
    budMng.loadFromFile();

    int ch;
    do {
        menu();
        cin >> ch;
        switch (ch) {
            case 1:
                incMng.add();
                break;
            case 2:
                expMng.add();
                break;
            case 3:
                budMng.set();
                break;
            case 4:
                repMng.gen(incMng, expMng, budMng);
                break;
            case 5:
                cout << "Exit.\n";
                break;
            default:
                cout << "Wrong choice!\n";
        }
    } while (ch != 5);

    return 0;
}

