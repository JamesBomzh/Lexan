/*������ �������� ������� ����� �� 50(L)*/

/*�����:
��� ��������� ��������� ����������� ������������ ������ � ������� ������. ������ ������� �������������� � �����.
���������� ����������� ���� �� ����.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;
enum States { START, I, V, X, L, ERROR, FINISH, STOP, BLANK }; //������ ���������

void addEdge(vector<int>[], int, int);

int main()
{
    setlocale(LC_ALL, "Russian");
    set<pair<int, int>> setPair; //������� ��������
    ifstream f("file.txt");
    if (!f.is_open()) { cout << "���� �� ������!" << endl; return 1; }
    string s;
    while (!f.eof()) {
        getline(f, s);
        States st = START;
        int currI = 0;
        int currX = 0;
        int i = s.length() - 1;
        while (st != STOP)
        {
            switch (st)
            {
            case START: {
                if (s.length() == 0) { st = BLANK;  setPair.insert({ START, BLANK }); }
                else 
                    if (s[i] == 'I') {
                        st = I; setPair.insert({ START, I }); i--; currI++; // ��������� ����� - I
                    }
                    else if (s[i] == 'L') { 
                        st = L; setPair.insert({ START, L }); i--; // ��������� ����� - L
                    }
                    else if (s[i] == 'X') {
                        st = X; setPair.insert({ START, X }); i--; currX++; // ��������� ����� - X
                    }
                    else if (s[i] == 'V') {
                        st = V; setPair.insert({ START, V }); i--; // ��������� ����� - V
                    }
                    else {
                    st = ERROR; setPair.insert({ START, ERROR }); // ���� ������ ������ � ����� - ������
                }
                break;
            }
            case I:
            {

                if (i == -1) {
                    st = FINISH; setPair.insert({ I, FINISH }); // ������� ����� �� ����� ������ - �����.
                }
                else
                    if (s[i] != 'X' && s[i] != 'V' && s[i] != 'L' && s[i] != 'I') { 
                        st = ERROR; setPair.insert({ I, ERROR }); // �������� �� ������ �������
                    }
                    else if (s.length() - i >= 2 && s[i] == 'I' && (s[i + 2] == 'V' || s[i + 2] == 'X')) { st = ERROR; setPair.insert({ I, ERROR }); }
                // �������� �� ��, ����� ����� V � X ���� �� ����� ����� I
                    else if (s[i] == 'V') { st = V; setPair.insert({ I, V }); i--; } // ���������� ����� - V
                    else if (s[i] == 'X') { st = X; setPair.insert({ I, X }); i--; } // ���������� ����� - X
                    else if (s[i] == 'L') { st = L; setPair.insert({ I, L }); i--; } // ���������� ����� - L
                    else if (s[i] == 'I' && currI > 2) { st = ERROR; setPair.insert({ I, ERROR }); } // �������� �� ������������� ���������� ����� ���� I ������
                    else if (s[i] == 'I') { i--; currI++; } // ���������� ����� - I
                    else { st = ERROR; setPair.insert({ I, ERROR }); } // ������ � ���� ������
                break;
            }
            case V:
            {
                if (i == -1) {
                    st = FINISH; setPair.insert({ V, FINISH }); // ������� ����� �� ����� ������ - �����.
                }
                else
                    if (s[i] != 'X' && s[i] != 'L' && s[i] != 'I') {
                        st = ERROR; setPair.insert({ I, ERROR }); // �������� �� ������ �������
                    }
                    else if (s[i] == 'I' && s[i + 2] == 'I') { st = ERROR; setPair.insert({ V, ERROR }); } // �������������� ������������ ���������� I ������������ �� � ����� V
                    else if (s[i] == 'I') { st = I; setPair.insert({ V, I }); i--; } // ���������� ����� - I
                    else if (s[i] == 'X') { st = X; setPair.insert({ V, X }); i--; } // ���������� ����� - X
                    else if (s[i] == 'L') { st = L; setPair.insert({ V, L }); i--; } // ���������� ����� - L
                    else { st = ERROR; setPair.insert({ X, ERROR }); } // ������ � ���� ������ (���� ��� V, ��� ��� ��� V �� ����� ���� ������)
                break;
            }
            case X:
            {
                if (i == -1) {
                    st = FINISH; setPair.insert({ X, FINISH }); // ������� ����� �� ����� ������ - �����.
                }
                else
                    if (s[i] != 'X' && s[i] != 'V' && s[i] != 'L' && s[i] != 'I') {
                        st = ERROR; setPair.insert({ I, ERROR });
                    }
                    else if (s[i] == 'X' && currX > 2) { st = ERROR; setPair.insert({ X, ERROR }); } // �������� �� ������������� ���������� ����� ���� X ������
                    else if (s[i] == 'X') { i--; currX++; } // ���������� ����� - X
                    else if (s[i] == 'I' && s[i + 2] == 'I') { st = ERROR; setPair.insert({ X, ERROR }); } // �������������� ������������ ���������� I ������������ �� � ����� X
                    else if (s[i] == 'I') { st = I; setPair.insert({ X, I }); i--; } // ���������� ����� - I
                    else if (s[i] == 'V') { st = V; setPair.insert({ X, V }); i--; } // ���������� ����� - V
                    else if (s[i] == 'L') { st = L; setPair.insert({ X, L }); i--; } // ���������� ����� - L
                    else { st = ERROR; setPair.insert({ X, ERROR }); } // ������ � ���� ������
                break;
            }
            case L:
            {
                if (i == -1) {
                    st = FINISH; setPair.insert({ L, FINISH }); // ������� ����� �� ����� ������ - �����.
                }
                else
                    if (i != -1 && i != 0) { st = ERROR; setPair.insert({ L, ERROR }); } //�������� �� ������������ ���������� L � �����
                    else if (i == 0 && s[i] == 'X') { st = FINISH; setPair.insert({ L, FINISH }); } // �������� �� ������������ ���������� X �� L               
                    else { st = ERROR; setPair.insert({ L, ERROR }); } // ������ � ���� ������
                break;
            }
            
            case ERROR: {
                cout << s << " - ����� ���������� ��������!" << "\n"; // ����� ��������� �� ������
                st = STOP; // ������� � ����
                setPair.insert({ ERROR, STOP });
                break;
            }
            case FINISH: {
                cout << s << " - ����� ���������� ������!" << "\n"; // ����� ��������� � ������������
                st = STOP; setPair.insert({ FINISH, STOP }); // ������� � ����
                break;
            }
            case BLANK: {
                cout << s << " - ������ ������!" << endl; // ����� ��������� � �������
                st = STOP;
                setPair.insert({ BLANK, STOP });// ������� � ����
                break;
            }
            }
        }
        vector<int> adj[9];
        for (auto x : setPair)
        {
            addEdge(adj, x.first, x.second);
        }
    }


    f.close();
    system("pause");
    return 0;
}

void addEdge(vector<int>adj[], int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}