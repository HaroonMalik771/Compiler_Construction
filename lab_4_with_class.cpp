#include <iostream>
#include <string>
using namespace std;

struct Rule {
    string r;
    Rule* next;
};

struct Production {
    string name;
    Production* next;
    Rule* first;
    Rule* last;
};

class CFG {
private:
    Production* start;

    Rule* createRule(const string& ruleStr) {
        Rule* newRule = new Rule;
        newRule->r = ruleStr;
        newRule->next = nullptr;
        return newRule;
    }

public:
    CFG() : start(nullptr) {}

    Production* createProduction(const string& prodName) {
        Production* newProd = new Production;
        newProd->name = prodName;
        newProd->next = nullptr;
        newProd->first = nullptr;
        newProd->last = nullptr;
        if (start == nullptr) {
            start = newProd;
        }
        return newProd;
    }

    void addRuleToProduction(Production* production, const string& ruleStr) {
        Rule* newRule = createRule(ruleStr);
        if (production->first == nullptr) {
            production->first = newRule;
            production->last = newRule;
        } else {
            production->last->next = newRule;
            production->last = newRule;
        }
    }

    void displayCFG() {
        Production* prodPtr = start;
        while (prodPtr != nullptr) {
            cout << prodPtr->name << " -> ";
            Rule* rulePtr = prodPtr->first;
            while (rulePtr != nullptr) {
                cout << rulePtr->r;
                if (rulePtr->next != nullptr) {
                    cout << " | ";
                }
                rulePtr = rulePtr->next;
            }
            cout << endl;
            prodPtr = prodPtr->next;  // Move to the next production
        }
    }

    void freeCFG() {
        Production* prodPtr = start;
        while (prodPtr != nullptr) {
            Rule* rulePtr = prodPtr->first;
            while (rulePtr != nullptr) {
                Rule* temp = rulePtr;
                rulePtr = rulePtr->next;
                delete temp;
            }
            Production* tempProd = prodPtr;
            prodPtr = prodPtr->next;
            delete tempProd;
        }
    }

    void deleteProduction(const string& prodName) {
        Production* prev = nullptr;
        Production* current = start;

        while (current != nullptr) {
            if (current->name == prodName) {
                if (prev == nullptr) {
                    start = current->next;
                } else {
                    prev->next = current->next;
                }

                Rule* rulePtr = current->first;
                while (rulePtr != nullptr) {
                    Rule* temp = rulePtr;
                    rulePtr = rulePtr->next;
                    delete temp;
                }

                delete current;
                return;
            }

            prev = current;
            current = current->next;
        }
    }

    void deleteRuleOfProduction(const string& prodName, const string& ruleStr) {
        Production* prodPtr = start;

        while (prodPtr != nullptr) {
            if (prodPtr->name == prodName) {
                Rule* prev = nullptr;
                Rule* current = prodPtr->first;

                while (current != nullptr) {
                    if (current->r == ruleStr) {
                        if (prev == nullptr) {
                            prodPtr->first = current->next;
                        } else {
                            prev->next = current->next;
                        }
                        delete current;
                        return;
                    }
                    prev = current;
                    current = current->next;
                }
                return; // Rule not found
            }

            prodPtr = prodPtr->next;
        }
    }

    void linkProductions(const string& prodName1, const string& prodName2) {
        Production* prodPtr = start;
        Production* prod1 = nullptr;
        Production* prod2 = nullptr;

        while (prodPtr != nullptr) {
            if (prodPtr->name == prodName1) {
                prod1 = prodPtr;
            }
            if (prodPtr->name == prodName2) {
                prod2 = prodPtr;
            }
            prodPtr = prodPtr->next;
        }

        if (prod1 != nullptr && prod2 != nullptr) {
            prod1->next = prod2;
            if (start == prod1) {
                start = prod1;
            }
        }
    }
};

int main() {
    CFG cfg;

    // Create productions and add rules
    Production* p1 = cfg.createProduction("A");
    cfg.addRuleToProduction(p1, "Ab");
    cfg.addRuleToProduction(p1, "dB");
    cfg.addRuleToProduction(p1, "e");

    Production* p2 = cfg.createProduction("B");
    cfg.addRuleToProduction(p2, "i");
    cfg.addRuleToProduction(p2, "u");

    // Link productions
    cfg.linkProductions("A", "B");

    // Display the CFG
    cfg.displayCFG();

    // cout << "After deleting the rule 'dB' of production 'A'" << endl;

    // // Delete specific rule "dB" of production A
    // cfg.deleteRuleOfProduction("A", "dB");

    // // Display the CFG after deleting the specific rule
    // cfg.displayCFG();

    // // Free memory
    // cfg.freeCFG();

    return 0;
}