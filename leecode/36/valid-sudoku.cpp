class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<int>> row(9, vector<int>(9, 0));
        vector<vector<int>> col(9, vector<int>(9, 0));
        vector<vector<vector<int>>> unit(9, vector<vector<int>>(9, vector<int>(9, 0)));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char c = board[i][j];
                if (c != '.') {
                    int num = c - '0' - 1;
                    row[i][num]++;
                    col[j][num]++;
                    unit[i / 3][j / 3][num]++;
                    if (row[i][num] > 1 || col[j][num] > 1 || unit[i / 3][j / 3][num] > 1) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};