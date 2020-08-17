#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include <time.h>

using namespace std;

struct card {
    string name;
    int price;
};

struct problem {
    vector<struct card> cards;
    int max_amount;
};


bool card_exists(string name, vector<struct card> &cards) {
    // return true if card named `name`, exists in vector `cards`
    // otherwise false
    for(int i=0; i<cards.size(); i++) {
        if(cards[i].name == name) {
            return true;
        }
    }
    return false;
}


vector<struct card> get_all_market_prices(ifstream& infile) {
    // parses the market file prices and returns the cards
    string line, word, card_name;
    int lineno = 0, price;
    vector<struct card> cards;
    stringstream ss;
    
    while(getline(infile, line)) {
        // each line contains card name, a space and the price of the card
        // accordingly, parse the file line by line
        lineno++;
        if(lineno == 1) { continue; }

        ss << line;
        ss >> card_name;
        ss >> price;
        ss.str("");
        ss.clear();

        cards.push_back((struct card) { card_name, price });
    }
    return cards;
}


vector<problem> get_all_prices(ifstream& infile, vector<struct card> &market_price_list) {
    // parses the prices Gertrude is willing to sell the cards at
    string line, card_name, word;
    int price, linecount = 0, max_amount;
    stringstream ss;
    vector<struct problem> problems;

    while(getline(infile, line)) {
        // parse <line_count> <max_amount>
        ss << line;
        ss >> linecount;
        ss >> max_amount;
        ss.str(""); ss.clear();
        vector<struct card> cards;
        for(int i=0; i<linecount; i++) {
            // retrive <linecount> number of lines
            // where each line contains card name, a space and the price of the card
            getline(infile, line);

            ss << line;
            ss >> card_name;
            ss >> price;

            if(! card_exists(card_name, market_price_list)) {
                // if card is not there in market price list, just show an error
                cout << "Card '" << card_name << "' was not found in market price list" << endl;
                exit(0);
            }

            ss.str(""); ss.clear();
            cards.push_back((struct card) {card_name, price});
        }
        problems.push_back((struct problem) {cards, max_amount});
    }
    return problems;
}

long long pow(long long n, long long n1) {
    // return n raised to the power of n1
    if(n1 == 0) { return 1; }
    long long n2 = 1;
    for(long long i=0; i<n1; i++) {
        n2 = n2 * n;
    }
    return n2;
}

void next_subset(long long &current_state, vector<struct card> &cards, vector<struct card> &all_cards) {
    // generates the next power set
    long long copy = current_state;
    int count = 1, len = all_cards.size(), bit;
    // bits[] array will store the binary representation of the number `current_state`
    // where each element in array is either true or false signifying the corresponding 1 and 0
    // respectively.
    bool bits[len];
    for(int i=0; i<len; i++) { bits[i] = false; }
    while(copy > 0) {
        // converting to binary
        bit = copy % 2;
        bits[len - count] = ((bit == 1) ? true : false);
        copy = copy / 2;
        count++;
    }
    cards.clear();
    for(int i=0; i<len; i++) {
        if(bits[i]) {
            // push cards according the bit
            // true means card at that position is included
            // false means not included
            cards.push_back(all_cards[i]);
        }
    }
    current_state++;
}

int sumPrices(vector<struct card> &cards) {
    // returns the sum of prices of all the given cards
    int prices = 0;
    for(int i=0; i<cards.size(); i++) {
        prices += cards[i].price;
    }
    return prices;
}

int sumProfits(vector<struct card> &cards, vector<struct card> &mp) {
    // returns the sum of prices in mp(market price list) for all the `cards`
    int profits = 0;
    bool found;
    for(int i=0; i<cards.size(); i++) {
        found = false;
        for(int j=0; j<mp.size(); j++) {
            if(cards[i].name == mp[j].name) {
                profits += mp[j].price;
                found = true;
                break;
            }
        }
    }
    return profits;
}

void copy_cards(vector<struct card> &destination, vector<struct card> &source) {
    // copies vector `source` to vector `destination`
    destination.clear();
    for(int i=0; i<source.size(); i++) {
        destination.push_back(source[i]);
    }
}

vector<struct card> compute_max_profit(vector<struct card> I, vector<struct card> &X, int W) {
    // computes the maximum profit possible for the given amount, W
    int maxProfit = 0, profit;
    vector<struct card> S;
    vector<struct card> M;
    long long max_subsets = pow(2, X.size());
    long long current_state = 1;

    if(sumPrices(I) <= W) {
        return I;
    }
    while(current_state < max_subsets) {
        for(int i=0; i<S.size(); i++) {
        }
        if(sumPrices(S) <= W) {
            profit = sumProfits(S, X);
            if(profit > maxProfit) {
                // update max profit, if
                // profit is greater than what we have now
                maxProfit = profit;
                copy_cards(M, S);
            }
        }
        next_subset(current_state, S, I);
    }
    return M;
}


int main(int argc, char *argv[]) {
    char *market_price_file_name;
    char *price_list_file_name;
    bool market_price_file_set = false, price_list_file_set = false;

    for(int i=1; i<argc; ) {
        if(strcmp(argv[i], "-m") == 0) {
            // if `m` switch was found, then
            // argument is the market price file
            market_price_file_name = argv[++i];
            market_price_file_set = true;
            i++;
        } else if(strcmp(argv[i], "-p") == 0) {
            // if `p` switch was found, then
            // argument is a price list file
            price_list_file_name = argv[++i];
            price_list_file_set = true;
            i++;
        } else {
            return 0;
        }
    }

    if(market_price_file_set == false || price_list_file_set == false) {
        cout << "Invalid arguments";
        return 0;
    }

    ifstream market_price_file(market_price_file_name);
    ifstream price_list_file(price_list_file_name);

    if(market_price_file.fail()) {
        cout << "File '" << market_price_file_name << "' does not exist" << endl;
        return 0;
    }

    if(price_list_file.fail()) {
        return 0;
    }

    // parse all cards in market price list
    vector<struct card> market_price_list = get_all_market_prices(market_price_file);
    // parse all cards in price list
    vector<struct problem> problems = get_all_prices(price_list_file, market_price_list);
    market_price_file.close();
    price_list_file.close();

    // best cards list
    vector<struct card> best_cards;
    int max_profit;
    time_t start_time, end_time;

    
    ofstream output("output.txt");

    for(int i=0; i<problems.size(); i++) {
        start_time = time(NULL);
        best_cards = compute_max_profit(problems[i].cards, market_price_list, problems[i].max_amount);
        end_time = time(NULL);
        max_profit = sumProfits(best_cards, market_price_list);
        output << problems[i].max_amount << " " << problems[i].cards.size() << " " << max_profit << " " << best_cards.size() << " "<< (end_time - start_time) << endl;
    }
    output.close();

    return 0;
}