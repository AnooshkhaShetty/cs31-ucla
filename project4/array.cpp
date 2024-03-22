#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int locateMinimum(const string array[], int n) {
    // For loop does not work with arrays of size 1, so validation is done in
    // advance
    if (n > 1) {
        int min_value_index = 0;
        string min_value = array[0];

        for (int i = 1; i < n; i++) {
            if (array[i] < min_value) {
                min_value_index = i;
                min_value = array[i];
            }
        }

        return min_value_index;
    } else if (n == 1) {
        return 0;
    } else {
        return -1;
    }
}

int countCommonElements(const string array1[], int n1, const string array2[],
                        int n2) {
    if (n1 > 0 && n2 > 0) {
        int num_common_elements = 0;

        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                num_common_elements = array1[i] == array2[j]
                                          ? num_common_elements + 1
                                          : num_common_elements;
            }
        }

        return num_common_elements;
    } else {
        return -1;
    }
}

int countVowels(const string array[], int n) {
    if (n > 0) {
        int num_vowels = 0;

        for (int i = 0; i < n; i++) {
            for (size_t j = 0; j < array[i].length(); j++) {
                const char letter = tolower(array[i].at(j));
                num_vowels = letter == 'a' || letter == 'e' || letter == 'i' ||
                                     letter == 'o' || letter == 'u' ||
                                     letter == 'y'
                                 ? num_vowels + 1
                                 : num_vowels;
            }
        }

        return num_vowels;
    } else {
        return -1;
    }
}

bool hasThreeOfX(const string array[], int n, string x) {
    if (n > 0) {
        int num_x = 0;

        for (int i = 0; i < n; i++) {
            num_x = array[i] == x ? num_x + 1 : num_x;
        }

        return num_x == 3;
    } else {
        return false;
    }
}

// Uses Boyer–Moore majority vote algorithm
string majorityElement(const string array[], int n) {
    if (n > 1) {
        string majority_candidate = array[0];
        int candidate_count = 1;
        int majority_threshold = n / 2;
        int majority_candidate_count = 0;

        // First pass finds the majority element, if it exists
        for (int i = 1; i < n; i++) {
            if (array[i] == majority_candidate) {
                candidate_count++;
            } else {
                candidate_count--;

                majority_candidate =
                    candidate_count <= 0 ? array[i] : majority_candidate;
            }
        }

        // Second pass to check that majority_candidate is actually the majority
        // element
        for (int i = 0; i < n; i++) {
            majority_candidate_count = array[i] == majority_candidate
                                           ? majority_candidate_count + 1
                                           : majority_candidate_count;
        }

        return majority_candidate_count > majority_threshold
                   ? majority_candidate
                   : "";
    } else {
        return "";
    }
}

bool shiftRight(string array[], int n, int amount, string placeholder) {
    if (n > 0 && amount > n) {
        for (int i = 0; i < n; i++) {
            array[i] = placeholder;
        }

        return true;
    } else if (n > 0 && amount > 0) {
        // Moves each element forward by one index, down to amount
        for (int i = n - 1; i >= amount; i--) {
            array[i] = array[i - amount];
        }

        for (int i = 0; i < amount; i++) {
            array[i] = placeholder;
        }

        return true;
    } else {
        return false;
    }
}

// Helper function for rotateLeft()
void reverseArray(string array[], int start, int end) {
    // Note that start to end is reversed, inclusive
    const int halfway = (end - start + 1) / 2 + start;
    for (int i = start; i < halfway; i++) {
        const int partner = end - (i - start);
        string temp = array[i];
        array[i] = array[partner];
        array[partner] = temp;
    }
}

bool rotateLeft(string array[], int n, int amount) {
    // array stays the same when amount is a multiple of n
    if (n > 0 && amount > 0 && amount % n != 0) {
        // Rotating by more than n is equivalent to rotating by modulo n. For
        // example, rotating by 9 is equivalent to rotating by 1. Modulo
        // operation is performed inside the if statement to avoid
        // division-by-zero errors.
        amount = amount % n;
        reverseArray(array, 0, n - 1);
        // Reverses elements that only move left and are not wrapped to the
        // right end of the array
        reverseArray(array, 0, n - amount - 1);
        // Reverses elements that are wrapped to the right end of the array
        reverseArray(array, n - amount, n - 1);

        return true;
    } else {
        return false;
    }
}

int replaceAll(string array[], int n, char letterToReplace, char letterToFill) {
    if (n > 0) {
        int num_replacements = 0;

        for (int i = 0; i < n; i++) {
            for (size_t j = 0; j < array[i].length(); j++) {
                if (array[i].at(j) == letterToReplace) {
                    array[i].at(j) = letterToFill;
                    num_replacements++;
                    array[i].replace(j, 1, 1, letterToFill);
                }
            }
        }

        return num_replacements;
    } else {
        return -1;
    }
}

