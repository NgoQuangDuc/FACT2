#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100];

// Function to check if a number is prime
ll prime(ll pr) {
    ll i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++) {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

// Function to calculate the modular multiplicative inverse
ll cd(ll x) {
    ll k = 1;
    while (1) {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}

// Function to generate e and d values
void ce() {
    ll k = 0;
    for (i = 2; i < t; i++) {
        if (t % i == 0)
            continue;

        flag = prime(i);
        if (flag == 1 && i != p && i != q) {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0) {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}

// Function to encrypt the message
void encrypt(ll e_val) {
    ll pt, key = e_val, k, len;
    i = 0;
    len = strlen(msg);
    while (i < len) {
        pt = msg[i];
        k = 1;

        for (j = 0; j < key; j++) {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        en[i] = temp[i];

        i++;
    }

    cout << "\nTHE ENCRYPTED MESSAGE IS\n";
    for (i = 0; i < len; i++) {
        cout << en[i] << " ";
    }
    cout << endl;
}

// Function to decrypt the message
void decrypt(ll d_val) {
    ll ct, key = d_val, k;
    i = 0;
    ll len = strlen(msg);
    while (i < len) {
        ct = en[i];
        k = 1;
        for (j = 0; j < key; j++) {
            k = k * ct;
            k = k % n;
        }
        m[i] = k;
        i++;
    }

    cout << "\nTHE DECRYPTED MESSAGE IS\n";
    for (i = 0; i < len; i++) {
        char val = m[i];
        cout << val;
    }
    cout << endl;
}

int main() {
    cout << "\nENTER FIRST PRIME NUMBER\n";
    cin >> p;
    flag = prime(p);

    if (flag == 0) {
        cout << "\nWRONG INPUT\n";
        exit(1);
    }

    cout << "\nENTER ANOTHER PRIME NUMBER\n";
    cin >> q;
    flag = prime(q);

    if (flag == 0 || p == q) {
        cout << "\nWRONG INPUT\n";
        exit(1);
    }

    n = p * q;
    cout << "n=" << p << "*" << q << "=" << n << endl;
    t = (p - 1) * (q - 1);

    ce();

    cout << "\nPOSSIBLE VALUES OF e AND d ARE\n";
    for (i = 0; i < j - 1; i++)
        cout << e[i] << "\t" << d[i] << "\n";

    cout << "Choose the value of e,d pair" << endl;
    ll e_val, d_val;
    cin >> e_val >> d_val;

    cout << "\nENTER FILENAME CONTAINING MESSAGE\n";
    string filename;
    cin >> filename;

    // Read message from file
    ifstream infile(filename);
    if (!infile) {
        cout << "Error opening file!" << endl;
        return 1;
    }
    infile.getline(msg, sizeof(msg)); // Read a line from the file
    infile.close();

    encrypt(e_val);

    // Overwrite the original message file with the encrypted message
    ofstream outfile(filename);
    if (!outfile) {
        cout << "Error opening file for writing!" << endl;
        return 1;
    }

    for (i = 0; i < strlen(msg); i++) {
        outfile << en[i] << " "; // Write the encrypted values to the file
    }
    outfile.close();

    cout << "\nTHE ENCRYPTED MESSAGE HAS BEEN WRITTEN TO THE FILE.\n";

    // Optionally, you can decrypt the message as well
    decrypt(d_val);

    return 0;
}
