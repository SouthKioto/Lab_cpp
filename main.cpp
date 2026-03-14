#include <iostream>
#include <vector>
#include <string>

using namespace std;

void wyswietlSkladniki(const vector<string>& skladniki) {
  for (string skladnik : skladniki) {
    cout << skladnik << endl; 
  }
}
 
void KGK(const vector<string>& skladniki, int k)
{
    int n = skladniki.size();
    vector<int> c(k);
 
    for(int i = 0; i < k; i++){
        c[i] = i;
    }
 
    while(true)
    {
        cout << "Numery: ";
        for(int i = 0; i < k; i++){
            cout << c[i] + 1 << " ";
        }
 
        cout << " | Skladniki: ";
 
        for(int i = 0; i < k; i++){
            cout << skladniki[c[i]] << " ";
        }
 
        cout << endl;
 
        int i = k - 1;
        while(i >= 0 && c[i] == n - k + i){
            i--;
        }
 
        if(i < 0){
            break;
        }
 
        c[i]++;
 
        for(int j = i + 1; j < k; j++){
            c[j] = c[j - 1] + 1;
        }
    }
}
 
int main()
{
    vector<string> skladniki = {
        "Ser", "Szynka", "Papryka", "Pieczarki", "Kukurydza"
    };
 
    int wybor;

    cout<<"|Pizzeria „Mamma Mia”|"<<endl;
    cout<<endl;
    cout<<"[1] Wyświetl dostępne składniki"<<endl;
    cout<<"[2] Generuj kombinacje składników — algorytm klasyczny"<<endl;
    cout<<"[3] Generuj kombinacje składników — algorytm Semby"<<endl;
    cout<<"[4] Porównaj kolejność generacji obu algorytmów"<<endl;
    cout<<"[5] Trójkąt Pascala"<<endl;
    cout<<"[0] Wyjście"<<endl;

    cout<<"Wybierz opcję: ";
    cin >> wybor;
 

    while(true)
    {
        cout<<"|Pizzeria „Mamma Mia”|"<<endl;
        cout<<endl;
        cout<<"[1] Wyświetl dostępne składniki"<<endl;
        cout<<"[2] Generuj kombinacje składników — algorytm klasyczny"<<endl;
        cout<<"[3] Generuj kombinacje składników — algorytm Semby"<<endl;
        cout<<"[4] Porównaj kolejność generacji obu algorytmów"<<endl;
        cout<<"[5] Trójkąt Pascala"<<endl;
        cout<<"[0] Wyjście"<<endl;

        cout<<"Wybierz opcję: ";
        cin>>wybor;

        if(wybor == 0)
        {
            cout<<"Koniec programu."<<endl;
            break;
        }
        if(wybor < 0 || wybor > 5)
        {
            cout<<"Błąd w wyborze z menu."<<endl;
        }
        else
        {
          switch (wybor) {
            case 1:
              wyswietlSkladniki(skladniki);
              break;
            case 2:
              int ilosc;
              cout << "Podaj ilosc skladnikow: ";
              cin >> ilosc; 
              KGK(skladniki, ilosc);
            case 3:
              break;

            default:
              break;
          }
        }
        cout<<endl;
    }
    return 0; 
}  
