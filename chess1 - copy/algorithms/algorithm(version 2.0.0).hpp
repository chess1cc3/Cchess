#include "include"
typedef long double ld;

int multi_max(int arr[8][8], int currentMinscore, int depth);
int multi_min(int arr[8][8], int currentMaxscore, int depth);

bool is_it_tie(int arr[8][8], string p)
{
    int arr2[8][8];
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) arr2[i][j] = arr[i][j];
    
    int kingpos[2];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (arr[i][j] == 5 && p[p.size()-1] == '1') {
                kingpos[0] = i;
                kingpos[1] = j;
            } if (arr[i][j] == -5 && p[p.size()-1] == '2') {
                kingpos[0] = i;
                kingpos[1] = j;
            }
        }
    }
    if (is_place_safe(arr, p[p.size()-1], kingpos)) return true;
    else return false;
}

// int eval(int arr[8][8])
// {
//     for (int i = 0; i < 8; i++) {
//         for (int j = 0; j < 8; j++) {
//             2000(K-K')
//             + 90(Q-Q')
//             + 50(R-R')
//             + 30(B-B' + N-N')
//             + 10(P-P')
//             - 5(D-D' + S-S' + I-I')
//             + 1(M-M')';
//         };
//     }
// }

int one_max(int arr[8][8], int currentMinscore)
{
    int arr2[8][8];
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) arr2[i][j] = arr[i][j];
    vector<int> v;
    allmove(arr2, "player2", v);

    int maxscore = -99999999;
    for (int i: v) {
        for (int k = 0; k < 8; k++) for (int j = 0; j < 8; j++) arr2[k][j] = arr[k][j];
        int arrr[2][2] = {(i/1000)%10, (i/100)%10, (i/10)%10, i%10};
        bool spec = check_special_move(arr2, arrr);
        move_piece_simpler(arr2, arrr, "player2", spec);
        int sc = 0;
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (arr2[x][y] == 1) sc-=50;
                if (arr2[x][y] == 2) sc-=30;
                if (arr2[x][y] == 3) sc-=30;
                if (arr2[x][y] == 4) sc-=90;
                if (arr2[x][y] == 5) sc-=900;
                if (arr2[x][y] == 6) sc-=10;
                if (arr2[x][y] == -1) sc+=50;
                if (arr2[x][y] == -2) sc+=30;
                if (arr2[x][y] == -3) sc+=30;
                if (arr2[x][y] == -4) sc+=90;
                if (arr2[x][y] == -5) sc+=900;
                if (arr2[x][y] == -6) sc+=10;
            }
        }
        maxscore = max(sc, maxscore);
        if (maxscore > currentMinscore) return 1;
    }

    if (v.size() != 0) return maxscore;
    else {
        if (!is_it_tie(arr, "player2")) return -1300;
        else {
            if (currentMinscore < 0) return 1;
            return 0;
        }
    }
}

int one_min(int arr[8][8], int currentMaxscore)
{
    int arr2[8][8];
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) arr2[i][j] = arr[i][j];
    vector<int> v;
    allmove(arr2, "player1", v);

    int minscore = 99999999;
    for (int i: v) {
        for (int k = 0; k < 8; k++) for (int j = 0; j < 8; j++) arr2[k][j] = arr[k][j];
        int arrr[2][2] = {(i/1000)%10, (i/100)%10, (i/10)%10, i%10};
        bool spec = check_special_move(arr2, arrr);
        move_piece_simpler(arr2, arrr, "player1", spec);

        int sc = 0;
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (arr2[x][y] == 1) sc-=50;
                if (arr2[x][y] == 2) sc-=30;
                if (arr2[x][y] == 3) sc-=30;
                if (arr2[x][y] == 4) sc-=90;
                if (arr2[x][y] == 5) sc-=900;
                if (arr2[x][y] == 6) sc-=10;
                if (arr2[x][y] == -1) sc+=50;
                if (arr2[x][y] == -2) sc+=30;
                if (arr2[x][y] == -3) sc+=30;
                if (arr2[x][y] == -4) sc+=90;
                if (arr2[x][y] == -5) sc+=900;
                if (arr2[x][y] == -6) sc+=10;
            }
        }
        minscore = min(minscore, sc);
        if (minscore < currentMaxscore) return 1;
    }

    if (v.size() != 0) return minscore;
    else {
        if (!is_it_tie(arr, "player1")) return 1300;
        else {
            if (currentMaxscore > 0) return 1;
            return 0;
        }
    }
}