// Helper function for testing
bool areArraysEqual(string array1[], string array2[], int n) {
    for (int i = 0; i < n; i++) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    string test_0[1];
    string test_1[8] = {"samwell", "jon",   "margaery",  "daenerys",
                        "tyrion",  "sansa", "magdalena", "jon"};
    string test_2[5] = {"mama", "mama", "12", "sansa", "mama"};
    string test_3[7] = {"a", "b", "b", "A", "C", "c", "R"};
    string test_4[10] = {"C", "C++", "Java", "Python",     "Bash",
                         "R", "Go",  "Rust", "JavaScript", "PHP"};
    string test_5[4] = {"identical", "identical", "identical", "identical"};
    string test_6[1] = {""};
    string test_7[5] = {"XYZ", "Abc", "XYZ", "zzZ", "XYZ"};

    // locateMinimum()
    assert(locateMinimum(test_1, 8) == 3);
    assert(locateMinimum(test_2, 5) == 2);
    assert(locateMinimum(test_3, 7) == 3);
    assert(locateMinimum(test_4, 10) == 4);
    assert(locateMinimum(test_0, 0) == -1);
    assert(locateMinimum(test_6, 1) == 0);
    assert(locateMinimum(test_7, 5) == 1);

    // countCommonElements()
    assert(countCommonElements(test_1, 8, test_2, 5) == 1);
    assert(countCommonElements(test_1, 8, test_3, 6) == 0);
    assert(countCommonElements(test_3, 7, test_4, 10) == 2);
    assert(countCommonElements(test_0, 0, test_0, 0) == -1);
    assert(countCommonElements(test_6, 1, test_6, 1) == 1);
    assert(countCommonElements(test_5, 4, test_5, 4) == 16);
    assert(countCommonElements(test_7, 5, test_7, 5) == 11);

    // countVowels()
    assert(countVowels(test_2, 5) == 8);
    assert(countVowels(test_1, 8) == 21);
    assert(countVowels(test_0, 0) == -1);
    assert(countVowels(test_6, 1) == 0);

    // hasThreeOfX()
    assert(!hasThreeOfX(test_1, 8, "jon"));
    assert(hasThreeOfX(test_2, 5, "mama"));
    assert(!hasThreeOfX(test_5, 4, "identical"));
    assert(!hasThreeOfX(test_0, 0, ""));
    assert(!hasThreeOfX(test_6, 1, ""));
    assert(hasThreeOfX(test_7, 5, "XYZ"));
    assert(!hasThreeOfX(test_7, 5, "Abc"));

    // majorityElement()
    assert(majorityElement(test_2, 5) == "mama");
    assert(majorityElement(test_5, 4) == "identical");
    assert(majorityElement(test_6, 1) == "");
    assert(majorityElement(test_0, 0) == "");
    assert(majorityElement(test_7, 5) == "XYZ");

    // shiftRight()
    assert(shiftRight(test_1, 8, 2, "lol, lmao"));
    string test_1_modified[8] = {"lol, lmao", "lol, lmao", "samwell", "jon",
                                 "margaery",  "daenerys",  "tyrion",  "sansa"};
    assert(areArraysEqual(test_1, test_1_modified, 8));
    assert(shiftRight(test_5, 4, 5, "lol, lmao"));
    string test_5_modified[4] = {"lol, lmao", "lol, lmao", "lol, lmao",
                                 "lol, lmao"};
    assert(areArraysEqual(test_5, test_5_modified, 4));
    assert(!shiftRight(test_0, 0, 1, "lol, lmao"));

    // rotateLeft()
    assert(!rotateLeft(test_1, 8, 8));
    assert(areArraysEqual(test_1, test_1_modified, 5));
    assert(rotateLeft(test_4, 10, 4));
    string test_4_modified[10] = {"Bash", "R", "Go",  "Rust", "JavaScript",
                                  "PHP",  "C", "C++", "Java", "Python"};
    assert(areArraysEqual(test_4, test_4_modified, 10));
    assert(!rotateLeft(test_0, 0, 1));
    string test_1_copy[8] = {"samwell", "jon",   "margaery",  "daenerys",
                             "tyrion",  "sansa", "magdalena", "jon"};
    string test_1_copy_modified[8] = {"margaery", "daenerys",  "tyrion",
                                      "sansa",    "magdalena", "jon",
                                      "samwell",  "jon"};
    assert(rotateLeft(test_1_copy, 8, 2));
    assert(areArraysEqual(test_1_copy, test_1_copy_modified, 8));

    // replaceAll()
    assert(replaceAll(test_7, 5, 'X', 'W') == 3);
    string test_7_modified[5] = {"WYZ", "Abc", "WYZ", "zzZ", "WYZ"};
    assert(areArraysEqual(test_7, test_7_modified, 5));
    assert(replaceAll(test_6, 1, 'X', 'W') == 0);
    assert(replaceAll(test_0, 0, '\0', 'W') == -1);

    cerr << "Reached end of tests" << endl;

    return 0;
}
