#include <iostream>
#include <string>

using namespace std;

bool ValidCellPlan(string plan) {
    return plan == "Unlimited Elite" || plan == "Unlimited Extra" ||
           plan == "Unlimited Starter" || plan == "Prepaid";
}

bool ValidAutopay(string autopay) {
    return autopay == "Yes" || autopay == "No";
}

bool ValidPaperlessBilling(string paperless_billing) {
    return paperless_billing == "Yes" || paperless_billing == "No";
}

bool ValidLines(int lines) { return lines == 1 || lines == 2 || lines == 3; }

bool ValidGigabytes(int gigabytes) { return gigabytes >= 0 && gigabytes <= 30; }

int ApplyCommonDiscounts(int cost, string autopay, string paperless_billing,
                         int lines) {
    // Discount if signed up for Autopay
    cost = (autopay == "Yes") ? cost - 2 * lines : cost;
    // Discount if signed up for Paperless Billing
    cost = (paperless_billing == "Yes") ? cost - 3 * lines : cost;
    // Discount For Extra Phone Lines On This Plan
    cost = (lines > 1) ? cost - lines * 10 : cost;
    return cost;
}

int main() {
    string plan = "", autopay = "", paperless_billing = "";
    int lines = 0, gigabytes = 0;
    // `cost` is an integer to avoid the accuracy headaches of floating-point
    // arithmetic
    int cost = 0;

    cout << "What type of cell plan do you have? ";
    getline(cin, plan);
    cout << "Are you on autopay? ";
    getline(cin, autopay);
    cout << "Are you on paperless billing? ";
    getline(cin, paperless_billing);
    cout << "How many lines will be on your plan? ";
    cin >> lines;
    cout << "How many gigabytes did you consume this month? ";
    cin >> gigabytes;

    if (!ValidCellPlan(plan)) {
        cout << "Your cell plan is not valid!" << endl;
    } else if (!ValidAutopay(autopay)) {
        cout << "Your autopay is not valid!" << endl;
    } else if (!ValidPaperlessBilling(paperless_billing)) {
        cout << "Your paperless billing is not valid!" << endl;
    } else if (!ValidLines(lines)) {
        cout << "Your lines are not valid!" << endl;
    } else if (!ValidGigabytes(gigabytes)) {
        cout << "Your gigabytes are not valid!" << endl;
    } else {
        // Calculates cost of monthly cell service
        if (plan == "Unlimited Elite") {
            cost = 85 * lines;
            cost =
                ApplyCommonDiscounts(cost, autopay, paperless_billing, lines);
        } else if (plan == "Unlimited Extra") {
            cost = 75 * lines;
            cost =
                ApplyCommonDiscounts(cost, autopay, paperless_billing, lines);
        } else if (plan == "Unlimited Starter") {
            cost = 65 * lines;
            cost =
                ApplyCommonDiscounts(cost, autopay, paperless_billing, lines);
        } else if (plan == "Prepaid") {
            cost = 50 * lines;
            cost =
                ApplyCommonDiscounts(cost, autopay, paperless_billing, lines);
            // Data usage charge: First 4 gigabytes included at no charge then
            // $10.00 for each 2 gigabytes used additionally
            if (gigabytes > 4) {
                cost += 10 * ((gigabytes - 4) / 2);
            }
        }

        cout << "Your " << plan << " cell plan costs $" << cost << ".00."
             << endl;
    }

    return 0;
}
