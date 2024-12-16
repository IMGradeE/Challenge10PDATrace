#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <strings.h>
using namespace std;


string stack;
string stack2;
string tape;
enum states{
    START,
    READ_1,
    READ_2,
    PUSH_1_STACK_2,
    PUSH_2_STACK_1,
    PUSH_3_STACK_2,
    PUSH_4_STACK_2,
    PUSH_5_STACK_1,
    PUSH_6_STACK_1,
    PUSH_7_STACK_2,
    PUSH_8_STACK_2,
    POP_1_STACK_2,
    POP_2_STACK_1,
    POP_3_STACK_1,
    POP_4_STACK_1,
    POP_5_STACK_1,
    POP_6_STACK_2,
    POP_7_STACK_2,
    POP_8_STACK_1,
    REJECT,
    ACCEPT
};
enum states state;

string stateToString(){
    switch (state) {
        case START:
            return "START";
        case READ_1:
            return "READ_1";
        case READ_2:
            return "READ_2";
        case PUSH_3_STACK_2:
            return "PUSH_2";
        case PUSH_4_STACK_2:
            return "PUSH_2";
        case PUSH_7_STACK_2:
            return "PUSH_2";
        case PUSH_8_STACK_2:
            return "PUSH_2";
        case PUSH_1_STACK_2:
            return "PUSH_2";
        case PUSH_5_STACK_1:
            return "PUSH_1_ii";
        case PUSH_6_STACK_1:
            return "PUSH_1";
        case PUSH_2_STACK_1:
            return "PUSH_1_i";
        case POP_6_STACK_2:
            return "POP_2_i";
        case POP_7_STACK_2:
            return "POP_2";
        case POP_1_STACK_2:
            return "POP_2_i";
        case POP_8_STACK_1:
            return "POP_1";
        case POP_3_STACK_1:
            return "POP_1_i";
        case POP_4_STACK_1:
            return "POP_1";
        case POP_5_STACK_1:
            return "POP_1";
        case POP_2_STACK_1:
            return "POP_1_ii";
        case REJECT:
            return "REJECT";
        case ACCEPT:
            return "ACCEPT";
    }
}

char performRead(){
    if(tape.empty()){
        return '-';
    }
    char r = tape.front();
    tape.assign(++tape.begin(), tape.end());
    return r;
}

void performPush(){
    stack.push_back('X');
}

void pushStack_1(char x){
    stack.push_back(x);
}

void pushStack_2(char x){
    stack2.push_back(x);
}

char popStack_1() {
    if(stack.empty()){
        return '-';
    }
    char r = stack.back();
    stack.pop_back();
    return r;
}

char popStack_2() {
    if(stack2.empty()){
        return '-';
    }
    char r = stack2.back();
    stack2.pop_back();
    return r;
}

void printInfoAsMKDWN_LATEX(){
    char tape_c_str[64] = "";
    string delta = "\\Delta";
    string t;
    t = tape;
    t.append(delta);
    t.copy(tape_c_str, t.length(), 0);
    printf("|$%-s$|$\\Delta %-s$|$\\Delta %-s$|$%-s$|\n", stateToString().c_str(), stack.c_str(), stack2.c_str(), tape_c_str);
}

void printInfo(){
    char tape_c_str[64] = "";
    tape.copy(tape_c_str, tape.length(), 0);
    tape_c_str[tape.length()] = '-';
    printf("%-15s-%-15s-%-15s%-s\n", stateToString().c_str(), stack.c_str(), stack2.c_str(), tape_c_str);
}

