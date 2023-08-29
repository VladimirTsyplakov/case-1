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
public:
    Str() { text = nullptr; len = 0;  }
    Str(Str&& a)noexcept
    {
        len = a.len;
        text = a.text;
        a.text = nullptr; a.len = 0;
        cout << "constructor copy+move" << endl;
    }

    Str(const Str& a)
    {
        len = a.len;
        text = new char[len];
        strcpy(text, a.text);
        cout << "constructor copy"<<endl;
    }

    Str& operator=(Str&& a)noexcept
    { 
        if (this != &a)
        {
            delete [] text; 
            len = a.len;
            text = a.text; 
            a.text = nullptr; a.len = 0; 
            cout << "operator move="<<endl;
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
        cout << "operator =" << endl;
        }
        return *this;
    }

    ~Str() { delete []text; cout << "text deleted" << endl; }

    Str(const char* a, int l) 
    {
            len = l+1;
            text = new char[len]; strcpy(text, a);
            cout << "constrictor initialise" << endl;
    }

    Str(string& a)
    {
        len = strlen(a.c_str());
        text = new char[len]; strcpy(text, a.c_str());
        cout << "constrictor initialise with string parameter" << endl;
    }

   void getd()
    {
       cout << text << endl;
    }

   operator string()
    {
        string s = this->text; 
        cout << "convert to string" << endl;
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
    const char getreg() //если первый символ массива буква верхнего регистра, то возвращает ее вариант нижнего регистра
    {
        if (*text > 'A' && *text < 'Z')
        {
            const char s = *text; ///////
            const char s1=tolower(s); 
            return s1;
        }
        else return *text; 
    }

    friend Str& operator+(Str& , Str& );

};//end of class

   Str& operator+(Str& a, Str& b)//внешний оператор сложения
   {
       cout << "outline operator +" << endl;
       a=a+b;
    return a;
   }
void sort(Str** st, int n) // принимает массив указателей на Str и сортирует указатели по содержимому строк (обратный порядок)
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

    Str a(*arr[1]);//конструктор копирования
    a = (*arr[1]);//оператор присваивания
    Str b;
    b += a;//оператор +=
    Str c;
    c= a + b;//внещний оператор +
    Str d(move(b));
    string e = "opanki";
    d += e;//инициализация с аргументом стринг через 2 этапа
    string f;
    f = a;
    for (int u = 0; u < argc-1; u++) 
    { delete arr[u]; }//new add
    delete[] arr;
    return 0;
}
