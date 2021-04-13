/*
 *
 *
 * Don't try to read this code. Just compile and run it.
 *
 *
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CodeSplitter {
private:
    int maxDigitCount;
    vector<string> lines;
public:
    CodeSplitter(vector<string> code);
    int getLineCount();
    string getCodeblock(int start, int end);
    string getCodeblock(int start, int end, int pointerLine);
};

CodeSplitter::CodeSplitter(vector<string> code) {
    lines = code;
    int maxLine = code.size();
    maxDigitCount = 0;
    while (maxLine > 0) {
        maxDigitCount += 1;
        maxLine /= 10;
    }
}

int CodeSplitter::getLineCount() {
    return lines.size();
}

string CodeSplitter::getCodeblock(int start, int end, int pointerLine) {
    string ret = "";
    for (int i = start; i <= end; i++) {
        if (0 <= i && i < lines.size()) {
            int j = i + 1;
            int indentSize = maxDigitCount;
            while (j > 0) {
                indentSize -= 1;
                j /= 10;
            }
            for (int indent = 0; indent < indentSize; indent++) {
                ret += " ";
            }
            if (i == pointerLine) {
                ret += to_string(i + 1) + ":  > ";
            } else {
                ret += to_string(i + 1) + ":    ";
            }
            ret += lines[i];
        }
        ret += "\n";
    }
    return ret;
}

string CodeSplitter::getCodeblock(int start, int end) {
    return getCodeblock(start, end, start - 1);
}

class Demo {
private:
    vector<string> lines = vector<string>();
    bool wait();
    void printNewlines(int n);
public:
    void addLine(string line);
    void display();
};

void Demo::printNewlines(int n) {
    for (int i = 0; i < n; i++) {
        cout << '\n';
    }
}

bool Demo::wait() {
    cout << "\nPress enter to continue. Press any key to go back. ";
    bool moveForward = true;
    char c;
    do {
        c = cin.get();
        if (c != '\n') {
            moveForward = false;
        }
    } while (c != '\n');
    return moveForward;
}

void Demo::addLine(string line) {
    lines.push_back(line);
}

void Demo::display() {
    int currentLine = 0;
    if (!wait()) {
        return;
    };
    while (currentLine < lines.size()) {
        printNewlines(50);
        cout << lines[currentLine];
        if (wait()) {
            currentLine++;
        } else if (currentLine > 0) {
            currentLine--;
        } else {
            return;
        }
    }
}

string drawBoard(int b[][8]) {
    string ret = "\n\n";
    for (int r = 0; r < 8; r++) {
        ret += "   ";
        for (int c = 0; c < 8; c++) {
            ret += (b[r][c] == 1 ? " 1 ":" 0 ");
        }
        ret += '\n';
    }
    ret += '\n';
    return ret;
}

string drawBoard(int b[][8], int highlightRow, int highlightCol, int markedRow, int markedCol) {
    string ret = "\n   ";
    for (int i = 0; i < highlightCol; i++) {
        ret += "   ";
    }
    ret += " V\n";
    for (int r = 0; r < 8; r++) {
        ret += r == highlightRow ? " > " : "   ";
        for (int c = 0; c < 8; c++) {
            ret += (r == markedRow && c == markedCol ? " X " : (b[r][c] == 1 ? " 1 ":" 0 "));
        }
        ret += '\n';
    }
    ret += '\n';
    return ret;
}

bool passesRowTest(int b[][8], int r, int c) {
    for (int i = 0; i < c; i++) {
        if (b[r][i] == 1) {
            return false;
        }
    }
    return true;
}

bool passesUpDiagTest(int b[][8], int r, int c) {
    for (int i = 1; c - i >= 0 && r - i >= 0; i++) {
        if (b[r-i][c-i] == 1) {
            return false;
        }
    }
    return true;
}

bool passesDownDiagTest(int b[][8], int r, int c) {
    for (int i = 1; c - i >= 0 && r + i < 8; i++) {
        if (b[r+i][c-i] == 1) {
            return false;
        }
    }
    return true;
}

string drawBoard(int b[][8], int highlightRow, int highlightCol) {
    return drawBoard(b, highlightRow, highlightCol, -1, -1);
}

string getRowcheckMessage(string message, CodeSplitter code, int b[][8], int r, int c, int i, bool highlightGoto) {
    return "c: " + to_string(c) + "\nr: " + to_string(r) + "\ni: " + to_string(i)
        + "\n" + message
        + drawBoard(b, r, i, r, c) + (highlightGoto ? code.getCodeblock(12, 17, 15) : code.getCodeblock(12, 17));
}

string getNewrowMessage(string message, CodeSplitter code, int b[][8], int r, int c, int i, bool highlightNr) {
    return "c: " + to_string(c) + "\nr: " + to_string(r)
        + "\n" + message
        + drawBoard(b, r, c, r, c) + (highlightNr ? code.getCodeblock(7, 10, 7) : code.getCodeblock(7, 10));
}

string getNrBacktrackMessage(string message, CodeSplitter code, int b[][8], int r, int c, int i) {
    return "c: " + to_string(c) + "\nr: " + to_string(r)
        + "\n" + message
        + drawBoard(b, r, c, r, c) + code.getCodeblock(7, 10, 9);
}

string getUpDiagonalMessage(string message, CodeSplitter code, int b[][8], int r, int c, int i, bool highlightGoto) {
    return "c: " + to_string(c) + "\nr: " + to_string(r) + "\ni: " + to_string(i)
        + "\nc - i = " + to_string(c) + " - " + to_string(i) + " = " + to_string(c-i) +"\nr - i = " + to_string(r) + " - " + to_string(i) + " = " + to_string(r-i)
        + "\n" + message
        + drawBoard(b, r - i, c - i, r, c) + (highlightGoto ? code.getCodeblock(19, 24, 22) : code.getCodeblock(19, 24));
}

string getDownDiagonalMessage(string message, CodeSplitter code, int b[][8], int r, int c, int i, bool highlightGoto) {
    return "c: " + to_string(c) + "\nr: " + to_string(r) + "\ni: " + to_string(i)
        + "\nc - i = " + to_string(c) + " - " + to_string(i) + " = " + to_string(c-i) +"\nr + i = " + to_string(r) + " + " + to_string(i) + " = " + to_string(r+i)
        + "\n" + message
        + drawBoard(b, r + i, c - i, r, c) + (highlightGoto ? code.getCodeblock(26, 31, 29) : code.getCodeblock(26, 31));
}

string getNewcolMessage(string message, CodeSplitter code, int b[][8], int r, int c, int i, bool highlightEndbrace) {
    return "c: " + to_string(c) + "\nr: " + to_string(r)
        + "\n" + message
        + drawBoard(b, r, c, r, c) + (highlightEndbrace ? code.getCodeblock(2, 10, 10) : code.getCodeblock(2, 10, 10));
}

string getBacktrackMessage(string message, CodeSplitter code, int b[][8], int r, int c, int i, int h) {
    return "c: " + to_string(c) + "\nr: " + to_string(r)
        + "\n" + message
        + drawBoard(b, r, c) + code.getCodeblock(36, 45, 36 + h);
}

int main() {
    Demo demo;

    CodeSplitter eightQueens = CodeSplitter(vector<string>({
        "int b[8][8] = {0}, r, c = 0, solutionNumber = 1;",
        "b[0][0] = 1;",
        "nc: c++;",
        "if (c == 8) {",
        "    goto print;",
        "}",
        "r = -1;",
        "nr: r++;",
        "if (r == 8) {",
        "    goto backtrack;",
        "}",
        "",
        "// Row test",
        "for (int i = 0; i < c; i++) {",
        "    if (b[r][i] == 1) {",
        "        goto nr;",
        "    }",
        "}",
        "",
        "// Up diagonal test",
        "for (int i = 0; 0 <= c - i && 0 <= r - i; i++) {",
        "    if (b[r - i][c - i] == 1) {",
        "        goto nr;",
        "    }",
        "}",
        "",
        "// Down diagonal test",
        "for (int i = 0; 0 <= c - i && r + i < 8; i++) {",
        "    if (b[r + i][c - i] == 1) {",
        "        goto nr;",
        "    }",
        "}",
        "",
        "b[r][c] = 1;",
        "goto nc;",
        "",
        "backtrack: c--;",
        "if (c == -1) {",
        "    return 0;",
        "}",
        "r = 0;",
        "while (b[r][c] != 1) {",
        "    r++;",
        "}",
        "b[r][c] = 0;",
        "goto nr;",
        "",
        "print:",
        "cout << \"Solution \" << solutionNumber << \":\\n\";",
        "solutionNumber++;",
        "for (int i = 0; i < 8; i++) {",
        "    for (int j = 0; j < 8; j++) {",
        "        cout << b[i][j] << ' ';",
        "    }",
        "    cout << endl;",
        "}",
        "",
        "goto backtrack;"
    }));

    demo.addLine("Full code:\n" + eightQueens.getCodeblock(0, eightQueens.getLineCount() - 1));

    int b[8][8] = {0}, r = 0, c = 0, solution = 1;
    b[0][0] = 1;

    demo.addLine("Line 1 initializes variables and line 2 puts a queen in column 0 row 0 (the top left corner)."
        + drawBoard(b) + eightQueens.getCodeblock(0, 1));

    c = 1;
    demo.addLine("c: " + to_string(c) + "\nr: " + to_string(r)
        + "\nNext, the program moves to column 1 and row 0 to try to place a queen.\nThe reason that the program starts at column 1 is that there was already a queen placed at column 0."
        + drawBoard(b, r, c, r, c) + eightQueens.getCodeblock(2, 7));

    int i = 0;
    demo.addLine(getRowcheckMessage(
        "The first test that the program performs to see if a queen can be placed is the row test.",
        eightQueens, b, r, c, i, false));

    demo.addLine(getRowcheckMessage(
        "Each column in the row is checked to see if it already contains a queen.\nIn this case, column 0 in the row contains a queen, so the program goes to check the next row by going to the next row with `goto nr;`.",
        eightQueens, b, r, c, i, true));

    r = 1;
    demo.addLine(getNewrowMessage(
        "The program now moves on to trying to place a queen in column 1 and row 1.",
        eightQueens, b, r, c, i, true));

    demo.addLine(getRowcheckMessage(
        "Once again, the program will do the row test to see if a queen can be placed.",
        eightQueens, b, r, c, i, false));

    demo.addLine(getRowcheckMessage(
        "This time, the check passes (no queens are found), so the program does not go to nr.",
        eightQueens, b, r, c, i, false));

    i = 1;
    demo.addLine(getUpDiagonalMessage(
        "Now, the program will perform the up diagonal test.",
        eightQueens, b, r, c, i, false));

    demo.addLine(getUpDiagonalMessage(
        "Because there is a queen in row 0 and column 0, the up diagonal test fails, and the program goes to the next row.",
        eightQueens, b, r, c, i, true));

    r = 2;
    demo.addLine(getNewrowMessage(
        "The program will now try to put a queen in column 1 row 2.",
        eightQueens, b, r, c, i, true));

    i = 0;
    demo.addLine(getRowcheckMessage(
        "This queen passes the row test...",
        eightQueens, b, r, c, i, false));

    i = 1;
    demo.addLine(getUpDiagonalMessage(
        "...the up diagonal test...",
        eightQueens, b, r, c, i, false));

    i = 1;
    demo.addLine(getDownDiagonalMessage(
        "...and the down diagonal test...",
        eightQueens, b, r, c, i, false));

    b[r][c] = 1;
    demo.addLine("c: " + to_string(c) + "\nr: " + to_string(r)
        + "\n...meaning that the program will successfully put a queen at column 1 row 2."
        + drawBoard(b, r, c) + eightQueens.getCodeblock(12, 34, 33));

    demo.addLine("c: " + to_string(c) + "\nr: " + to_string(r)
        + "\nNow, with a queen placed in this column, the program moves on to the next column with `goto nc;`"
        + drawBoard(b, r, c) + eightQueens.getCodeblock(33, 34, 34));

    c++;
    r = 0;
    demo.addLine(getNewcolMessage(
        "After going to nc, the program will move to row 0 in the next column.\nOnce again, the program will try to place a queen in each row until it succeeds.",
        eightQueens, b, r, c, i, true));

    i = 0;
    demo.addLine(getRowcheckMessage(
        "Column 2 row 0 fails the row check...",
        eightQueens, b, r, c, i, true));

    r = 1;
    i = 1;
    demo.addLine(getDownDiagonalMessage(
        "...column 2 row 1 fails the down diagonal check...",
        eightQueens, b, r, c, i, true));

    r = 2;
    for (i = 0; i <= 1; i++) {
        demo.addLine(getRowcheckMessage(
            "...column 2 row 2 fails the row check...",
            eightQueens, b, r, c, i, i==1));
    }

    r = 3;
    i = 1;
    demo.addLine(getUpDiagonalMessage(
        "...column 2 row 3 fails the up diagonal check...",
        eightQueens, b, r, c, i, true));

    r = 4;
    b[r][c] = 1;
    demo.addLine("c: " + to_string(c) + "\nr: " + to_string(r)
        + "\n...and column 2 row 4 passes all checks, meaning we place a queen there."
        + drawBoard(b, r, c) + eightQueens.getCodeblock(12, 34, 33));

    demo.addLine("c: " + to_string(c) + "\nr: " + to_string(r)
        + "\nOnce again, the program moves on to the next column with `goto nc;`"
        + drawBoard(b, r, c) + eightQueens.getCodeblock(33, 34, 34));

    c++;
    r = 0;
    demo.addLine(getNewcolMessage(
        "Now, the program will attempt to place a queen in column 3.",
        eightQueens, b, r, c, i, true));

    i = 0;
    demo.addLine(getRowcheckMessage(
        "...column 3 row 0 fails the row check...",
        eightQueens, b, r, c, i, true));

    r = 1;
    b[r][c] = 1;
    demo.addLine("c: " + to_string(c) + "\nr: " + to_string(r)
        + "\n...and column 3 row 1 passes all checks.\nOnce again the program will move on to the next column to place another queen."
        + drawBoard(b, r, c) + eightQueens.getCodeblock(33, 34, 34));

    c++;
    r = 3;
    b[r][c] = 1;
    demo.addLine("c: " + to_string(c) + "\nr: " + to_string(r)
        + "\nIn column 4, the first row to pass all checks is row 3."
        + drawBoard(b, r, c) + eightQueens.getCodeblock(33, 34, 34));

    c++;
    r = 0;
    demo.addLine(getNewcolMessage(
        "In column 5, however, there are no valid places to put a queen.",
        eightQueens, b, r, c, i, false));

    i = 0;
    for (r = 0; r <= 4; r++) {
        for (i = 0; b[r][i] == 0; i++) {
            demo.addLine(getRowcheckMessage(
                (r == 0 ? "Column 5 row " : "...column 5 row ") + to_string(r) + " fails the row check...",
                eightQueens, b, r, c, i, false));
        }
        demo.addLine(getRowcheckMessage(
            (r == 0 ? "Column 5 row " : "...column 5 row ") + to_string(r) + " fails the row check...",
            eightQueens, b, r, c, i, true));
    }
    for (r = 5; r < 8; r++) {
        for (i = 1; b[r-i][c-i] == 0; i++) {
            demo.addLine(getUpDiagonalMessage(
                (r == 7 ? "...and column 5 row " : "...column 5 row ") + to_string(r) + " fails the up diagonal check...",
                eightQueens, b, r, c, i, false));
        }
        demo.addLine(getUpDiagonalMessage(
            (r == 7 ? "...and column 5 row " : "...column 5 row ") + to_string(r) + " fails the up diagonal check...",
            eightQueens, b, r, c, i, true));
    }

    r = 8;
    demo.addLine(getNewrowMessage(
        "So, when going to check a new row, `r` will now be 8, which is off the board.",
        eightQueens, b, r, c, i, true));

    demo.addLine(getNrBacktrackMessage(
        "To deal with this, the program will backtrack.",
        eightQueens, b, r, c, i));

    c--;
    demo.addLine(getBacktrackMessage(
        "The first thing that the backtracking code does is move back to the previous column.",
        eightQueens, b, r, c, i, 0));

    r = 0;
    demo.addLine(getBacktrackMessage(
        "Next, it sets the current row back to 0.",
        eightQueens, b, r, c, i, 4));

    for (r = 0; b[r][c] == 0; r++) {
        demo.addLine(getBacktrackMessage(
            "Then, the backtracking code goes through every row in the column until it finds where the queen is.",
            eightQueens, b, r, c, i, 5));
    }
    demo.addLine(getBacktrackMessage(
        "Then, the backtracking code goes through every row in the column until it finds where the queen is.",
        eightQueens, b, r, c, i, 7));

    b[r][c] = 0;
    demo.addLine(getBacktrackMessage(
        "Once it does, it removes the queen there.",
        eightQueens, b, r, c, i, 8));

    demo.addLine(getBacktrackMessage(
        "Then, it goes to the next row in the same column to try to replace the queen further down.",
        eightQueens, b, r, c, i, 9));

    r++;
    demo.addLine(getNewrowMessage(
        "Now, the program is going to try to find a new position for the queen in column 4, starting from row 4.\nThis is one row after row 3, which is the row where the queen had just been.",
        eightQueens, b, r, c, i, true));

    for (i = 0; b[r][i] == 0; i++) {
        demo.addLine(getRowcheckMessage(
            "Column 4 row 4 fails the row check...",
            eightQueens, b, r, c, i, false));
    }
    demo.addLine(getRowcheckMessage(
            "Column 4 row 4 fails the row check...",
            eightQueens, b, r, c, i, true));

    for (r = 5; r <= 6; r++) {
        for (i = 1; b[r - i][c - i] == 0; i++) {
            demo.addLine(getUpDiagonalMessage(
                "...column 4 row " + to_string(r) + " fails the up diagonal check...",
                eightQueens, b, r, c, i, false));
        }
        demo.addLine(getUpDiagonalMessage(
            "...column 4 row " + to_string(r) + " fails the up diagonal check...",
            eightQueens, b, r, c, i, true));
    }

    r = 7; // redundant. whatever.
    b[r][c] = 1;
    demo.addLine("c: " + to_string(c) + "\nr: " + to_string(r)
        + "\n...and column 4 row 7 passes all checks."
        + drawBoard(b, r, c) + eightQueens.getCodeblock(33, 34, 33));

    demo.addLine("c: " + to_string(c) + "\nr: " + to_string(r)
        + "\nNow that the queen in column 4 has been moved from row 3 to row 7, the program will try to place a queen in column 5 again."
        + drawBoard(b, r, c) + eightQueens.getCodeblock(33, 34, 34));

    c++;
    for (r = 0; r < 8; r++) {
        if (passesRowTest(b, r, c)) {
            for (i = 1; b[r - i][c - i] == 0; i++) {
                demo.addLine(getUpDiagonalMessage(
                    "...column 4 row " + to_string(r) + " fails the up diagonal check...",
                    eightQueens, b, r, c, i, false));
            }
            demo.addLine(getUpDiagonalMessage(
                "...column 4 row " + to_string(r) + " fails the up diagonal check...",
                eightQueens, b, r, c, i, true));
        } else {
            for (i = 0; b[r][i] == 0; i++) {
                    demo.addLine(getRowcheckMessage(
                        (r == 0 ? "Column 5 row " : "...column 5 row ") + to_string(r) + " fails the row check...",
                        eightQueens, b, r, c, i, false));
                }
                demo.addLine(getRowcheckMessage(
                        (r == 0 ? "Column 5 row " : (r == 7 ? "...and column 5 row " : "...column 5 row ")) + to_string(r) + " fails the row check...",
                        eightQueens, b, r, c, i, true));
        }
    }

    demo.addLine(getNrBacktrackMessage(
        "So, the program still can not put a queen in column 5 and must backtrack to column 4 again.",
        eightQueens, b, r, c, i));

    c--;
    r = 0;
    for (r = 0; b[r][c] == 0; r++) {
        demo.addLine(getBacktrackMessage(
            "The program finds the queen in column 4 again...",
            eightQueens, b, r, c, i, 5));
    }
    demo.addLine(getBacktrackMessage(
        "The program finds the queen in column 4 again...",
        eightQueens, b, r, c, i, 7));

    b[r][c] = 0;
    demo.addLine(getBacktrackMessage(
        "...removes it...",
        eightQueens, b, r, c, i, 8));

    demo.addLine(getBacktrackMessage(
        "...and goes to the next row to try to replace the queen in column 4 again.",
        eightQueens, b, r, c, i, 9));

    r = 8;
    demo.addLine(getNrBacktrackMessage(
        "Because the queen in column 4 was in row 7 however, the program has nowhere to put a queen in column 4 now, and must backtrack further to column 3.",
        eightQueens, b, r, c, i));

    c--;
    r = 0;
    for (r = 0; b[r][c] == 0; r++) {
        demo.addLine(getBacktrackMessage(
            "So, the program finds the queen in column 3...",
            eightQueens, b, r, c, i, 5));
    }
    demo.addLine(getBacktrackMessage(
        "So, the program finds the queen in column 3...",
        eightQueens, b, r, c, i, 7));

    b[r][c] = 0;
    demo.addLine(getBacktrackMessage(
        "...removes it...",
        eightQueens, b, r, c, i, 8));

    demo.addLine(getBacktrackMessage(
        "...and goes to the next row to try to replace the queen in column 3 again.",
        eightQueens, b, r, c, i, 9));

    r++;
    vector<string> firstSolutionLines = vector<string>();

    while (c < 8) {
        bool placedQueen = false;
        for (; r < 8; r++) {
            if (passesRowTest(b, r, c) && passesUpDiagTest(b, r, c) && passesDownDiagTest(b, r, c)) {
                b[r][c] = 1;
                placedQueen = true;
                break;
            }
        }
        if (!placedQueen) {
            c--;
            for (r = 0; b[r][c] == 0; r++);
            b[r][c] = 0;
            firstSolutionLines.push_back(getNrBacktrackMessage(
                "Backtracked to column " + to_string(c) + ".",
                eightQueens, b, r, c, i));
            r++;
        } else {
            firstSolutionLines.push_back("c: " + to_string(c) + "\nr: " + to_string(r)
                + "\nPut a queen at column " + to_string(c) + " row " + to_string(r) + "."
                + drawBoard(b, r, c) + eightQueens.getCodeblock(33, 34, 33) + "\n\n");
            c++;
            r = 0;
        }
    }
    for (int i = 0; i < firstSolutionLines.size(); i++) {
        demo.addLine("The program continues adding queens and backtracking as necessary until it finds the first solution.\n(Step "
            + to_string(i + 1) + "/" + to_string(firstSolutionLines.size()) + ")\n" + firstSolutionLines[i]);
    }

    demo.addLine("c: " + to_string(c) + "\nr: " + to_string(r)
        + "\nOnce the first solution has been found, the program will try to go to the next column, but the the next column 8 will be off the board.\nSo, the program will go to print instead."
        + drawBoard(b, r, c) + eightQueens.getCodeblock(2, 5, 4));

    demo.addLine("c: " + to_string(c) + "\nr: " + to_string(r)
        + "\nThe print code uses a nested loop to print every cell on the board, as well as which solution this is (solution 1, 2, .. 92)."
        + drawBoard(b) + eightQueens.getCodeblock(47, 55));

    demo.addLine("c: " + to_string(c) + "\nr: " + to_string(r)
        + "\nOnce the solution has been printed, the program will backtrack to column 7 and try to move the queen there, backtracking as much as necessary.\nThis will cause the program to re-enter the 'main code', and continue placing moving queens until all 8 columns contain queens again."
        + drawBoard(b) + eightQueens.getCodeblock(47, 57, 57));

    vector<string> secondSolutionLines = vector<string>();
    c = 7;
    r = 3;
    b[r][c] = 0;
    secondSolutionLines.push_back(getNrBacktrackMessage(
                "Backtracked to column " + to_string(c) + ".",
                eightQueens, b, r, c, i));
    r++;
    while (c < 8) {
        bool placedQueen = false;
        for (; r < 8; r++) {
            if (passesRowTest(b, r, c) && passesUpDiagTest(b, r, c) && passesDownDiagTest(b, r, c)) {
                b[r][c] = 1;
                placedQueen = true;
                break;
            }
        }
        if (!placedQueen) {
            c--;
            for (r = 0; b[r][c] == 0; r++);
            b[r][c] = 0;
            secondSolutionLines.push_back(getNrBacktrackMessage(
                "Backtracked to column " + to_string(c) + ".",
                eightQueens, b, r, c, i));
            r++;
        } else {
            secondSolutionLines.push_back("c: " + to_string(c) + "\nr: " + to_string(r)
                + "\nPut a queen at column " + to_string(c) + " row " + to_string(r) + "."
                + drawBoard(b, r, c) + eightQueens.getCodeblock(33, 34, 33) + "\n\n");
            c++;
            r = 0;
        }
    }
    for (int i = 0; i < secondSolutionLines.size(); i++) {
        demo.addLine("The program now continues backtracking and adding queens until it finds the second solution.\n(Step "
            + to_string(i + 1) + "/" + to_string(secondSolutionLines.size()) + ")\n" + secondSolutionLines[i]);
    }

    for (c = 7; c >= 0; c--) {
        for (r = 0; r < 8; r++) {
            b[r][c] = 0;
        }
    }
    demo.addLine(getBacktrackMessage(
        "The program will end sometime after finding the 92nd solution when it tries to place a 93rd queen and ends up backtracking off the board trying to do so.\nOnce that happens, we know that there are no solutions left.",
        eightQueens, b, r, c, i, 2));

    demo.addLine("it's over hope that helped bye\n");

    for (i = 15; i >= 1; i--) {
        demo.addLine("quitting in " + to_string(i) + (i != 1 ? " lines\n" : " line\n"));
    }

    demo.display();

    return 0;
}