int multi_max(int arr[8][8], int currentMinscore, int depth)
{
    int arr2[8][8];
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) arr2[i][j] = arr[i][j];
    vector<int> v;
    allmove(arr2, "player2", v);

    int maxscore = -99999999;
    for (int i: v) {
        for (int k = 0; k < 8; k++) for (int j = 0; j < 8; j++) arr2[k][j] = arr[k][j];
        int arrr[2][2] = {(i/1000)%10, (i/100)%10, (i/10)%10, i%10};
        bool spec = check_special_move(arr2, arrr);
        move_piece_simpler(arr2, arrr, "player2", spec);
        
        int sc;
        if (depth == 2) sc = one_min(arr2, maxscore);
        if (depth > 2) sc = multi_min(arr2, maxscore, depth-1);

        if (sc == 1) continue;
        maxscore = sc;
        if (maxscore > currentMinscore) return 1;
    }

    if (v.size() != 0) return maxscore;
    else {
        if (!is_it_tie(arr, "player2")) return -1300;
        else {
            if (currentMinscore < 0) return 1;
            return 0;
        }
    }
}

int multi_min(int arr[8][8], int currentMaxscore, int depth)
{
    int arr2[8][8];
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) arr2[i][j] = arr[i][j];
    vector<int> v;
    allmove(arr2, "player1", v);

    int minscore = 99999999;
    for (int i: v) {
        for (int k = 0; k < 8; k++) for (int j = 0; j < 8; j++) arr2[k][j] = arr[k][j];
        int arrr[2][2] = {(i/1000)%10, (i/100)%10, (i/10)%10, i%10};
        bool spec = check_special_move(arr2, arrr);
        move_piece_simpler(arr2, arrr, "player1", spec);

        int sc; 
        if (depth == 2) sc = one_max(arr2, minscore);
        if (depth > 2) sc = multi_max(arr2, minscore, depth-1);

        if (sc == 1) continue;
        minscore = sc;
        if (minscore < currentMaxscore) return 1;
    }

    if (v.size() != 0) return minscore;
    else {
        if (!is_it_tie(arr, "player1")) return 1300;
        else {
            if (currentMaxscore > 0) return 1;
            return 0;
        }
    }
}

int computer_move(int arr[8][8], bool &specialMove)
{
    // search depth of DEPTH
    int DEPTH = 3;
    int arr2[8][8];
    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) arr2[i][j] = arr[i][j];
    vector<int> v, w;
    allmove(arr2, "player2", v);

    int maxscore = -99999999;
    for (int i: v) {
        for (int k = 0; k < 8; k++) for (int j = 0; j < 8; j++) arr2[k][j] = arr[k][j];
        int arrr[2][2] = {(i/1000)%10, (i/100)%10, (i/10)%10, i%10};
        bool spec = check_special_move(arr2, arrr);
        move_piece_simpler(arr2, arrr, "player2", spec);

        int sc = multi_min(arr2, maxscore, DEPTH-1);
        if (sc == 1) continue;
        if (sc != maxscore) {
            maxscore = sc;
            w.clear();
        }
        w.push_back(i);
    }

    int SZ = w.size();
    std::srand((unsigned) time(0));
    int result = (rand() % SZ);
    int move = w[result];

    for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) arr2[i][j] = arr[i][j];
    int arrr[2][2] = {(move/1000)%10, (move/100)%10, (move/10)%10, move%10};
    bool spec = false;
    move_is_valid(arr2, arrr, "player2", spec);
    specialMove = spec;
    return move;
}