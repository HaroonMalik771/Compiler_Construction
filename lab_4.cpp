#include <iostream>
#include <string>

struct Rule {
    std::string r;
    Rule* next;
};

struct Production {
    std::string name;
    Production* next;
    Rule* first;
    Rule* last;
};

// Function to create a new Rule
Rule* createRule(const std::string& ruleStr) {
    Rule* newRule = new Rule;
    newRule->r = ruleStr;
    newRule->next = nullptr;
    return newRule;
}

// Function to create a new Production
Production* createProduction(const std::string& prodName) {
    Production* newProd = new Production;
    newProd->name = prodName;
    newProd->next = nullptr;
    newProd->first = nullptr;
    newProd->last = nullptr;
    return newProd;
}

// Function to add a rule to a production
void addRuleToProduction(Production* production, const std::string& ruleStr) {
    Rule* newRule = createRule(ruleStr);
    if (production->first == nullptr) {
        production->first = newRule;
        production->last = newRule;
    } else {
        production->last->next = newRule;
        production->last = newRule;
    }
}

// Function to display the CFG
void displayCFG(Production* start) {
    Production* prodPtr = start;
    while (prodPtr != nullptr) {
        std::cout << prodPtr->name << " -> ";
        Rule* rulePtr = prodPtr->first;
        while (rulePtr != nullptr) {
            std::cout << rulePtr->r;
            if (rulePtr->next != nullptr) {
                std::cout << " | ";
            }
            rulePtr = rulePtr->next;
        }
        std::cout << std::endl;
        prodPtr = prodPtr->next;
    }
}

// Function to free memory allocated for the CFG
void freeCFG(Production* start) {
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

// Function to delete a given production
void deleteProduction(Production*& start, const std::string& prodName) {
    Production* prev = nullptr;
    Production* current = start;

    while (current != nullptr) {
        if (current->name == prodName) {
            if (prev == nullptr) {
                start = current->next;
            } else {
                prev->next = current->next;
            }

            // Free memory allocated for rules of the production
            Rule* rulePtr = current->first;
            while (rulePtr != nullptr) {
                Rule* temp = rulePtr;
                rulePtr = rulePtr->next;
                delete temp;
            }

            // Free memory allocated for the production
            delete current;
            return;
        }

        prev = current;
        current = current->next;
    }
}

// Function to delete a specific rule of a given production
void deleteRuleOfProduction(Production* start, const std::string& prodName, const std::string& ruleStr) {
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




 int main() {
    Production* start = nullptr;
    
    // Create productions and add rules
    Production* p1 = createProduction("A");
    addRuleToProduction(p1, "Ab");
    addRuleToProduction(p1, "dB");
    addRuleToProduction(p1, "e");
    
    Production* p2 = createProduction("B");
    addRuleToProduction(p2, "i");
    addRuleToProduction(p2, "u");
    
    // Link productions together
    p1->next = p2; // Link A to B
    
    start = p1; // Set start pointer to the first production
    
    // Display the CFG
    displayCFG(start);
    
    // Delete specific rule "dB" of production A
    deleteRuleOfProduction(start, "A", "dB");
    
    // Display the CFG after deleting the specific rule
    displayCFG(start);
    
    // Free memory
    freeCFG(start);
    
    return 0;

}






