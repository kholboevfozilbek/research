

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    fstream in("utility.txt", ios::in);
    fstream out("tayyori.txt", ios::out);

    int size, time;
    while(!in.eof())
    {
        in >> size >> time;
        out << time << endl;
    }

    in.close();
    out.close();
    return 0;
}