void Problem_1(){
    char readLetter;
    while(state != REJECT && state != ACCEPT) {
        switch (state) {
            case START:
                state = READ_1;
                break;

            case READ_1:
                readLetter = performRead();
                switch (readLetter) {
                    case '-':
                        state = POP_1_STACK_2;
                        break;
                    default:
                        state = PUSH_1_STACK_2;
                        break;
                }
                break;


            case POP_1_STACK_2:
                // read from stack 2
                readLetter = popStack_2();
                switch (readLetter) {
                    case '-':
                        state = POP_3_STACK_1;
                        break;
                    default:
                        state = PUSH_2_STACK_1;
                        break;
                }
                break;

            case POP_2_STACK_1:
                // read from stack 1.
                readLetter = popStack_1();
                switch (readLetter) {
                    case 'b':
                        state = POP_3_STACK_1;
                        break;
                    case 'a':
                        state = POP_8_STACK_1;
                        break;
                    default:
                        state = REJECT;
                        break;
                }
                break;

            case POP_3_STACK_1:
                // read from the stack.
                readLetter = popStack_1();
                switch (readLetter) {
                    case '-':
                        state = ACCEPT;
                        break;
                    case 'a':
                        state = POP_2_STACK_1;
                        break;
                    case 'b':
                        state = POP_4_STACK_1;
                        break;
                }
                break;
            case POP_4_STACK_1:
                // read from the stack.
                readLetter = popStack_1();
                switch (readLetter) {
                    case 'a':
                        state = POP_3_STACK_1;
                        break;
                    case 'b':
                        state = POP_5_STACK_1;
                        break;
                    default:
                        state = REJECT;
                        break;
                }
                break;

            case POP_5_STACK_1:
                // read from the stack.
                readLetter = popStack_1();
                switch (readLetter) {
                    case '-':
                        state = PUSH_4_STACK_2;
                        break;
                    default:
                        state = PUSH_3_STACK_2;
                        break;
                }
                break;
            case POP_6_STACK_2:
                // read from the stack.
                readLetter = popStack_2();
                switch (readLetter) {
                    case '-':
                        state = POP_4_STACK_1;
                        break;
                    default:
                        state = PUSH_5_STACK_1;
                        break;
                }
                break;

            case POP_7_STACK_2:
                // read from the stack.
                readLetter = popStack_2();
                switch (readLetter) {
                    case '-':
                        state = POP_2_STACK_1;
                        break;
                    default:
                        state = POP_7_STACK_2;
                        break;
                }
                break;

            case POP_8_STACK_1:
                // read from the stack.
                readLetter = popStack_1();
                switch (readLetter) {
                    case '-':
                        state = PUSH_7_STACK_2;
                        break;
                    default:
                        state = POP_8_STACK_1;
                        break;
                }
                break;


            case PUSH_1_STACK_2:
                pushStack_2(readLetter);
                state = READ_1;
                break;

            case PUSH_2_STACK_1:
                pushStack_1(readLetter);
                state = POP_1_STACK_2;
                break;


            case PUSH_3_STACK_2:
                pushStack_2(readLetter);
                state = POP_5_STACK_1;
                break;

            case PUSH_4_STACK_2:
                pushStack_2('b');
                state = POP_6_STACK_2;
                break;

            case PUSH_5_STACK_1:
                pushStack_1(readLetter);
                state = POP_6_STACK_2;
                break;

            case PUSH_6_STACK_1:
                pushStack_1(readLetter);
                state = POP_7_STACK_2;
                break;

            case PUSH_7_STACK_2:
                pushStack_2('a');
                state = POP_7_STACK_2;
                break;

            case PUSH_8_STACK_2:
                pushStack_2(readLetter);
                state = POP_8_STACK_1;
                break;
        }
        // print info
        printInfo();
    }
}

void TRAILING_COUNT(){
    while(state != REJECT && state != ACCEPT) {
        char readLetter;
        switch (state) {
            case START:
                state = READ_1;
                break;
            case READ_1:
                readLetter = performRead();
                switch (readLetter) {
                    case '-':
                        state = POP_3_STACK_1;
                        break;
                    default:
                        state = PUSH_2_STACK_1;
                        break;
                }
                break;
            case PUSH_1_STACK_2:
                pushStack_2(readLetter);
                state = POP_2_STACK_1;
                break;
            case PUSH_2_STACK_1:
                pushStack_1(readLetter);
                state = READ_1;
                break;
            case PUSH_5_STACK_1:
                pushStack_1(readLetter);
                state = POP_1_STACK_2;
                break;
            case POP_1_STACK_2:
                // read from stack 2.
                readLetter = popStack_2();
                switch (readLetter) {
                    case '-':
                        state = POP_3_STACK_1;
                        break;
                    default:
                        state = PUSH_5_STACK_1;
                        break;
                }
                break;
            case POP_2_STACK_1:
                // read from stack 1.
                readLetter = popStack_1();
                switch (readLetter) {
                    case '-':
                        state = POP_6_STACK_2;
                        break;
                    default:
                        state = PUSH_1_STACK_2;
                        break;
                }
                break;
            case POP_3_STACK_1:
                // read from stack 1.
                readLetter = popStack_1();
                switch (readLetter) {
                    case '-':
                        state = ACCEPT;
                        break;
                    case 'a':
                        state = POP_2_STACK_1;
                        break;
                    default:
                        state = REJECT;
                        break;
                }
                break;
            case POP_6_STACK_2:
                // read from stack 1.
                readLetter = popStack_2();
                switch (readLetter) {
                    case '-':
                        state = REJECT;
                        break;
                    default:
                        state = POP_1_STACK_2;
                        break;
                }
                break;
        }
        printInfo();
    }
}

int main() {
    /*do{
        state = START;
        cout << "Enter an input string: ";
        getline(cin, tape);
        cout << "\n";
        cout << "STATE     STACK_1   STACK_2   TAPE\n"
             << "----------------------------------\n";
        printInfo();
        loop();
        cout << "q to quit: ";
        getline(cin, tape);
    }while(tape != "q");*/

    string s[4] ={ "bbaa", "aaaaaa", "abaaaa", "baabaa" };
    for (string t: s) {
        stack.clear();
        stack2.clear();
        state = START;
        tape = t;
        cout << "STATE          STACK_1        STACK_2        TAPE\n"
             << "----------------------------------\n";
        printInfo();
        TRAILING_COUNT();
        cout << "\n";
    }
}
