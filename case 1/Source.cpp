#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<ctype.h>
#include<string>

using namespace std;
const int lim = 100;

class Str
{
private:
    char* text;
    int len=0;
    string ap = "t";
public:
    Str() { text = nullptr; len = 0;  }
    Str(Str&& a)noexcept
    {
        len = a.len;
        text = a.text;
        a.text = nullptr; a.len = 0;
        cout << "����������� ����������� �������." << endl;
    }

    Str(const Str& a)
    {
        len = a.len;
        text = new char[len];
        strcpy(text, a.text);
        cout << "����������� �����������"<<endl;
    }

    Str& operator=(Str&& a)noexcept
    { 
        if (this != &a)
        {
            delete [] text; 
            len = a.len;
            text = a.text; 
            a.text = nullptr; a.len = 0; 
            cout << "�������� ������������ �������."<<endl;
        }
       
        return *this;
    }
 
    Str& operator=(const Str &a)
    {
        if (this != &a)
        {   
        if (text)
        {
            delete[] text;
        } 
        len = a.len;
        text = new char[len];
        strcpy(text, a.text);
        cout << "�������� ������������" << endl;
        }
        return *this;
    }

    ~Str() { delete []text; cout << "text deleted" << endl; }

    Str(const char* a, int l) 
    {
            len = l+1;
            text = new char[len]; strcpy(text, a);
            cout << "����������� �������������" << endl;
    }

    Str(string& a)
    {
        len = strlen(a.c_str());
        text = new char[len]; strcpy(text, a.c_str());
        cout << "����������� ������������� � ���������� string" << endl;
    }

   void getd()
    {
       cout << text << endl;
    }

   operator string()
    {
        string s = this->text; 
        cout << "��������������� � ������" << endl;
        return s;
       
    }


    Str& operator+=(const Str& a)
    {
        int m = len + a.len;
        char* temp = new char[m];
        if (text)
        {
            strcpy(temp, text);
        }
        strcat(temp, a.text);
        delete []text;
        text = temp;
        cout << "+=" << endl;
        return *this;
    }

    const char getreg() //���� ������ ������ ������� ����� �������� ��������, �� ���������� �� ������� ������� ��������
    {
        if (*text > 'A' && *text < 'Z')
        {
            const char s = *text; ///////
            const char s1=tolower(s); 
            return s1;
        }
        else return *text; 
    }

    friend Str operator+(Str& , Str& );

};//end of class

   Str operator+(Str& a, Str& b)//������� �������� ��������
   {
       cout << "������� �������� +" << endl;
    return Str(a += b);
   }

void sort(Str** st, int n) // ��������� ������ ���������� �� Str � ��������� ��������� �� ����������� ����� (�������� �������)
{
    Str* temp=new Str;
    for (int n1 = 1; n1 < n-1; n1++)
    {
        int ind = n1;
        temp = st[ind];

        while (ind-1 >= 0)
        {
            const char a1 = st[ind]->getreg();
            const char a2 = st[ind-1]->getreg();
                                                                                            
            if (strcmp(&a1 , &a2)>0)
            {
                st[ind] = st[ind - 1];
                st[ind - 1] = temp;
            }
            ind--;
            
        }
    }
    delete temp;
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    int i = 0;
    Str** arr;
    arr = new Str*[argc-1];
    int leng;

    for (int r = 1; r < argc; r++)
    {   
       leng = strlen(argv[r])+1;
       arr[r-1] = new Str(argv[r], leng);
    }
    
    for (int x = 0; x < argc-1; x++) 
    { arr[x]->getd(); }
 
    sort(arr, argc);
  
    for (int u = 0; u < argc-1; u++) 
    { arr[u]->getd(); }

    Str a(*arr[1]);//������������ �����������
    a = (*arr[1]);//�������� ������������
    Str b;
    b += a;//�������� +=
    Str c;
    c= a + b;//������� �������� +
    Str d(move(b));
    string e = "opanki";
    d += e;//������������� � ���������� ������ ����� 2 �����
    string f;
    f = a;

    delete[] arr;
    return 0;
}