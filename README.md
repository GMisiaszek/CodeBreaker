# CodeBreaker
Projekt studencki, narzędzie do łamania haseł w plikach oparte na przetwarzaniu rozproszonym.
# Tech
- [GTK+3](https://developer.gnome.org/gtk3/stable/)
- Pvm
- C++11
- make
- [vscode](https://code.visualstudio.com/)
- gcc
# Instrukcja uruchamiania
Aby uruchomić projekt należy mieć zainstalowaną virtualną maszynę pvm, pakiet pvm-dev oraz gtk+3-dev
```sh
- sudo apt install pvm
- sudo apt install pvm-dev
- sudo apt install libgtk-3-dev
```
Plik budujemy za pomocą polecania ```make all```, można też od razu uruchomić aplikację przy użyciu ```make run```,
wszystko powinno działać z obecnymi ustawieniami makefile, jednakże może być konieczna edycja ścieżek. 
Po zbudowaniu pliku main, należy go skopiować do katalogu ```$PVM_HOME```, następnie po uruchomieniu demona pvm włączyć aplikację poleceniem ``` pvm>spawn main ```. Po wydaniu polecenia halt aplikacja się zamknie. Uwaga: może zdarzyć się że użytkownik student nie ma uprawnień do uruchomienia pliku main, wówczas pvm zwróci błąd ```file not found```.
# VSCode
Do repozytorium jest dołączony katalog z ustawieniami vscode, ustawiania cpp są w pliku c_cpp_properties.json, żeby poprawnie działało podpowiadanie należy w tym pliku edytować tablicę includePath i dodać potrzebne ścieżki do plików .h
# Ogólne informacje o kodzie
Projekt jest podzielony na części - MainGui, PvmContainer, callbacks, mainapp.
- MainGui.cpp - są to klasy odpowiedzialne za Gui, oraz klasy odpowiedzialne za Api łączące gui z pvm, ponieważ GTK wykorzystuje machanizm callbacków podpiętych pod eventy poszczególnych komponentów konieczne jest przekazanie do callbacków struktury zawierającej referencje zarówno do elementów gui jak i PvmContainera, struktura GuiPvm zawiera referencje do GuiApi oraz PvmApi które z kolei posiadają referencje do elementów Gui oraz (na razie jednej) klasy która odpowiada za wywoływanie metod Pvm.
- PvmContainer jest to kontener zawierający metody wykonujące różne operacje związane z Pvm i zwracające wyniki tych operacji
- callbacks - są to callbacki podpięte pod poszczególne eventy związane z Gui, metoda g_signal_connect przekazuje pointer typu void* do callbacku(posiada on alias gpointer) i w danych callbacku rzutujemy ten pointer na strukturę którą przekazujemy(czyly PvmGui) dzięki czemu możemy w danej funkcji korzystać z metod GuiApi oraz PvmApi.
- mainapp - to metoda main, funkcje inicjalizujące GTK oraz tutaj tworzone są obiekty do których referencje są potem przekazywane dalej. 
