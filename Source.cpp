#include <iostream>
#include <random>
#include <vector>
using namespace std;

template <typename T = unsigned int>
T RandomNumberGenerator(T min, T max)
{
    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_int_distribution<T> dist6(min, max); 
    return static_cast<T>(dist6(rng));
}

class Inventory
{
private:
    std::string ItemName;
    int value = -1;
    int weight = -1;
public:
    Inventory(std::string v1) : ItemName(v1.c_str()) {
        value = RandomNumberGenerator(100, 800);
        weight = RandomNumberGenerator(15, 35);
    }
    ~Inventory() { ItemName.clear(); }
    void DisplayInventory() {
        if (value > 0 && weight > 0 && ItemName.length() > 0) {
            std::cout << "\t\t" << ItemName << "\t\tValue: " << value << "\tWeight: " << weight << std::endl;
        }
    }
    std::string GetItemName() { return this->ItemName; }
    auto GetVal() { return this->value; }
    auto GetWeight() { return this->weight; }
};

std::vector<Inventory*> m_Inventory;
bool CompareItemName(Inventory* a, Inventory* b) {
    return a->GetItemName() < b->GetItemName(); 
}

bool CompareValue(Inventory* a, Inventory* b) {
    return a->GetVal() < b->GetVal();
}

bool CompareWeight(Inventory* a, Inventory* b) {
    return a->GetWeight() < b->GetWeight();
}

bool inventorySet = false;

int main()
{
    int itemNumCount = -1;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~INVENTORY ORGANIZER~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl << endl;
    cout << "\t\tHow many items do you want to store? \n\t\t~~~~~~(No more than 10 items)~~~~~~\n\t\t\t-> ";
    cin >> itemNumCount;

    cout << "\n\t\tWhat items would you like to store? " << endl;
    for (int i = 0; i < itemNumCount; i++)
    {
        std::string temp;
        std::cout << "\t\tItem " << i + 1 << ": ";
        cin >> temp;
        m_Inventory.push_back(new Inventory(temp));
    }


    cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~YOUR INVENTORY~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    for (auto i : m_Inventory)
    {
        i->DisplayInventory();
    }

    int sorttype = -1;
    start:
    if (inventorySet)
    {
        cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~INVENTORY ORGANIZER~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;        
        cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~YOUR INVENTORY~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        for (auto i : m_Inventory)
        {
            i->DisplayInventory();
        }
    }
    cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SORT BY~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\n\t\tPress 1: Alphabetical\n\t\tPress 2: Value\n\t\tPress 3: Weight\n\t\tPress 4: EXIT\n\n\t\tYour Option: ";
    cin >> sorttype;
    switch (sorttype)
    {
    case 1:
        std::sort(m_Inventory.begin(), m_Inventory.end(), CompareItemName);//Sort the vector alphabetically
        break;
    case 2:
        std::sort(m_Inventory.begin(), m_Inventory.end(), CompareValue);//Sort the vector by value
        break;
    case 3:
        std::sort(m_Inventory.begin(), m_Inventory.end(), CompareWeight);//Sort the vector weight
        break;
    case 4:
        return 0;
    default:break;
    }
    
    auto SortType = [](int sorttype) -> std::string
    {
        switch (sorttype)
        {
        case 1:return "\n\t\tSorted Alphabetically";
        case 2:return "\n\t\tSorted By Value";
        case 3:return "\n\t\tSorted By Weight";
        default:return "none";
        }
    };

    cout << SortType(sorttype) << endl;
    for (auto i : m_Inventory)
    {
        i->DisplayInventory();
    }
    inventorySet = true;
    system("CLS");
    goto start;

    return 0;
}